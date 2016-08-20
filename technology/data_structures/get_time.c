#include<time.h>
#include<stdio.h>
#include<stdlib.h>

#include <sys/time.h>

#ifdef WINSOWS_DEF
#include<windows.h>
#endif

int main()
{

    //精确到秒 ==========================================
    time_t t1,t2;

    time(&t1);

    //////////////////////
    //此处放置要测试的代码
    sleep(2);//延时
    //////////////////////
    time(&t2);

    printf("%d %d %ds\n",t1,t2,t2-t1);

    //精确到毫秒 ========================================
    clock_t c1,c2;

    c1=clock();

    //此处放置要测试的代码

    sleep(2);//延时

    c2=clock();

    printf("%d %d %lfms\n",c1,c2,(c2-c1) / CLOCKS_PER_SEC);

#ifdef WINDOWS
    //精确到 0.000001毫秒 ===============================

    LARGE_INTEGER litmp;

    LONGLONG start, end;

    double dft, dff, dfm;

    QueryPerformanceFrequency(&litmp);//获得时钟频率

    dff = (double) litmp.QuadPart;

    QueryPerformanceCounter(&litmp);//获得初始值

    start = litmp.QuadPart;

    //此处放置要测试的代码

    sleep(1);//延时

    QueryPerformanceCounter(&litmp);//获得终止值

    end = litmp.QuadPart;

    dfm = (double) (end - start);

    dft = dfm / dff;//获得对应的时间值,单位秒

    printf("%lf毫秒\n",dfm/dff*1000);
#endif


    struct timeval tv_start,tv_end;

    gettimeofday(&tv_start, NULL);
    //此处放要测试的代码或程序
    sleep(2);
    gettimeofday(&tv_end, NULL);
    printf("%lfs\n", tv_end.tv_sec-tv_start.tv_sec+(tv_end.tv_usec-tv_start.tv_usec)/1000000.0);
}
