#include <cstring>
#include <cstdlib>
#include "DTString.h"
#include "Exception.h"

using namespace std;

namespace DTLib {

void String::init(const char* s)
{
    m_str = strdup(s ? s : "");
    if (m_str) {
        m_length = strlen(m_str);
    } else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create string ...");
    }
}

bool String::equal(const char* l, const char* r, int len) const
{
    bool ret = ((l != NULL) && (r != NULL) && (len > 0));

    if (ret) {
        for (int i=0; i<len && ret; i++) {
            ret = (l[i] == r[i]);
        }
    }

    return ret;
}

String::String()
{
    init("");
}

String::String(char c)
{
    char s[] = {c, '\0'};

    init(s);
}

String::String(const char* s)
{
    init(s);
}

String::String(const String& s)
{
    init(s.m_str);
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

char& String::operator [] (int i)
{
    if ((0 <= i) && (i < m_length)) {
        return m_str[i];
    } else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid index ...");
    }
}

char String::operator [] (int i) const
{
    return const_cast<String&>(*this)[i];
}

bool String::startWith(const char* s) const
{
    bool ret = (s != NULL);

    if (ret) {
        int len = strlen(s);

        ret = (len <= m_length) && equal(m_str, s, len);
    }

    return ret;
}

bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}

bool String::endOf(const char* s) const
{
    bool ret = (s != NULL);

    if (ret) {
        int len = strlen(s);
        char* str = m_str + m_length - len;

        ret = (len <= m_length) && equal(str, s, len);
    }

    return ret;
}

bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

String& String::insert(int i, const char* s)
{
    if ((0 <= i) && (i <= m_length)) {
        if ((s != NULL) && (s[0] != '\0')) {
            int len = strlen(s);
            char* str = reinterpret_cast<char*>(malloc(m_length + len + 1));

            if (str) {
                strncpy(str, m_str, i);
                strncpy(str + i, s, len);
                strncpy(str + i + len, m_str + i, m_length - i);
                str[m_length + len] = '\0';

                free(m_str);
                m_str = str;
                m_length += len;
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert string value ...")    ;
            }
        }
    } else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid paramter ...");
    }

    return *this;
}

String& String::insert(int i, const String& s)
{
    return insert(i, s.m_str);
}

String& String::trim()
{
    int b = 0;
    int e = m_length - 1;

    while (m_str[b] == ' ') {
        b++;
    }

    while (m_str[e] == ' ') {
        e--;
    }

    if (0 == b) {
        m_str[e + 1] = '\0';
    } else {
        for (int i=0, j=b; j<=e; i++, j++) {
            m_str[i] = m_str[j];
        }

        m_str[e - b + 1] = '\0';
        m_length = e - b + 1;
    }


    return *this;
}

bool String::operator == (const String& s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}
bool String::operator == (const char* s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}
bool String::operator != (const String& s) const
{
    return !(*this == s);
}
bool String::operator != (const char* s) const
{
    return !(*this == (s ? s : ""));
}

bool String::operator > (const String& s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}
bool String::operator > (const char* s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}
bool String::operator < (const String& s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}
bool String::operator < (const char* s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}
bool String::operator >= (const String& s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}
bool String::operator >= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}
bool String::operator <= (const String& s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}
bool String::operator <= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

String String::operator + (const String& s) const
{
    return (*this + s.m_str);
}

String String::operator + (const char* s) const
{
    String ret;

    int len = m_length + strlen(s ? s : "");
    char* str = reinterpret_cast<char*>(malloc(len + 1));
    if (str) {
        strcpy(str, m_str);
        strcat(str, s ? s : "");

        free(ret.m_str);
        ret.m_str = str;
        ret.m_length = len;
    } else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add string ...");
    }

    return ret;
}

String& String::operator += (const String& s)
{
    *this = *this + s.m_str;

    return *this;
}

String& String::operator += (const char* s)
{
    *this = *this + (s ? s : "");

    return *this;
}

String& String::operator = (const String& s)
{
    *this = s.m_str;

    return *this;
}

String& String::operator = (const char* s)
{
    if (m_str != s) {
        char* str = strdup(s ? s : "");
        if (str) {
            free(m_str);
            m_str = str;
            m_length = strlen(m_str);
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create string ...");
        }
    }

    return *this;
}

String& String::operator = (const char c)
{
    char s[] = {c, '\0'};
    *this = s;

    return *this;
}

String::~String()
{
    free(m_str);
}

}


