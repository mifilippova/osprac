#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
  char     *array;    // Pointer to shared memory
  int     shmid;     // IPC descriptor for the shared memory
  char    pathname[] = "07-1.c"; // The file name used to generate the key.
                                 // A file with this name must exist in the current directory.
  char *data;

  key_t   key;       // IPC key
  //
  // Generate an IPC key from the file name 06-1a.c in the current directory
  // and the instance number of the shared memory 0.
  //
  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }
  
  if ((shmid = shmget(key, 10*sizeof(char), 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-1);
      }

  //
  // Try to map shared memory to the address space of the current process.
  // Note that for proper comparison we explicitly convert the value -1 to a pointer to an integer.
  //
  if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)("a")) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }
  //
  // Depending on the value of the flag,
  // we either initialize the array or increment the corresponding counters.
  //
  
  data = array;

  printf ("Program 2 has read '%s' from shared memory.\n", data);

  if (shmdt(array) < 0) {
    printf("Can't detach shared memory.\n");
    exit(-1);
  }

  if (shmctl(shmid, IPC_RMID, 0) < 0){
    printf("Failed at deleteing shared memory.\n");
    exit(-1);
  }
  

  return 0;
}
