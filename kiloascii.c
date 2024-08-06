#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  //apply 2 terminal
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
  enableRawMode();
  char c;
  //while there are bytes to read, read 1 byte from standard input into variable c untillllll we press 'q'
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    if(iscntrl(c)) {
	printf("%d\n", c);
    } else {
	printf("%d ('%c')\n", c, c);
    }
}
  return 0;
}
