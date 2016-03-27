//
//  MergeSort.cpp
//
//  Created by 罗铮 on 8/20/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <cmath>

using namespace std;

const int INPUT_SIZE = 10;

// A simple print function
void print(int *input)
{
    for ( int i = 0; i < INPUT_SIZE; i++ )
        cout << input[i] << " ";

    cout << endl;
}

void merge(int* input, int p, int r)
{
    int mid = floor((p + r) / 2);
    int i1 = 0;
    int i2 = p;
    int i3 = mid + 1;
    
    // Temp array
    int temp[r-p+1];
    
    // Merge in sorted form the 2 arrays
    while ( i2 <= mid && i3 <= r )
        if ( input[i2] < input[i3] )
            temp[i1++] = input[i2++];
        else
            temp[i1++] = input[i3++];
    
    // Merge the remaining elements in left array
    while ( i2 <= mid )
        temp[i1++] = input[i2++];
    
    // Merge the remaining elements in right array
    while ( i3 <= r )
        temp[i1++] = input[i3++];
    
    // Move from temp array to master array
    for ( int i = p; i <= r; i++ )
        input[i] = temp[i-p];
}

void merge_sort(int* input, int p, int r)
{
    if ( p < r )
    {
        int mid = floor((p + r) / 2);
        merge_sort(input, p, mid);
        merge_sort(input, mid + 1, r);
        merge(input, p, r);
    }
}

int main()
{
    int input[INPUT_SIZE] = {500, 700, 800, 100, 300, 200, 
                             900, 400, 1000, 600};
    cout << "Input: ";
    print(input);
    merge_sort(input, 0, 9);
    cout << "Output: ";
    print(input);
    return 0;
}

