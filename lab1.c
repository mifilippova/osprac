#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	printf("Current user ID = %d\n", getuid());
	printf("Current group ID = %d\n", getgid());

	return 0;
}
