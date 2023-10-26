#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>

#define BUFFER_SIZE 1024
#define FIFO1 "/tmp/my_fifo1"
#define FIFO2 "/tmp/my_fifo2"

void main(){
    
    remove(FIFO1);
    remove(FIFO2);

    if(mkfifo(FIFO1 , 0666) == -1 || mkfifo(FIFO2 , 0666)){
        perror("Cannot create Pipes");
        return;
    }


   pid_t child ;
   child= fork();


    if(child < 0){
        perror("Cannot create child process");
        return;
    }

    if(child == 0){
        int read_fd = open(FIFO1 , O_RDONLY);
        char read_buffer[BUFFER_SIZE];

        read(read_fd,read_buffer,sizeof(read_buffer));
        close(read_fd);

        printf("CHILD PROCESS\nData received\n\%s",read_buffer);

       int length = strlen(read_buffer);

      int word_count = 0 , line_count=0 , char_count = length;

    //   for(int i = 0 ; i< length ; i++){

    //     if(read_buffer[i] == ' ') word_count++;
    //     if(read_buffer[i] == '\n'){
    //         line_count++;
    //         word_count++;
    //     }
    //   }
        //for final word
        if(length >0) word_count++;
        char output_buffer[BUFFER_SIZE];
        snprintf(output_buffer , sizeof(output_buffer) , "total character = %d\ntotal words = %d\n total lines = %d" ,char_count , word_count , line_count);
        int write_fd = open(FIFO2 , O_WRONLY);
        write(write_fd , output_buffer , strlen(output_buffer) + 1);

        close(write_fd);

    }
    else{

        int w_fd = open(FIFO1 , O_WRONLY);

        printf("Enter a sentance:");
        char buffer[BUFFER_SIZE];

        fgets(buffer , sizeof(buffer) , stdin);

        write(w_fd , buffer , strlen(buffer)+1);
        close(w_fd);
       // wait(NULL);

       int r_fd = open(FIFO2 , O_RDONLY);
       char r_buffer[BUFFER_SIZE];

       read(r_fd , r_buffer , sizeof(r_buffer));
       close(r_fd);

       printf("PARENT PROCESS:\noutput from child\n%s", r_buffer);

    }


    unlink(FIFO1);
    unlink(FIFO2);

}