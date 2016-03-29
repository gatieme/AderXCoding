#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define IPCKEY 0x366378

typedef struct st_setting
{
    char agen[10];
    unsigned char file_no;
}st_setting;

int main(int argc, char** argv)
{
    int         shm_id;
    key_t       key;
    st_setting  *p_setting;

    //  首先检查共享内存是否存在，存在则先删除
    shm_id = shmget(IPCKEY , 1028, 0640);
    if(shm_id != -1)
    {
        p_setting = (st_setting *)shmat(shm_id, NULL, 0);

        if (p_setting != (void *)-1)
        {
            shmdt(p_setting);

            shmctl(shm_id,IPC_RMID,0) ;
        }
    }

    //  创建共享内存
    shm_id = shmget(IPCKEY, 1028, 0640 | IPC_CREAT | IPC_EXCL);
    if(shm_id == -1)
    {
        printf("shmget error\n");
        return -1;
    }

    //  将这块共享内存区附加到自己的内存段
    p_setting = (st_setting *)shmat(shm_id, NULL, 0);

    strncpy(p_setting->agen, "gatueme", 10);
    printf( "agen:%s\n",p_setting->agen );

    p_setting->file_no = 1;
    printf( "file_no:%d\n",p_setting->file_no );

    system("ipcs -m");//  此时可看到有进程关联到共享内存的信息，nattch为1

    //  将这块共享内存区从自己的内存段删除出去
    if(shmdt(p_setting) == -1)
       perror(" detach error ");

    system("ipcs -m");//  此时可看到有进程关联到共享内存的信息，nattch为0

    //  删除共享内存
    if (shmctl( shm_id , IPC_RMID , NULL ) == -1)
    {
        perror(" delete error ");
    }

    return RXIT_SUCCESS;

}
