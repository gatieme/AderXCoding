/*************************************************************************
    > File Name: client.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年03月28日 星期一 23时35分29秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHMSZ 27

char SEM_NAME[]= "vik";

int main()
{
    char ch;
    int shmid;
    key_t key;
    char *shm,*s;
    sem_t *mutex;

    //name the shared memory segment
key = 1000;
//create & initialize existing semaphore
mutex = sem_open(SEM_NAME,0,0644,0);
if(mutex == SEM_FAILED)
{
perror("reader:unable to execute semaphore");
sem_close(mutex);
exit(-1);
}
//create the shared memory segment with this key
shmid = shmget(key,SHMSZ,0666);
if(shmid<0)
{
perror("reader:failure in shmget");
exit(-1);
}
//attach this segment to virtual memory
shm = shmat(shmid,NULL,0);
//start reading
s = shm;
for(s=shm;*s!=NULL;s++)
{
sem_wait(mutex);
putchar(*s);
sem_post(mutex);
}
//once done signal exiting of reader:This can be replaced by
another semaphore
*shm = '*';
sem_close(mutex);
shmctl(shmid, IPC_RMID, 0);
exit(0);
}
