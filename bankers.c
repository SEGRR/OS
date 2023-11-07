#include<stdio.h>


int np,nr;


void input_matrix(int mat[np][nr]){
    char c = 'A';
    printf("\t");
    for(int i = 0 ; i < nr ; i++)
    { 
        printf("%c ",c);
        c++;

    }   
    printf("\n");
    for(int i = 0 ; i< np ;i++){
        printf("[p%d]\t",(i+1));
        for(int j = 0 ; j< nr ; j++){
            scanf("%d",&mat[i][j]);
        }
    }

}

void print_matrix(int mat[np][nr]){
    char c = 'A';
    printf("\t");
    for(int i = 0 ; i < nr ; i++)
    { 
        printf("%c ",c);
        c++;

    }   
    printf("\n");
    for(int i = 0 ; i< np ;i++){
        printf("[p%d]\t",(i+1));
        for(int j = 0 ; j< nr ; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

}

void calc_need(int allocation[np][nr] , int need[np][nr] , int max[np][nr]){
    for(int i = 0 ;i < np ; i++){
        for(int j = 0 ; j< nr ; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void banker(int allocation[np][nr] , int need[np][nr] , int available[nr]){
    int finished[np], safe_sequence[np] , k =0;
    for(int i = 0 ; i< np ;i++) finished[i] = 0;

    for(int i = 0 ; i<np ; i++){

        if(!finished[i]){
            int flag = 0;

            for(int j = 0 ; j<nr ; j++){
                if(need[i][j] > available[j]){
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                for(int j = 0 ; j< nr ; j++) available[j] += allocation[i][j];
                safe_sequence[k] = i+1;
                k++;
                finished[i] = 1;
                i = -1;
            }
        }
    }
    int flag = 0;
    int i;
    for(i = 0 ; i< np ; i++){
        if(!finished[i]){
            flag = 1;
            break;
        }
    }

    if(flag ==1){
        printf("\nSystem is not in Safe Mode!");
    }
    else{
        printf("\nSYSTEM IS IN SAFE MODE!\nSAFE SEQUENCE : < ");
        for(int i = 0 ;i<np ; i++) printf("P%d ",safe_sequence[i]);
        printf(">");
    }
}


void main(){
    printf("Enter number of process: ");
    scanf("%d",&np);
    printf("Enter number of resources: ");
    scanf("%d",&nr);

    int allocation[np][nr] , need[np][nr] , max[np][nr];
    int available[nr];
    
    printf("Enter Process Allocation:\n");
    input_matrix(allocation);
    printf("Enter Max requirement:\n");
    input_matrix(max);
    printf("Enter available resources:\n");
    char c = 'A';
    for(int i = 0 ; i< nr ; i++){
        printf("[%c]: ",c);
        scanf("%d",&available[i]);
        c++;
    }

   
    calc_need(allocation , need , max);

    printf("\n NEED OF PROCESS:\n");
    print_matrix(need);

    banker(allocation , need , available);

    printf("\n\n\n");



}