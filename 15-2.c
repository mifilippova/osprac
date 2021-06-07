#define _CRT_SECURE_NO_WARNINGS
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

int count;
int sign = 0;
int number = 18;
pid_t other;

void my_handler(int nsig) { 
  if (number == 18){
   if (nsig == SIGUSR1){
     sign = 1;
  }
  else{
     sign = 0;
  }
 }else{
  if (nsig == SIGUSR1){
     count = count * 2 + 1;
  }
  else{
     count = count * 2;
  }
 }
  number = number - 1;
  
  kill(other, SIGUSR1);
}

int main(void) {
  pid_t pid = getpid();
  printf("Pid программы: %d\n", pid);

  printf("Введите pid собеседника "); 
  scanf("%d", &other);
  count = 0;

  (void) signal(SIGUSR1, my_handler);
  (void) signal(SIGUSR2, my_handler);

  while(number);
  if (sign)
	printf("Result: %d\n", 0 - count);
  else printf("Result: %d\n", count);
  return 0;
}
