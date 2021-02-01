#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	printf("Current process ID = %d\n", getpid());
	printf("Parent ID = %d\n", getppid());

	return 0;
}
