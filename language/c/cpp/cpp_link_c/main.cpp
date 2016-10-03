#include <iostream>
using namespace std;



#ifdef __cplusplus
extern "C"
{
#endif

int add(const int a, const int b);

#ifdef __cplusplus
}
#endif



int main( )
{
    std::cout <<add(3, 4) <<std::endl;

    return 0;
}


