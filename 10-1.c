/*
Начальное значение семафора S = 0.
В цикле родителя мы совершаем операцию записи в pipe, затем совершаем A(S,3), значение семафора становится равным 3. Затем Z(S)-ожидаем завршения пары операции чтения-записи процесса-ребенка (сумма опреций над значением семафора в нем равна -3), когда значение семафора становится 0 читаем то, что записал ребенок. Если условие выхода из цикла не выполненно, то начинаем новую итерацию (родитель снова записывает данные, совершает A(S,3) и ожидает значения семафора, раное 0, читает данные от ребенка..).

В цикле ребенка значение семафора на момент начала итерации цикла равно 3, совершаем D(S, 2) перед началом операций чтения из pipe и записи,
и D(S, 1) по окончании, тем самым значение семафора становится 0 и в процессе родителе
сработает чтение данных от ребенка после Z(S).
*/


#define _CRT_SECURE_NO_WARNINGS
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/sem.h>


int main()
{
  int     fd[2], result;

  int n;
  size_t size;
  char  resstring[14];
  int semid;
  struct sembuf sem_lock_pc = {0, -2, 0};
  struct sembuf sem_unlock_pc = {0, 3, 0};
  struct sembuf sem_lock_cp = {0, 0, 0};
  struct sembuf sem_unlock_cp = {0, -1, 0};
  key_t   val;
  char    path[] = "10-1.c";
  int v;

   if ((val = ftok(path,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }
 
  if ((semid = semget(val, 1, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("Can\'t create semaphore\n");
      exit(-1);
    } else {
      if ((semid = semget(val, 1, 0666|IPC_CREAT)) < 0) {
        printf("Can\'t find semaphore\n");
        exit(-1);
      }
    }
  }

  printf("\nInput number of operations: ");
  scanf("%d", &n);

  if (n < 2){
    printf("Number of operations must be more than 1");
    exit(-1);
  }


  if (pipe(fd) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }

  result = fork();

  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (result > 0) {
  while (n > 0){
   /* Parent process */

    size = write(fd[1], "Hello, world!", 14);
    printf("Parent wrote to pipe %s\n", "Hello, world!");

    if (size != 14) {
      printf("Can\'t write all string to pipe\n");
      exit(-1);
    }

     if (semop(semid, &sem_unlock_pc, 1) < 0) {
         printf("Can\'t wait for condition\n");
         exit(-1);
     }
     
     if (semop(semid, &sem_lock_cp, 1) < 0) {
         printf("Can\'t wait for condition\n");
         exit(-1);
     }
   
     size = read(fd[0], resstring, 14);
     printf("Parent read from pipe : %s\n", resstring);

    if (size < 0) {
      printf("Can\'t read string from pipe\n");
      exit(-1);
    }  
 
    n = n - 1;
   }

  } else {
  

while(n > 0){

    /* Child process */
    
    if (semop(semid, &sem_lock_pc, 1) < 0) {
         printf("Can\'t wait for condition\n");
         exit(-1);
     }

     size = read(fd[0], resstring, 14);
     printf("Child read from pipe %s\n", resstring);

    if (size < 0) {
      printf("Can\'t read string from pipe\n");
      exit(-1);
    }

    size = write(fd[1], "HELLO, WORLD!", 14);

    printf("Child wrote to pipe %s\n", "HELLO, WORLD!");

    if (size != 14) {
      printf("Can\'t write all string to pipe\n");
      exit(-1);
    }
    
    if (semop(semid, &sem_unlock_cp, 1) < 0) {
         printf("Can\'t wait for condition\n");
         exit(-1);
     }

     n = n - 1;
   }
}
  return 0;
}
