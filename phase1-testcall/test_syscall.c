#include <sys/syscall.h>
#include <stdio.h>

#define __NR_cs3013_syscall 355


int main(int argc, char **argv) {
  long returnV = (long)syscall(__NR_cs3013_syscall);
  printf("\tKernel call to cs3013_syscall1() returned: %ld\n", returnV);
  return 0;
}
