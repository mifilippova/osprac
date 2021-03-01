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
  char data[] = "Some data";

  key_t   key;       // IPC key
  //
  // Generate an IPC key from the file name 07-1.c in the current directory
  // and the instance number of the shared memory 0.
  //
  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }
  //
  // Trying to create a shared memory exclusively for the generated key, that is,
  // if it already exists for this key, the system call will return a negative value.
  // The memory size is defined as the size of an array of three integer variables,
  // access rights 0666 - reading and writing are allowed for everyone.
  //
  if ((shmid = shmget(key, 10*sizeof(char), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
    //
    // In case of an error, try to determine: whether it arose due to the fact
    // that the shared memory segment already exists or for some other reason.
    //
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    } 
  }
  //
  // Try to map shared memory to the address space of the current process.
  //
  if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)("a")) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }
   
  // Write data into shared memory.
  int i;
  for(i = 0; i < 10; i++){
    array[i] = data[i];
  }

  printf ("Program 1 has written '%s' into shared memory.\n", array);

  if (shmdt(array) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }

  return 0;
}
