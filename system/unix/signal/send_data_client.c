#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc != 2){
        fprintf(stderr,"usage:%s pid\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    pid_t pid = atoi(argv[1]);    
    sleep(2);
    union sigval mysigval;
    mysigval.sival_int = 100;
    printf("sending SIGINT signal to %d......\n",pid);
    if(sigqueue(pid,SIGINT,mysigval) == -1){
        perror("sigqueue error");
        exit(EXIT_FAILURE);
    }
    return 0;
}