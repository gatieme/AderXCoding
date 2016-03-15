#include <iostream>
using namespace std;


class a
{
public:
 a()
 {
  cout<<"Constructed a!!!"<<endl;
 }
 ~a()
 {
  cout<<"Destory a!!!!"<<endl;
 }
};
void* get_condesfun_add(int n)
{
 a *pa;
 if (n)  //非0值获取构造函数地址
 {
__asm
  {
   push eax
   mov eax,confunadd   //保存构造函数的跳转地址
   mov pa,eax
   pop eax
  }
 }
 else
 {
  __asm
  {
   push eax
   mov eax,desfunadd   //保存析构函数的跳转地址
   mov pa,eax
   pop eax
  }
 }
 return pa;
confunadd:  //这个标号充当构造函数的符号地址
 a::a();
 __asm ret    //用函数指针跳进来执行后，从这里返回
desfunadd:  //这个标号充当析构函数的符号地址
 pa->~a();
 __asm ret //同上
}
int  main()
{
 typedef void(*pf)();
 void*p=get_condesfun_add(0);  //获取析构函数地址
 pf desfun=(pf)p;  //强制转换
 desfun();  //执行
 p=get_condesfun_add(1);  //获取构造函数地址
 pf confun=(pf)p;
 confun();
 return 0;
}
