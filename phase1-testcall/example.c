#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(void) {
  int fd = open("file1.txt", O_RDONLY, 0);
  char *buffer = (char*)malloc(sizeof(char) * 1024);
  read(fd, buffer, 1024);
  printf("%s\n", buffer);
  close(fd);
  printf("File descriptor was: %d\n", fd);
}
