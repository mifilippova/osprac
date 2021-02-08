#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
  int i;
  int s = 0;
  for (i = 0; i < 5; i++)
      s = s + i;
  printf("sum of 0 1 2 3 4 = %d\n", s);

  return 0;
}
