//
//  QS_Randomized_QS_Select.cpp
//
//  Created by 罗铮 on 10/8/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int length = 10;

// Print the array
void print(int input[])
{
    for(int i = 0; i < length; i++ )
        cout << input[i] << " ";

    cout << endl;
}

// The swap function
inline void exchange(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Partitioning the array
int Partition(int A[], int p, int r)
{
    int x =  A[r];
    int i = p-1;
    for (int j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            i++;
            exchange(A[i], A[j]);
        }
    }
    exchange(A[i+1], A[r]);
    return i+1;
}

// Quick Sort
void QuickSort(int A[], int p, int r)
{
    if (p < r)
    {
        int q = Partition(A, p, r);
        QuickSort(A, p, q-1);
        QuickSort(A, q+1, r);
    }
}

int Ramdomized_Partition(int A[], int p, int r)
{
    int i = p + rand()%(r-p);
    exchange(A[r], A[i]);
    return Partition(A, p, r);
}

// Randomized Quicksort
void Ramdomized_QuickSort(int A[], int p, int r)
{
    if (p < r)
    {
        int q = Ramdomized_Partition(A, p, r);
        Ramdomized_QuickSort(A, p, q-1);
        Ramdomized_QuickSort(A, q+1, r);
    }
}

// Randomized Select
int Ramdomized_Select(int A[],int p, int r, int i)
{
    if (p == r)
        return A[p];

    int q = Ramdomized_Partition(A, p, r);
    int k = q - p + 1;

    if (i == k)
        return A[q];
    else if (i < k)
        return Ramdomized_Select(A, p, q-1, i);
    else
        return Ramdomized_Select(A, q+1, r, i-k);
}


int main(int argc, const char * argv[])
{
    /* initialize random seed: */
    srand ( (unsigned int)time(NULL) );
    // initialze array
    int a[length] = {2,3,4,5,8,9,1,10,6,7};
    cout << "Input: ";
    print(a);
    // Randomized Select
    int rank = 5;
    int value = Ramdomized_Select(a, 0, 9, rank);
    cout << "The rank = " << rank << " value is " << value << endl;
    // Call Quicksort or Ramdomized Quick Sort
    // QuickSort(a, 0, 9);
    Ramdomized_QuickSort(a, 0, 9);
    cout << "Output: ";
    print(a);
    
    return 0;
}

