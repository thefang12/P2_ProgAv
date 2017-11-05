
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
  Display *display;
  Window window;
  int s;
  XEvent event;

  /* open connection with the server */
  display = XOpenDisplay(NULL);

  if (display == NULL) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  s = DefaultScreen(display);
  /* create window */
  window =
      XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 200, 200, 1,
                          BlackPixel(display, s), WhitePixel(display, s));
  if (XSelectInput(display, window, KeyPressMask | KeyReleaseMask) ==
      BadWindow) {
    perror("ventana invalida");
    exit(1);
  }
  XMapWindow(display, window);
  while (1) {
    XNextEvent(display, &event);
    char string[200];
    int len;
    KeySym keysym;
    XKeyEvent keyEv = event.xkey;
    len = XLookupString(&event.xkey, string, 200, &keysym, NULL);
    printf("Se  detecto Keypress con Keycode  = %i\n", keyEv.keycode);
    printf("Se  detecto Keypress con estado  = %li\n", keyEv.state);
    printf("Se  detecto Keypress con valor legible = %s\n", string);
    if (keyEv.keycode == 0x09)
      break;
  }
  XCloseDisplay(display);
  return EXIT_SUCCESS;
}
