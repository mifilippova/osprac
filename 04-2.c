#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
  pid_t pid;

  pid = fork();

  if (pid == -1){
  	printf("Error");
  }
  else if (pid == 0){
	execve("action.out", 0, envp);
  }
  else{
	printf("It is a rainy day for %d\n", getppid());
  }

  return 0;
}
