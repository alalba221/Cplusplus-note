#include<iostream>

//--------------------------- template 多态
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
// --------------------------- End template 多态

// --------------------------- MACRO test code

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
// --------------------------- End MACRO test code


// --------------------------- 单例 -----------------
// 模板单例类: 对于每个不同的class，不需要重复编写单例代码
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

// --------------------------- End 单例 -----------------


int main() {
    // FCHello fcHello;
    // FTHello<int>* ftHello;
    // ftHello = &fcHello;
    // ftHello->hello();

/// MACRO
    // FHello<int> fHello;
    // fHello.Work();

/// 单例
   TestSingletonInstance::getInstance()->showMessage();
   TestSingletonInstance2::getInstance()->showMessage();
    return 0;
}