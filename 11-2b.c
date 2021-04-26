#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
  int msqid;
  char pathname[]="11-2a.c";
  key_t  key;
  int len, maxlen;
  int i = 0;

  struct mymsgbuf 
  {
    long mtype;
    struct{
	short day;
        float degrees;
    } info;
  } mybuf;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t get msqid\n");
    exit(-1);
  }

  while (i < 30) {
    maxlen = sizeof(mybuf.info);

    if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0)) < 0) {
      printf("Can\'t receive message from queue\n");
      exit(-1);
    }
   

    printf("second program message type = %ld, info = %d : %4.2f\n", mybuf.mtype, mybuf.info.day, mybuf.info.degrees);

    mybuf.mtype = 2;
    mybuf.info.day = i;
    mybuf.info.degrees = i * 0.5;
    len = sizeof(mybuf.info);

    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
      printf("Can\'t send message to queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
      exit(-1);
    }
    
    i++;

  }

  return 0;
}
