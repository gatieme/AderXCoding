#include <iostream>




class Word
{
public :

    ~Word()
    {
        std::cout <<"1111";
        delete[]  str;
    }

private :
    int cnt;
    char *str;
};
int main(void)
{
    Word word1;

    Word word2 = word1;
}
