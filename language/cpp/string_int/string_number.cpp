#include <iostream>
#include <string>
#include <cstring>

using namespace std;

/** atoi */
void StringToInt( )
{
   string str = "123";
   int i = atoi(str.c_str( ));   
    cout <<"[func :" <<__func__ <<"] "<<str <<" to " <<i <<endl; 
}
/** itoa */
void IntToString( )
{
    int num = 100;
    char temp[81];
    string str = itoa(num, temp, 10);   
    cout <<"[func :" <<__func__ <<"] "<<num <<" to " <<str <<endl;   
}

/** atof */
void StringToDouble( )
{
   string str = "123.12";
   double dou = atof(str.c_str( ));   
    cout <<"[func :" <<__func__ <<"] "<<str <<" to " <<dou <<endl; 
}


int main(void)
{
    StringToDouble( );
    IntToString( );
    StringToInt( );
    return 0;
}