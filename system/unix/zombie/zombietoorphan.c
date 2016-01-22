/*************************************************************************
    > File Name: zombietoorphan.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2015年12月10日 星期四 22时49分02秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>

/**
 * 如果一个进程要frok一个子进程，但不要求它等待
 * 子进程终止，也不希望子进程处于僵死状态直到父进程终止，
 * 实现这一要求的诀窍是调用fork两次
 **/
int main()
{
    pid_t  pid;

    if((pid = fork( )) < 0)        // 父进程中创建子进程
    {
        perror("fork error:");
        exit(-1);
    }
    else if(pid == 0)          //  第一个子进程中
    {
        printf("first child  %d : pid = %d, ppid = %d\n",getpid( ), getpid( ),getppid( ));

        /**
         *  在子进程中
         *  我们再次fork产生第二个子进程
         *  然后第二个子进程在等待其父进程(第一个子进程)退出后再退出
         *  这样第二个子进程成为孤儿进程, 由init接管它
         **/
        if((pid = fork( )) < 0)    //  子进程中再创建子进程
        {
            perror("fork error:");
            exit(-1);
        }
        else if(pid > 0)        //  第一个子进程直接退出
        {
            printf("first child %d : is exited.\n", getpid( ));
            exit(0);
        }
        else                    //  第二子进程在其父进程第一个子进程退出后再退出
        {
            printf("second child %d : pid = %d, ppid = %d\n", getpid( ), getpid( ), getppid( ));
            printf("second child %d : I will sleep 3 second...\n", getpid());

            //  睡眠3s保证第一个子进程退出，这样第二个子进程的父亲就是init进程里
            sleep(3);

            ////////////////////////////////////////////////////////////////////
            //
            // 第二个进程才是我们真正创建出来期望工作的进程
            //
            ////////////////////////////////////////////////////////////////////
            printf("\nsecond child %d : pid = %d, ppid = %d\n\n", getpid( ), getpid( ), getppid( ));
            system("ps -o pid,ppid,state,tty,command");
            exit(0);
        }
    }

    //父进程处理第一个子进程退出
    if (waitpid(pid, NULL, 0) != pid)
    {
        perror("waitepid error:");
        exit(1);
    }
    exit(0);
    return 0;
}


