#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib {

template <typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
        Node* prev;
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
        Node* prev;
    } m_header;
    int m_length;

    int m_step;
    Node* m_current;

    Node *position(int i) const     // O(n)
    {
        Node* current = reinterpret_cast<Node*>(&m_header);

        for (int p=0; p<i; p++) {
            current = current->next;
        }

        return current;
    }
    virtual Node* create()
    {
        return new Node();
    }
    virtual void destroy(Node* pn)
    {
        delete pn;
    }

public:
    DualLinkList();
    ~DualLinkList();
    virtual bool insert(const T& e);
    virtual bool insert(int i, const T& e);
    virtual bool remove(int i);
    virtual bool set(int i, const T& e);
    virtual bool get(int i, T& e) const;
    virtual int find(const T& e) const;
    virtual T get(int i) const;
    virtual int length() const;
    virtual void clear();

    virtual bool move(int i, int step = 1);
    virtual bool end();
    virtual T current();
    virtual bool next();
    virtual bool prev();
};

template <typename T>
DualLinkList<T>::DualLinkList()
{
    m_length = 0;
    m_header.next = NULL;
    m_header.prev = NULL;

    m_step = 1;
    m_current = NULL;
}

template <typename T>
DualLinkList<T>::~DualLinkList()
{
    clear();
}

template <typename T>
bool DualLinkList<T>::insert(const T& e)
{
    return insert(m_length, e);
}

template <typename T>
bool DualLinkList<T>::insert(int i, const T& e)     // O(n)
{
    bool ret = ((i>=0) && (i<=m_length));

    if (ret) {
        Node* node = create();
        if (node) {
            node->value = e;

            Node* current = position(i);
            Node* next = current->next;

            node->next = next;
            current->next = node;

            if (current != reinterpret_cast<Node*>(&m_header)) {
                node->prev = current;
            } else {
                node->prev = NULL;
            }

            if (NULL != next) {
                next->prev = node;
            }

            m_length ++;
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "Create Node error");
        }
    }

    return ret;
}

template <typename T>
bool DualLinkList<T>::remove(int i)     // O(n)
{
    bool ret = ((i>=0) && (i<m_length));

    if (ret) {
        Node* current = position(i);
        Node* toDel = current->next;
        Node* next = toDel->next;

        if (m_current == toDel) {
            m_current = next;
        }

        current->next = next;
        if (NULL != next) {
            next->prev = toDel->prev;
        }

        m_length --;

        destroy(toDel);
    }

    return ret;
}

template <typename T>
bool DualLinkList<T>::set(int i, const T& e)       // O(n)
{
    bool ret = ((i>=0) && (i<m_length));

    if (ret) {
        position(i)->next->value = e;
    }

    return ret;
}

template <typename T>
bool DualLinkList<T>::get(int i, T& e) const       // O(n)
{
    bool ret = ((i>=0) && (i<m_length));

    if (ret) {
        e = position(i)->next->value;
    }

    return ret;
}

template <typename T>
int DualLinkList<T>::find(const T& e) const       // O(n)
{
    int ret = -1;
    int i = 0;
    Node* node = m_header.next;

    while (node) {
        if (node->value == e) {
            ret = i;
            break;
        } else {
            node = node->next;
            i++;
        }
    }

    return ret;
}

template <typename T>
T DualLinkList<T>::get(int i) const       // O(n)
{
    T ret;

    if (get(i, ret)) {
        return ret;
    } else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Get value error ...");
    }

    return ret;
}



template <typename T>
int DualLinkList<T>::length() const       // O(1)
{
    return m_length;
}

template <typename T>
void DualLinkList<T>::clear()       // O(n)
{
    while (m_length > 0) {
        remove(0);
    }
}


template <typename T>
bool DualLinkList<T>::move(int i, int step)
{
    bool ret = (i>=0) && (i<m_length) && (step>0);

    if (ret) {
        m_current = position(i)->next;
        m_step = step;
    }

    return ret;
}

template <typename T>
bool DualLinkList<T>::end()
{
    return (m_current == NULL);
}

template <typename T>
T DualLinkList<T>::current()
{
    if (!end()) {
        return m_current->value;
    } else {
        THROW_EXCEPTION(InvalidOperaionException, "No value at current position ...");
    }

}

template <typename T>
bool DualLinkList<T>::next()
{
    int i = 0;

    while ( (i<m_step) && !end() ) {
        m_current = m_current->next;
        i++;
    }

    return (i == m_step);
}

template <typename T>
bool DualLinkList<T>::prev()
{
    int i = 0;

    while ( (i<m_step) && !end() ) {
        m_current = m_current->prev;
        i++;
    }

    return (i == m_step);
}

}

#endif // DUALLINKLIST_H
