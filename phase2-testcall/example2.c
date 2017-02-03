#include <sys/syscall.h>
#include <stdio.h>
#define __NR_cs3013_syscall2 378

struct ancestry{
	pid_t ancestor[10];
	pid_t siblings[100];
	pid_t children[100];
};

long testcall(unsigned short *target_pid, struct ancestry *response){	
	return(long)syscall(__NR_cs3013_syscall2, target_pid, response);
}
int main(){
	/* Allocate memory*/
	unsigned short *target_pid = (unsigned short*)malloc(sizeof(unsigned short));
	struct ancestry* ancestryTest = malloc(sizeof(ancestry)); 
	printf("\tcs3013_syscall2: %ld\n", testcall());
	printf("Target ID: %d\n", (int)target_pid);
	printf("Ancestor: %d\n", (int)ancestry->ancestor);
	printf("Siblings: %d\n", (int)ancestry->siblings);
	printf("Children:  %d\n", (int)ancestry->children);

	free(target_pid);
	free(ancestryTest);
	return 0;
}
