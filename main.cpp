#include <iostream>
#include <string>
#include "mysharedptr.h"

template <typename T>
void copy_func_test(MySharedPtr<T> ptr)
{
    std::cout << "Func. Ptr passed as value. It contains \"" << *ptr << "\"" << std::endl;
}

template <typename T>
void link_func_test(MySharedPtr<T> &ptr)
{
    std::cout << "Func. Ptr passed as link. It contains \"" << *ptr << "\"" << std::endl;
}

int main()
{
    MySharedPtr<std::string> strPtr = new std::string("my std::string");
    std::cout << "Ptr created. It contains \"" << *strPtr << "\"" << std::endl;
    MySharedPtr<std::string> copyPtr1 = strPtr;
    std::cout << "Copy 1 created. Values. Original: \"" << *strPtr << "\"" << ", Copy: \"" << *copyPtr1 << "\"" << std::endl;
    MySharedPtr<std::string> copyPtr2;
    copyPtr2 = strPtr;
    std::cout << "Copy 2 created. Values. Original: \"" << *strPtr << "\"" << ", Copy: \"" << *copyPtr2 << "\"" << std::endl;
    std::cout << "Cycle test. Strating cycle" << std::endl;
    for(int i = 1; i < 2; ++i)
    {
        MySharedPtr<std::string> cyclePtr = strPtr;
        std::cout << "Value in cycle: \"" << *cyclePtr << "\"" << std::endl;
    }
    std::cout << "Cycle ended" << std::endl;
    copy_func_test(strPtr);
    link_func_test(strPtr);

    std::cout << "CREATING POINTER" << std::endl;
    MySharedPtr<std::string> mptr;
    for(int i = 1; i < 2; i++)
    {
        std::cout << "ASSIGNING VALUE IN CYCLE" << std::endl;
        mptr = MySharedPtr<std::string>(new std::string("created in cycle"));
        std::cout << "VALUE: \"" << *mptr << "\"" << std::endl;
    }
    std::cout << "VALUE JUST AFTER END OF CYCLE: \"" << *mptr << "\"" << std::endl;
    std::cout << "ASSIGNING VALUE OUT OF CYCLE" << std::endl;
    mptr = MySharedPtr<std::string>(new std::string("created not in cycle"));
    std::cout << "VALUE: \"" << *mptr << "\"" << std::endl;
    return 0;
}
