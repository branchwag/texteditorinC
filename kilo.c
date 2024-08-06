#include <unistd.h>

int main(){
  char c;
  //while there are bytes to read, read 1 byte from standard input into variable c untillllll we press 'q'
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
  return 0;
}
