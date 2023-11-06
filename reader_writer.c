#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int data = 0;
pthread_mutex_t count , mutex;
int readcount = 0;


void * reader(){
   while(1){
    pthread_mutex_lock(&count);
    readcount++;
    if(readcount == 1) pthread_mutex_lock(&mutex);
    pthread_mutex_unlock(&count);


    printf("Reading value ---> %d\n",data);

 pthread_mutex_lock(&count); 
     readcount--;
     if(readcount == 0) pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&count);
   sleep(3);
   }
}


void * writer(){
    while(1){
        pthread_mutex_lock(&mutex);

        data++;
        printf("Writing value --->%d\n",data);

        pthread_mutex_unlock(&mutex);
        sleep(3);
    }
}

void main(){
    int n = 2;
    if(pthread_mutex_init(&count , NULL) == -1 ||  pthread_mutex_init(&mutex ,NULL) == -1){
        perror("MUTEXT INIT ERROR:");
        return;
    }
    pthread_t readers[n] , writers[n];

    for(int i = 0; i< n ;i++){
        pthread_create(&readers[i] , NULL, reader , NULL);
        pthread_create(&writers[i] , NULL ,writer , NULL);
    }

     for(int i = 0; i< n ;i++){
        pthread_join(writers[i] ,NULL);
        sleep(3);
        pthread_join(readers[i], NULL);
    }


    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&count);
}