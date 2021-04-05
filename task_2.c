#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;  // The variable a is global static for the entire program,
            // so it will be shared by both threads of execution.

/**
  Below follows the text of the function
  that will be associated with the 2nd thread.

  Parameter dummy is used only for type compatibility.
  For the same reason, the function returns void *.
**/
void *mythread(void *dummy)
{
  pthread_t mythid;
  //
  // Note that mythid variable is a dynamic local variable of mythread () function,
  // that is, it is pushed on the stack and, therefore, is not shared by the threads.
  //
  mythid = pthread_self();

  a = a+1;
  printf("Thread %u, Calculation result = %d\n", mythid, a);
  return NULL;
}

void *mysecondthread(void *dummy)
{
   pthread_t mysecondthid;

   mysecondthid = pthread_self();
   a = a * 10;
   printf("Thread %u, Calculation result = %d\n", mysecondthid, a);
   return NULL;
}

int main()
{
  pthread_t thid, mythid, secondthid;
  int       result;
 
  result = pthread_create (&thid, (pthread_attr_t *)NULL, mythread, NULL);

  if (result != 0) {
    printf ("Error on first thread create, return value = %d\n", result);
    exit(-1);
  }

  printf("First thread created, thid = %u\n", thid);

  result = pthread_create(&secondthid, (pthread_attr_t *)NULL, mysecondthread, NULL);
  if (result != 0){
    printf("Error on thread create, return value = %d\n", result);
    exit(-1);
  }
 
  printf("Second thread created, secondthid = %u\n", secondthid);

  mythid = pthread_self();

  a = a+1;

  printf("Thread %u, Calculation result = %d\n", mythid, a);
 
  pthread_join(thid, (void **)NULL);
  pthread_join(secondthid, (void **)NULL);

  return 0;
}
