#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    T* copy(T* array, int length, int newLen);
    void update(T* array, int length);
    void init(T* array, int length);
public:
    DynamicArray(int length);

    DynamicArray(DynamicArray<T>& obj);
    DynamicArray<T>& operator= (const DynamicArray<T>& obj);

    int length() const;
    void resize(int length);

    ~DynamicArray();
};

template <typename T>
T* DynamicArray<T>::copy(T* array, int length, int newLen)
{
    T* ret = new T[newLen];

    if (NULL != ret) {
        int size = (length < newLen) ? length : newLen;

        for (int i=0; i<size; i++) {
            ret[i] = array[i];
        }
    }

    return ret;
}

template <typename T>
void DynamicArray<T>::update(T* array, int length)
{
   if (NULL != array) {
       T* temp = this->m_array;

       this->m_array = array;
       this->m_length = length;

       delete[] temp;
    } else {
        THROW_EXCEPTION(NoEnoughMemoryException, "NO memory to copy DynamicArray object...");
    }
}

template <typename T>
void DynamicArray<T>::init(T* array, int length)
{
    if (NULL != array) {
        this->m_array = array;
        this->m_length = length;
    } else {
        THROW_EXCEPTION(NoEnoughMemoryException, "NO memory to create DynamicArray object...");
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(int length)
{
    init(new T[length], length);
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>& obj)
{
    init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator= (const DynamicArray<T>& obj)
{
    if (this != &obj) {

        update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    return *this;
}

template <typename T>
int DynamicArray<T>::length() const
{
    return m_length;
}

template <typename T>
void DynamicArray<T>::resize(int length)
{
    if (length != m_length) {

        update(copy(this->m_array, m_length, length), length);
    }
}


template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] this->m_array;
}


}






#endif
