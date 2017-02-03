#include <sys/syscall.h>
#include <stdio.h>
#define __NR_cs3013_syscall1 378
#define __NR_cs3013_syscall2 378
#define __NR_cs3013_syscall3 378

struct ancestry{
	pid_t ancestor[10];
	pid_t siblings[100];
	pid_t children[100];
};

long testcall(pid_t *target_pid, struct ancestry *response){	
	return(long)syscall(__NR_cs3013_syscall2, target_pid, response);; 
}
int main(){
	struct ancestry* ancestryTest = malloc(sizeof(ancestry)); 
	int pid = fork(); 

}
