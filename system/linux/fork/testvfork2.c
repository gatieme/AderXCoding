#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>


int main(void)
{
   int count = 1;
    int child;

   // child = vfork( );

    printf("Before create son, the father's count is : %d\n", count);

    if((child = vfork()) < 0)
    {
        printf("%d", child);
        perror("fork error : ");
    }
    else if(child == 0)     //  fork return 0 in the child process because child can get hid PID by getpid( )
    {
        printf("This is son, his count is: %d (%p). and his pid is: %d\n", ++count, &count, getpid());

    }
    else                    //  the PID of the child process is returned in the parent’s thread of execution
    {
        printf("After son, This is father, his count is: %d (%p), his pid is: %d\n", count, &count, getpid());
        sleep(2);
    }

    return EXIT_SUCCESS;
}
