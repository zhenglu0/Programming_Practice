//
//  MoreThanHalfNum.cpp
//  
//  Created by 罗铮 on 11/7/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// The sign is used to show that whether the input is valid
bool g_bInputInvalid = false;

//////////////////////////////////////////////////////////////////////////
// Input: an array with "length" numbers. A number in the array
// appear more than "length / 2 + 1" times.
// Output: If the input is valid, return the number appearing more than
// "length / 2 + 1" times. Otherwise, return 0 and set flag g_bInputInvalid
// to be true.
//////////////////////////////////////////////////////////////////////////
int MoreThanHalfNum(int* numbers, int length)
{
    if(numbers == NULL && length == 0)
    {
        g_bInputInvalid = true;
        return 0;
    }
    
    g_bInputInvalid = false;
    
    int result = numbers[0];
    int times = 1;
    for(int i = 1; i < (int)length; ++i)
    {
        if(times == 0)
        {
            result = numbers[i];
            times = 1;
        }
        else if(numbers[i] == result)
            times++;
        else
            times--;
    }
    
    // verify whether the input is valid, 
    // this is very important
    times = 0;
    for(int i = 0; i < length; ++i)
    {
        if(numbers[i] == result)
            times++;
    }
    
    if(times * 2 <= length)
    {
        g_bInputInvalid = true;
        result = 0;
    }
    
    return result;
}

/*
    Or we can use the randomized selectd to
    find the median of the array
*/

// The swap function
void exchange(int &a, int &b)
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

int Ramdomized_Partition(int A[], int p, int r)
{
    int i = p + rand()%(r-p);
    exchange(A[r], A[i]);
    return Partition(A, p, r);
}

// Randomized Select
int Ramdomized_Select(int A[],int p, int r, int i)
{
    if (p == r)
    {
        return A[p];
    }
    int q = Ramdomized_Partition(A, p, r);
    int k = q - p + 1;
    if (i == k)
    {
        return A[q];
    }
    else if (i < k)
    {
        return Ramdomized_Select(A, p, q-1, i);
    }
    else
    {
        return Ramdomized_Select(A, q+1, r, i-k);
    }
}

int main(int argc, const char * argv[])
{
    int A[10] = {1, 2, 3, 1, 1, 0, 0, 0, 0, 0};
    
    int result = MoreThanHalfNum(A, 10);

    cout << "The input is invalid ? " << boolalpha 
         << g_bInputInvalid << endl
         << "The number is " << result << endl;
    
    // Randomized Select
    int rank = 4;
    int value = Ramdomized_Select(A, 0, 9, rank);
    cout << "The rank = " << rank 
         << " value is " << value << endl;

    return 0;
}

