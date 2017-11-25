#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DTLib {

template <typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_top;
    int m_size;

public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity() const
    {
        return N;
    }

    void push(const T& e)
    {
        if (m_size < N) {
            m_space[m_top + 1] = e;     // 先赋值，再改变m_top 和m_size，是为了异常安全

            m_top ++;
            m_size ++;
        } else {
            THROW_EXCEPTION(InvalidOperaionException, "No space in current stack ...");
        }
    }

    void pop()
    {
        if (m_size > 0) {
            m_top --;
            m_size --;
        } else {
            THROW_EXCEPTION(InvalidOperaionException, "No element in current stack ...");
        }
    }

    T top()
    {
        if (m_size > 0) {
            return m_space[m_top];
        } else {
            THROW_EXCEPTION(InvalidOperaionException, "No element in current stack ...");
        }
    }

    void clear()
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const
    {
        return m_size;
    }
};

}

#endif // STATICSTACK_H
