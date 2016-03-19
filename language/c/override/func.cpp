#include <iostream>
using namespace std;

int func(void)
{
    cout << "func without parameters" << endl;
}

int func(int ia)
{
    cout << "func with one int parameter: " << endl;
    cout << ia << endl;
}

int func(int ia, float fb)
{
    cout << "func with one int parameter and one float parameter" << endl;
    cout << ia << endl;
    cout << fb << endl;
}

int main()
{

    func();
    func(5);
    func(5, 5.0);
}
