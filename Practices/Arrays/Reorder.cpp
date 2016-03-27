//
//  Reorder.cpp
//  
//  Created by 罗铮 on 10/29/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>

using namespace std;

void Reorder(int *pData, unsigned int length, bool (*func)(int));
bool isEven(int n);


/////////////////////////////////////////////////////////////////////////
// Devide an array of integers into two parts, odd in the first part,
// and even in the second part
// Input: pData  - an array of integers
//        length - the length of array
/////////////////////////////////////////////////////////////////////////
void ReorderOddEven(int *pData, unsigned int length)
{
    // Always remember to check if the array is NULL
    if(pData == NULL || length == 0)
        return;
    
    Reorder(pData, length, isEven);
}


/////////////////////////////////////////////////////////////////////////
// Devide an array of integers into two parts, the intergers which
// satisfy func in the first part, otherwise in the second part
// Input: pData  - an array of integers
//        length - the length of array
//        func   - a function
/////////////////////////////////////////////////////////////////////////
void Reorder(int *pData, unsigned int length, bool (*func)(int))
{
    // Always remember to check if the array is NULL
    if(pData == NULL || length == 0)
        return;
    
    int *pBegin = pData;
    int *pEnd = pData + length - 1;
    
    while(pBegin < pEnd)
    {
        // if *pBegin does not satisfy func, move forward
        if(!func(*pBegin))
        {
            pBegin++;
            continue;
        }
        
        // if *pEnd does not satisfy func, move backward
        if(func(*pEnd))
        {
            pEnd--;
            continue;
        }
        
        // if *pBegin satisfy func while *pEnd does not,
        // swap these integers
        int temp = *pBegin;
        *pBegin = *pEnd;
        *pEnd = temp;
    }
}


/////////////////////////////////////////////////////////////////////////
// Determine whether an integer is even or not
// Input: an integer
// otherwise return false
// The &(and) operation is faster than the % operation
/////////////////////////////////////////////////////////////////////////
bool isEven(int n)
{
    return (n & 1) == 0;
}

bool isOdd(int n)
{
    return (n & 1) == 1;
}

// Print the elements in the array
void printArray(int A[], int length)
{
    for (int i = 0; i < length; i++)
        cout << A[i] << " ";
}

int main(int argc, const char * argv[])
{
    // 1. Test Null Array
    int a[2]={};
    ReorderOddEven(a, 2);
    printArray(a, 2);
    cout << endl;
    
    // 2. Test One element Aarray
    int b[1]={1};
    ReorderOddEven(b, 1);
    printArray(b, 1);
    cout << endl;
    
    // 3. Test Two element Aarray
    int c[2]={1,2};
    ReorderOddEven(c, 2);
    printArray(c, 2);
    cout << endl;
    
    // 4. Test Array with Negatvie numbers
    int d[10]={1,2,-1,-2,5,3,4,5,6,7};
    ReorderOddEven(d, 10);
    printArray(d, 10);
    cout << endl;
    
    return 0;
}

