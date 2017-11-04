#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <linux/input-event-codes.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>

typedef struct keyStruct {
  int         keyCode;
  const char *keystr;
} keyStr;
XKeyEvent createKeyEvent(Display *display,
                         Window   win,
                         Window   winRoot,
                         Bool     press,
                         int      keycode,
                         int      modifiers);
int main(void) {
  // ubicacion del archivo de dispisitivo de teclado cambia dependiendo el
  // sistema
  // /dev/input/eventN es una interfaz a los drivers de sistema por el modulo evdev del kernel
  //devuelve los keycodes que interpreto el kernel de los scancodes leidos del driver
  const char *dev = "/dev/input/event0";

  // estructura definida en input.h guarda datos del evdev: una interfaz-handler
  // generica para manejar  todos los eventos
  struct input_event ev;
  ssize_t n;
  int     fd;

  // abre el  archivo de dispisitivo - device file
  fd = open(dev, O_RDONLY);

  if (fd == -1) {
    fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
    return EXIT_FAILURE;
  }
  //incializacion de  para creacion de evento falso
  //X Window System provee librerias para manipular keycodes dado que es una aplicacion en keycode mode
  //http://www.tldp.org/HOWTO/Keyboard-and-Console-HOWTO-2.html para mas informacion al respecto
  //Desafortunadamente, dado que X toma keycodes y los interpreta su tabla de mapeo
  //de teclas es diferente a la del resto del SO
  //Afortunadamente, la diferencia entre una y otra tabla es de 8 enteros es decir
  // en consola la tecla b = 48 y en xorg b = 56
  //esto nos permite usar las librerias de X para decodificar los keycodes del driver del teclado
  Display *display;
  Window   window;
  int s;
  XEvent event;
  /* open connection with the server */
  display = XOpenDisplay(NULL);
  if (display == NULL)
  {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }
  // Get the root window for the current display.
  Window winRoot = XDefaultRootWindow(display);

  // Find the window which has the current keyboard focus.
  Window winFocus;
  int    revert;
  XGetInputFocus(display, &winFocus, &revert);

  // lee del archivo indefinidamente
  long int ac      = 0L;
  long int caps    = 0L;
  long int numlock = 0L;

  while (1) {
    n = read(fd, &ev, sizeof ev);

    if (n == (ssize_t)-1) {
      if (errno == EINTR)
        // interrupcion del sistema signal(7) para mas info
        continue;  // vuelve a intentar abrirlo
      else break;  // termina ERROR
    } else
    if (n != sizeof ev) {
      errno = EIO;
      break; // termina ERROR
    }

    // **si se escribe al mismo tiempo en consola parece que se estan interpretando los keycodes,
    // pero solo es la consola reconociendo los caracters e imprimiendolos XD

    // ev.type nos dice que tipo de evento que buscamos
    // EV_KEY = Used to describe state changes of keyboards, buttons, or other
    // key-like devices.
    // mas info sobre types
    // https://www.kernel.org/doc/html/v4.13/input/event-codes.html#input-event-codes
    // ev.value tiene 3 estados presionado =1 liberado = 0 repetido =2
    // TODO guardar en archivo
    // TODO*** volver proceso en daemon
    // TODO agregar ctrl+alt+shift  para terminar este proceso

    ////presionado
    if ((ev.type == EV_KEY) && (ev.value == 1)) {
      //ev.code nos devuelve los keycodes -> variable numericas que representan las teclas fisicas
      //estas constantes son las mismas en todas las arquitecturas y on independientes de hardware
      //mas info https://www.kernel.org/doc/html/v4.13/input/event-codes.html#input-event-codes
      switch (ev.code) {
      //la variable ac registra los modificadores--> teclas que cambian el output de otras teclas
      //mas informacion https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html#XKeyEvent
      case KEY_LEFTSHIFT:
        ac |= ShiftMask;
        break;

      case KEY_RIGHTSHIFT:
        ac |= ShiftMask;
        break;

      case KEY_RIGHTALT:
        ac |= Mod1Mask;
        break;

      case KEY_LEFTALT:
        ac |= Mod1Mask;
        break;

      case  KEY_LEFTCTRL:
        ac |= ControlMask;
        break;

      case KEY_RIGHTCTRL:
        ac |= ControlMask;
        break;

      case KEY_NUMLOCK:

        if (!numlock) numlock = Mod2Mask;
        else numlock = 0L;
        break;

      case KEY_CAPSLOCK:

        if (!caps) caps = LockMask;
        else caps = 0L;
        break;

      default:
        printf("CODE = %d \t EVENT = %d\n", ev.code, (int)ev.value);
        char   string[200];
        KeySym keysym;
        XKeyEvent keyEv = createKeyEvent(display, winFocus, winRoot, True, ev.code + 8, ac|caps|numlock);
        XLookupString(&keyEv, string, 200, &keysym, NULL);
        printf("Se  detecto Keypress con Keycode  = %i\n",      keyEv.keycode);
        printf("Se  detecto Keypress con estado  = %li\n",      keyEv.state); //
        if(string[0]>31)
          printf("Se  detecto Keypress con valor legible = %c\n", string[0]);
        else
          printf("Se  detecto Keypress con valor no legible\n");

        if (keyEv.keycode == 0x09) break;
      }
    }
    ////liberado
    if ((ev.type == EV_KEY) && (ev.value == 0)) {
      switch (ev.code) {
        case KEY_LEFTSHIFT:
          ac -= ShiftMask;
          break;

        case KEY_RIGHTSHIFT:
          ac -= ShiftMask;
          break;

        case KEY_RIGHTALT:
          ac -= Mod1Mask;
          break;

        case KEY_LEFTALT:
          ac -= Mod1Mask;
          break;

        case  KEY_LEFTCTRL:
          ac -= ControlMask;
          break;

        case KEY_RIGHTCTRL:
          ac -= ControlMask;
          break;

        case KEY_NUMLOCK:
          break;

        case KEY_CAPSLOCK:
          break;
          
        default:
          printf("CODE = %d \t EVENT = %d\n", ev.code, (int)ev.value);
          char   string[200];
          KeySym keysym;
          XKeyEvent keyEv = createKeyEvent(display, winFocus, winRoot, False, ev.code + 8, ac|caps|numlock);
          XLookupString(&keyEv, string, 200, &keysym, NULL);

          printf("Se  detecto Keypress con Keycode  = %i\n",      keyEv.keycode);
          printf("Se  detecto Keypress con estado  = %li\n",      keyEv.state);
          if(string[0]>31)
            printf("Se  detecto Keypress con valor legible = %c\n", string[0]);
          else
            printf("Se  detecto Keypress con valor no legible\n");
          if (keyEv.keycode == 0x09) break;
      }
    }
  }
  fflush(stdout);
  fprintf(stderr, "%s.\n", strerror(errno));
  return EXIT_FAILURE;
}
// funcion obtenida de http://www.doctort.org/adam/nerd-notes/x11-fake-keypress-event.html
XKeyEvent createKeyEvent(Display *display, Window win, Window winRoot, Bool press, int keycode, int modifiers)
{
  //mas info de XKeyEvent struct
  //https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html#XKeyEvent

  XKeyEvent event;
  event.display     = display;
  event.window      = win;
  event.root        = winRoot;
  event.subwindow   = None;
  event.time        = CurrentTime;
  event.x           = 1;
  event.y           = 1;
  event.x_root      = 1;
  event.y_root      = 1;
  event.same_screen = True;
  event.keycode     =  keycode;
  event.state       = modifiers;

  if (press) event.type = KeyPress;
  else event.type = KeyRelease;

  return event;
}
