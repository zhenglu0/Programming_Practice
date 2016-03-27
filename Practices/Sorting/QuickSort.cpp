//
//  QuickSort.cpp
//  
//  Created by 罗铮 on 8/22/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <algorithm>

using namespace std;

const int INPUT_SIZE = 10;

void print(int input[])
{
    for(int i = 0; i <INPUT_SIZE; i++ )
        cout << input[i] << " ";

    cout << endl;
}


inline void exch( int a[], int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int partition(int a[], int l, int r)
{
    int i = l - 1;
    int j = r;
    while(true)
    {
        while(a[++i] < a[r])
            if (i == r) break;
        while(a[r] < a[--j])
            if (j == i) break;
        if (i >= j) break;
        exch(a, i, j);
    }
    exch(a, i ,r);
    return i;
}

void sort(int a[], int l, int r)
{
    if (r <= l) return;
    int m = partition(a, l, r);
    sort(a, l, m-1);
    sort(a, m+1, r);
}

void quick_sort(int a[])
{
    // shuffle the array
    random_shuffle (a, a+INPUT_SIZE);
    sort(a, 0, INPUT_SIZE-1);
}

int main(int argc, char* argv[])
{
    int input[INPUT_SIZE] = {500,700,800,100,300,
                             200,900,400,1000,600};
    cout << "Input: ";
    print(input);
    quick_sort(input);
    cout << "Output: ";
    print(input);
    return 0;
}


