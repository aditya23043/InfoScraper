#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysymdef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* TODO: INITIAL CONFIG
 * time taken to load website
 */

char *check_browser();
void key_press(Display *display, KeyCode key_code);
void sleep_notify(int seconds, char *msg);

int main(int argc, char **argv) {

  Display *display;
  Window rootWindow;

  display = XOpenDisplay(NULL);
  rootWindow = XDefaultRootWindow(display);

  char *browser_command = malloc(sizeof(char) * 256);
  snprintf(browser_command, 256, "%s --new-window https://suno.com/create",
           check_browser());
  printf("%s", browser_command);
  system(browser_command);

  sleep_notify(10, "Opening browser...");

  for (int i = 0; i < 22; i++) { /* NOTE hardcoded value */
    key_press(display, XKeysymToKeycode(display, XK_Tab));
    sleep(0.1);
  }

  XFlush(display);
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

void key_press(Display *display, KeyCode key_code) {
  XTestFakeKeyEvent(display, key_code, True, CurrentTime);
  XFlush(display);
  XTestFakeKeyEvent(display, key_code, False, CurrentTime);
  XFlush(display);
}

void sleep_notify(int seconds, char *msg) {

  /* Checking if dunst is running */
  FILE *fp;
  char path[1024];

  fp = popen("pgrep dunst", "r");
  if (fp == NULL) {
    perror("popen");
    exit(-1);
  }
  // dunst running
  if (fgets(path, sizeof(path), fp) != NULL) {
    char command[256];
    snprintf(command, sizeof(command), "notify-send '%s'", msg);
    system(command);
    while (seconds--) {
      char *cmd = malloc(sizeof(char) * 256);
      snprintf(cmd, 256, "notify-send %d -t 1000", seconds + 1);
      system(cmd);
      sleep(1);
    }
  } else {
    sleep(seconds);
  }
  pclose(fp);
}
