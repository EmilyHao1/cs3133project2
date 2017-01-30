#include <stdlib.h>
#include <stdio.h>

void main(void) {
  int fd = open("file1.txt", 0);
  char *buffer = (char*)malloc(sizeof(char) * 1024);
  read(fd, buffer, 1024);
  close(fd);
  printf("File descriptor was: %d\n", fd);
}
