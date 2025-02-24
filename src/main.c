#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <X11/keysymdef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *check_browser();

int main(int argc, char *argv[]) {

    /* ---- Arg checking ---- */
    if (argc != 3) {
        printf("Usage: ./main <prompt> <audio_filename>.mp3\n");
        exit(0);
    }

    /* ---- INIT ---- */
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display!\n");
        return 1;
    }
    int screen = DefaultScreen(display);
    Window root_window = RootWindow(display, screen);

    /* /1* Move Mouse *1/ */
    /* XWarpPointer(display, None, root_window, 0, 0, 0, 0, 200, 200); */
    /* XFlush(display); */

    /* /1* Key Press *1/ */
    /* KeyCode key_windows = XKeysymToKeycode(display, XK_Super_L); */
    /* KeyCode key_2 = XKeysymToKeycode(display, XK_2); */

    /* XTestFakeKeyEvent(display, key_windows, True, CurrentTime); */
    /* XTestFakeKeyEvent(display, key_2, True, CurrentTime); */
    /* XFlush(display); */

    /* sleep(0.1); */

    /* XTestFakeKeyEvent(display, key_2, False, CurrentTime); */
    /* XTestFakeKeyEvent(display, key_windows, False, CurrentTime); */
    /* XFlush(display); */

    /* ---- Open Browser ---- */
    char *default_browser = check_browser();
    printf("%s", default_browser);

    char *open_browser_cmd = malloc(sizeof(char) * 256);
    // the --new-window arg works with most popular browsers
    // also, i am using this arg to avoid situations in which
    // people already have the browser open in a different workspace
    // but I want the browser to be in focus
    snprintf(open_browser_cmd, 256, "%s --new-window https://udio.com/create",
             default_browser);
    system(open_browser_cmd);

    /* ---- Prompt Input ---- */

    /* char *prompt = argv[1]; */
    char prompt[] =
        "Make a song about being a thinkpad nerd running arch linux "
        "alongside a split ergo keyboard and a crazy good IEM";

    // delay so that the browser window can open
    sleep(5);

    // enter text
    for (int i = 0; i < strlen(prompt); i++) {
        KeyCode key_code;
        if (prompt[i] == ' ') {
            key_code = XKeysymToKeycode(display, XK_space);
        } else {
            char *key_code_str = malloc(sizeof(char));
            sprintf(key_code_str, "%c", prompt[i]);
            key_code = XKeysymToKeycode(display, XStringToKeysym(key_code_str));
        }
        XTestFakeKeyEvent(display, key_code, True, CurrentTime);
        XFlush(display);
        XTestFakeKeyEvent(display, key_code, False, CurrentTime);
        XFlush(display);
    }

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
