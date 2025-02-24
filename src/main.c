#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysymdef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *check_browser();

int main(int argc, char *argv[]) {

  /* INIT */
  Display *display = XOpenDisplay(NULL);
  int screen = DefaultScreen(display);
  Window root_window = RootWindow(display, screen);

  /* Move Mouse */
  XWarpPointer(display, None, root_window, 0, 0, 0, 0, 200, 200);
  XFlush(display);

  /* Key Press */
  KeyCode key_windows = XKeysymToKeycode(display, XK_Super_L);
  KeyCode key_2 = XKeysymToKeycode(display, XK_2);

  XTestFakeKeyEvent(display, key_windows, True, CurrentTime);
  XTestFakeKeyEvent(display, key_2, True, CurrentTime);
  XFlush(display);

  sleep(0.1);

  XTestFakeKeyEvent(display, key_2, False, CurrentTime);
  XTestFakeKeyEvent(display, key_windows, False, CurrentTime);
  XFlush(display);

  /* Open Browser */
  char *default_browser = check_browser();
  printf("%s", default_browser);

  char *open_browser_cmd = malloc(sizeof(char) * 256);
  snprintf(open_browser_cmd, 256, "%s https://udio.com", default_browser);
  system(open_browser_cmd);

  /* CLEANUP */
  XCloseDisplay(display);

  return 0;
}

char *check_browser() {
  char *browser = getenv("BROWSER");
  if (browser != NULL) {
    return browser;
  }

  // if $BROWSER var not set
  if (system("which firefox > /dev/null 2>&1") == 0) {
    return "firefox";
  }

  if (system("which chromium > /dev/null 2>&1") == 0) {
    return "chromium";
  }

  if (system("which chrome > /dev/null 2>&1") == 0) {
    return "chrome";
  }

  if (system("which qutebrowser > /dev/null 2>&1") == 0) {
    return "qutebrowser";
  }

  if (system("which brave > /dev/null 2>&1") == 0) {
    return "brave";
  }

  return browser;
}
