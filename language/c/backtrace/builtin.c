#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ucontext.h>
#include <dlfcn.h>
#include <execinfo.h>

void showBacktrace()
{
        void * ret = __builtin_return_address(1);
        printf("ret address [%p]\n", ret);
        void * caller = __builtin_frame_address(0);
        printf("call address [%p]\n", caller);
#ifdef __cplusplus
        Dl_info dlinfo;

        void *ip = ret;
        if(!dladdr(ip, &dlinfo)) {
                perror("addr not found\n");
                return;
        }

        const char *symname = dlinfo.dli_sname;
        int f = 0;
        fprintf(stderr, "% 2d: %p %s+%u (%s)\n",
                        ++f,
                        ip,
                        symname, 0,
// (unsigned)(ip - dlinfo.dli_saddr),

                        dlinfo.dli_fname);
#endif
}

int MyFunc_A()
{
        showBacktrace();
        return 10;
}

int MyFunc_B()
{
        return MyFunc_A();
}

int main()
{
        MyFunc_B();
        return 0;
}
