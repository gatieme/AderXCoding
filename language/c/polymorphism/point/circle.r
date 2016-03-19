//Point内部头文件(外面看不到)：point.r
 
#ifndef CIRCLE_R
 
#define CIRCLE_R
 
struct Circle
{
    const struct Point point; //放在第一位，可表继承
    int radius;
};
 
#endif