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
#include "Sort.h"

using namespace std;
using namespace DTLib;


int main()
{
    StaticArray<double, 10> a; //= {4, 1, 8, 3, 10, 6, 5, 9, 7, 2};
    for (int i=0; i<10; i++) {
        a[i] = i;
    }
    Sort::insert(a, 0);

    for (int i=0; i<10; i++) {
        cout << a[i] << endl;
    }

    return 0;
}
