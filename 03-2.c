#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  pid_t pid;

  pid = fork();

  if (pid == -1){
  	printf("Error");
  }
  else if (pid == 0){
	printf("It is a sunny day for %d\n", getpid());
  }
  else{
	printf("It is a rainy day for %d\n", getppid());
  }


  return 0;
}
