#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<semaphore.h>
#include<stdlib.h>

int n;
int p_at;
int c_at;
int iteration = 0;
sem_t empty , full;
pthread_mutex_t mutex;


void* producer(void * buffer){
  while(iteration < 20){
    sleep(3);
  sem_wait(&empty);    // wait till buffer has empty slot
  pthread_mutex_lock(&mutex) ; // acquire lock on buffer
  iteration++;
  int val = rand()%100;
  ((int*)buffer)[p_at] = val;
  printf("----- PRODUCER -----\n");
   for(int i = 0 ; i< n; i++){
      int val = ((int*)buffer)[i];
      if(val == -1) printf("[ ]--");
       else printf("[%d]--",val);
   }
  printf("\nProducerd value in buffer at: %d\n", p_at);
  int em , fu;
  sem_getvalue(&empty , &em);
  sem_getvalue(&full , &fu);
  printf("EMPTY = %d\tFULL = %d\n\n",em ,fu);
   p_at = (p_at + 1)%n;
  pthread_mutex_unlock(&mutex);
  sem_post(&full);
   sleep(3);
  }
}

void * consumer(void * buffer){
  while(iteration < 20){
    sleep(3); 
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    iteration++;
    int val = ((int*)buffer)[c_at] ;
    ((int*)buffer)[c_at]   = -1;

     printf("----- PRODUCER -----\n");
      for(int i = 0 ; i< n; i++){
      int val = ((int*)buffer)[i];
      if(val == -1) printf("[ ]--");
       else printf("[%d]--",val);
   }
   int em , fu;
   sem_getvalue(&empty , &em);
   sem_getvalue(&full , &fu);
   printf("\nConsumed %d at %d\n",val , c_at);
  printf("EMPTY = %d\tFULL = %d\n\n",em ,fu);

    c_at = (c_at + 1)%n;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    sleep(3);
  }
}


void main(){
   
    printf("Enter Size of Buffer: ");
    scanf("%d",&n);

    int BUFFER[n];

     for(int i = 0 ; i< n ;i++) BUFFER[i] = -1;

    p_at=0;
    c_at=0;
    int num_consumer , num_producers;

    printf("Enter number of producers:");
    scanf("%d",&num_producers);

    printf("Enter number of consumers:");
    scanf("%d",&num_consumer);
    
    sem_init(&empty , 0 , n);
    sem_init(&full , 0 , 0);
  if( pthread_mutex_init(&mutex,NULL) == -1){
    perror("MUTEXT INITIALIZATION :");
    return;
  }

    pthread_t producers[num_producers] , consumers[num_consumer];
    int greater = num_consumer?num_consumer>num_producers:num_producers;
    int arr [greater];

    for(int i = 1; i<=greater ; i++) arr[i-1] = i;
   
    for(int i = 0 ; i<num_producers ; i++)
    { 
        pthread_create(&producers[i] , NULL , producer ,(void*)BUFFER);
    }

     for(int i = 0 ; i<num_consumer ; i++)
    { 
        pthread_create(&consumers[i] , NULL , consumer , (void*)BUFFER);
       
    }

   

    for(int i = 0 ; i<num_producers ; i++){
      if(pthread_join(producers[i] , NULL) == -1){
         perror("cannot create producer thread:");
         return;
      }
    } 
    for(int i = 0 ; i<num_consumer ; i++){

    if(pthread_join(consumers[i] , NULL) == -1){
      perror("cannot create consumer thread: ");
      return;
    }
  } 


    for(int i = 0 ; i<num_consumer ; i++){
      pthread_detach(consumers[i]);
     
    }

      for(int i = 0 ; i<num_producers ; i++){
      pthread_detach(producers[i]);
     
    }




}