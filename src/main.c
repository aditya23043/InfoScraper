#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysymdef.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  Display *display = XOpenDisplay(NULL);
  int screen = DefaultScreen(display);
  Window root_window = RootWindow(display, screen);

  XWarpPointer(display, None, root_window, 0, 0, 0, 0, 200, 200);
  XFlush(display);

  KeyCode key_windows = XKeysymToKeycode(display, XK_Super_L);
  KeyCode key_2 = XKeysymToKeycode(display, XK_2);

  XTestFakeKeyEvent(display, key_windows, True, CurrentTime);
  XTestFakeKeyEvent(display, key_2, True, CurrentTime);
  XFlush(display);

  sleep(0.1);

  XTestFakeKeyEvent(display, key_2, False, CurrentTime);
  XTestFakeKeyEvent(display, key_windows, False, CurrentTime);
  XFlush(display);

  XCloseDisplay(display);

  return 0;
}
