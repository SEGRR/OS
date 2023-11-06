#include<stdio.h>
#include<stdlib.h>

#define MAX_FRAME_SIZE 10
int n_frame  , n_pages;

void printPages(int page_string[]){
     printf("\n Given page string \n");
    printf("[ ");
     for(int i = 0 ; i< n_pages ;i++){
       printf("%d ",page_string[i]);
    }

    printf("]\n");
}

void printFrames(int frames[] , int res){
     for(int i = 0 ; i< n_frame ;i++){
       if(frames[i] != -1) printf("[%d] ",frames[i]);
       else printf("[ ] ");
    }
    if(res == 1){
        printf("| M");
    }
    else if(res == 0) printf("| H");

    printf("\n");
}

int find_lru(int frames[] , int page_string[] , int current_page){
     int lruIndex = 0;
    int minReference = n_pages;

    for (int i = 0; i < n_frame; i++) {
        int j;
        for (j = current_page -1 ; j>= 0; j--) {
            if (frames[i] == page_string[j]) {
                if(j < minReference){
                     minReference = j;
                     lruIndex = i;
                }
                break;
            }
        }
    }

    return lruIndex;
}

void calculate(int hit , int miss){
    printf("\nTOTAL PAGE FAULTS= %d\nTOTAL PAGE HITS= %d\n",miss ,hit);
    double hit_percent = (hit / n_pages) * 100;
    double miss_percent = (miss / n_pages) * 100;

 //   printf("\nTOTAL HIT= %lf\nTOTAL MISS= %lf",hit_percent , miss_percent);

}

int find_optimal(int frames[] , int page_string[] , int current_page){
    int optimal_index = -1;
    int max_ref = -1;

    for(int i = 0 ; i<n_frame ; i++){
        int j;
        for(j = current_page ; j<n_pages ; j++){
            if(frames[i] == page_string[j]){
              if(j > max_ref){

                optimal_index = i;
                max_ref = j;

              }

              break;
            }
        }

        if(j == n_pages) return i;
    }

    return optimal_index;

}


void optimal(int frames[] , int page_string[]){
     int frameindex= 0;
    int hit = 0 , miss =0;
    printPages(page_string);

    for(int i = 0 ;i < n_pages  ; i++){
        int page = page_string[i];
        int page_fault = 1;
        for(int j = 0 ; j < n_frame ; j++){
            if(frames[j] == page){
                page_fault = 0;
            }
        }

        if(page_fault){
            if(frameindex < n_frame){
                frames[frameindex] = page;
                frameindex++;
            }
            else{
                int lru_index = find_optimal(frames , page_string , i);
                frames[lru_index] = page;
            }
            miss++;
           printf("PAGE REFRENCE %d: " , page);
            printFrames(frames , page_fault);
        }
        else{
            hit++;
            printf("PAGE REFRENCE %d: " , page);
            printFrames(frames , page_fault);
        }

    }

    calculate(hit,miss);
}


void LRU(int frames[] , int page_string[]){
    int frameindex= 0;
    int hit = 0 , miss =0;
    printPages(page_string);

    for(int i = 0 ;i < n_pages  ; i++){
        int page = page_string[i];
        int page_fault = 1;
        for(int j = 0 ; j < n_frame ; j++){
            if(frames[j] == page){
                page_fault = 0;
            }
        }

        if(page_fault){
            if(frameindex < n_frame){
                frames[frameindex] = page;
                frameindex++;
            }
            else{
                int lru_index = find_optimal(frames , page_string , i);
                frames[lru_index] = page;
            }
            miss++;
           printf("PAGE REFRENCE %d: " , page);
            printFrames(frames , page_fault);
        }
        else{
            hit++;
            printf("PAGE REFRENCE %d: " , page);
            printFrames(frames , page_fault);
        }

    }

    calculate(hit,miss);
}

void init(int frames[]){
    for(int i = 0 ;i <n_frame ; i++) frames[i] = -1;
}



void main(){
    
    printf("Enter numbe of Frames :");
    scanf("%d",&n_frame);
    printf("Enter number of Pages: ");
    scanf("%d",&n_pages);

    int frames[n_frame];
    int page_string[n_pages];

    printf("Enter page-string:\n");
    for(int i = 0 ; i< n_pages ;i++){
        scanf("%d",&page_string[i]);
    }


   int a;
do{
   printf("1. LRU\n2. OPTIMAL\n3. EXIT\nEnter choice: ");
   scanf("%d",&a);

   switch (a)
   {
   case 1:
    init(frames);
    LRU(frames , page_string);
    break;
   case 2:
    init(frames);
   optimal(frames , page_string);
   case 3:
     
      printf("exiting");

   }
}while(a != 3);
  
}