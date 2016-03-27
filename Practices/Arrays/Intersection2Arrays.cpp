//
//  Intersection2Arrays.cpp
//  
//  Created by 罗铮 on 03/17/14.
//  Copyright (c) 2014 罗铮. All rights reserved.

#include <cstdio>

/* Function prints union of arr1[] and arr2[]
   m is the number of elements in arr1[]
   n is the number of elements in arr2[] */
void printUnion(int arr1[], int arr2[], int m, int n)
{
    int i = 0, j = 0;
    while(i < m && j < n) {
        if(arr1[i] < arr2[j])
            printf(" %d ", arr1[i++]);
        else if(arr2[j] < arr1[i])
            printf(" %d ", arr2[j++]);
        else {
            printf(" %d ", arr2[j++]);
            i++;
        }
    }
 
    /* Print remaining elements of the larger array */
    while(i < m)
        printf(" %d ", arr1[i++]);
    while(j < n)
        printf(" %d ", arr2[j++]);
}

void printIntersection(int arr1[], int arr2[], int m, int n)
{
    int i = 0, j = 0;
    while(i < m && j < n) {
        if(arr1[i] < arr2[j])
            i++;
        else if(arr2[j] < arr1[i])
            j++;
        else {
            /* if arr1[i] == arr2[j] */
            printf(" %d ", arr2[j++]);
            i++;
        }
    }
}

/*
 Do you think that this approach always work better? Not necessarily… 
 Think what happens when n is very large, say one billion…

 Compare this approach with the binary search approach.
 O(m+n) and O(m*lg(n))

 lg(n) is much smaller than n when n is very big. 
 However, this does not necessarily means binary search is better in 
 this case. In fact, binary search approach is only better when m << n 
 (m is very small compared to n). For example, when m = 1 and n = 
 one billion, which method will you choose? Binary search is definitely
 the winner here.
*/
// Here we always assume that n > m
bool binarySearch(int arr[], int l, int r, int v)
{
    if (l > r)
        return false;
    
    int mid = (l + r) / 2;

    if (arr[mid] == v)
        return true;
    else if (arr[mid] > v)
        return binarySearch(arr,l,mid-1,v);
    else
        return binarySearch(arr,mid+1,r,v);
}

void intersectionBinarySearch(int arr1[], int arr2[], int m, int n)
{
    for (int i = 0; i < m; ++i) {
        if (binarySearch(arr2,0,n,arr1[i]))
            printf(" %d", arr1[i]);
    }
    printf("\n");
}

/* Driver program to test above function */
int main()
{
    int arr1[] = {1, 2, 4, 5, 6};
    int arr2[] = {2, 3, 5, 7};

    int m = sizeof(arr1)/sizeof(arr1[0]);
    int n = sizeof(arr2)/sizeof(arr2[0]);

    printf("The union of the array\n");
    printUnion(arr1, arr2, m, n);
    printf("\n");

    printf("The printIntersection of the array\n");
    printIntersection(arr1, arr2, m, n);
    printf("\n");

    printf("Intersection of the array using binary search\n");
    if (n > m) 
        intersectionBinarySearch(arr1, arr2, m-1, n-1);    
    else
        intersectionBinarySearch(arr2, arr1, n-1, m-1);

    return 0;
}
