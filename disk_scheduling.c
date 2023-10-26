#include<stdio.h>
#include<stdlib.h>

#define MAX_TRACK 199
#define MIN_TRACK 0


void fcfs(int positions[] , int n , int current_head){
    int total_seek = 0;
     printf("%d ",current_head);
    for(int i =0 ;i <n ; i++){
        total_seek += abs(current_head - positions[i]);
        printf("--> %d",positions[i]);
        current_head = positions[i];
    }

    printf("\nTotal seek distance = %d" , total_seek);
}

void sstf(int positions[] , int n , int current_head){

    int visited[n];

      for(int i = 0; i<n ; i++) visited[i] = 0;

     int total_seek = 0;
     printf("%d ",current_head);
    for(int i =0 ;i <n ; i++){

    

       for(int i = 0 ; i< n ; i++){
      int nearest_track = -1;
      int current_distance = __INT_MAX__;
        for(int j = 0 ; j < n;  j++){
         if(!visited[j] && (abs(current_head - positions[j]) < current_distance)){
             nearest_track = j;
             current_distance = abs(current_head - positions[j]);
            
         }

        }
        if(nearest_track == -1) break;

        visited[nearest_track] = 1;
        total_seek += current_distance;
        current_head = positions[nearest_track];
         printf("--> %d",positions[nearest_track]);
       }
    }

    printf("\nTotal seek time = %d", total_seek);
}


int calc_seek(int arr[] , int n , int *head){
      int seek = 0 ; 
       printf("%d ", *head);
      for(int i = 0 ; i<n ; i++){
        if(arr[i] == -1) continue;
        seek += abs(arr[i] - *head);
        printf("--> %d",arr[i]);
        *head = arr[i];
      }

  return seek;
}


void scan(int positions[] , int n , int current_head){
    int sequence[n];
    for(int i = 0; i<n ; i++) sequence[i] = -1;
    int nearest_smaller = 0;
    int nearest_greater = 199;
    int total_seek = 0;
    for(int i = 0 ; i<n; i++){
        if(positions[i] > nearest_smaller && positions[i] < current_head){
            nearest_smaller = positions[i];
        }
    }

    for(int i = 0 ; i<n ; i++){
        if(positions[i] > current_head && positions[i] <= nearest_greater ){
            nearest_greater = positions[i];
        }
    }


    int direction = abs(nearest_greater - current_head) < abs(nearest_smaller - current_head) ? 1 : 0;

    if(direction){
        // right side
        for(int i = 0 ; i< n ; i++){
            if(positions[i] >= current_head){
                 sequence[i] = positions[i];
                 positions[i] = -1;
            
            }
        }
         total_seek += calc_seek(sequence , n , &current_head) + (abs(current_head - MAX_TRACK));
         
        total_seek += calc_seek(positions , n ,&current_head);
    }
    else{
          // left side
        for(int i = 0 ; i< n ; i++){
            if(positions[i] <= current_head){
                 sequence[i] = positions[i];
                 positions[i] = -1;
            
            }
        }
         total_seek += calc_seek(sequence , n , &current_head) + (abs(current_head - MIN_TRACK));
         total_seek += calc_seek(positions , n , &current_head);
    }

    printf("\nTotal seek distance = %d" , total_seek);

}


void clook(int positions[] , int n , int current_head){
  int sequence[n];
    for(int i = 0; i<n ; i++) sequence[i] = -1;
    int nearest_smaller = 0;
    int nearest_greater = 199;
    int total_seek = 0;
    for(int i = 0 ; i<n ; i++){
        if(positions[i] > nearest_smaller && positions[i] < current_head){
            nearest_smaller = positions[i];
        }
    }

    for(int i = 0 ; i<n ; i++){
        if(positions[i] > current_head && positions[i] <= nearest_greater ){
            nearest_greater = positions[i];
        }
    }

    int direction = abs(nearest_greater - current_head) < abs(nearest_smaller - current_head) ? 1 : 0;

    if(direction){
        // right side
        for(int i = 0 ; i< n ; i++){
            if(positions[i] >= current_head){
                 sequence[i] = positions[i];
                 positions[i] = -1;
            
            }
        }
         total_seek += calc_seek(sequence , n , &current_head);
        total_seek += calc_seek(positions , n , &current_head);
    }
    else{
          // left side
        for(int i = 0 ; i< n ; i++){
            if(positions[i] <= current_head){
                 sequence[i] = positions[i];
                 positions[i] = -1;
            
            }
        }
         total_seek += calc_seek(sequence , n , &current_head);
         total_seek += calc_seek(positions , n , &current_head);
    }

    printf("\nTotal seek distance = %d" , total_seek);   
}



void main(){
    int n = 8;
 int arr[] = {176, 79, 34, 60, 92, 11, 41, 114};
    int head = 50;
    
    printf("Initial head position is %d\n", head);

    fcfs(arr , n , head);
    printf("\n");
    sstf(arr, n , head);
    printf("\n");
    scan(arr , n , head);
    printf("\n");
    clook(arr , n ,head);

}