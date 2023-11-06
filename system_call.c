#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>


void main(){

  pid_t child = fork();

  if(child == -1){
    perror("FORK : ");
    return;
  }

  if(child == 0){
     char *args[] = {"./hello" , NULL};
     execvp(args[0] , args);
  }
  else{
    return;
  int pid = (int)  wait(NULL);
   // printf("Parent-\n");
   // printf("child -%d",pid);        
  
  }


}