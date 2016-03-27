//
//  NProduct.cpp
//  
//  Created by 罗铮 on 2/9/13.
//  Modified by 罗铮 on 04/09/14.
//  Copyright (c) 2013 罗铮. All rights reserved.

#include <iostream>

#define max 6

using namespace std;


float* nProduct(float A[], int n) 
{
    // temporary arrays
    float* prefix = new float[n];
    float* suffix = new float[n];
    float* result = new float[n];

    // if there is something wrong with memory allocation
    if (!prefix || !suffix || !result)
        return 0;
    
    // Compute the prefix
    prefix[0] = A[0];
    for(int i = 1; i < n; i++) {
        prefix[i] = prefix[i-1] * A[i];
    }

    // Compute the suffix
    suffix[n-1] = A[n-1];
    for(int i = n-2; i > -1; i--) {
        suffix[i] = suffix[i+1] * A[i];
    }

    // Compute the result
    result[0] = suffix[1];
    result[n-1] = prefix[n-2];
    for(int i = 1; i < n-1 ; i++) {
        result[i] = prefix[i-1] * suffix[i+1];
    }
    
    delete [] prefix;
    delete [] suffix;
    return result;
}

int main(int argc, const char * argv[])
{
    float A[max] = {1, 2, 3, 4, 5, 6};
    float *result = nProduct(A, max);
    
    for (int i = 0; i < max; i++)
        cout << result[i] << " ";
    cout << endl;
    
    delete [] result;

    return 0;
}