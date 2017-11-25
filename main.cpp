#include <iostream>

#include "DynamicList.h"
#include "StaticList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "StaticLinkList.h"
#include "SmartPointer.h"
#include "SharedPointer.h"
#include "CircleList.h"
#include "DualLinkList.h"
#include "DualCircleList.h"
#include "StaticStack.h"
#include "LinkStack.h"
#include "StaticQueue.h"
#include "LinkQueue.h"
#include "DTString.h"

using namespace std;
using namespace DTLib;


int main()
{
    String s = "  hel  lo!      ";

    (s.trim())[0]='H';
    cout << "[" << s.str() << "]" << endl;

    return 0;
}
