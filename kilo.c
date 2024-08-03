#include <windows.h>
#include <unistd.h>

void enableRawMode() {
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD dwMode = 0;

    GetConsoleMode(hStdIn, &dwMode);

    // Disable the line input, echo input, and process input modes
    dwMode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
    SetConsoleMode(hStdIn, dwMode);
}

int main() {
    enableRawMode();
    char c;

    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');

    return 0;
}
