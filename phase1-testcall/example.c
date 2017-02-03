#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(void) {
  int fd = open("Virus.txt", O_RDONLY, 0);
  char *buffer = (char*)malloc(sizeof(char) * 1024);
  read(fd, buffer, 1024);
  printf("File read: %s", buffer);
  close(fd);
  printf("File descriptor was: %d\n", fd);
  int fd2 = open("Clean.txt", O_RDONLY, 0);
  char *buffer2 = (char*)malloc(sizeof(char) * 1024);
  read(fd2, buffer2, 1024);
  printf("File read: %s\n", buffer2);
  close(fd);
  printf("File descriptor was: %d\n", fd2);
}
