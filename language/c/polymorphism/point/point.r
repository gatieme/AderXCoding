//Point内部头文件(外面看不到)：point.r
 
#ifndef POINT_R
 
#define POINT_R
 
struct Point
{
    const void * base; //继承，基类指针，放在第一个位置，const是防止修改
    int x, y;        //坐标
};
 
#endif