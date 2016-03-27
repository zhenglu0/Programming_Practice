//
//  HeapSort_CLRS.cpp
//
//  Created by 罗铮 on 10/29/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int heap_size = 1;
int array_max = 10;

int Parent(int i)
{
    return (i-1)/2;
}

int Left(int i)
{
    return 2*i+1;
}

int Right(int i)
{
    return 2*i + 2;
}

void exchange(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void Max_Heapify(int A[], int i, int n)
{
    int l = Left(i);
    int r = Right(i);
    int largest = 0;

    if (l < n && A[l] > A[i])
        largest = l;
    else
        largest = i;
    if (r < n && A[r] > A[largest])
        largest = r;

    if (largest != i)
    {
        exchange(A[i], A[largest]);
        Max_Heapify(A, largest, n);
    }


}

void Build_Max_Heap(int A[], int n)
{
    for (int i = n/2-1; i >= 0; i--)
        Max_Heapify(A, i, n);
}

void PrintArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
}

void HeapSort(int A[], int n)
{
    Build_Max_Heap(A, n);
    for (int i = n-1; i >= 1; i--)
    {
        exchange(A[0], A[i]);
        n--;
        Max_Heapify(A, 0, n);
    }
}

int Heap_Maximum(int A[], int n)
{
    return A[0];
}

int Heap_Extract_Max(int A[], int &n)
{
    if (n < 1)
        cout << "Heap Underflow" << endl;

    int max = A[0];
    A[0] = A[n-1];
    n--;
    Max_Heapify(A, 0, n);
    return max;
}

void Heap_Increase_Key(int A[], int i, int key)
{
    if (key < A[i])
        cout << "Error, new key is smaller than current key" << endl;

    A[i] = key;
    while (i > 0 && A[Parent(i)] < A[i])
    {
        exchange(A[i], A[Parent(i)]);
        i = Parent(i);
    }
}

void Max_Heap_Insert(int* &A , int key, int &n)
{

    if (array_max < n)
    {
        // double size of array
        array_max = array_max * 2;
        // create a new array of the double size
        int *B = new int [array_max];
        for (int i = 0; i < n ; i++)
            B[i] = A[i];

        delete [] A;
        A = B;
    }
    n++;
    A[n-1] = numeric_limits<int>::min();
    Heap_Increase_Key(A, n-1, key);
}

// Method 2
void insert(vector<int> &array, int x)
{
    array.push_back(x);
    unsigned long hole = array.size()-1;
    //percolate up
    for (; hole>1 && x>array[hole/2]; hole/=2)
        array[hole] = array[hole/2];
    array[hole]= x;
}

void heapSort(vector<int> &array)
{
    unsigned long last_element_index = array.size()-1;
    while (true)
    {
        // check whether the heap is empty
        if(last_element_index != 0)
        {
            int tmp = array[last_element_index];
            //create a hole at root
            size_t hole = 1;
            array[last_element_index] = array[hole];
            unsigned long currentSize = last_element_index;
            size_t child;
            for( ; hole*2 < currentSize; hole=child)
            {   //identify child position
                child = hole*2;
                //compare left and right child, select the bigger one
                if (child < (currentSize-1) && array[child+1] > array[child]){
                     ++child;
                }
                if(array[child]>tmp)
                {
                    //bubble down if child is bigger
                    array[hole] = array[child];
                } 
                //compare the smaller child with tmp
                else 
                {
                    break; //bubble stops movement
                }
            }
            array[hole] = tmp; //fill the hole
            --last_element_index;
        } else {
            break;
        }
    }
}

int main(int argc, const char * argv[])
{
    int A[10] = {4,1,3,2,16,9,10,14,8,7};
    HeapSort(A,10);
    PrintArray(A,10);
    cout << endl << endl;

    int B[10] = {4,1,3,2,16,9,10,14,8,7};
    Build_Max_Heap(B, 10);
    cout << "The Max = " << Heap_Maximum(B, 10) << endl;
    int n1 = 10;
    int max1 = Heap_Extract_Max(B, n1);
    cout << "The Max1 = " << max1 << endl;
    int max2 = Heap_Extract_Max(B, n1);
    cout << "The Max2 = " << max2 << endl;

    int *C = new int [heap_size];
    C[0] = 4;
    Max_Heap_Insert(C, 1, heap_size);
    Max_Heap_Insert(C, 3, heap_size);
    Max_Heap_Insert(C, 2, heap_size);
    Max_Heap_Insert(C, 16, heap_size);
    Max_Heap_Insert(C, 9, heap_size);
    Max_Heap_Insert(C, 10, heap_size);
    Max_Heap_Insert(C, 14, heap_size);
    Max_Heap_Insert(C, 8, heap_size);
    Max_Heap_Insert(C, 7, heap_size);
    Max_Heap_Insert(C, 20, heap_size);
    cout << endl;
    PrintArray(C,heap_size);

    // build the heap
    vector<int> array;
    vector<int> heap;
    array.push_back(0);
    array.push_back(20);
    array.push_back(18);
    array.push_back(16);
    array.push_back(4);
    array.push_back(17);
    array.push_back(14);
    array.push_back(8);
    array.push_back(7);
    array.push_back(9);
    array.push_back(88);
    array.push_back(66);
    array.push_back(22);
    array.push_back(33);
    array.push_back(99);
    array.push_back(100);
    cout << "\n\nThe unsorted array:" << endl;
    //print the array
    for ( vector<int>::iterator it = array.begin(); 
          it < array.end(); it++ )
    {
        cout << " " << *it;
        // build the heap
        insert(heap, *it);
    }
    // print the heap
    cout << endl << "The built heap:" << endl;
    for ( vector<int>::iterator it = heap.begin(); 
          it < heap.end(); it++ )
        cout << " " << *it;

    cout << endl << "The sorted array:" << endl;
    // print the sorted array
    heapSort(heap);
    for ( vector<int>::iterator it = heap.begin(); 
          it < heap.end(); it++ )
        cout << " " << *it;

    cout << endl;

    return 0;
}

