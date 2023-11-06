#include<stdio.h>

#include<unistd.h>
#include<string.h>

int main(char* argc[] , int argv){
    
    printf("Am I orphan = %d\n",getppid());
    
    char *drip[] = {" ps -elf | head -1; ps -elf | awk '{if ($5 == 1 && $3 != \"root\") {print $0}}' | head" , NULL};
    char *file = "/bin/ps";
    execvp(file , drip);
}