#include <iostream>
#include <cstring>
#include <cmath>
// general version
template<class T>
class Compare
{
public:
    static bool IsEqual(const T& lh, const T& rh)
    {
        std::cout <<"in the general class..." <<std::endl;
        return lh == rh;
    }
};



// specialize for float 全特化
template<>
class Compare<float>
{
public:
    static bool IsEqual(const float& lh, const float& rh)
    {
        std::cout <<"in the float special class..." <<std::endl;

        return std::abs(lh - rh) < 10e-3;
    }
};

// specialize for double 全特化
template<>
class Compare<double>
{
public:
    static bool IsEqual(const double& lh, const double& rh)
    {
        std::cout <<"in the double special class..." <<std::endl;

        return std::abs(lh - rh) < 10e-6;
    }
};





int main(void)
{
    Compare<int> comp1;
    std::cout <<comp1.IsEqual(3, 4) <<std::endl;
    std::cout <<comp1.IsEqual(3, 3) <<std::endl;

    Compare<float> comp2;
    std::cout <<comp2.IsEqual(3.14, 4.14) <<std::endl;
    std::cout <<comp2.IsEqual(3, 3) <<std::endl;

    Compare<double> comp3;
    std::cout <<comp3.IsEqual(3.14159, 4.14159) <<std::endl;
    std::cout <<comp3.IsEqual(3.14159, 3.14159) <<std::endl;
    return 0;
}
