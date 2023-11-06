#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define MAX_LEN 10000

void print_tracks(int tracks[] , int request){

    printf("\nGIVEN TRACKS\n[ ");
    for(int i = 0 ; i<request ; i++){
        printf("%d ",tracks[i]);

    }
    printf("]\n");

}

void sort(int tracks[] , int n_rq){
    for(int i = 0 ; i < n_rq ; i++){
        for(int j = 0 ;  j < n_rq-1 ; j++){
            if(tracks[j] > tracks[j+1]){
                int temp = tracks[j];
                tracks[j] = tracks[j+1];
                tracks[j+1] = temp;
            }
        }
    }
}

void fcfs(int tracks[] , int init_position , int requests){
    int head = init_position , seek_time =0;

    print_tracks(tracks , requests);
    printf("FCFS: [%d] ---> ",head);
    for(int i = 0 ;i<requests ;i++){
        seek_time += abs(head - tracks[i]);
        head = tracks[i];
        printf("[%d] ---> ",head);
    }

    printf("\nTOTAL SEEK TIME = %d\n\n",seek_time);

}

int copy_tracks(int cp[] , int tracks[] , int n_rq){
    for(int i = 0 ; i< n_rq ; i++){
        cp[i] = tracks[i];
    }
}

void sstf(int tracks[] , int init , int n_rq){
    int head = init , seek_time = 0;
    int count = 0;
    int cp[n_rq];

     copy_tracks(cp , tracks , n_rq);
     print_tracks(cp , n_rq);
     printf("SSTF: [%d] ---> ",head);
    while(count < n_rq){
        int min = MAX_LEN;
        int index = -1;
        for(int i = 0 ; i<n_rq ; i++){
            if(abs(head - cp[i]) < min){
                min = abs(head - cp[i]);
                index = i;
            }
        }

        if(index != -1){
            seek_time += abs(head - cp[index]);
            head = cp[index];
            cp[index] = MAX_LEN;
            count++;
            printf("%d ---> ",head);
        }

    }
    printf("\nTOTAL SEEK TIME = %d\n",seek_time);
}


void scan(int tracks[] , int init , int n_rq){
    int last_sector;
    printf("Enter Last Sector: ");
    scanf("%d",&last_sector);
    int head = init , seek_time = 0;
    int  cp[n_rq];
    int direction = tracks[0] > head?1:0;    // right = 1 ,left = 0 

    copy_tracks(cp , tracks , n_rq);
    sort(cp , n_rq);
    int index = 0;

    for(int i = 0; i<n_rq ; i++){ 
        if(head < cp[i]){ index = i ; break;}
    }
     print_tracks(cp , n_rq);

     printf("SCAN: [%d] ---> ",head);
    if(direction ==1){
        // scan in right direction
        for(int i = index ; i<n_rq ; i++){
            seek_time += abs(head - cp[i]);
            head = cp[i];
            printf("%d -->",head);
        }

        seek_time += abs(head - last_sector);
        head = last_sector;
         printf("[%d] -->",head);

        for(int i = index -1 ; i>=0; i--){
            seek_time += abs(head - cp[i]);
            head = cp[i];
             printf("%d -->",head);
        }
    }
    else{
          for(int i = index ; i>=0; i--){
            seek_time += abs(head - cp[i]);
            head = cp[i];
             printf("%d -->",head);
        }

        seek_time += abs(head - 0);
        head = 0;
         printf("[%d] -->",head);

        for(int i = index+1 ; i<n_rq ; i++){
            seek_time += abs(head - cp[i]);
            head = cp[i];
            printf("%d -->",head);
        }


    }

    printf("\nTOTAL SEEK TIME = %d\n",seek_time);
}

void c_scan(int tracks[] ,int init , int n_rq){
    int last_sector;
    printf("Enter Last Sector: ");
    scanf("%d",&last_sector);
    int head = init , seek_time = 0;
    int  cp[n_rq];
    int direction = tracks[0] > head?1:0;    // right = 1 ,left = 0 

    copy_tracks(cp , tracks , n_rq);
    sort(cp , n_rq);
    int index = 0;

    for(int i = 0; i<n_rq ; i++){ 
        if(head < cp[i]){ index = i ; break;}
    }
     print_tracks(cp , n_rq);

     printf("C-SCAN: [%d] ---> ",head);
    if(direction ==1){
        // scan in right direction
        for(int i = index ; i<n_rq ; i++){
            seek_time += abs(head - cp[i]);
            head = cp[i];
            printf("%d -->",head);
        }

        seek_time += abs(head - last_sector);
        head = last_sector;
         printf("[%d] -->",head);

         seek_time += last_sector;
         head = 0;
         printf("[%d] ---> ",head);

        for(int i = 0 ; i<index; i++){
            seek_time += abs(head - cp[i]);
            head = cp[i];
             printf("%d -->",head);
        }
    }
    else{
          for(int i = index ; i>=0; i--){
            seek_time += abs(head - cp[i]);
            head = cp[i];
             printf("%d -->",head);
        }

        seek_time += abs(head - 0);
        head = 0;
         printf("[%d] -->",head);
        
        seek_time += last_sector;
        head = last_sector;

        printf("[%d] --->",head);

        for(int i = n_rq-1 ; i>index ; i--){
            seek_time += abs(head - cp[i]);
            head = cp[i];
            printf("%d -->",head);
        }


    }

    printf("\nTOTAL SEEK TIME = %d\n",seek_time);
}


void look(int tracks[] , int init , int n_rq){

    int head = init , seek_time = 0;
    int  cp[n_rq];
    int direction = tracks[0] > head?1:0;    // right = 1 ,left = 0 

    copy_tracks(cp , tracks , n_rq);
    sort(cp , n_rq);
    int index = 0;

    for(int i = 0; i<n_rq ; i++){ 
        if(head < cp[i]){ index = i ; break;}
    }
     print_tracks(tracks , n_rq);

     printf("SCAN: [%d] ---> ",head);
    if(direction ==1){
        // scan in right direction
        for(int i = index ; i<n_rq ; i++){
            seek_time += abs(head - cp[i]);
            head = cp[i];
            printf("%d -->",head);
        }

        for(int i = index -1 ; i>=0; i--){
            seek_time += abs(head - cp[i]);
            head = cp[i];
             printf("%d -->",head);
        }
    }
    else{
          for(int i = index ; i>=0; i--){
            seek_time += abs(head - cp[i]);
            head = cp[i];
             printf("%d -->",head);
        }

        for(int i = index+1 ; i<n_rq ; i++){
            seek_time += abs(head - cp[i]);
            head = cp[i];
            printf("%d -->",head);
        }

    }

    printf("\nTOTAL SEEK TIME = %d\n",seek_time);
}

void c_look(int tracks[] ,int init , int n_rq){

    int head = init , seek_time = 0;
    int  cp[n_rq];
    int direction = tracks[0] > head?1:0;    // right = 1 ,left = 0 

    copy_tracks(cp , tracks , n_rq);
    sort(cp , n_rq);
    int index = 0;

    for(int i = 0; i<n_rq ; i++){ 
        if(head < cp[i]){ index = i ; break;}
    }
     print_tracks(cp , n_rq);

     printf("C-LOOK: [%d] ---> ",head);
    if(direction ==1){
        // scan in right direction
        for(int i = index ; i<n_rq ; i++){
            seek_time += abs(head - cp[i]);
            head = cp[i];
            printf("%d -->",head);
        }

        for(int i = 0 ; i<index; i++){
            seek_time += abs(head - cp[i]);
            head = cp[i];
             printf("%d -->",head);
        }
    }
    else{
          for(int i = index ; i>=0; i--){
            seek_time += abs(head - cp[i]);
            head = cp[i];
             printf("%d -->",head);
        }

        for(int i = n_rq-1 ; i>index ; i--){
            seek_time += abs(head - cp[i]);
            head = cp[i];
            printf("%d -->",head);
        }


    }

    printf("\nTOTAL SEEK TIME = %d\n",seek_time);
}



void main(){

    int requests;

    printf("Enter number of requests: ");
    scanf("%d",&requests);

    int tracks[requests] , init_position;

    printf("Enter Tracks:\n");
    for(int i = 0; i<requests ; i++) scanf("%d",&tracks[i]);
    
    printf("Enter Initial Head position: ");
    scanf("%d",&init_position);

    int a;

    do{
       printf("1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. LOOK\n6. C-LOOK\n7.EXIT\nEnter choice: ");
       scanf("%d",&a);

       switch (a)
       {
       case 1:
        fcfs(tracks ,init_position,requests);
        break;
       case 2:
         sstf(tracks , init_position , requests);
         break;
        case 3:
        scan(tracks ,init_position , requests);
        break;
        case 4:
        c_scan(tracks , init_position , requests);
        break;
        case 5:
        look(tracks ,init_position , requests);
        break;
        case 6:
        c_look(tracks , init_position ,requests);
        break;
       case 7:
       printf("EXITING\n");
       default:
        break;
       }
    }while(a != 7);
    

}