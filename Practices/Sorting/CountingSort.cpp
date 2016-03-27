//
//  CountingSort.cpp
//  
//  Created by 罗铮 on 9/25/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>

using namespace std;

void counting_sort(int A[], int n, int k)
{
    int C[k+1];
    int B[n];
    
    for (int j = 1; j <= k; j++)
        C[j] = 0;

    for(int i = 0; i < n; i++)
        C[A[i]]++;

    for (int j = 2; j <= k; j++)
        C[j] = C[j]+C[j-1];

    for (int i = n-1; i >= 0; i--)
    {
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }

    for (int i = 0; i < n; i++)
        A[i] = B[i];
}

void counting_sort_unstable(int A[], int n, int k)
{
    int C[k+1];

    for (int j = 1; j <= k; j++)
        C[j] = 0;

    for(int i = 0; i < n; i++)
        C[A[i]]++;

    int i = 0;
    for (int j = 1; j <= k; j++)
        for (int m = 1; m <= C[j]; m++)
            A[i++] = j;
}

int main(int argc, const char * argv[])
{
    int a[10] = {2,4,5,1,2,5,3,2,1,2};
    counting_sort(a, 10, 5);

    // print a after counting sort
    for (int i = 0; i < 10; i++)
        cout << a[i] << " ";

    cout << endl;

    int b[10] = {2,4,5,1,2,5,3,2,1,2};
    counting_sort_unstable(b, 10, 5);

    // print a after counting sort
    for (int i = 0; i < 10; i++)
        cout << b[i] << " ";

    cout << endl;
    
    return 0;
}

