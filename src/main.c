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

    // get focused window
    sleep(5); // sleep because browser takes time to load
    int revert_to;
    Window focused_window;
    XGetInputFocus(display, &focused_window, &revert_to);
    if (focused_window == None) {
        fprintf(stderr, "No window has focus!\n");
        return 1;
    }
    XSetInputFocus(display, focused_window, RevertToParent, CurrentTime);

    // write the text
    for (int i = 0; i < strlen(prompt); i++) {

        KeySym key_sym;
        KeyCode key_code;

        if (prompt[i] == ' ') {
            key_code = XKeysymToKeycode(display, XK_space);
        } else {
            char *key_str = malloc(sizeof(char) * 2);
            sprintf(key_str, "%c", prompt[i]);
            key_sym = XStringToKeysym(key_str);
            key_code = XKeysymToKeycode(display, key_sym);
        }
        if (key_code == 0) {
            fprintf(stderr, "Could not get key code!");
            return 1;
        }

        XEvent event;

        /* EVENT CONFIG */
        event.type = KeyPress;
        event.xkey.window = focused_window;
        event.xkey.root = root_window;
        event.xkey.subwindow = None;
        event.xkey.time = CurrentTime;
        event.xkey.x = 1;
        event.xkey.y = 1;
        event.xkey.x_root = 1;
        event.xkey.y_root = 1;
        event.xkey.state = 0;
        event.xkey.keycode = key_code;
        event.xkey.same_screen = True;

        XSendEvent(display, focused_window, True, KeyPressMask, &event);

        // release key
        event.type = KeyRelease;
        XSendEvent(display, focused_window, True, KeyReleaseMask, &event);

        XFlush(display);
        sleep(0.01);
    }

    // Enter text

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
