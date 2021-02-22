#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
  int     fd[2];
  long size = 0;
  int res = 0;
 
  /// Устанавливаем флаг O_NONBLOCK, который 
  /// не позволяет блокироваться записи при
  /// достижении конца pipe.
  if (pipe2(fd, O_NONBLOCK) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }


  while(1){
    /// Пытаемся записать 1 байт в pipe.	
    res = write(fd[1], "1", 1);
    /// Если байт не записался, то pipe - полон.
    if (res != 1){
      close(fd[0]);
      printf("Finally, %d\n", size);
      break;
    }
    /// Если байт записан, то увеличиваем размер.
    size++;
  }
	
  return 0;
}
