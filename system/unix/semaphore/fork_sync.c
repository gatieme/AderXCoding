/*************************************************************************
    > File Name: 1.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年03月28日 星期一 23时20分06秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


#include <semaphore.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char **argv)
{
    int     fd, i;
    int     nloop = 10, zero = 0;
    int     *ptr;
    sem_t   mutex;

    //  open a file and map it into memory
    fd = open("log.txt", O_RDWR | O_CREAT, S_IRWXU);

    write(fd,&zero,sizeof(int));

    ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    close(fd);

    /* create, initialize semaphore */
    if(sem_init(&mutex, 1, 1) < 0) //
    {
        perror("semaphore initilization");
        exit(0);
    }

    if (fork() == 0)
    {   /* child process*/
        for (i = 0; i < nloop; i++)
        {
            sem_wait(&mutex);

            printf("child: %d\n", (*ptr)++);
            //sleep(1);
            sem_post(&mutex);
        }
        exit(0);
    }


    /* back to parent process */
    for (i = 0; i < nloop; i++)
    {
        sem_wait(&mutex);

        printf("parent: %d\n", (*ptr)++);
        //sleep(1);
        sem_post(&mutex);
    }
    exit(0);
}
