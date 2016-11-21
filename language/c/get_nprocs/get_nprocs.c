/*************************************************************************
    > File Name: test.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年11月21日 星期一 15时37分30秒
 ************************************************************************/


//  http://www.man7.org/linux/man-pages/man3/get_nprocs_conf.3.html
#include <stdio.h>
#include <stdlib.h>

#include <sys/sysinfo.h>


/*  returns the number of processors configured by the operating system.  */
int get_nprocs(void);

/*  returns the number of processors currently available in the system.
 *  This may be less than the number returned by get_nprocs_conf( )
 *  because processors may be offline (e.g., on hotpluggable systems).
 */
int get_nprocs_conf(void);


int main(void)
{
    printf("the number of processor configured by kernel : %d\n", get_nprocs( ));
    printf("the number of processor currently avaliable  : %d\n", get_nprocs_conf( ));
    printf("the number of processor which may be offline : %d\n", get_nprocs( ) - get_nprocs_conf( ));

    return EXIT_SUCCESS;
}
