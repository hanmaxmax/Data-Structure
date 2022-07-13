#pragma once
#include<iostream>
using namespace std;

int Quick_swap = 0;
int Quick_com = 0;

void QSwap(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
    Quick_swap++;
}


void QuickSort(int arry[], int low, int high) 
{
    if (low >= high) return;
    int i = low, j = high;
    int temp = arry[low];
    while (i < j) 
    {
        while (i < j && arry[j] >= temp)
        {
            j--;
            Quick_com++;
        }

        if (i < j) 
        {
            arry[i] = arry[j];
            i++;
            Quick_swap++;
        }
        while (i < j && arry[i] < temp)
        {
            ++i;
            Quick_com++;
        }
        if (i < j) 
        {
            arry[j] = arry[i];
            j--;
            Quick_swap++;
        }
    }
    arry[i] = temp;//��ֵ�ع�
    Quick_swap++;

    QuickSort(arry, i + 1, high);
    QuickSort(arry, low, i - 1);
}



void QuickSort(int a[], int len) //len�������С
{
    if (len <= 1) return;

    QuickSort(a, 0, len - 1);
    //quickSort(a, 0, len - 1);

    ////��ӡ���
    //cout << "QuickSort: " << endl;
    //for (int i = 0; i < len; i++)
    //{
    //    cout << a[i] << " ";
    //}
    //cout << endl << endl;
}

void QuickCount(int& a, int& b)
{
    a = Quick_swap;
    b = Quick_com;
    cout << "QuickCount:" << endl;
    cout << "Swap: " << a << endl;
    cout << "Compare: " << b << endl << endl;
}





//template<class T>
//int indexOfMax(T a[], int n)
//{//  ���� a[0:n-1] ������Ԫ�ص� �±�indexOfMax
//    int indexOfMax = 0;
//    for (int i = 1; i < n; i++)
//        if (a[indexOfMax] < a[i])
//            indexOfMax = i;
//    return indexOfMax;
//}

//
//template <class T>
//void quickSort(T a[], int n)
//{// �� a[0 : n - 1] ���п�������
//    if (n <= 1) return;
//    // move largest element to right end
//    int max = indexOfMax(a, n); //max�� a[0:n - 1] ������Ԫ�ص��±�
//    swap(a[n - 1], a[max]);
//    quickSort(a, 0, n - 2);
//}



//
//void quickSort(int a[], int leftEnd, int rightEnd)
//{// Sort a[leftEnd:rightEnd]
// // a[rightEnd+1] >= a[leftEnd:rightEnd].
//    if (leftEnd >= rightEnd) return;
//
//    int leftCursor = leftEnd,        // left-to-right ����
//        rightCursor = rightEnd + 1;  // right-to-left �ҹ��
//    int pivot = a[leftEnd];            // ���� ����ߵ���leftEnd
//
//    // swap elements >= pivot on left side
//    // with elements <= pivot on right side
//    while (true)
//    {
//        do
//        {// find >= element on left side
//            //Ϊʲô�� do while ������ while�� LeftCursor = LeftEnd �������ᣬû��Ҫ���Լ����Լ���һ��
//            leftCursor++;
//        } while (a[leftCursor] < pivot);
//
//        do
//        {// find <= element on right side
//            //Ϊʲô�� do while ������ while�� rightCursor = rightEnd + 1��Ҫ�ȼ�һ��һ��ʹ rightCursor = rightEnd
//            rightCursor--;
//        } while (a[rightCursor] > pivot);
//
//        if (leftCursor >= rightCursor) break;  // swap pair not found
//        QSwap(a[leftCursor], a[rightCursor]);
//    }
//
//    // place pivot
//    a[leftEnd] = a[rightCursor];
//    a[rightCursor] = pivot;
//
//    quickSort(a, leftEnd, rightCursor - 1);   // sort left segment
//    quickSort(a, rightCursor + 1, rightEnd);  // sort right segment
//}
//

