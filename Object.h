#ifndef OBJECT_H
#define OBJECT_H

namespace DTLib {

class Object
{
public:
    void* operator new (unsigned int size) throw(); // throw() 代表不抛出任何异常
    void operator delete (void* p);
    void* operator new[] (unsigned int size) throw();
    void operator delete[] (void* p);
    bool operator == (const Object& obj);
    bool operator != (const Object& obj);
    virtual ~Object() = 0;
};

}


#endif // OBJECT_H
