
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <alloca.h>


//http://tech.ccidnet.com/art/302/20070108/995995_1.html
#define SHW_VAR_ADR(ID, I)                    \
printf("the %20s\t is at adr:%p\n", ID, &I); //打印变量地址宏


#define SHW_POT_ADR(ID, I)                    \
printf("the %20s\t is at adr:%p\n", ID, I);  //打印指针指向地址宏


extern void afunc(void);

/*extern etext, edata, end;*/

/**
(1)全局变量和静态变量的存储是放在一块的，
初始化的全局变量和静态变量在一块区域（RW data），
未初始化的全局变量和未初始化的静态变量在相邻的另一块区域（BSS）。
程序结束后有系统释放
如下面(1).1   (1).2   (1).3所述
**/
// (1).1  -- 只要是静态变量，即使是局部的，也不存储在栈中，而是即存储在静态区域中，并依据其是否初始化，分别存储在BSS段和DATA段
static int /*bss_*/unini_glo_sta_var;                           //  静态未初始化全局变量，虽然系统会默认初始化为0，但仍然存放在BSS区
static int /*data_*/ini_glo_sta_var = 10;                       //  静态初始化全局变量，存放在RW DATA区

// (1).2  --  只要是全局变量，即存储在静态区域，并依据其是否初始化，分别存储在BSS段和DATA段
int /*bss_*/unini_glo_var;                                      //  未初始化全局数据存储在BSS数据区
int /*data_*/ini_glo_var = 42;                                  //  初始化全局数据存储在RW DATA数据区

// (1).3  --  全局常量，其本身是全局变量，即存储在静态区域, 同(1).2
const int unini_glo_cnt_var;                                        //  未初始化全局常量[不安全]， 自动初始化为0， 但仍然存放在BSS区
const int ini_glo_cnt_var = 10;                                     //  初始化全局常量，存储在常量区
// 对于常量我们需要注意的问题在于，他们并不像我们期望的那样存储在常量区(RO data)，
// 常量区只用于存储初始化好的全局常量以及字符串变量本身（不是是指针）
// 局部常量作为局部量仍然存储与栈中
// 因为常量区与代码段是在一起的（在有些段分类结果中，是不存在常量区的，常量区和代码段合成为代码区）
// 而本身来说常量只是限制了其读写权限，这种读写权限的限制可以在编译阶段由编译器进行制定和限制，
// 这样在严格的编译器审查结果下，运行阶段的代码就不存在对常量的读写操作，因此就没必要将其他局部常量也存储在常量区
// 否则将造成代码段的臃肿。。。

static int unini_glo_sta_cnt_var;
static int ini_glo_sta_cnt_var = 10;

int main(void)
{
    char *p_alloca = NULL, *b_malloc = NULL, *nb_malloc = NULL;

    // (1).4  局部静态变量，仍然是静态变量，同(1).1
    static int unini_sta_var;               //  局部未初始化静态变量，存储在BSS段
    static int ini_sta_var = 10;            //  静态初始化局部变量，存储在DATA段中

    // 局部非静态变量存储在栈中
    // (2).1  --  局部变量(不管初始化没有)存储在栈中
    int unini_var;                          //  局部未初始化变量，
    int ini_var = 10;                       //  局部初始化变量

    //  (2).2  --  局部常量(不管初始化没有)存储在栈中, 同(2).1
    const int unini_cnt_var;            // 未被初始化的局部常量，不安全，存储在栈中
    const int ini_cnt_var = 10;         // 局部常量，存储在栈中

    //  (2).3  --  指针常量和常量指针，其本质还是局部变量或者局部常量，存储在栈中，同(2).1 (2).2
    const int *p_cnt_var =  &ini_cnt_var;   //  指向常量的指针
    int * const cnt_p_var = &ini_var;       //  指针常量
    const int * const cnt_p_cnt_var =  &unini_cnt_var;    // 指向常量的常指针

    // (3)  字符串常量，存储在常量区
    /*const */char* str_cnt = "ABCDE";      //  字符串面变量, 存储在常量区, 即（RO data）
                                            //  本代码等价于const char* str1 = "ABCDE"
    char str_array[] = "ABCDE";             //  字符数组， 相当于初始化的局部变量，存储在栈中


/*    printf("Adr etext:%8x\t Adr edata %8x\t Adr end %8x\t\n", &etext, &edata, &end);*/

    // TEXT段 -- 代码段
    printf("------------------------------------------------------\n");
    printf(".Text Location:\n");
    SHW_VAR_ADR("main", main);              //查看代码段main函数位置
    SHW_VAR_ADR("afunc", afunc);           //查看代码段afunc函数位置
    printf("------------------------------------------------------\n\n");

    // BSS段 -- 未初始化全局变量区
    printf("------------------------------------------------------\n");
    printf(".Bss Location:\n");
    SHW_VAR_ADR("unini_glo_sta_var", unini_glo_sta_var);                //  全局未初始化静态变量, 在BSS段
    SHW_VAR_ADR("unini_sta_var", unini_sta_var);                        //  未初始化静态变量，在BSS段
    SHW_VAR_ADR("unini_glo_cnt_var", unini_glo_cnt_var);                //  全局未初始化常量，在BSS段
    SHW_VAR_ADR("unini_glo_var", unini_glo_var);                        //  全局未初始化变量在, BSS段
    SHW_VAR_ADR("unini_glo_sta_cnt_var", unini_glo_sta_cnt_var);        //  全局未初始化静态常量，在BSS段
    printf("------------------------------------------------------\n\n");


    // RW DATA段 -- 可读写已初始化数据段
    printf("------------------------------------------------------\n");
    printf(".Data Location:\n");
    SHW_VAR_ADR("ini_glo_sta_var", ini_glo_sta_var);                    //  全局初始化静态变量存储在RW data区域
    SHW_VAR_ADR("ini_glo_var", ini_glo_var);                            //  全局初始化变量存储在RW data

    SHW_VAR_ADR("ini_sta_var", ini_sta_var);                            //  局部初始化静态变量存储在RW data区域

    SHW_VAR_ADR("ini_glo_sta_cnt_var", ini_glo_sta_cnt_var);            //  全局静态已初始化常量，存储在RW data区域
    printf("------------------------------------------------------\n\n");

    // RO data  --  只读数据段
    printf("------------------------------------------------------\n\n");
    printf("RW data");
    SHW_VAR_ADR("ini_glo_cnt_var", ini_glo_cnt_var);     // 初始化全局常量，同字符串面变量一样，位于文本区，即常量区
    SHW_POT_ADR("str_cnt", str_cnt);                  //  字符串面变量保存在常量区，即文本区
    SHW_VAR_ADR("str_cnt", str_cnt);             //  指针str1本身在栈中

    printf("------------------------------------------------------\n\n");

    // STACK -- 栈
    printf("------------------------------------------------------\n");
    printf("Stack Locations:\n");
    afunc();                                    //   递归调用5此afunc函数

    p_alloca = (char *)alloca(32);              //   从栈中分配空间, 用完立即释放
    if(p_alloca != NULL)
    {
        SHW_VAR_ADR("start", p_alloca);
        SHW_VAR_ADR("end",p_alloca + 31);
    }


    // 局部变量(不管初始化没有)存储在栈中
    SHW_VAR_ADR("unini_var", unini_var);
    SHW_VAR_ADR("ini_var", ini_var);

    //  局部常量(不管初始化没有)存储在栈中
    SHW_VAR_ADR("unini_cnt_var", unini_cnt_var);        // 未被初始化的局部常量，不安全，存储在栈中
    SHW_VAR_ADR("ini_cnt_var", ini_cnt_var);            // 局部常量，存储在栈中

    //  指针常量和常量指针，其本质还是局部变量或者常量，存储在栈中
    SHW_VAR_ADR("p_cnt_var", p_cnt_var);            //  该指向常量的指针，其本身其实是一个（初始化的）局部变量[同ini_var], 存储在栈中
    SHW_VAR_ADR("cnt_p_var", cnt_p_var);            //  该指针常量，其本身其实是一个初始化的局部常量[同ini_cnt_var]， 存储在栈中
    SHW_VAR_ADR("cnt_p_cnt_var", cnt_p_cnt_var);    //  该指向常量的指针常量作为一个初始化的局部常量，存储在栈中

    SHW_POT_ADR("str_array", str_array);             //  字符串数组，相当于初始化的局部变量，保存在栈中
    SHW_VAR_ADR("str_array", str_array);             //  指针str2本身在栈中，其地址本身，就是字符串数组的地址

    printf("------------------------------------------------------\n\n");


    printf("------------------------------------------------------\n");
    printf("Heap Locations:\n");
    b_malloc = (char *)malloc(32 * sizeof(char));   //从堆中分配空间
    nb_malloc = (char *)malloc(16 * sizeof(char));  //从堆中分配空间
    printf("the Heap start: %p\n", b_malloc);   //堆起始位置
    printf("the Heap end:%p\n",(nb_malloc + 16 * sizeof(char)));//堆结束位置

    // 指针指向的区域在堆中，但是指针本身在栈中
    printf("\nb and nb in Stack\n");
    SHW_VAR_ADR("b_malloc", b_malloc);       //显示栈中数据b的位置
    SHW_VAR_ADR("b_malloc", nb_malloc);     //显示栈中数据nb的位置
    free(b_malloc);               //释放申请的空间，以避免内存泄漏
    b_malloc = NULL;
    free(nb_malloc);              //释放申请的空间，以避免内存泄漏
    nb_malloc = NULL;
    printf("------------------------------------------------------\n\n");



    return EXIT_SUCCESS;
}

void afunc(void)
{
    static int long level=0;          // 静态数据存储在数据段中
    int      stack_var;               // 局部变量，存储在栈区
    if(++level==5)                    // 此函数递归调用5次
    {
        return;
    }
    printf("stack_var is at:%p\n",&stack_var);
    //      SHW_VAR_ADR("stack_var in stack section",stack_var);
    //      SHW_VAR_ADR("Level in data section",level);
    afunc();
}

