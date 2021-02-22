#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int     fd[2], fda[2], result;
 
  size_t size;
  char  resstring[14];
  char  resstringa[7];

  if (pipe(fd) < 0) {
    printf("Can\'t open first pipe\n");
    exit(-1);
  }

  if (pipe(fda) < 0){
     printf("Can\'t open second pipe\n");
     exit(-1);
  }

  result = fork();

  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);

  } else if (result > 0) {

   /* Parent process */

    if (close(fd[0]) < 0) {
      printf("parent: Can\'t close reading side of the first pipe\n"); 
      exit(-1);
    }

    size = write(fd[1], "Hello, world!", 14);

    if (size != 14) {
      printf("Can\'t write all string to the first pipe\n");
      exit(-1);
    }
    
    printf("Parent wrote\n");

    if (close(fd[1]) < 0) {
      printf("parent: Can\'t close writing side of the first pipe\n"); exit(-1);
    }

  } else {

    /* Child process */
    
    if (close(fda[0]) < 0){
      printf("child: Can\'t close reading side of the second pipe\n");
      exit(-1);
    }

    if (close(fd[1]) < 0) {
      printf("child: Can\'t close writing side of the first pipe\n"); 
      exit(-1);
    }

    size = read(fd[0], resstring, 14);

    if (size < 0) {
      printf("Can\'t read string from the first pipe\n");
      exit(-1);
    }

    printf("Child read, resstring:%s\n", resstring);

    if (close(fd[0]) < 0) {
      printf("child: Can\'t close reading side of the first pipe\n");
      exit(-1);
    }

    size = write(fda[1], "Hello!", 7);
    
    if (size != 7) {
      printf("Can\'t write all string to the second pipe\n");
      exit(-1);
    }
    
    printf("Child wrote\n");

    if (close(fda[1]) < 0){
      printf("child: Can\'t close writing side of the second pipe\n");
      exit(-1);
    }
   
    printf("Child exit\n");
  }

  if (result > 0){
  	
    /* Parent process */

    if (close(fda[1]) < 0){
      printf("parent: Can\'t close writing side of the second pipe\n");
      exit(-1);
    }

    size = read(fda[0], resstringa, 7);

    if (size != 7) {
      printf("Can\'t read string from the second pipe\n");
      exit(-1);
    }

    printf("Parent read, %s\n", resstringa);

    if (close(fda[0]) < 0){
      printf("parent: Can\'t close reading side of the second pipe\n");
      exit(-1);
    }
    
    printf("Parent exit\n");
  }

  return 0;
}
