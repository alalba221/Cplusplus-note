#include<iostream>

/// --------------------------- 00 通过模版偏特化来获取可变参数大小-----------------

template<typename T, typename... Args>
class FuncLen
{
public:
    enum 
    {
        Number = FuncLen<T>::Number + FuncLen<Args...>::Number
    };
};

template<typename LastType>
class FuncLen<LastType>
{
public:
   enum 
   {
      Number = sizeof(LastType)
   };

};

#define DDD(Name, ...) FuncLen<__VA_ARGS__> Name;
/// -------------------------------------------------


int main() 
{
/// 00 通过模版偏特化来获取可变参数大小
    FuncLen<int, float, double, char> Len;
    std::cout << "Number of parameters: " << Len.Number << std::endl;

    DDD(myFuncLen, int, float, double, char, long);
    std::cout << "Number of parameters (macro): " << myFuncLen.Number << std::endl;
    return 0;
}