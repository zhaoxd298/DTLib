#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;       // 计数机制成员指针

    void assign(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if (this->m_ref) {
            (*this->m_ref) ++;
        }
    }
public:
    SharedPointer(T* p=NULL) : Pointer<T>(p), m_ref(NULL)
    {
        if (p) {
            this->m_ref = new int;
            if (this->m_ref) {
                *(this->m_ref) = 1;
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer object ...");
            }
        }
    }
    SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL)
    {
        assign(obj);
    }
    SharedPointer<T>& operator = (const SharedPointer<T>& obj)
    {
        if (this != &obj) {
            clear();

            assign(obj);
        }

        return *this;
    }
    void clear()
    {
        int* ref = this->m_ref;
        T* toDel = this->m_pointer;

        this->m_ref = NULL;
        this->m_pointer = NULL;

        if (ref) {
            (*ref) --;

            if (0 == *ref) {
                delete ref;
                delete toDel;
            }
        }
    }
    ~SharedPointer()
    {
        clear();
    }
};

template <typename T>
bool operator == (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (l.get() == r.get());
}

template <typename T>
bool operator != (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return !(l == r);
}

}

#endif // SHAREDPOINTER_H
