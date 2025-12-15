#include<iostream>

///---------------------------  00 template 多态
template<typename T>
class FTHello
{
public:
    virtual void hello(){
        std::cout << "Hello from FTHello!" << std::endl;
    }
private:
    T* data;
};

class FCHello : public FTHello<int>
{
    typedef FTHello<int> Base;
public:
    virtual void hello() override {
        //Base::hello();
        std::cout << "Hello from FCHello!" << std::endl;
    }
};
/// --------------------------- End template 多态

/// ---------------------------  01 MACRO test code

#define HELLO_CLASS(ClassName,Code,Format,...) \
template<class T> \
class F##ClassName\
{\
public:\
    void Work()\
    {\
        printf(#Format, __VA_ARGS__);\
        Code;\
    }\
private:\
    T* data;\
};

HELLO_CLASS(Hello, {std::cout << "Hello from macro!" << std::endl;},%s,"Hello from FHello Prinf!\n")
/// --------------------------- End MACRO test code


/// ---------------------------  02 单例 -----------------
/* 模板单例类: 对于每个不同的class，不需要重复编写单例代码*/
template <typename T>
class FSingleton {
public:
    
static T* getInstance() {
       
        if(!instance) 
        {
           instance = new T();
        }
        return instance;
    }

    static void destroyInstance() {
        delete instance;
        instance = nullptr;
    }
private:
    static T* instance;
};                    
/* 所有静态成员变量都要在类外初始化，即便是 template 类的静态成员变量*/
template <typename T>
T* FSingleton<T>::instance = nullptr;

class TestSingleton
{
public:
    void showMessage() {
        std::cout << "Hello from TestSingleton!" << std::endl;
    }
};

class TestSingleton2
{
public:
    void showMessage() {
        std::cout << "Hello from TestSingleton 2!" << std::endl;
    }
};

using TestSingletonInstance = FSingleton<TestSingleton>;
using TestSingletonInstance2 = FSingleton<TestSingleton2>;

/// --------------------------- End 单例 -----------------

/// --------------------------- 03 高阶宏替换 -----------------
typedef unsigned int uint8;

template <uint8 showMessageType>
class NetControlMessage
{
};

class FNetControlMessageInfo
{
public:
    template<typename ... ParamTypes>
    static void ReceiveParams(ParamTypes& ... params)
    {
        // 处理接收到的参数
    }

    template<typename ... ParamTypes>
    static void SendParams(ParamTypes& ... params)
    {
        // 处理接收到的参数
    }
};

/*
enum {NMT_AAA = 0};

template<>
class NetControlMessage<0>
{
public:
    template<typename ... ParamTypes>
    static void Receive(ParamTypes& ... params)
    {
        FNetControlMessageInfo::ReceiveParams(params...);
    }

    template<typename ... ParamTypes>
    static void Send(ParamTypes& ... params)
    {
        FNetControlMessageInfo::SendParams(params...);
    }
};
*/
// specialize
#define DEFINE_CONTOL_CHANNEL_MESSAGE(Name, Index, ...) \
enum {NMT_##Name = Index};\
template<>\
class NetControlMessage<Index>\
{\
public:\
    template<typename ... ParamTypes>\
    static void Receive(ParamTypes& ... params)\
    {\
        FNetControlMessageInfo::ReceiveParams(params...);\
    }\
    template<typename ... ParamTypes>\
    static void Send(ParamTypes& ... params)\
    {\
        FNetControlMessageInfo::SendParams(params...);\
    }\
};
/*
Templates are compile-time entities and must live at:
namespace scope (global scope), or
class scope (for member templates)
They cannot be inside:
functions
if, for, while, etc.
*/
DEFINE_CONTOL_CHANNEL_MESSAGE(Hello, 0, int, float, char);
DEFINE_CONTOL_CHANNEL_MESSAGE(World, 1, int, char);
/// --------------------------- End 高阶宏替换 -----------------


/// --------------------------- 04 可变参数 -----------------
template<typename T>
char PrintArg(T& arg) 
{
    std::cout << arg << std::endl;
    return 0;
}

template<typename... Args>
void PrintAll(Args& ... args) 
{
    char arr[] = {PrintArg(args) ...}; // 使用折叠表达式展开参数包
    /*arr[] = {0,0,0,0,0,}*/
};
/// --------------------------- End 可变参数 -----------------

/// --------------------------- 05 通过递归来遍历变参数 -----------------

void RecursivePrint() 
{
    std::cout<<std::endl;// 递归终止条件：没有参数时什么都不做
}

template<typename T, typename... Args>
void RecursivePrint(T& firstArg, Args& ... args)
{
    std::cout << firstArg << std::endl; // 处理第一个参数
    RecursivePrint(args...); // 递归调用，处理剩余参数
}
/// --------------------------- End 通过递归来遍历变参数 -----------------

///---------------------------  06 如何获取可变参数数量
template<typename ... ParamTypes>
void FuncLen(ParamTypes& ... params)
{
    constexpr size_t paramCount = sizeof...(params);
    std::cout << "Number of parameters: " << paramCount << std::endl;
}

///--------------------------- End 获取可变参数数量
int main() {
    // FCHello fcHello;
    // FTHello<int>* ftHello;
    // ftHello = &fcHello;
    // ftHello->hello();

/// MACRO
    // FHello<int> fHello;
    // fHello.Work();

/// 单例
//    TestSingletonInstance::getInstance()->showMessage();
//    TestSingletonInstance2::getInstance()->showMessage();

///  03 高阶宏替换
    // int a = 1;
    // float b = 2.0f;
    // char c = 'a';
    // NetControlMessage<NMT_Hello>::Send(a, b, c);
    // NetControlMessage<NMT_Hello>::Receive(a, b, c);

/// 04 可变参数
    // int x = 10;
    // float y = 20.5f;
    // std::string z = "Hello, Variadic Templates!";  
    // PrintAll(x, y, z);
/// 05 通过递归来遍历变参数
    int m = 100;
    double n = 200.5;
    std::string s = "Recursive Print!";
    RecursivePrint(m, n, s);
    return 0;
}