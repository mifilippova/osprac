#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
  //Число аргументов в командной строке.
  printf("argc = %d\n", argc);

  //Аргументы командной строки.
  int i;
  for(i = 0; i < argc; i++){
  	printf("agv[%d] = %s\n", i, argv[i]);
  }
  
  //Параметры окружающей среды для текущего процесса.
  while(*envp)
	printf("%s\n", *envp++);

  return 0;
}
