//
//  DeterministicSelect.cpp
//  
//  Created by 罗铮 on 10/19/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>

using namespace std;

const int length = 15;


// Print the array
void print(int input[], int length)
{
    for(int i = 0; i < length; i++ )
        cout << input[i] << " ";

    cout << endl;
}


// Insertion Sort
void Insertion_Sort(int A[], int n)
{
    for (int j = 1; j < n; j++)
    {
        int key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > key)
        {
            A[i+1] = A[i];
            i = i - 1;
        }
        A[i+1] = key;
    }
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
    int x = A[r];
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


// Modified Partition
int Modified_Partition(int A[], int p, int r, int x)
{
    int i = 0;
    while (A[i] != x)
        i++;

    exchange(A[r], A[i]);
    return Partition(A, p, r);
}


// Deterministic Select
int Deterministic_Select(int A[],int n,int i)
{
    // base case
    if(n == 1)
        return A[0];

    int j = 0; // index to access the array
    int x = 0; // the median of the median
    // Find the meadian of each troup of 5 elements and 
    // put them in array B
    // if n can be divided by 5
    if (n % 5 == 0)
    {
        int * B = new int [n/5];
        // sort the 5 element sub array and then find the median
        for (int i = 5; i <= n; i = i+5)
        {
            Insertion_Sort(A+(i-5),5);
            // store the median into array B
            B[j++] = A[i-3];
        }
        // find the midian of the meidians x
        x = Deterministic_Select(B,n/5,(n/5-1)/2+1);
    }
    // if n can not be divided by 5
    else
    {
        int * B = new int [n/5+1];
        // sort the 5 element sub array and then find the median
        for (int i = 5; i <= n; i = i+5)
        {
            Insertion_Sort(A+(i-5),5);
            // store the median into array B
            B[j++] = A[i-3];
        }
        // sort and select median in the last part
        Insertion_Sort(A+(5*(n/5)),(n-5*(n/5)));
        // find the median in the last part in the array A
        B[j] = A[(5*(n/5))+(n-5*(n/5)-1)/2];
        // find the midian of the meidians x
        x = Deterministic_Select(B,n/5+1,n/10+1);
    }
    
    // Partition the array by x
    int q = Modified_Partition(A,0,n-1,x);
    int k = q;
    if ( i == k+1)
        return x;
    else if (i <= k)
        return Deterministic_Select(A, k, i);
    else if (i > k)
        return Deterministic_Select(A+k+1, n-k-1, i-(k+1));

    // if there is an unexpected error
    return -1;
}


int main(int argc, const char * argv[])
{
    // initialze array
    int a[length] = {14,15,4,5,8, 9,1,10,6,7, 11,13,12,2,3};
    cout << "Input: ";
    print(a,length);
    // Determinstic Select
    int rank = 5;
    int value = Deterministic_Select(a, length, rank);
    cout << "The rank = " << rank << " value is " << value << endl;
    //Insertion_Sort(a, length);
    cout << "Output: ";
    print(a,length);

    cout << endl;

    int b[8] = {9,1,13,6,7, 10,12,2};
    cout << "Input: ";
    print(b,8);
    // Determinstic Select
    int rankb = 6;
    int valueb = Deterministic_Select(b, 8, rankb);
    cout << "The rank = " << rankb << " value is " << valueb << endl;
    Insertion_Sort(b, 8);
    cout << "Output: ";
    print(b,8);

    return 0;
}


