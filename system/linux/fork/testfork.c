#include <stdio.h>

/**

从代码里面可以看出2者的pid不同，

内存资源count是值得复制，子进程改变了count的值，而父进程中的count没有被改变。有人认为这样大批量的复制会导致执行效率过低。其实在复制过程中，子进程复制了父进程的task_struct，系统堆栈空间和页面表，这意味着上面的程序，我们没有执行count++前，其实子进程和父进程的count指向的是同一块内存。而当子进程改变了父进程的变量时候，会通过copy_on_write的手段为所涉及的页面建立一个新的副本。所以当我们执行++count后，这时候子进程才新建了一个页面复制原来页面的内容，基本资源的复制是必须的，而且是高效的。整体看上去就像是父进程的独立存储空间也复制了一遍。

其次，我们看到子进程和父进程直接没有互相干扰，明显2者资源都独立了。我们看下面程序



*/
int main(void)
{
    int count = 1;
    int child;

    if(!(child = fork()))
    {   
        //开始创建子进程
        printf("This is son, his count is: %d. and his pid is: %d\n", ++count, getpid());//子进程的内容
    }
    else
    {
        printf("This is father, his count is: %d, his pid is: %d\n", count, getpid());
    }

    return EXIT_SUCCESS;
}