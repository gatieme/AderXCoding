#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void StringToCharp( )
{
    string str("OK");
    const char *charp = str.c_str( );
    cout <<"[func :" <<__func__ <<"] "<<str <<" to " <<charp <<endl;
}


void CharpToString( )
{
    const char *p = "Hello";
    string str(p);
    cout <<"[func :" <<__func__ <<"] "<<p <<" to " <<str <<endl;
}

void StringToNumber()
{
   string str = "123.12";
   double dou = atof(str.c_str( ));   
    cout <<"[func :" <<__func__ <<"] "<<str <<" to " <<dou <<endl; 
}
int main(void)
{
    StringToCharp( );
    CharpToString( );
    StringToNumber( );
    return 0;
}