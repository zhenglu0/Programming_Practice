//
//  PartitionNPZ.cpp
//  
//  Created by 罗铮 on 2/11/13.
//  Modified by 罗铮 on 04/09/14.
//  Copyright (c) 2013 罗铮. All rights reserved.

#include <iostream>

using namespace std;

void intSwap(int &a, int &b) 
{
    int temp = a;
    a = b;
    b = temp;
}

int partitionByPivit(int A[], int l, int r, int p) 
{
    int i = l;
    int j = r;

    while (i < j) {
        while (A[i] < p && i < j)
            i++;
        while (A[j] >= p && j > i)
            j--;
        if (i != j) {
            intSwap(A[i],A[j]);
            i++;
            j--;
        }
    }
    return i;
}

void partitionNPZ(int A[], int n) 
{
    int i = partitionByPivit(A, 0, n-1, 0);
    partitionByPivit(A, i, n-1, 1);
}

void printArray(int A[], int n) 
{
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main(int argc, const char * argv[])
{
    int n = 7;
    int A[] = {-1, 2, 3, 0, 5, -2, 0};
    partitionNPZ(A, n);
    printArray(A, n);
    
    int B[] = {0, 2, 3, 0, 5, 2, 0};
    partitionNPZ(B, n);
    printArray(B, n);
    
    int C[] = {-1, 2, 3, -9, 5, 2, -1};
    partitionNPZ(C, n);
    printArray(C, n);
    
    return 0;
}

