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
 // tomado de #include <linux/input-event-codes.h> y convertido en una
 // estructura para convertir keycodes en strings legibles
const keyStr keys[] = {
{ KEY_RESERVED,         "RESERVED"                        },
{ KEY_ESC,              "ESC"                             },
{ KEY_1,                "1"                               },
{ KEY_2,                "2"                               },
{ KEY_3,                "3"                               },
{ KEY_4,                "4"                               },
{ KEY_5,                "5"                               },
{ KEY_6,                "6"                               },
{ KEY_7,                "7"                               },
{ KEY_8,                "8"                               },
{ KEY_9,                "9"                               },
{ KEY_0,                "0"                               },
{ KEY_MINUS,            "MINUS"                           },
{ KEY_EQUAL,            "EQUAL"                           },
{ KEY_BACKSPACE,        "BACKSPACE"                       },
{ KEY_TAB,              "TAB"                             },
{ KEY_Q,                "Q"                               },
{ KEY_W,                "W"                               },
{ KEY_E,                "E"                               },
{ KEY_R,                "R"                               },
{ KEY_T,                "T"                               },
{ KEY_Y,                "Y"                               },
{ KEY_U,                "U"                               },
{ KEY_I,                "I"                               },
{ KEY_O,                "O"                               },
{ KEY_P,                "P"                               },
{ KEY_LEFTBRACE,        "LEFTBRACE"                       },
{ KEY_RIGHTBRACE,       "RIGHTBRACE"                      },
{ KEY_ENTER,            "ENTER"                           },
{ KEY_LEFTCTRL,         "LEFTCTRL"                        },
{ KEY_A,                "A"                               },
{ KEY_S,                "S"                               },
{ KEY_D,                "D"                               },
{ KEY_F,                "F"                               },
{ KEY_G,                "G"                               },
{ KEY_H,                "H"                               },
{ KEY_J,                "J"                               },
{ KEY_K,                "K"                               },
{ KEY_L,                "L"                               },
{ KEY_SEMICOLON,        "SEMICOLON"                       },
{ KEY_APOSTROPHE,       "APOSTROPHE"                      },
{ KEY_GRAVE,            "GRAVE"                           },
{ KEY_LEFTSHIFT,        "LEFTSHIFT"                       },
{ KEY_BACKSLASH,        "BACKSLASH"                       },
{ KEY_Z,                "Z"                               },
{ KEY_X,                "X"                               },
{ KEY_C,                "C"                               },
{ KEY_V,                "V"                               },
{ KEY_B,                "B"                               },
{ KEY_N,                "N"                               },
{ KEY_M,                "M"                               },
{ KEY_COMMA,            "COMMA"                           },
{ KEY_DOT,              "DOT"                             },
{ KEY_SLASH,            "SLASH"                           },
{ KEY_RIGHTSHIFT,       "RIGHTSHIFT"                      },
{ KEY_KPASTERISK,       "KPASTERISK"                      },
{ KEY_LEFTALT,          "LEFTALT"                         },
{ KEY_SPACE,            "SPACE"                           },
{ KEY_CAPSLOCK,         "CAPSLOCK"                        },
{ KEY_F1,               "F1"                              },
{ KEY_F2,               "F2"                              },
{ KEY_F3,               "F3"                              },
{ KEY_F4,               "F4"                              },
{ KEY_F5,               "F5"                              },
{ KEY_F6,               "F6"                              },
{ KEY_F7,               "F7"                              },
{ KEY_F8,               "F8"                              },
{ KEY_F9,               "F9"                              },
{ KEY_F10,              "F10"                             },
{ KEY_NUMLOCK,          "NUMLOCK"                         },
{ KEY_SCROLLLOCK,       "SCROLLLOCK"                      },
{ KEY_KP7,              "KP7"                             },
{ KEY_KP8,              "KP8"                             },
{ KEY_KP9,              "KP9"                             },
{ KEY_KPMINUS,          "KPMINUS"                         },
{ KEY_KP4,              "KP4"                             },
{ KEY_KP5,              "KP5"                             },
{ KEY_KP6,              "KP6"                             },
{ KEY_KPPLUS,           "KPPLUS"                          },
{ KEY_KP1,              "KP1"                             },
{ KEY_KP2,              "KP2"                             },
{ KEY_KP3,              "KP3"                             },
{ KEY_KP0,              "KP0"                             },
{ KEY_KPDOT,            "KPDOT"                           },
{ KEY_ZENKAKUHANKAKU,   "ZENKAKUHANKAKU"                  },
{ KEY_102ND,            "102ND"                           },
{ KEY_F11,              "F11"                             },
{ KEY_F12,              "F12"                             },
{ KEY_RO,               "RO"                              },
{ KEY_KATAKANA,         "KATAKANA"                        },
{ KEY_HIRAGANA,         "HIRAGANA"                        },
{ KEY_HENKAN,           "HENKAN"                          },
{ KEY_KATAKANAHIRAGANA, "KATAKANAHIRAGANA"                },
{ KEY_MUHENKAN,         "MUHENKAN"                        },
{ KEY_KPJPCOMMA,        "KPJPCOMMA"                       },
{ KEY_KPENTER,          "KPENTER"                         },
{ KEY_RIGHTCTRL,        "RIGHTCTRL"                       },
{ KEY_KPSLASH,          "KPSLASH"                         },
{ KEY_SYSRQ,            "SYSRQ"                           },
{ KEY_RIGHTALT,         "RIGHTALT"                        },
{ KEY_LINEFEED,         "LINEFEED"                        },
{ KEY_HOME,             "HOME"                            },
{ KEY_UP,               "UP"                              },
{ KEY_PAGEUP,           "PAGEUP"                          },
{ KEY_LEFT,             "LEFT"                            },
{ KEY_RIGHT,            "RIGHT"                           },
{ KEY_END,              "END"                             },
{ KEY_DOWN,             "DOWN"                            },
{ KEY_PAGEDOWN,         "PAGEDOWN"                        },
{ KEY_INSERT,           "INSERT"                          },
{ KEY_DELETE,           "DELETE"                          },
{ KEY_MACRO,            "MACRO"                           },
{ KEY_MUTE,             "MUTE"                            },
{ KEY_VOLUMEDOWN,       "VOLUMEDOWN"                      },
{ KEY_VOLUMEUP,         "VOLUMEUP"                        },
{ KEY_POWER,            "POWER"                           },
{ KEY_KPEQUAL,          "KPEQUAL"                         },
{ KEY_KPPLUSMINUS,      "KPPLUSMINUS"                     },
{ KEY_PAUSE,            "PAUSE"                           },
{ KEY_SCALE,            "SCALE"                           },
{ KEY_KPCOMMA,          "KPCOMMA"                         },
{ KEY_HANGEUL,          "HANGEUL"                         },
{ KEY_HANGUEL,          "HANGUEL"                         },
{ KEY_HANJA,            "HANJA"                           },
{ KEY_YEN,              "YEN"                             },
{ KEY_LEFTMETA,         "LEFTMETA"                        },
{ KEY_RIGHTMETA,        "RIGHTMETA"                       },
{ KEY_COMPOSE,          "COMPOSE"                         },
{ KEY_STOP,             "STOP"                            },
{ KEY_AGAIN,            "AGAIN"                           },
{ KEY_PROPS,            "PROPS"                           },
{ KEY_UNDO,             "UNDO"                            },
{ KEY_FRONT,            "FRONT"                           },
{ KEY_COPY,             "COPY"                            },
{ KEY_OPEN,             "OPEN"                            },
{ KEY_PASTE,            "PASTE"                           },
{ KEY_FIND,             "FIND"                            },
{ KEY_CUT,              "CUT"                             },
{ KEY_HELP,             "HELP"                            },
{ KEY_MENU,             "MENU"                            },
{ KEY_CALC,             "CALC"                            },
{ KEY_SETUP,            "SETUP"                           },
{ KEY_SLEEP,            "SLEEP"                           },
{ KEY_WAKEUP,           "WAKEUP"                          },
{ KEY_FILE,             "FILE"                            },
{ KEY_SENDFILE,         "SENDFILE"                        },
{ KEY_DELETEFILE,       "DELETEFILE"                      },
{ KEY_XFER,             "XFER"                            },
{ KEY_PROG1,            "PROG1"                           },
{ KEY_PROG2,            "PROG2"                           },
{ KEY_WWW,              "WWW"                             },
{ KEY_MSDOS,            "MSDOS"                           },
{ KEY_COFFEE,           "COFFEE"                          },
{ KEY_SCREENLOCK,       "SCREENLOCK"                      },
{ KEY_DIRECTION,        "DIRECTION"                       },
{ KEY_CYCLEWINDOWS,     "CYCLEWINDOWS"                    },
{ KEY_MAIL,             "MAIL"                            },
{ KEY_BOOKMARKS,        "BOOKMARKS"                       },
{ KEY_COMPUTER,         "COMPUTER"                        },
{ KEY_BACK,             "BACK"                            },
{ KEY_FORWARD,          "FORWARD"                         },
{ KEY_CLOSECD,          "CLOSECD"                         },
{ KEY_EJECTCD,          "EJECTCD"                         },
{ KEY_EJECTCLOSECD,     "EJECTCLOSECD"                    },
{ KEY_NEXTSONG,         "NEXTSONG"                        },
{ KEY_PLAYPAUSE,        "PLAYPAUSE"                       },
{ KEY_PREVIOUSSONG,     "PREVIOUSSONG"                    },
{ KEY_STOPCD,           "STOPCD"                          },
{ KEY_RECORD,           "RECORD"                          },
{ KEY_REWIND,           "REWIND"                          },
{ KEY_PHONE,            "PHONE"                           },
{ KEY_ISO,              "ISO"                             },
{ KEY_CONFIG,           "CONFIG"                          },
{ KEY_HOMEPAGE,         "HOMEPAGE"                        },
{ KEY_REFRESH,          "REFRESH"                         },
{ KEY_EXIT,             "EXIT"                            },
{ KEY_MOVE,             "MOVE"                            },
{ KEY_EDIT,             "EDIT"                            },
{ KEY_SCROLLUP,         "SCROLLUP"                        },
{ KEY_SCROLLDOWN,       "SCROLLDOWN"                      },
{ KEY_KPLEFTPAREN,      "KPLEFTPAREN"                     },
{ KEY_KPRIGHTPAREN,     "KPRIGHTPAREN"                    },
{ KEY_NEW,              "NEW"                             },
{ KEY_REDO,             "REDO"                            },
{ KEY_F13,              "F13"                             },
{ KEY_F14,              "F14"                             },
{ KEY_F15,              "F15"                             },
{ KEY_F16,              "F16"                             },
{ KEY_F17,              "F17"                             },
{ KEY_F18,              "F18"                             },
{ KEY_F19,              "F19"                             },
{ KEY_F20,              "F20"                             },
{ KEY_F21,              "F21"                             },
{ KEY_F22,              "F22"                             },
{ KEY_F23,              "F23"                             },
{ KEY_F24,              "F24"                             },
{ KEY_PLAYCD,           "PLAYCD"                          },
{ KEY_PAUSECD,          "PAUSECD"                         },
{ KEY_PROG3,            "PROG3"                           },
{ KEY_PROG4,            "PROG4"                           },
{ KEY_DASHBOARD,        "DASHBOARD"                       },
{ KEY_SUSPEND,          "SUSPEND"                         },
{ KEY_CLOSE,            "CLOSE"                           },
{ KEY_PLAY,             "PLAY"                            },
{ KEY_FASTFORWARD,      "FASTFORWARD"                     },
{ KEY_BASSBOOST,        "BASSBOOST"                       },
{ KEY_PRINT,            "PRINT"                           },
{ KEY_HP,               "HP"                              },
{ KEY_CAMERA,           "CAMERA"                          },
{ KEY_SOUND,            "SOUND"                           },
{ KEY_QUESTION,         "QUESTION"                        },
{ KEY_EMAIL,            "EMAIL"                           },
{ KEY_CHAT,             "CHAT"                            },
{ KEY_SEARCH,           "SEARCH"                          },
{ KEY_CONNECT,          "CONNECT"                         },
{ KEY_FINANCE,          "FINANCE"                         },
{ KEY_SPORT,            "SPORT"                           },
{ KEY_SHOP,             "SHOP"                            },
{ KEY_ALTERASE,         "ALTERASE"                        },
{ KEY_CANCEL,           "CANCEL"                          },
{ KEY_BRIGHTNESSDOWN,   "BRIGHTNESSDOWN"                  },
{ KEY_BRIGHTNESSUP,     "BRIGHTNESSUP"                    },
{ KEY_MEDIA,            "MEDIA"                           },
{ KEY_SWITCHVIDEOMODE,  "SWITCHVIDEOMODE"                 },
{ KEY_KBDILLUMTOGGLE,   "KBDILLUMTOGGLE"                  },
{ KEY_KBDILLUMDOWN,     "KBDILLUMDOWN"                    },
{ KEY_KBDILLUMUP,       "KBDILLUMUP"                      },
{ KEY_SEND,             "SEND"                            },
{ KEY_REPLY,            "REPLY"                           },
{ KEY_FORWARDMAIL,      "FORWARDMAIL"                     },
{ KEY_SAVE,             "SAVE"                            },
{ KEY_DOCUMENTS,        "DOCUMENTS"                       },
{ KEY_BATTERY,          "BATTERY"                         },
{ KEY_BLUETOOTH,        "BLUETOOTH"                       },
{ KEY_WLAN,             "WLAN"                            },
{ KEY_UWB,              "UWB"                             },
{ KEY_UNKNOWN,          "UNKNOWN"                         },
{ KEY_VIDEO,            "VIDEO"                           },
{ KEY_NEXT,             "NEXT"                            },
{ KEY_VIDEO,            "VIDEO"                           },
{ KEY_WWAN,             "WWAN"                            },
{ KEY_WIMAX,            "WIMAX"                           },
{ KEY_RFKILL,           "RFKILL"                          },
{ KEY_MICMUTE,          "MICMUTE"                         },

};
XKeyEvent createKeyEvent(Display *display,
                         Window   win,
                         Window   winRoot,
                         Bool     press,
                         int      keycode,
                         int      modifiers);
int main(void) {
  // ubicacion del archivo de dispisitivo de teclado cambia dependiendo el
  // sistema
  // /dev/input/eventN es una interfaz a los drivers de sistema por el modulo
  // evdev del kernel
  // devuelve los keycodes que interpreto el kernel de los scancodes leidos del
  // driver
  const char *dev = "/dev/input/event0";
  int keyLen      = (sizeof(keys) / sizeof(keys[0]));

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

  // incializacion de  para creacion de evento falso
  // X Window System provee librerias para manipular keycodes dado que es una
  // aplicacion en keycode mode
  // http://www.tldp.org/HOWTO/Keyboard-and-Console-HOWTO-2.html para mas
  // informacion al respecto
  // Desafortunadamente, dado que X toma keycodes y los interpreta su tabla de
  // mapeo
  // de teclas es diferente a la del resto del SO
  // Afortunadamente, la diferencia entre una y otra tabla es de 8 enteros es
  // decir
  // en consola la tecla b = 48 y en xorg b = 56
  // esto nos permite usar las librerias de X para decodificar los keycodes del
  // driver del teclado
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

    // **si se escribe al mismo tiempo en consola parece que se estan
    // interpretando los keycodes,
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
      // ev.code nos devuelve los keycodes -> variable numericas que representan
      // las teclas fisicas
      // estas constantes son las mismas en todas las arquitecturas y on
      // independientes de hardware
      // mas info
      // https://www.kernel.org/doc/html/v4.13/input/event-codes.html#input-event-codes
      switch (ev.code) {
      // la variable ac registra los modificadores--> teclas que cambian el
      // output de otras teclas
      // mas informacion
      // https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html#XKeyEvent
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
        XKeyEvent keyEv = createKeyEvent(display,
                                         winFocus,
                                         winRoot,
                                         True,
                                         ev.code + 8,
                                         ac | caps | numlock);
        XLookupString(&keyEv, string, 200, &keysym, NULL);
        printf("Se  detecto Keypress con Keycode  = %i\n", keyEv.keycode);
        printf("Se  detecto Keypress con estado  = %li\n", keyEv.state); //

        if (string[0] > 31)
          printf("Se  detecto Keypress con valor legible = %c\n",
              string[0]);
        else
          for (int i = 0; i < keyLen; i++) {
            if (keys[i].keyCode == ev.code) {
              printf("Se  detecto Keypress con valor no legible -> tecla = %s\n",
                     keys[i].keystr);
              break;
            }
          }


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
        XKeyEvent keyEv = createKeyEvent(display,
                                         winFocus,
                                         winRoot,
                                         False,
                                         ev.code + 8,
                                         ac | caps | numlock);
        XLookupString(&keyEv, string, 200, &keysym, NULL);

        printf("Se  detecto Keypress con Keycode  = %i\n", keyEv.keycode);
        printf("Se  detecto Keypress con estado  = %li\n", keyEv.state);

        if (string[0] > 31)
          printf("Se  detecto Keypress con valor legible = %c\n",
              string[0]);
        else
          for (int i = 0; i < keyLen; i++) {
            if (keys[i].keyCode == ev.code) {
              printf("Se  detecto Keypress con valor no legible = %s\n",
                     keys[i].keystr);
              break;
            }
          }

        if (keyEv.keycode == 0x09) break;
      }
    }
  }
  fflush(stdout);
  fprintf(stderr, "%s.\n", strerror(errno));
  return EXIT_FAILURE;
}

// funcion obtenida de
// http://www.doctort.org/adam/nerd-notes/x11-fake-keypress-event.html
XKeyEvent createKeyEvent(Display *display,
                         Window   win,
                         Window   winRoot,
                         Bool     press,
                         int      keycode,
                         int      modifiers){
  // mas info de XKeyEvent struct
  // https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html#XKeyEvent

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
