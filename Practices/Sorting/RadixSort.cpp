//
//  RadixSort.cpp
//  
//  Created by 罗铮 on 9/25/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void radix_sort(int A[], int d, int k, int n)
{
    int C[k+1];
    int B[n];
    int pow = 1;
    
    while (pow < powf(10, d))
    {
        for (int j = 0; j <= k; j++)
            C[j] = 0;
        
        for(int i = 0; i < n; i++)
            C[(A[i]/pow)%10]++;
        
        for (int j = 1; j <= k; j++)
            C[j] = C[j]+C[j-1];
        
        for (int i = n-1; i >= 0; i--)
        {
            B[C[(A[i]/pow)%10]-1] = A[i];
            C[(A[i]/pow)%10]--;
        }
        
        for (int i = 0; i < n; i++)
            A[i] = B[i];
    
        pow *= 10;
    }
}

int main(int argc, const char * argv[])
{
    int a[10] = {202,431,523,121,233,586,863,278,123,265};
    // call radix_sort
    radix_sort(a,3,10,10);
    
    // print array after counting sort
    for (int i = 0; i < 10; i++)
        cout << a[i] << " ";
    
    return 0;
}

