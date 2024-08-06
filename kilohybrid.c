#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <termios.h>
#include <unistd.h>
struct termios orig_termios;
#endif

void disableRawMode() {
#ifdef _WIN32
    // For Windows, this function could reset the console mode to its original state.
    // Implementation can vary based on what modes need to be reset.
    // For now, this is a placeholder as Windows does not provide an easy way to reset to original mode without storing it first.
#else
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
#endif
}

void enableRawMode() {
#ifdef _WIN32
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD dwMode = 0;

    GetConsoleMode(hStdIn, &dwMode);

    // Disable the line input, echo input, and process input modes
    dwMode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
    SetConsoleMode(hStdIn, dwMode);
#else
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
#endif
}

int main() {
    enableRawMode();
    char c;

    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        if (iscntrl(c)){
            printf("%d\n", c);
        } else {
            printf("%d ('%c')\n", c, c);
        }
    }

    return 0;
}
