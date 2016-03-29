#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MAX_ATTACH_NUM 15

int main(int argc, char* argv[])
{
    key_t       mem_key;
    long        mem_id;
    void*       mem_addr[MAX_ATTACH_NUM];
    int         i;

    if ((mem_key = ftok("./mykeyfile", 1)) == (key_t)(-1))
    {
            printf("Failed to generate shared memory access key"
                   ", ERRNO = %d : %s\n", errno, strerror(errno));

            shmctl(mem_id, IPC_RMID, NULL);
            exit(-1);
    }

    if ((mem_id = shmget(mem_key, 256, IPC_CREAT)) == (-1))
    {
            printf("Failed to obtain shared memory ID"
                   ", ERRNO = %d : %s\n", errno, strerror(errno));
            shmctl(mem_id, IPC_RMID, NULL);
            exit(-1);
    }
    for (i = 1; i <= MAX_ATTACH_NUM; i++)
    {
        if ((mem_addr[i] = (void *)shmat(mem_id, 0, 0)) == (void *)(-1))
        {
            printf("Failed to attach shared memory"
                   ", times [%02d], ERRNO = %d : %s\n", i, errno, strerror(errno));
            shmctl(mem_id, IPC_RMID, NULL);
            exit(-1);
        }
        else
        {
            printf("Successfully attached shared memory, times [%02d]\n", i);
        }
    }

    shmctl(mem_id, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}
