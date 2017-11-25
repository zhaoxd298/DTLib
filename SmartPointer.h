#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace DTLib {

template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p)
    {

    }

    // 重载拷贝构造函数保证一片堆空间中最多只能由一个指针标识
    SmartPointer(const SmartPointer<T>& obj) : Pointer<T>(NULL)
    {
        this->m_pointer = obj.m_pointer;

        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    // 重载赋值函数保证一片堆空间中最多只能由一个指针标识
    SmartPointer<T>& operator= (const SmartPointer<T>& obj)
    {
        if (this != &obj) {
            T* p = this->m_pointer;

            this->m_pointer = obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

            delete p;
        }

        return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};

}

#endif // SMARTPOINTER_H
