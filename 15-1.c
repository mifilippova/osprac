#define _CRT_SECURE_NO_WARNINGS
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

int flag = 1;

void my_handler(int nsig) { 
  if (nsig == SIGUSR1){
     flag = 0;
  }
}

int main(void) {
  pid_t pid = getpid();
  printf("Pid программы: %d\n", pid);

  pid_t other;
  printf("Введите pid собеседника ");
  scanf("%d", &other);

  int n;
  printf("Введите целое число ");
  scanf("%d", &n);

  (void) signal(SIGUSR1, my_handler);
  (void) signal(SIGUSR2, my_handler);

  if (n < 0){
    kill(other, SIGUSR1);
    n = 0 - n;
  }
  else{
   kill(other, SIGUSR2);
  }

 

  for(int i = 65536; i >= 1; i /= 2){
       while(flag);
       flag = 1;
       if (i & n){
       // 1.
         kill(other, SIGUSR1);
       }
       else{
       // 0.
         kill(other, SIGUSR2);
       }
  
       
  }
  
  return 0;
}
