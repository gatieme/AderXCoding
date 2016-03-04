// 李四.c
// http://blog.chinaunix.net/uid-27034868-id-3394243.html


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define FIFO_WRITE    "writefifo"   //另外一个程序只要把本程序
#define FIFO_READ    "readfifo"     //拷贝一份然后调换这两个宏即可

#define BUF_SIZE    1024

int left = 0;

void *read_buf ()
{
    int     rfd = -1;
    char    buf[BUF_SIZE] = { '\0' };
    int     i;

    printf("等待对方……\n");
    while ((rfd = open(FIFO_READ, O_RDONLY)) == -1)
    {
        sleep(1);
    }
    while (left != 1)
    {
        //printf("i=%d ",i++);
        int len = read(rfd, buf, BUF_SIZE);

        if (len > 0)
        {
            buf[len] = '\0';

            if(strcmp(buf,"不理你了") == 0){
                printf("\n对方已经走开!\n");
                left = 1;
                break;
            //    exit(0);
            }
            for(i = 0; i < strlen("我："); i++)
                printf("\b");

            printf("对方：%s\n", buf);
            printf("我：");
            fflush(stdout);
        }
    }

    close(rfd);
    return NULL;
}

void *write_to()
{
    int wfd;
    char buf[BUF_SIZE];
    int len;

    umask(0);

    if (mkfifo(FIFO_WRITE, S_IFIFO | 0666))
    {
        printf("Can't create FIFO %s because %s",
                FIFO_WRITE, strerror(errno));

        exit(1);
    }

    umask(0);

    wfd = open(FIFO_WRITE, O_WRONLY);
    if (wfd == -1)
    {
        printf("open FIFO %s error: %s",
                FIFO_WRITE, strerror(errno));
        exit(1);
    }

    while (left != 1)
    {
        printf("我: ");

        fgets(buf, BUF_SIZE, stdin);
        buf[strlen(buf) - 1] = '\0';

        if (strcmp(buf, "不理你了") == 0 || left == 1)
        {
            write(wfd, buf, strlen(buf));//通知对方
            close(wfd);
            unlink(FIFO_WRITE);
            exit(0);
        }
        write(wfd, buf, strlen(buf));
        fflush(stdin);
    }
}

int main(int argc, char *argv[])
{
    pthread_t thIDr, thIDw;

    pthread_create(&thIDr, NULL,(void *)read_buf, NULL);
    pthread_create(&thIDw, NULL,(void *)write_to, NULL);

    pthread_join(thIDr, NULL);
    pthread_join(thIDw, NULL);

    return 0;
}
