ANSI C 标准中，有可变参数的概念，可以通过一组宏实现
 
    va_list arg_ptr:                       定义一个可变参数列表指针
    va_start(arg_ptr, argN):        让arg_ptr指向参数argN
    va_arg(arg_ptr, type):          返回类型为type的参数指针,并指向下一个参数
    va_copy(dest, src):               拷贝参数列表指针,src->dest,
    va_end(arg_ptr)：               清空参数列表，并置参数指针arg_ptr无效。每个va_start()必须与一个va_end()对应
 

 
[c-sharp] view plain copy
#include<stdio.h>  
#include<stdarg.h>  
int getMax(int n, ...)  
{  
        va_list va;  
        va_start(va,n); // init va, pointing to the first argument  
        int tmp,smax=-1;  
        int i;  
        for(i=0;i<n;i++)  
        {  
                tmp=va_arg(va,int); // get the next argument, the type is int  
                if(tmp>smax) smax=tmp;  
        }  
        va_end(va);  
        return smax;  
}  
int main()  
{  
        printf("%d/n",getMax(4,9,5,2,19));  
        printf("%d/n",getMax(6,1,3,4,5,2,0));  
}  
 
 
参数的内存存放格式：参数存放在内存的堆栈段中，在执行函数的时候，从最后一个开始入栈
因此，假设定义一个可变参数的函数 void f(int x, ...)， 通过f( x, y, z) 调用，那么，z先入栈，然后y， 然后x。 因此我们只要得到任何一个变量的地址，就可以找到其它变量的地址。
va_start(va, n) 就是让va指向n的地址。这样，后面就可以得到所有参数的值。前提是，我们必须知道每个参数的类型。在本例子中，都是int类型。