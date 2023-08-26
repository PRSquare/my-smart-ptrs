#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H

template <typename T>
class MySharedPtr
{
public:
    MySharedPtr();
    MySharedPtr(T *val);
    MySharedPtr& operator=(const MySharedPtr<T> &ptr);
    MySharedPtr(const MySharedPtr<T> &ptr);
    T& operator *();
    ~MySharedPtr();
private:
    unsigned long long *refs_amount;
    T* val;
    void take_val(const MySharedPtr<T> &ptr);
};

template <typename T>
MySharedPtr<T>::MySharedPtr()
{
    this->val = nullptr;
    this->refs_amount = nullptr;
}

template <typename T>
MySharedPtr<T>::MySharedPtr(T *val)
{
    this->val = val;
    this->refs_amount = new unsigned long long;
    *(this->refs_amount) = 1;
}

template <typename T>
MySharedPtr<T>& MySharedPtr<T>::operator=(const MySharedPtr<T> &ptr)
{
    this->take_val(ptr);
    return *this;
}

template <typename T>
MySharedPtr<T>::MySharedPtr(const MySharedPtr<T> &ptr)
{
    this->val = nullptr;
    this->refs_amount = nullptr;
    this->take_val(ptr);
}

template <typename T>
T& MySharedPtr<T>::operator *()
{
    return *(this->val);
}

template <typename T>
MySharedPtr<T>::~MySharedPtr()
{
    if (this->refs_amount != nullptr)
    {
        --*(this->refs_amount);
        if(!*(this->refs_amount))
        {
            delete val;
            delete refs_amount;
        }
    }
}

template <typename T>
void MySharedPtr<T>::take_val(const MySharedPtr<T> &ptr)
{
    if (this->refs_amount != nullptr)
    {
        --*(this->refs_amount);
        if (*(this->refs_amount) == 0)
        {
            delete this->refs_amount;
            if (this->val)
                delete this->val;
        }
    }
    this->refs_amount = ptr.refs_amount;
    ++*(this->refs_amount);
    this->val = ptr.val;
}


#endif
