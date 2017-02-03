#include <sys/syscall.h>
#include <stdio.h>


struct ancestry{
	pid_t ancestor[10];
	pid_t siblings[100];
	pid_t children[100];
};

int testcall(){
	new_sys_cs3013_syscall2(unsigned short *target_pid, struct ancestry *response);	
	return 0; 
}
int main(){



}
