/*************************************************************************
    > File Name: kill.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年03月27日 星期日 11时07分40秒
 ************************************************************************/

///   父ls
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


int main(int argc, char *argv[])
{
    int pid;

    if((pid = fork()) < 0)              //  创建新的进程
    {

        perror("Fail to fork");
        exit(EXIT_FAILURE);

    }
    else if(pid == 0)                   //  子进程中返回0
    {

        while(1);

    }
    else                                //  父进程中返回子进程的pid
    {

        int signum;

        while(scanf("%d",&signum) == 1) //  用户输入带发送的信号
        {
            kill(pid, signum);          //  父进程向子进程发送信号
            system("ps -aux | grep ./test_kill1");
        }
    }

    return 0;
}
