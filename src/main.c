#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysymdef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* TODO: INITIAL CONFIG
 * time taken to load website
 */

char *check_browser();
void key_press(Display *display, KeyCode key_code);
void sleep_notify(int seconds, char *msg);

int main(int argc, char **argv) {

  if (argc != 2) {
    printf("Usage: ./<bin> <prompt>");
    exit(-1);
  }

  Display *display;
  Window rootWindow;

  display = XOpenDisplay(NULL);
  rootWindow = XDefaultRootWindow(display);

  char browser_command[256];
  snprintf(browser_command, 256, "%s --new-window https://suno.com/create",
           check_browser());
  printf("%s", browser_command);
  system(browser_command);

  sleep_notify(10, "Opening browser...");

  // focusing on text box
  for (int i = 0; i < 22; i++) { /* NOTE hardcoded value */
    key_press(display, XKeysymToKeycode(display, XK_Tab));
    sleep(0.1);
  }

  /* ---- Prompt Input ---- */

  char *prompt = argv[1];

  sleep(1);

  // enter text
  for (int i = 0; i < strlen(prompt); i++) {
    KeyCode key_code;
    if (prompt[i] == ' ') {
      key_code = XKeysymToKeycode(display, XK_space);
    } else {
      char key_code_str[256];
      snprintf(key_code_str, sizeof(key_code_str), "%c", prompt[i]);
      key_code = XKeysymToKeycode(display, XStringToKeysym(key_code_str));
    }

    key_press(display, key_code);
  }

  // focus on create button
  for (int i = 0; i < 4; i++) { /* NOTE hardcoded value */
    key_press(display, XKeysymToKeycode(display, XK_Tab));
    sleep(0.1);
  }
  key_press(display, XKeysymToKeycode(display, XK_Return));

  // wait for song to generate
  sleep_notify(40, "Generating song...");

  // focus on three dot for downloading song
  for (int i = 0; i < 18; i++) { /* NOTE hardcoded value */
    key_press(display, XKeysymToKeycode(display, XK_Tab));
    sleep(0.1);
  }
  key_press(display, XKeysymToKeycode(display, XK_Return));
  sleep(2);

  for (int i = 0; i < 5; i++) { /* NOTE hardcoded value */
    key_press(display, XKeysymToKeycode(display, XK_Down));
    sleep(1);
  }
  sleep(1);
  key_press(display, XKeysymToKeycode(display, XK_Return));
  sleep(1);
  key_press(display, XKeysymToKeycode(display, XK_Return));

  // now wait for the "where to download" prompt to come
  /* sleep_notify(30, "Downloading..."); */

  /* key_press(display, XKeysymToKeycode(display, XK_Return)); */

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
    char cmd[256];
    while (seconds--) {
      snprintf(cmd, sizeof(cmd), "notify-send %d -t 1000", seconds + 1);
      system(cmd);
      sleep(1);
    }
  } else {
    sleep(seconds);
  }
  pclose(fp);
}
