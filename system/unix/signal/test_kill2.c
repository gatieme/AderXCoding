/*************************************************************************
    > File Name: test_kill2.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年03月27日 星期日 11时23分06秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int i = 0;

    pid = fork(); // 创建进程
    if( pid < 0 )
    {   // 出错
        perror("fork");
    }

    if(pid == 0)
    {   // 子进程
        while(1)
        {
            printf("I am son\n");
            sleep(1);
        }
    }
    else if(pid > 0)
    {   // 父进程
        while(1)
        {
            printf("I am father\n");
            sleep(1);

            i++;
            if(3 == i)
            {   // 3秒后
                kill(pid, SIGINT);      // 给子进程 pid ，发送中断信号 SIGINT
                // kill(pid, 2);        // 等级于kill(pid, SIGINT);
            }
        }
    }

    return 0;
}



