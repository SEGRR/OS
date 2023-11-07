#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    int pid;
    int wt;
    int bt;
    int tat;
    int at;
} Process;


void printtable(Process ready_queue[] , int n){

    double avg_wt = 0; 
    double avg_tat = 0;

    for(int i = 0 ; i< n; i++){
        avg_tat += ready_queue[i].tat;
        avg_wt  += ready_queue[i].wt;
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nPid\tBT\tWT\tTAT\n");

    for(int i = 0 ; i < n ;i++){
        Process p = ready_queue[i];
        printf("%d\t%d\t%d\t%d\n",p.pid,p.bt,p.wt,p.tat);
    }

    printf("Average Waiting Time = %lf\nAverage Turn around Time = %lf",avg_wt ,avg_tat);

}

void swap(Process *p1 , Process *p2){
    Process p3 = *p2;
    *p2 = *p1;
    *p1 = p3;
}

void sort(Process ready_queue[] , int n){

    for(int i = 0 ; i< n ;i++){
        for(int j =0 ; j<n-1 ; j++){
            if(ready_queue[j].bt > ready_queue[j+1].bt){
               Process temp = ready_queue[j];
               ready_queue[j] = ready_queue[j+1];
               ready_queue[j+1] = temp;
            }
        }
    }

}



void srtf(Process ready_queue[] , int n){

   int rt[n];

    for(int i = 0 ; i< n ;i++) rt[i] = ready_queue[i].bt;
    int time =0;
    int count=0;
     int last_process = -1;
     int minimum = __INT_MAX__;
     int check = 0;

    while(count < n){
       int current_process = last_process;
       //select process with minimumn Remaining time 
       for(int i = 0 ; i< n ; i++){
         Process p = ready_queue[i];
         if( p.at <= time && rt[i] > 0  &&  rt[i] < minimum){
            current_process = i;
            minimum = rt[i];
            check = 1;
         }
       }

       
       if(!check){
         time++;
         printf("-----");
         continue;
       }

       if(current_process != last_process){
         printf("|%d|",time);
         printf("-- P%d --",ready_queue[current_process].pid);
       }

       last_process = current_process;


       rt[current_process]--;
       time++;
       minimum = rt[current_process];
       if (minimum == 0) 
           minimum = __INT_MAX__; 
     

       if(rt[current_process] == 0){

         ready_queue[current_process].tat = time - ready_queue[current_process].at;
         ready_queue[current_process].wt =  ready_queue[current_process].tat - ready_queue[current_process].bt;
         count++;
         printf("|%d|",time);

       }

    }

    printtable(ready_queue , n);
}

void rr(Process ready_queue[] ,int n , int tq ){

  // sort by arrival time
   for(int i = 0 ; i< n ;i++){
        for(int j =0 ; j<n-1 ; j++){
            if(ready_queue[j].at > ready_queue[j+1].at){
               Process temp = ready_queue[j];
               ready_queue[j] = ready_queue[j+1];
               ready_queue[j+1] = temp;
            }
        }
    }

    int rt[n];
    int queue[n*n];
    for(int i = 0; i<n*n ; i++){
        queue[i] = -1;
    }
    for(int i = 0 ; i< n ;i++) rt[i] = ready_queue[i].bt;

    int time = 0;
    int count = 0;
    int i = 0;

    if(ready_queue[0].at > 0){
        printf("|0|----");
        time = ready_queue[0].at;
       
    }
  
    while(count < n){

     if(rt[i] > 0 && ready_queue[i].at <= time){
        Process *p = &ready_queue[i];

        printf("|%d|-- P%d --",time,p->pid);
            if(rt[i] < tq){

              time += rt[i];
              rt[i] = 0;

              count++;
              p->tat = time - p->at;
              p->wt = p->tat - p->bt;

            }
            else{
                rt[i] -= tq;
                time += tq;

                if(rt[i] <= 0){
                    count++;
                 p->tat = time - p->at;
                p->wt = p->tat - p->bt;
                }
               

            }


     }

     i = (i +1)%n;
     
    }
     printf("|%d|",time);

    printtable(ready_queue , n);

}

void sjf(Process ready_queue[] , int n){

    for(int i = 0 ; i < n ;i++){
        for(int j = 0 ; j < n- i -1 ; j++){
            if(ready_queue[j].bt < ready_queue[j++].bt){
               // swap(&ready_queue[j] , &ready_queue[j++]);
               printf("swapped\n");
               Process temp = ready_queue[j];
               ready_queue[j] = ready_queue[j++];
               ready_queue[j++] = temp;
            }
        }
    }

    int time = 0;
    for(int i = 0 ; i< n ; i++){
        printf("|%d|",time);
        Process *p1 = &ready_queue[i];
        printf("-- P%d --" ,p1->pid);
        p1->wt = time;
        time += p1->bt;
        p1->tat = time + p1->wt;
      
    }
    printf("|%d|",time);
   

 printtable(ready_queue , n);

}

void fcfs(Process ready_queue[] , int n){

   
    int time = 0;
    for(int i = 0 ; i< n ; i++){
        printf("|%d|",time);
        Process *p1 = &ready_queue[i];
        printf("-- P%d --" ,p1->pid);
        p1->wt = time;
        time += p1->bt;
        p1->tat = time + p1->wt;
    }
    printf("|%d|",time);
   

  printtable(ready_queue , n );
}



void main(){
   int n;
   printf("Enter number of process: ");
   scanf("%d",&n);
   Process ready_queue[n];
   printf("\nEnter process information -> pid  burst time\n");
   for (int i = 0; i < n; i++)
   {
     Process p;
    scanf("%d %d %d",&p.pid , &p.bt , &p.at);
    p.wt=0;
    p.tat =0;
    ready_queue[i] = p;
   }
  int tq;
  printf("Enter time quantum: ");
  scanf("%d",&tq);
   //fcfs(ready_queue , n);
  // printf("\nSJF\n");
 // sjf(ready_queue,n);
//srtf(ready_queue , n);

 rr(ready_queue , n , tq);
   
}