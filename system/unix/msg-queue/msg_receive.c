#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

#define MSG_KEY 1024

struct msg_st
{
    long int msg_type;
    char text[BUFSIZ];
};

int main()
{
    int running = 1;
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0; //注意1

    //建立消息队列
    //建立消息队列
    msgid=msgget(MSG_KEY, IPC_EXCL);  /*检查消息队列是否存在*/
    if(msgid < 0)
    {
        msgid = msgget(MSG_KEY, IPC_CREAT|0666);/*创建消息队列*/
        if(msgid < 0)
        {

            printf("failed to create msq, errno=%d : %s\n",errno,strerror(errno));
            exit(-1);
        }
        msgid = msgget((key_t)MSG_KEY, 0666 | IPC_CREAT);
        if(msgid == -1)
        {
            fprintf(stderr, "msgget failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    //从队列中获取消息，直到遇到end消息为止
    while(running)
    {
        if(msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0) == -1)
        {
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }

        printf("You wrote: %s\n", data.text);

       //遇到end结束
        if(strncmp(data.text, "end", 3) == 0)
        {
            running = 0;
        }
    }

    //删除消息队列
    if(msgctl(msgid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
