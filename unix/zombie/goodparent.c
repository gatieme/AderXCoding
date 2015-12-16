/*************************************************************************
    > File Name: zombie1.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2015年12月10日 星期四 19时45分16秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include <sys/wait.h>
#include <sys/types.h>




void signal_child(int signo)
{
     pid_t          pid;
     int            state;

     //处理僵尸进程
     while((pid = waitpid(-1, &state, WNOHANG)) > 0)
     {
         printf("\n==child %d terminated.==\n\n", pid);
     }
     return ;
}

/**
 *   在这个程序中
 *   父进程每隔5s就将产生一个僵尸进程
**/
int main()
{
    pid_t pid;


    signal(SIGCHLD, signal_child);
    while( 1 )
    {
        //创建一个进程
        pid = fork();

        if(pid < 0)   //  FROK创建进程失败时返回-1
        {
            printf("fork error errno = %d:%s", errno , strerror(errno));
            exit(1);
        }
        else if(pid == 0)      //  FROK在子进程中返回0
        {
            printf("child  %d : I am the child process...\n", getpid( ));

            //  输出子进程ID和父进程ID
            printf("child  %d : pid =  %d, ppid = %d\n", getpid(), getpid(), getppid());

            printf("child  %d :process is exited [not zombie]....\n\n", getpid());

            //  注意子进程需要退出exit
            //  要不然会子进程也进入循环疯狂的创建子进程
            exit(0);
        }
        else                //  FROK在父进程中返回子进程的pid
        {

            printf("parent %d : I am the parent process...\n", getpid());
            printf("parent %d : pid =  %d, ppid = %d\n", getpid(), getpid(), getppid());

            //  父进程睡眠5s，保证子进程退出
            printf("parent %d : I will sleep 5 seconds...\n\n", getpid());
            sleep(5);

            system("ps -o pid,ppid,state,tty,command");

        }
    }
    return 0;
}
