#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include "Array.h"

namespace DTLib {


class Sort : public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator = (const Sort&);

    template <typename T>
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

    template <typename T>
    static void merge(T src[], T helper[], int begin, int mid, int end, bool min2max)
    {
        int i = begin;
        int j = mid+1;
        int k = begin;

        while ((i<=mid) && (j<=end)) {
            if (min2max ? (src[i]<src[j]) : (src[i]>src[j])) {
                helper[k++] = src[i++];
            } else {
                helper[k++] = src[j++];
            }
        }

        while (i <= mid) {
            helper[k++] = src[i++];
        }

        while (j <= end) {
            helper[k++] = src[j++];
        }

        for(i=begin; i<=end; i++) {
            src[i] = helper[i];
        }
    }

    template <typename T>
    static void merge(T src[], T helper[], int begin, int end, bool min2max)
    {
        if (begin < end) {
            int mid = (begin + end) / 2;

            merge(src, helper, begin, mid, min2max);        // 对左边进行归并排序
            merge(src, helper, mid+1, end, min2max);        // 对右边进行归并排序
            merge(src, helper, begin, mid, end, min2max);   // 对上面划分的两路进行归并
        }
    }

    template <typename T>
    static int partition(T array[], int begin, int end, bool min2max)
    {
        T pv = array[begin];

        while (begin < end)
        {
            while ((begin<end) && (min2max ? (array[end]>pv) : (array[end]<pv)) ) {
                end--;
            }

            Swap(array[begin], array[end]);

            while ((begin<end) && (min2max ? (array[begin]<=pv) : (array[begin]>=pv))) {
                begin++;
            }

            Swap(array[begin], array[end]);
        }

        array[begin] = pv;

        return begin;
    }

    template <typename T>
    static void quick(T array[], int begin, int end, bool min2max)
    {
        if (begin < end) {
            int pivot = partition(array, begin, end, min2max);

            quick(array, begin, pivot-1, min2max);
            quick(array, pivot+1, end, min2max);
        }
    }

public:
    // 选择排序
    template <typename T>
    static void select(T array[], int len, bool min2max = true)
    {
        int min = 0;
        for (int i=0; i<len; i++) {
            min = i;
            for (int j=i+1; j<len; j++) {
                if (min2max ? (array[min] > array[j]) : (array[min] < array[j])) {
                    min = j;
                }
            }
            if (min != i) {
                Swap(array[min], array[i]);
            }
        }
    }

    template <typename T>
    static void select(Array<T>& array, bool min2max)
    {
        select(array.array(), array.length(), min2max);
    }

    // 插入排序
    template <typename T>
    static void insert(T array[], int len, bool min2max = true)
    {
        int k;
        for (int i=1; i<len; i++) {
            k = i;
            T e = array[i];

            for (int j=i-1; j>=0; j--) {
                if (min2max ? (array[j]>e) : (array[j]<e)) {
                    k = j;
                    array[j+1] = array[j];
                } else {
                    break;
                }
            }

            if (k != i) {
                array[k] = e;
            }
        }
    }

    template <typename T>
    static void insert(Array<T>& array, bool min2max)
    {
        insert(array.array(), array.length(), min2max);
    }

    // 冒泡排序
    template <typename T>
    static void bubble(T array[], int len, bool min2max = true)
    {
        bool exchange = true;

        for (int i=0; (i<len) && exchange; i++) {
            exchange = false;

            for (int j=len-1; j>i; j--) {
                if (min2max ? (array[j]>array[j-1]) : (array[j]<array[j-1])) {
                    Swap(array[j], array[j-1]);
                    exchange = true;
                }
            }
        }
    }

    template <typename T>
    static void bubble(Array<T>& array, bool min2max)
    {
        bubble(array.array(), array.length(), min2max);
    }

    // 希尔排序
    template <typename T>
    static void shell(T array[], int len, bool min2max = true)
    {
        int d = len;

        do {
            d = d / 3 + 1;

            for (int i=d; i<len; i+=d) {
                int k = i;
                T e = array[i];

                for (int j=i-d; j>=0; j-=d) {
                    if (min2max ? (array[j]>e) : (array[j]<e)) {
                        k = j;
                        array[j+d] = array[j];
                    } else {
                        break;
                    }
                }

                if (k != i) {
                    array[k] = e;
                }
            }
        } while (d > 1);
    }

    template <typename T>
    static void shell(Array<T>& array, bool min2max)
    {
        shell(array.array(), array.length(), min2max);
    }

    // 归并排序
    template <typename T>
    static void merge(T array[], int len, bool min2max = true)
    {
        T* helper = new T[len];

        if (helper != NULL) {
            merge(array, helper, 0, len-1, min2max);
        }

        delete[] helper;
    }

    template <typename T>
    static void merge(Array<T>& array, bool min2max)
    {
        merge(array.array(), array.length(), min2max);
    }

    // 快速排序
    template <typename T>
    static void quick(T array[], int len, bool min2max = true)
    {
        quick(array, 0, len-1, min2max);
    }

    template <typename T>
    static void quick(Array<T>& array, bool min2max)
    {
        quick(array.array(), array.length(), min2max);
    }
};

}


#endif // SORT_H
