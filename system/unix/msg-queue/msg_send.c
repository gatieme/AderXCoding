
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define MSG_KEY 1024
#define MAX_TEXT 512
struct msg_st
{
	long int msg_type;
	char text[MAX_TEXT];
};

int main()
{
	int running = 1;
	struct msg_st data;
	char buffer[BUFSIZ];
	int msgid = -1;

	//建立消息队列
    msgid = msgget(MSG_KEY, IPC_EXCL);  /*检查消息队列是否存在*/
    if(msgid < 0)
    {
        msgid = msgget((key_t)MSG_KEY, IPC_CREAT|0666);/*创建消息队列*/
        if(msgid < 0)
        {

            printf("failed to create msq, errno=%d : %s\n",errno,strerror(errno));
            exit(-1);
        }
    }

	//向消息队列中写消息，直到写入end
	while(running)
	{
		//输入数据
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);

        data.msg_type = 1;    //注意2

        strcpy(data.text, buffer);
		//向队列发送数据
		if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)
		{
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
		//输入end结束输入
		if(strncmp(buffer, "end", 3) == 0)
			running = 0;
		sleep(1);
	}


    return EXIT_SUCCESS;
}
