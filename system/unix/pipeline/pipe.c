#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_DATA_LEN 256
#define DELAY_TIME 1

int main(void)
{
    pid_t       pid;
    char        buf[MAX_DATA_LEN];
    const char  *data="Pipe Test program";
    int         real_read, real_write;
    int         pipe_fd[2];

    memset((void*)buf, 0, sizeof(buf));

    if(pipe(pipe_fd) < 0)
    {
        perror("Pipe create error...\n");
        exit(1);
    }
    else
    {
        printf("Pipe create success...\n");
    }

    if ((pid = fork()) < 0)
    {
        perror("Fork error!\n");

        exit(1);
    }
    else if (pid == 0)
    {
        printf("I am the child process, PID = %d, PPID = %d", getpid(), getppid());

        close(pipe_fd[1]);
        sleep(DELAY_TIME * 3);

        if ((real_read=read(pipe_fd[0],buf, MAX_DATA_LEN)) > 0)
        {
            printf("Child receive %d bytes from pipe: '%s'.\n", real_read, buf);
        }

        close(pipe_fd[0]);

        exit(0);
    }
    else
    {
        printf("I am the parent process, PID = %d, PPID = %d", getpid(), getppid());

        close(pipe_fd[0]);
        sleep(DELAY_TIME);

        if ((real_write = write(pipe_fd[1], data, strlen(data))) > 0)
        {
            printf("Parent write %d bytes into pipe: '%s'.\n", real_write, data);
        }

        close(pipe_fd[1]);
        waitpid(pid,NULL,0);

        exit(0);
    }

    return EXIT_SUCCESS;
}
