//
//  RoatationSortedArray.cpp
//  
//  Created by 罗铮 on 11/9/12.
//  Modified by 罗铮 on 04/02/14.
//  Copyright (c) 2012 罗铮. All rights reserved.
//  
//  http://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/
//  http://leetcode.com/2010/04/searching-element-in-rotated-array.html

/* Program to search an element in a sorted and pivoted array*/
#include <cstdio>
#include <iostream>

using namespace std;

// 1. Get the minimum number of a roatation of a sorted array
int Min(int *numbers, int length)
{
    if(numbers == 0 || length <= 0)
        return -1;
        //throw new std::exception("Invalid parameters");
    
    int index1 = 0;
    int index2 = length - 1;
    int indexMid = index1;
    while(numbers[index1] >= numbers[index2])
    {
        if(index2 - index1 == 1)
        {
            indexMid = index2;
            break;
        }
        // calculate the midpoint
        indexMid = (index1 + index2) / 2;
        if(numbers[indexMid] >= numbers[index1])
            index1 = indexMid;
        else if(numbers[indexMid] <= numbers[index2])
            index2 = indexMid;
    }
    
    return numbers[indexMid];
}


// 2. Get the minimum number of a roatation of 
// a sorted array iteratively
int FindMinInRotatedArrayIteratively(int *A, int length)
{
    // check if the array is null or length is less than 0, 
    // -1 means not found the element
    if(!A || length <= 0)
        return -1;
    
    int l = 0;
    int r = length - 1;
    int m = l;
    while(A[l] > A[r])
    {
        if(r - l == 1)
        {
            m = r;
            break;
        }
        // calculate the midpoint
        m = (l + r) / 2;
        // change parameter for the next iteration
        if(A[m] > A[l])
            l = m;
        else
            r = m;
    }
    return A[m];
}


// 3. Get the minimum number of a roatation of 
// a sorted array recursviely
int DoFindMinInRotatedArrayRecursively(int *A, int l, int r)
{
    // Base case
    if (r - l == 1)
        return A[r];
    // Find min element in rotated array recursively
    if (A[l] > A[r])
    {
        int m = (l + r) / 2;
        if (A[m] > A[l])
            return DoFindMinInRotatedArrayRecursively(A, m, r);
        else
            return DoFindMinInRotatedArrayRecursively(A, l, m);
    }
    else
        return A[l];
}

int FindMinInRotatedArrayRecursively(int *A, int length)
{
    return DoFindMinInRotatedArrayRecursively(A, 0, length-1);
}


// 4. Get the minimum number of a roatation of 
// a sorted array iteratively
int FindMaxInRotatedArrayIteratively(int *A, int length)
{
    // check if the array is null or length is less than 0, 
    // -1 means not found the element
    if(!A || length <= 0)
        return -1;
    
    int l = 0;
    int r = length - 1;
    int m = r;
    while(A[l] > A[r])
    {
        if(r - l == 1)
        {
            m = l;
            break;
        }
        // calculate the midpoint
        m = (l + r) / 2;
        // change parameter for the next iteration
        if(A[m] > A[l])
            l = m;
        else
            r = m;
    }
    return A[m];
}


// 5. Get the minimum number of a roatation of 
// a sorted array recursviely
int DoFindMaxInRotatedArrayRecursively(int *A, int l, int r)
{
    // Base case
    if (r - l == 1)
        return A[l];
    // Find min element in rotated array recursively
    if (A[l] > A[r])
    {
        int m = (l + r)/2;
        if (A[m] > A[l])
            return DoFindMaxInRotatedArrayRecursively(A, m, r);
        else
            return DoFindMaxInRotatedArrayRecursively(A, l, m);
    }
    else
        return A[r];
}

int FindMaxInRotatedArrayRecursively(int *A, int length)
{
    return DoFindMaxInRotatedArrayRecursively(A, 0, length-1);
}


// 6. Normal binary search recursive
int NormalBinarySearchRecursively(int *A, int v, int l, int r)
{
    if (l > r)
        return -1;
    int m = (l + r) / 2;
    if (A[m] == v)
        return m;
    if (A[m] > v)
        return NormalBinarySearchRecursively(A, v, l, m - 1);
    else
        return NormalBinarySearchRecursively(A, v, m + 1, r);
}


// 7. Normal binary search iterative
int NormalBinarySearchIteratively(int *A, int v, int l, int r)
{
    int m = (l + r) / 2;
    while (l <= r)
    {
        if (A[m] == v)
            return m;
        if (A[m] > v)
            r = m - 1;
        else
            l = m + 1;
        m = (l + r) / 2;
    }
    return -1;
}


// 8. Find an element in the rotated array
int FindMaxInRotatedArrayIteratively(int *A, int N, int key)
{
    int L = 0;
    int R = N - 1;
    
    while (L <= R)
    {
        // Avoid overflow, same as M=(L+R)/2
        int M = L + ((R - L) / 2);
        if (A[M] == key) 
            return M;
        
        // the bottom half is sorted
        if (A[L] <= A[M])
        {
            if (A[L] <= key && key < A[M])
                R = M - 1;
            else
                L = M + 1;
        }
        // the upper half is sorted
        else
        {
            if (A[M] < key && key <= A[R])
                L = M + 1;
            else
                R = M - 1;
        }
    }
    return -1;
}


// 9. Find an element in the rotated array
int FindElementInRotatedArrayRecursively(int *A, int v, int l, int r)
{
    if (l > r)
        return -1;
    // we can use m = l + ((r - l) / 2) to avoid overflow
    int m = (l + r) / 2;
    if (A[m] == v)
        return m;
    else if (A[l] == v)
        return l;
    else if (A[r] == v)
        return r;
    if (A[l] < A[m] && v > A[l] && v < A[m])
        return NormalBinarySearchRecursively(A, v, l + 1, r);
    else if(A[l] < A[m])
        return FindElementInRotatedArrayRecursively(A, v, m + 1, r - 1);
    if (A[l] > A[m] && v > A[l] && v < A[m])
        return NormalBinarySearchRecursively(A, v, m + 1, r);
    else if(A[l] > A[m])
        return FindElementInRotatedArrayRecursively(A, v, l + 1, m - 1);
    // if there is an unknown error
    return -1;
}

// 10.
/* Standard Binary Search function*/
int binarySearch(int arr[], int low, int high, int no)
{
    if (high < low)
        return -1;
    
    int mid = (low + high) / 2;  /*low + (high - low)/2;*/
    
    if (no == arr[mid])    
        return mid;

    if (no > arr[mid])
        return binarySearch(arr, (mid + 1), high, no);
    else
        return binarySearch(arr, low, (mid - 1), no);
}

/* Function to get pivot. For array 3, 4, 5, 6, 1, 2 it will
   return 3 (Index of 6). If array is not rotated at all, 
   then it returns -1 */
int findPivot(int arr[], int low, int high)
{
    // base cases
    if (high < low)  
        return -1;
    // base cases
    if (high == low)
        return low;

    int mid = (low + high) / 2; /*low + (high - low)/2;*/

    if (mid < high && arr[mid] > arr[mid + 1])
        return mid;
    
    if (mid > low && arr[mid] < arr[mid - 1])
        return (mid-1);
    
    if (arr[low] >= arr[mid])
        return findPivot(arr, low, mid - 1);
    else
        return findPivot(arr, mid + 1, high);
}

/* Searches an element no in a pivoted sorted array arrp[]
   of size arr_size */
int pivotedBinarySearch(int arr[], int arr_size, int no)
{
    int pivot = findPivot(arr, 0, arr_size - 1);

    // If we didn't find a pivot, then array is not rotated at all
    if (pivot == -1)
        return binarySearch(arr, 0, arr_size - 1, no);

    // If we found a pivot, then first compare with pivot and then
    // search in two subarrays around pivot
    if (arr[pivot] == no)
        return pivot;
    
    if (arr[0] <= no)
        return binarySearch(arr, 0, pivot - 1, no);
    else
        return binarySearch(arr, pivot + 1, arr_size - 1, no);
}


int main(int argc, const char * argv[])
{
    //int A[5] = {1,2,3,4,5};
    //int A[5] = {5,1,2,3,4};
    //int A[5] = {4,5,1,2,3};
    //int A[5] = {3,4,5,1,2};
    int A[5] = {2,3,4,5,1};

    // duplicate test case
    //int A[5] = {4,5,4,4,4};
    
    // test find max and min in the rotated array
    int min_i = FindMinInRotatedArrayIteratively(A, 5);
    int min_r = FindMinInRotatedArrayRecursively(A, 5);
    int max_i = FindMaxInRotatedArrayIteratively(A, 5);
    int max_r = FindMaxInRotatedArrayRecursively(A, 5);
    cout << "The min number in the array is " 
         << min_i << " " << min_r << endl;
    cout << "The max number in the array is " 
         << max_i << " " << max_r << endl;
    
    // test normal binary search
    int element = 2;
    cout << "NormalBinarySearchRecursively, the index = " 
         << NormalBinarySearchRecursively(A, element, 0, 4) << endl;
    cout << "NormalBinarySearchIteratively, the index = " 
         << NormalBinarySearchIteratively(A, element, 0, 4) << endl;
    
    // test find arbitrary element in the rotated array
    element = 5;
    cout << "FindElementInRotatedArrayRecursively, the index = " <<
    FindElementInRotatedArrayRecursively(A,element,0,4) << endl;
    cout << "FindElementInRotatedArrayIteratively, the index = " <<
    FindMaxInRotatedArrayIteratively(A,5,element) << endl;
    
    //int B[7] = {0,1,2,4,5,6,7};
    int B[7] = {4,5,6,7,0,1,2};
    
    // do more test on the find element in rotated array
    // test find arbitrary element in the rotated array
    int element2 = 2;
    cout << "FindElementInRotatedArrayRecursively, the index = " <<
    FindElementInRotatedArrayRecursively(B,element2,0,6) << endl;
    cout << "FindElementInRotatedArrayIteratively, the index = " <<
    FindMaxInRotatedArrayIteratively(B,7,element2) << endl;

    // Let us search 3 in below array
    int arr1[] = {5, 6, 7, 8, 9, 10, 1, 2, 3};
    int arr_size = sizeof(arr1)/sizeof(arr1[0]);
    int no = 3;
    printf("Index of the element is %d\n",
           pivotedBinarySearch(arr1, arr_size, no));

    // Let us search 3 in below array
    int arr2[] = {3, 4, 5, 1, 2};
    arr_size = sizeof(arr2)/sizeof(arr2[0]);
    printf("Index of the element is %d\n",
           pivotedBinarySearch(arr2, arr_size, no));

    // Let us search for 4 in above array
    no = 4;
    printf("Index of the element is %d\n",
           pivotedBinarySearch(arr2, arr_size, no));

    // Let us search 0 in below array
    int arr3[] = {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1};
    no = 0;
    arr_size = sizeof(arr3)/sizeof(arr3[0]);
    printf("Index of the element is %d\n",
            pivotedBinarySearch(arr3, arr_size, no));

    // Let us search 3 in below array
    int arr4[] = {2, 3, 0, 2, 2, 2, 2, 2, 2, 2};
    no = 3;
    arr_size = sizeof(arr4)/sizeof(arr4[0]);
    printf("Index of the element is %d\n",
            pivotedBinarySearch(arr4, arr_size, no));

    // Let us search 2 in above array
    no = 2;
    printf("Index of the element is %d\n",
           pivotedBinarySearch(arr4, arr_size, no));

    // Let us search 3 in below array
    int arr5[] = {1, 2, 3, 4};
    no = 3;
    arr_size = sizeof(arr5)/sizeof(arr5[0]);
    printf("Index of the element is %d\n",
           pivotedBinarySearch(arr5, arr_size, no));

    return 0;
}

