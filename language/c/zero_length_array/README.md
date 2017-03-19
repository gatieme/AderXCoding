GDB实用插件(peda, gef, gdbinit)全解
=======

| CSDN | GitHub |
|:----:|:------:|
| [GDB实用插件(peda, gef, gdbinit)全解](http://blog.csdn.net/gatieme/article/details/63254211) | [`AderXCoding/system/tools/gdb/plugin`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/gdb/plugin) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作
<br>


#1  零长度数组概念
-------


众所周知, `GNU/GCC` 在标准的 `C/C++` 基础上做了有实用性的扩展, 零长度数组（`Arrays of Length Zero`） 就是其中一个知名的扩展.

多数情况下,  其应用在变长数组中, 其定义如下


```cpp
struct Packet
{
    int state;
    int len;
    char cData[0]; //这里的0长结构体就为变长结构体提供了非常好的支持
};
```

首先对 `0长度数组`, 也叫柔性数组 做一个解释 ：

*   用途 : 长度为0的数组的主要用途是为了满足需要变长度的结构体

*   用法 : 在一个结构体的最后, 申明一个长度为0的数组, 就可以使得这个结构体是可变长的. 对于编译器来说, 此时长度为0的数组并不占用空间, 因为数组名本身不占空间, 它只是一个偏移量,  数组名这个符号本身代表了一个不可修改的地址常量 

>(注意 : 数组名永远都不会是指针!), 但对于这个数组的大小, 我们可以进行动态分配
>
>
>注意 ：如果结构体是通过calloc、malloc或 者new等动态分配方式生成，在不需要时要释放相应的空间。
>
>优点 ：比起在结构体中声明一个指针变量、再进行动态分 配的办法，这种方法效率要高。因为在访问数组内容时，不需要间接访问，避免了两次访存。
>
>缺点 ：在结构体中，数组为0的数组必须在最后声明，使 用上有一定限制。


**对于编译器而言, 数组名仅仅是一个符号, 它不会占用任何空间, 它在结构体中, 只是代表了一个偏移量, 代表一个不可修改的地址常量!**


#2	0长度数组的用途
-------

##2.1  变长数据缓冲区(开辟空间, 释放, 访问)
-------


对于**0长数组**的这个特点，很容易构造出变成结构体，如缓冲区，数据包等等：

```cpp
//  0长度数组
struct zero_buffer
{
    int     len;
    char    data[0];
};
```



这样的变长数组常用于网络通信中构造不定长数据包, 不会浪费空间浪费网络流量, 因为`char    data[0];` 只是个数组名, 是不占用存储空间的,


那么我们使用的时候, 只需要开辟一次空间即可

```cpp
    ///  开辟
    if ((zbuffer = (struct zero_buffer *)malloc(sizeof(struct zero_buffer) + sizeof(char) * CURR_LENGTH)) != NULL)
    {
        zbuffer->len = CURR_LENGTH;
        memcpy(zbuffer->data, "Hello World", CURR_LENGTH);


        printf("%d, %s\n", zbuffer->len, zbuffer->data);
    }
```


##2.2  定长包(开辟空间, 释放, 访问)
-------


比如我要发送1024字节的数据, 如果用**定长包**, 假设定长包的长度为2048, 就会浪费1024个字节的空间, 也会造成不必要的流量浪费.

```cpp
struct max_buffer
{
    int     len;
    char    data[MAX_LENGTH];
};
```

由于考虑到数据的溢出, 变长数据包中的 `data` 数组长度一般会设置得足够长足以容纳最大的数据, 因此 `packet` 中的 `data` 数组很多情况下都没有填满数据, 因此造成了浪费

而如果我们用变长数组来进行封包的话, 就不会造成浪费（最多会造成`4`个字节的浪费, 包头的 `int` 型的 `len` 不属于数据因此算是浪费）, 如前面的 `Buffer` 结构体，假如我们要发送 `1024` 个字节, 我们如何构造这个数据包呢:

```cpp
    ///  开辟
    if ((mbuffer = (struct max_buffer *)malloc(sizeof(struct max_buffer))) != NULL)
    {
        mbuffer->len = CURR_LENGTH;
        memcpy(mbuffer->data, "Hello World", CURR_LENGTH);


        printf("%d, %s\n", mbuffer->len, mbuffer->data);
    }
```

这段内存要分两部分使用

前部分4个字节p->len，作为包头(就是多出来的那部分)，这个包头是用来描述紧接着包头后面的数据部分的长度，这里是1024，所以前四个字节赋值为1024(既然我们要构造不定长数据包，那么这个包到底有多长呢，因此，我们就必须通过一个变量来表明这个数据包的长度，这就是len的作用)，

而紧接其后的内存是真正的数据部分, 通过p->cData定位到该部分的起始地址, 最后, 进行一个 `memcpy()` 内存拷贝, 把要发送的数据填入到这段内存当中,


##2.3  指针数据包(开辟空间, 释放, 访问)
-------

如果你将上面的长度为的数组换为**指针**, 那么只浪费了一个指针域的空间

```cpp
struct point_buffer
{
    int     len;
    char    *data;
};
```

但是在分配内存时，需采用两步

*	首先, 需为结构体分配一块内存空间;

*	其次再为结构体中的成员变量分配内存空间.

这样两次分配的内存是不连续的, 需要分别对其进行管理. 当使用长度为的数组时, 则是采用一次分配的原则, 一次性将所需的内存全部分配给它.

相反, 释放时也是一样的.

```cpp
    /// 销毁
    free(pbuffer->data);
    free(pbuffer);
```

##2.4 总结


```cpp
#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH      1024
#define CURR_LENGTH      512

//  0长度数组
struct zero_buffer
{
    int     len;
    char    data[0];
}__attribute((packed));


//  定长数组
struct max_buffer
{
    int     len;
    char    data[MAX_LENGTH];
}__attribute((packed));


//  指针数组
struct point_buffer
{
    int     len;
    char    *data;
}__attribute((packed));

int main(void)
{
    struct zero_buffer  *zbuffer = NULL;
    struct max_buffer   *mbuffer = NULL;
    struct point_buffer *pbuffer = NULL;


    // =====================
    // 0长度数组  占用-开辟-销毁
    // =====================
    ///  占用
    printf("the length of struct test1:%d\n",sizeof(struct zero_buffer));
    ///  开辟
    if ((zbuffer = (struct zero_buffer *)malloc(sizeof(struct zero_buffer) + sizeof(char) * CURR_LENGTH)) != NULL)
    {
        zbuffer->len = CURR_LENGTH;
        memcpy(zbuffer->data, "Hello World", CURR_LENGTH);


        printf("%d, %s\n", zbuffer->len, zbuffer->data);
    }
    ///  销毁
    free(zbuffer);
    zbuffer = NULL;


    // =====================
    // 定长数组  占用-开辟-销毁
    // =====================
    ///  占用
    printf("the length of struct test2:%d\n",sizeof(struct max_buffer));
    ///  开辟
    if ((mbuffer = (struct max_buffer *)malloc(sizeof(struct max_buffer))) != NULL)
    {
        mbuffer->len = CURR_LENGTH;
        memcpy(mbuffer->data, "Hello World", CURR_LENGTH);


        printf("%d, %s\n", mbuffer->len, mbuffer->data);
    }
    /// 销毁
    free(mbuffer);
    mbuffer = NULL;

    // =====================
    // 指针数组  占用-开辟-销毁
    // =====================
    ///  占用
    printf("the length of struct test3:%d\n",sizeof(struct point_buffer));
    ///  开辟
    if ((pbuffer = (struct point_buffer *)malloc(sizeof(struct point_buffer))) != NULL)
    {
        pbuffer->len = CURR_LENGTH;
        if ((pbuffer->data = (char *)malloc(sizeof(char) * CURR_LENGTH)) != NULL)
        {
            memcpy(pbuffer->data, "Hello World", CURR_LENGTH);


            printf("%d, %s\n", pbuffer->len, pbuffer->data);
        }
    }
    /// 销毁
    free(pbuffer->data);
    free(pbuffer);
    pbuffer = NULL;


    return EXIT_SUCCESS;
}
```

长度为的数组并不占有内存空间，而指针方式需要占用内存空间。

l 对于长度为数组，在申请内存空间时，采用一次性分配的原则进行；对于包含指针的结构体，才申请空间时需分别进行，释放时也需分别释放。

l 对于长度为的数组的访问可采用数组方式进行


#3	GNU Document中 变长数组的支持
-------

>参见
>
>[6.17 Arrays of Length Zero](https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html)
>
>[C Struct Hack – Structure with variable length array](http://frankchang0125.blogspot.com/2013/01/c-struct-hack-structure-with-variable.html)

在 `C90` 之前, 并不支持0长度的数组, 0长度数组是 `GNU C` 的一个扩展,



```cpp
// 1.c
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    char a[0];

    return EXIT_SUCCESS;
}
```

我们现在使用了0长度数组, 没有出现编译错误, 是因为目前默认的编译选项默认添加了变长数组的支持的.

0长度数组其实就是灵活的运用的数组指向的是其后面的连续的内存空间

```cpp
struct buffer
{
    int     len;
    char    data[0];
};
```
在早期没引入0长度数组的时候, 大家是通过定长数组和指针的方式来解决的, 但是

*	定长数组定义了一个足够大的缓冲区, 这样使用方便, 但是每次都造成空间的浪费
*	指针的方式, 要求程序员在释放空间是必须进行多次的free操作, 而我们在使用的过程中往往在函数中返回了指向缓冲区的指针, 我们并不能保证每个人都理解并遵从我们的释放方式


所以GNU就对其进行了0长度数组的扩展. 当使用data[0]的时候, 也就是0长度数组的时候，0长度数组作为数组名, 并不占用存储空间.

在C99之后，也加了类似的扩展，只不过用的是 `char payload[]`这种形式（所以如果你在编译的时候确实需要用到-pedantic参数，那么你可以将char payload[0]类型改成char payload[]，这样就可以编译通过了，当然你的编译器必须支持C99标准的，如果太古老的编译器，那可能不支持了）

所以结构体的末尾, 就是指向了其后面的内存数据。因此我们可以很好的将该类型的结构体作为数据报文的头格式，并且最后一个成员变量，也就刚好是负载或内容了.


GNU手册还提供了另外两个结构体来说明，更容易看懂意思：


```cpp
struct f1 {
    int x;
    int y[];
} f1 = { 1, { 2, 3, 4 } };

struct f2 {
    struct f1 f1;
    int data[3];
} f2 = { { 1 }, { 5, 6, 7 } };
```

我把f2里面的2,3,4改成了5,6,7以示区分。如果你把数据打出来。即如下的信息：

```cpp
f1.x = 1

f1.y[0] = 2

f1.y[1] = 3

f1.y[2] = 4
```

也就是f1.y指向的是{2,3,4}这块内存中的数据。所以我们就可以轻易的得到，f2.f1.y指向的数据也就是正好f2.data的内容了。打印出来的数据：

```cpp
f2.f1.x = 1

f2.f1.y[0] = 5

f2.f1.y[1] = 6

f2.f1.y[2] = 7
```

如果你不是很确认其是否占用空间。你可以用sizeof来计算一下。就可以知道sizeof(struct f1)=4,也就是int y[]其实是不占用空间的。但是这个0长度的数组，必须放在结构体的末尾。如果你没有把它放在末尾的话。编译的时候，会有如下的错误：

```cpp
main.c:37:9: error: flexible array member not at end of struct
     int y[];
         ^
```

到这边，你可能会有疑问，如果将struct f1中的int y[]替换成int *y，又会是如何？这就涉及到数组和指针的问题了。有时候吧，这两个是一样的，有时候又有区别。

首先要说明的是，支持0长度数组的扩展，重点在数组，也就是不能用int *y指针来替换。sizeof的长度就不一样了。把struct f1改成这样：

```cpp
struct f3 {
    int x;
    int *y;
};
```
在64位下，sizeof(struct f1)=4，而sizeof(struct f3)=16。因为int *y是指针，指针在64位下，是64位的，如果在32位环境的话，sizeof(struct f3)则是8了，sizeof(struct f1)不变。所以int *y是不能替代int y[]的。


#4	0长度数组的其他特征
-------


http://blog.csdn.net/pngynghay/article/details/24802719
http://blog.csdn.net/ssdsafsdsd/article/details/8234736


0长度数组与指针实现有什么区别呢, 为什么0长度数组不占用存储空间呢?


其实本质上涉及到的是一个C语言里面的数组和指针的区别问题. `char a[1]`里面的`a`和`char *b`的`b`相同吗？

《 Programming Abstractions in C》（Roberts, E. S.，机械工业出版社，2004.6）82页里面说


>“arr is defined to be identical to &arr[0]”。

也就是说，char a[1]里面的a实际是一个常量，等于&a[0]。而char *b是有一个实实在在的指针变量b存在。 所以，a=b是不允许的，而b=a是允许的。 两种变量都支持下标式的访问，那么对于a[0]和b[0]本质上是否有区别？我们可以通过一个例子来说明。


```cpp
// 2.c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a[0];
    char *b;

    printf("%d %d\n", sizeof(a), sizeof(b));
}
```


![运行结果](2.png)

http://blog.csdn.net/pngynghay/article/details/24802719



#参考
-------

[结构体中的指针与零长度数组](http://blog.csdn.net/pngynghay/article/details/24802719)

[零长度数组的妙用](http://blog.chinaunix.net/uid-20196318-id-28810.html)


[C语言中长度为0的数组](http://blog.csdn.net/zhaqiwen/article/details/7904515)

[C/C++ 中的0长数组（柔性数组）](http://blog.csdn.net/yby4769250/article/details/7294696)


[GNU C中的零长度数组](http://blog.csdn.net/ssdsafsdsd/article/details/8234736)


[C语言变长数组data[0]【总结】](http://www.cnblogs.com/Anker/p/3744127.html)


[长度为0的数组——C语言的非标准用法之一](https://www.douban.com/note/213324492/)


[长度为0的数组的size为什么不一定是0？](http://www.oschina.net/question/1470892_151368?sort=time)

[有关C语言占位符](http://bbs.csdn.net/topics/290045267)

[C语言技巧之长度为0的数组](http://liangqiu.blog.51cto.com/4461709/1175742)


[零长度数组使用 ](http://blog.chinaunix.net/uid-14113486-id-81440.html)


[使用零长度数组](http://www.2cto.com/kf/200906/39206.html)

[零长度数组](http://blog.csdn.net/encourage2011/article/details/51971509)


[C/C++ 中长度为0的数组](http://www.cnblogs.com/tangxin-blog/p/5560699.html)


[GCC 中零长数组与变长数组](http://www.cnblogs.com/hazir/p/variable_length_array.html)

[零长度数组的妙用](http://elkpi.com/topics/zero-length-arrays.html)


[Multiple 0-length arrays have the same address?](http://stackoverflow.com/questions/42883326/multiple-0-length-arrays-have-the-same-address/42883763#42883763)

<br><br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.


