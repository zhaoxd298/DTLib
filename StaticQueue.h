#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace DTLib {

template <typename T, int N>
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];   // 存储空间
    int m_front;    // 对头标识
    int m_rear;     // 队尾标识
    int m_length;   // 当前队列的长度
public:
    StaticQueue()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int capacity() const    // O(1)
    {
        return N;
    }

    void add(const T& e)    // O(1)
    {
        if (m_length < N) {
            m_space[m_rear] = e;
            m_rear = (m_rear + 1) % N;  // 采用循环计数，以提高效率
            m_length ++;
        } else {
            THROW_EXCEPTION(InvalidOperaionException, "No space in current queue ...");
        }
    }

    void remove()    // O(1)
    {
        if (m_length > 0) {
            m_front = (m_front + 1) % N;  // 采用循环计数，以提高效率
            m_length --;
        } else {
            THROW_EXCEPTION(InvalidOperaionException, "No element in current queue ...");
        }
    }

    T front()    // O(1)
    {
        if (m_length > 0) {
            return m_space[m_front];
        } else {
            THROW_EXCEPTION(InvalidOperaionException, "No element in current queue ...");
        }
    }

    void clear()    // O(1)
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int length() const    // O(1)
    {
        return m_length;
    }
};

}

#endif // STATICQUEUE_H
