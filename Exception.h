#ifndef EXCEPTION_H
#define EXCEPTION_H
#include "Object.h"

namespace DTLib {

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
protected:
    char* m_message;
    char* m_location;

    void init(const char* message, const char* file, int line);
public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator= (const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception() = 0;   // 析构函数不管是否为纯虚函数都需要提供具体实现
};

class ArithmeticException : public Exception
{
public:
    ArithmeticException() : Exception(0) {}
    ArithmeticException(const char* message) : Exception(message) {}
    ArithmeticException(const char* file, int line) : Exception(file, line) {}
    ArithmeticException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    ArithmeticException(const ArithmeticException& e) : Exception(e) {}

    ArithmeticException& operator= (const ArithmeticException&e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class NullPointerException : public Exception
{
public:
    NullPointerException() : Exception(0) {}
    NullPointerException(const char* message) : Exception(message) {}
    NullPointerException(const char* file, int line) : Exception(file, line) {}
    NullPointerException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    NullPointerException(const NullPointerException& e) : Exception(e) {}

    NullPointerException& operator= (const NullPointerException&e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException() : Exception(0) {}
    IndexOutOfBoundsException(const char* message) : Exception(message) {}
    IndexOutOfBoundsException(const char* file, int line) : Exception(file, line) {}
    IndexOutOfBoundsException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e) {}

    IndexOutOfBoundsException& operator= (const IndexOutOfBoundsException&e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class NoEnoughMemoryException : public Exception
{
public:
    NoEnoughMemoryException() : Exception(0) {}
    NoEnoughMemoryException(const char* message) : Exception(message) {}
    NoEnoughMemoryException(const char* file, int line) : Exception(file, line) {}
    NoEnoughMemoryException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    NoEnoughMemoryException(const NoEnoughMemoryException& e) : Exception(e) {}

    NoEnoughMemoryException& operator= (const NoEnoughMemoryException&e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class InvalidParameterException : public Exception
{
public:
    InvalidParameterException() : Exception(0) {}
    InvalidParameterException(const char* message) : Exception(message) {}
    InvalidParameterException(const char* file, int line) : Exception(file, line) {}
    InvalidParameterException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    InvalidParameterException(const InvalidParameterException& e) : Exception(e) {}

    InvalidParameterException& operator= (const InvalidParameterException&e)
    {
        Exception::operator =(e);

        return *this;
    }
};

class InvalidOperaionException : public Exception
{
public:
    InvalidOperaionException() : Exception(0) {}
    InvalidOperaionException(const char* message) : Exception(message) {}
    InvalidOperaionException(const char* file, int line) : Exception(file, line) {}
    InvalidOperaionException(const char* message, const char* file, int line) : Exception(message, file, line) {}

    InvalidOperaionException(const InvalidOperaionException& e) : Exception(e) {}

    InvalidOperaionException& operator= (const InvalidOperaionException&e)
    {
        Exception::operator =(e);

        return *this;
    }
};

}

#endif // EXCEPTION_H
