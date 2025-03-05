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
void key_press(Display *display, KeyCode key_code);

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

    /* ---- Open Browser ---- */
    // ensure that you are already logged in to udio
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

    char *prompt = argv[1];

    // delay so that the browser window can open
    sleep(7);

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

        key_press(display, key_code);
    }

    /* NOTE:
     * this is hardcoded for udio only
     * as of now, we can press 7 tabs to go from input text box to submit button
     */
    for (int i = 0; i < 7; i++) {
        KeyCode key_code = XKeysymToKeycode(display, XK_Tab);
        key_press(display, key_code);
    }
    // facing some issue with the quick click
    sleep(1);
    // click the submit button
    key_press(display, XKeysymToKeycode(display, XK_Return));

    /* ---- Download the song ---- */

    sleep(65);
    /* system("notify-send 'Hover over the three dots!'"); */
    /* system("notify-send '3'"); */
    /* sleep(1); */
    /* system("notify-send '2'"); */
    /* sleep(1); */
    /* system("notify-send '1'"); */
    /* sleep(1); */
    /* int root_x, root_y, win_x, win_y; */
    /* unsigned int mask; */
    /* Window root_return, child_return; */
    /* XQueryPointer(display, root_window, &root_return, &child_return, &root_x,
     */
    /*               &root_y, &win_x, &win_y, &mask); */
    /* system("notify-send 'Mouse position captured!'"); */
    /* printf("Mouse X: %d, Mouse Y: %d\n", root_x, root_y); */
    // focus the three dots
    /* for (int i = 0; i < 24; i++) { */
    /*     KeyCode key_code = XKeysymToKeycode(display, XK_Tab); */
    /*     key_press(display, key_code); */
    /*     sleep(0.2); */
    /* } */
    /* // click on the three dots */
    /* key_press(display, XKeysymToKeycode(display, XK_Return)); */

    XWarpPointer(display, None, root_window, 0, 0, 0, 0, 1871, 300);
    XTestFakeButtonEvent(display, Button1, True, CurrentTime);
    XTestFakeButtonEvent(display, Button1, False, CurrentTime);
    XFlush(display);

    sleep(1);
    // focus download option
    for (int i = 0; i < 7; i++) {
        KeyCode key_code = XKeysymToKeycode(display, XK_Down);
        key_press(display, key_code);
        sleep(3);
    }
    sleep(1);
    // click the download option
    key_press(display, XKeysymToKeycode(display, XK_Return));
    sleep(1);
    // focus the mp3 option
    key_press(display, XKeysymToKeycode(display, XK_Down));
    sleep(1);
    // click the mp3 option
    key_press(display, XKeysymToKeycode(display, XK_Return));
    sleep(1);

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

void key_press(Display *display, KeyCode key_code) {
    XTestFakeKeyEvent(display, key_code, True, CurrentTime);
    XFlush(display);
    XTestFakeKeyEvent(display, key_code, False, CurrentTime);
    XFlush(display);
}
