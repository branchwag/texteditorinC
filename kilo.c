#include <unistd.h>

int main() {
    char c;
    //We are asking read() to read 1 byte from the standard input into the variable c, and to keep doing it until there are no more bytes to read. read() returns the number of bytes that it read, and will return 0 when it reaches the end of a file.
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}