#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<strings.h>
#include<stdlib.h>

#define BUFFER_SIZE 1024


void main(){

    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key , BUFFER_SIZE , 0666);
    char * data = (char *) shmat(shmid , (void *) 0 , SHM_R);

    printf("\n Received data:\n%s",data);

    shmctl(shmid , IPC_RMID , NULL);
}