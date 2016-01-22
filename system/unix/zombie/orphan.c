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

#include <sys/types.h>


/**
 *   在这个程序中
 *   我们先在程序FROK一个子进程
 *   然后父进程等待1S,
 *   等待子进程打印出自己的PID, 和父进程的PID
 *   随后父进程立马退出
 *
 *   然后子进程在打印出自己和父进程的PID后
 *   睡眠5S, 以保证父进程先退出
 *   此时子进程成为孤儿进程, 由init接管
 *   然后在自己苏醒之后, 再打印出自己的PID和父进程的PID
 *
**/

int main()
{
    pid_t pid;

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


        //  睡眠5s，保证父进程先退出
        printf("child  %d : I will sleep five seconds.\n", getpid());
        sleep(5);

        printf("pid =  %d, ppid = %d\n", getpid(), getppid());

        system("ps -o pid,ppid,state,tty,command");
        printf("child process is exited.\n");
        //exit(0);
    }
    else                //  FROK在父进程中返回子进程的pid
    {

        printf("parent %d : I am the parent process...\n", getpid());
        printf("parent %d : pid =  %d, ppid = %d\n", getpid(), getpid(), getppid());

        //  父进程睡眠1s，保证子进程输出进程id
        sleep(1);
        printf("father process is  exited.\n");

    }
    return 0;
}
