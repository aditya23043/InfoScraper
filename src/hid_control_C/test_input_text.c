#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {

    Display *display;
    Window target_win;
    char text[] = "I dont know bruh what to do demn this sux";

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display!\n");
        return 1;
    }

    Window root_window;
    root_window = DefaultRootWindow(display);
    int revert_to;
    XGetInputFocus(display, &target_win, &revert_to);

    if (target_win == None) {
        fprintf(stderr, "No Window has focus!\n");
        return 1;
    }

    for (int i = 0; i < strlen(text); i++) {

        KeySym key_sym;
        KeyCode key_code;

        if (text[i] == ' ') {
            key_code = XKeysymToKeycode(display, XK_space);
        } else {
            char *key_str = malloc(sizeof(char));
            sprintf(key_str, "%c", text[i]);
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
        event.xkey.window = target_win;
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

        XSendEvent(display, target_win, True, KeyPressMask, &event);

        // release key
        event.type = KeyRelease;
        XSendEvent(display, target_win, True, KeyReleaseMask, &event);

        XFlush(display);
        sleep(0.01);
    }

    XCloseDisplay(display);

    return 0;
}
