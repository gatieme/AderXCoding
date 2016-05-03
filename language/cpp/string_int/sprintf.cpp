#include <iostream>
#include <string>
#include <cstring>

using namespace std;


int main(void)
{
    //把整数123 打印成一个字符串保存在s 中。
    sprintf(s, "%d", 123);              //产生"123", 可以指定宽度，不足的左边补空格：
    sprintf(s, "%8d%8d", 123, 4567);    //产生：" 123 4567",  当然也可以左对齐：
    sprintf(s, "%-8d%8d", 123, 4567);   //产生："123 4567", 也可以按照16 进制打印：
    sprintf(s, "%8x", 4567);            //小写16 进制，宽度占8 个位置，右对齐
    sprintf(s, "%-8X", 4568);           //大写16 进制，宽度占8 个位置，左对齐
    return 0;
}