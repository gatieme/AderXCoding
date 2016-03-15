//http://www.th7.cn/Program/cp/201503/408402.shtml


#include <iostream>
using namespace std;

class Test
{
	public:
	int a;
	int b;

	int fun1();
};


int main()
{
	Test obj;
	cout << "obj's Size = " << sizeof(obj) << endl;
	cout << "obj 's Address = " << &obj << endl;
	return 0;
}
