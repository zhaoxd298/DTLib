#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "LinuxList.h"
#include "DualLinkList.h"

namespace DTLib {

template <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head list;
        T value;
    };

    list_head m_header;
    list_head* m_current;

    int mod(int i) const
    {
        return (this->m_length==0) ? 0 : (i % this->m_length);
    }

    list_head* position(int i) const
    {
        list_head* ret = const_cast<list_head*>(&m_header);

        for (int p=0; p<i; p++) {
            ret = ret->next;
        }

        return ret;
    }

public:
    DualCircleList()
    {
        INIT_LIST_HEAD(&m_header);

        m_current = NULL;
        this->m_length = 0;
        this->m_step = 1;
    }

    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = true;
        Node* node = new Node();

        i = i % (this->m_length + 1);

        if (node) {
            node->value = e;

            list_add_tail(&(node->list), position(i)->next);   // ??
            this->m_length ++;
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "Not enough memory to insert node ...");
        }

        return ret;
    }

    bool remove(int i)
    {
        i = mod(i);

        bool ret = ((i>=0) && (i<=this->m_length));

        if (ret) {
            list_head* toDel = position(i)->next;

            if (m_current == toDel) {
                m_current = toDel->next;
            }

            list_del(toDel);

            this->m_length --;

            delete list_entry(toDel, Node, list);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        i = mod(i);

        bool ret = ((i>=0) && (i<=this->m_length));

        if (ret) {
            list_entry(position(i)->next, Node, list)->value = e;
        }

        return ret;
    }

    T get(int i) const       // O(n)
    {
        T ret;

        if (get(i, ret)) {
            return ret;
        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Get value error ...");
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        i = mod(i);

        bool ret = ((i>=0) && (i<=this->m_length));

        if (ret) {
            e = list_entry(position(i)->next, Node, list)->value;
        }

        return ret;
    }

    int find(const T& e) const
    {
        int ret = -1;
        int i = 0;
        list_head* slider = NULL;

        list_for_each(slider, &m_header)
        {
            if (list_entry(slider, Node, list)->value == e) {
                ret = i;
                break;
            }

            i++;
        }

        return ret;
    }

    int length() const
    {
        return this->m_length;
    }

    void clear()
    {
        while (this->m_length > 0) {
            remove(0);
        }
    }

    bool move(int i, int step = 1)
    {
        i = mod(i);

        bool ret = ((i>=0) && (i<=this->m_length));
        ret = ret && (step > 0);

        if (ret) {
            m_current = position(i)->next;

            this->m_step = step;
        }

        return ret;
    }

    bool end()
    {
        return (m_current == NULL) || (this->m_length == 0);
    }

    T current()
    {
        if (!end()) {
            return list_entry(m_current, Node, list)->value;
        } else {
            THROW_EXCEPTION(InvalidOperaionException, "No value at current position ...");
        }
    }

    bool next()
    {
        int i = 0;

        while ( (i<this->m_step) && !end() ) {
            if (m_current == &m_header) {
                m_current = m_current->next;
            } else {
                m_current = m_current->next;
                i++;
            }
        }

        if (m_current == &m_header) {
            m_current = m_current->next;
        }

        return (i == this->m_step);
    }

    bool prev()
    {
        int i = 0;

        while ( (i<this->m_step) && !end() ) {
            if (m_current == &m_header) {
                m_current = m_current->prev;
            } else {
                m_current = m_current->prev;
                i++;
            }
        }

        if (m_current == &m_header) {
            m_current = m_current->prev;
        }

        return (i == this->m_step);
    }

    ~DualCircleList()
    {
        clear();
    }

};

}


#endif // DUALCIRCLELIST_H
