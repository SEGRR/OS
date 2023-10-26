#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<string.h>
#include<stdlib.h>


#define BUFFER_SIZE 1024



void main(){
   key_t key;
   int shmid;
   char* data;

   key = ftok("shmfile" , 65);
   printf("key= %d", key);
   shmid = shmget(key , BUFFER_SIZE , 0666 | IPC_CREAT);
   if(shmid == -1) {
    perror("shmget");
    return;
   }


   data = (char *) shmat(shmid , (void *)0 , SHM_R);

   if(data == (char *)(-1)){
    perror("shmat");
    return;
   }

   printf("Enter what to send");
   char msg[BUFFER_SIZE];
   scanf("%s",msg);
    strncpy(data , msg , BUFFER_SIZE);
   printf("\n%s",msg);
    printf("\nMessage Sent");

    shmdt(data);
}