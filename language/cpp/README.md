#




#C++笔记

1：前向引用声明

使用前向引用声明时, 但是在提供一个完整的类定义之前，

不能定义该类的对象, 也不能在内联成员函数中使用该类的对象

但是可以声明该类的对象引用或者指针

class Fred;
class Barney
{
    Fred x;	// ERROR, 类Fred的定义尚不完整
};
class Fred
{
    Barney Y;
}