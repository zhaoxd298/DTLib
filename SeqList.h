#ifndef SEQLIST_H
#define SEQLIST_H
#include "Exception.h"

#include "List.h"

namespace DTLib {

template <typename T>
class SeqList : public List<T>
{
protected:
    T* m_array;     // 顺序存储空间
    int m_length;   // 当前线性表长度
public:
    bool insert(const T& e);
    bool insert(int i, const T& e);
    bool remove(int i);
    bool set(int i, const T& e);
    bool get(int i, T& e) const;
    int find(const T& e) const;
    int length() const;
    void clear();
    // 顺序存储线性表的数组访问方式
    T& operator[] (int i);
    T operator[] (int i) const;
    // 顺序存储空间的容量
    virtual int capacity() const = 0;
};

template <typename T>
bool SeqList<T>::insert(const T& e)
{
    return insert(m_length, e);
}

template <typename T>
bool SeqList<T>::insert(int i, const T& e)
{
    bool ret = ((0<=i) && (i<=length()));

    ret = ret && (m_length < capacity());

    if (ret) {
        for (int p=m_length-1; p>=i; p--) {
            m_array[p+1] = m_array[p];
        }

        m_array[i] = e;

        m_length++;
    }

    return ret;
}

template <typename T>
bool SeqList<T>::remove(int i)
{
    bool ret = ((0<=i) && (i<length()));

    if (ret) {
        for (int p=i; i<m_length-1; p++) {
            m_array[p] = m_array[p+1];
        }

        m_length--;
    }

    return ret;
}

template <typename T>
bool SeqList<T>::set(int i, const T& e)
{
    bool ret = ((0<=i) && (i<length()));

    if (ret) {
        m_array[i] = e;
    }

    return ret;
}

template <typename T>
bool SeqList<T>::get(int i, T& e) const
{
    bool ret = ((0<=i) && (i<length()));

    if (ret) {
        e = m_array[i];
    }

    return ret;
}

template <typename T>
int SeqList<T>::find(const T& e) const  // O(n)
{
    int ret = -1;

    for (int i=0; i<m_length; i++) {
        if (m_array[i] == e) {
            ret = i;
            break;
        }
    }

    return ret;
}

template <typename T>
int SeqList<T>::length() const
{
    return m_length;
}

template <typename T>
void SeqList<T>::clear()
{
    m_length = 0;
}

template <typename T>
T& SeqList<T>::operator[] (int i)
{
    bool ret = ((0<=i) && (i<length()));

    if (ret) {
        return m_array[i];
    } else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is inbalid");
    }
}

template <typename T>
T SeqList<T>::operator[] (int i) const
{
    return (const_cast<SeqList<T>&>(*this))[i]; // 去掉const属性，以调用非construction实现(T& operator[] (int i))
}

}


#endif // SEQLIST_H
