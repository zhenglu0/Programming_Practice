//
//  MaximumDifference.cpp
//  
//  Modified by 罗铮 on 03/30/14.
//  http://www.geeksforgeeks.org/maximum-difference-between-two-elements/

/*
    Given an array arr[] of integers, find out the difference between any 
    two elements such that larger element appears after the smaller number
    in arr[].

    Examples: If array is [2, 3, 10, 6, 4, 8, 1] then returned value s
    hould be 8 (Diff between 10 and 2). If array is [ 7, 9, 5, 6, 3, 2 ] 
    then returned value should be 2 (Diff between 7 and 9)
*/

#include <cstdio> 

/*  Method 1 (Simple)
    Use two loops. In the outer loop, pick elements one by one and in the 
    inner loop calculate the difference of the picked element with every 
    other element in the array and compare the difference with the 
    maximum difference calculated so far.
*/
/* The function assumes that there are at least two
   elements in array.
   The function returns a negative value if the array is
   sorted in decreasing order. 
   Returns 0 if elements are equal 
*/
int maxDiff_naive(int arr[], int arr_size)
{     
    int max_diff = arr[1] - arr[0];
    for(int i = 0; i < arr_size; i++)
        for(int j = i+1; j < arr_size; j++)
            if(arr[j] - arr[i] > max_diff)   
                max_diff = arr[j] - arr[i];
    return max_diff;
}    

/*
    Method 2 (Another Tricky Solution)
    First find the difference between the adjacent elements of the array 
    and store all differences in an auxiliary array diff[] of size n-1. Now 
    this problems turns into finding the maximum sum subarray of this 
    difference array.
*/
int maxDiff(int arr[], int n)
{
    // Create a diff array of size n-1. The array will hold
    // the difference of adjacent elements
    int diff[n-1];
    for (int i=0; i < n-1; i++)
        diff[i] = arr[i+1] - arr[i];
 
    // Now find the maximum sum subarray in diff array
    int max_diff = diff[0];
    for (int i = 1; i < n-1; i++)
    {
        if (diff[i-1] > 0)
            diff[i] += diff[i-1];
        if (max_diff < diff[i])
            max_diff = diff[i];
    }
    return max_diff;
}

/*
    Pirvious method is also O(n) time complexity solution, 
    but it requires O(n) extra space.
    We can modify the above method to work in O(1) extra space.
    Instead of creating an auxiliary array, 
    we can calculate diff and max sum in same loop. 
    Following is the space optimized version.
*/
int maxDiff_optimized (int arr[], int n)
{
    // Initialize diff, current sum and max sum
    int diff = arr[1]-arr[0];
    int curr_sum = diff;
    int max_sum = curr_sum;
 
    for(int i = 1; i < n-1; i++)
    {
        // Calculate current diff
        diff = arr[i+1]-arr[i];
 
        // Calculate current sum
        if (curr_sum > 0)
           curr_sum += diff;
        else
           curr_sum = diff;
 
        // Update max sum, if needed
        if (curr_sum > max_sum)
           max_sum = curr_sum;
    }
 
    return max_sum;
}

/* Driver program to test above function */
int main()
{
    int arr[] = {80, 2, 6, 3, 100};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Maximum difference is %d\n",  
            maxDiff(arr, size));
    return 0;
}
