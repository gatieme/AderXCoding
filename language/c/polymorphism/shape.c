//c语言面向对象
#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
typedef enum {point,circle} shape_type;//两种图形类型,点和圆
typedef struct
{//定义图像
    shape_type type;//图形的标示点和圆
    void (*destory)(void *);//销毁图像函数
    void (*draw)(void *);//绘制图像函数
}shape_t;
typedef struct
{//点
    shape_t common;//类型
    int x;//横坐标
    int y;//纵坐标
}point_t;
typedef struct
{//圆
    shape_t common;//类型
    point_t *center;//点类型指针
    int radius;//圆的半径大小
}circle_t;
void destoryPoint(point_t *This)
{//销毁点
    free(This);
    printf("销毁点图像!\n");
}
void drawPoint(point_t *This)
{//描点
    printf("P (%d,%d)",This->x,This->y);
}
shape_t* createPoint(va_list *ap)
{//创建点
    point_t * p_point;//定义点指针
    if((p_point=(point_t*)malloc(sizeof(point_t)))==NULL)//分配空间
       return NULL;
    p_point->common.type=point;//指明类型
    p_point->common.destory=(void (__cdecl *)(void *))destoryPoint;//指明撤销函数
    p_point->common.draw=(void (__cdecl *)(void *))drawPoint;//指明绘制点函数
    p_point->x=va_arg(*ap,int);//设置x值
    p_point->y=va_arg(*ap,int);//设置y值
    return (shape_t*)p_point;//强制返回类型
}
void destoryCircle(circle_t* This)
{//撤销圆函数
    free(This->center);
    free(This);
    printf("销毁圆形!\n");
}
void drawCircle(circle_t* This)
{//画圆函数
    printf("C (");
    This->center->common.draw(This->center);//描点
    printf(",%d)",This->radius);//指明半径
}
shape_t* createCircle(va_list* ap)
{
    circle_t* p_circle;//创建圆形指针
    if((p_circle=(circle_t*)malloc(sizeof(circle_t)))==NULL)//分配圆形空间
      return NULL;
    p_circle->common.type=circle;//指明类型
    p_circle->common.destory=(void (__cdecl *)(void *))destoryCircle;//指明撤销圆函数
    p_circle->common.draw=(void (__cdecl *)(void *))drawCircle;//指明绘制圆函数
    p_circle->center=(point_t*)createPoint(ap);//创建一个点
    p_circle->radius=va_arg(*ap,int);//指明圆的半径
    return (shape_t*)p_circle;//强制返回类型
}
shape_t* createShape(shape_type st,...)
{
    va_list ap;//申明可变参数
    shape_t* p_shape=NULL;//定义一个图形指针
    va_start(ap,st);
    //根据不同类型创建图形
    if(st==point)
      p_shape=createPoint(&ap);
    if(st==circle)
      p_shape=createCircle(&ap);
    va_end(ap);
    return p_shape;//返回图像类型
}
int main(int argc,char **argv)
{   
    int i;
    shape_t* shape[2];
    shape[0]=createShape(point,2,3);
    shape[1]=createShape(circle,20,40,10);
    for(i=0;i<2;i++)
    {
        shape[i]->draw(shape[i]);
        printf("\n");
    }
    for(i=1;i>=0;i--)
     shape[i]->destory(shape[i]);
    return 0;
}