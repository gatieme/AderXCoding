/*===================*
* pvm_hello.c - Demo
program of PVM.*
*==================*/

#include "pvm3.h"

int main(int argc, char** argv)
{
    int i, mytid, dtid, info, nhost, narch;
    struct pvmhostinfo* hostp;

    mytid = pvm_mytid();
    dtid = pvm_tidtohost(mytid);
    info = pvm_config(&nhost, &narch, &hostp);

    for (i = 0; i < nhost && hostp[i].hi_tid != dtid; i++);

    printf("Hello World! My task id is t%x on %s with %d hosts.\n",
            mytid, hostp[i].hi_name, nhost);

    pvm_exit( );
    return 0;


}
