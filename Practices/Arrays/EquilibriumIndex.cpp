//
//  EquilibriumIndex.cpp
//  
//  Modified by 罗铮 on 03/30/14.
//  http://www.geeksforgeeks.org/equilibrium-index-of-an-array/

#include <cstdio>
 
/*
    Method 1 (Simple but inefficient)
    Use two loops. Outer loop iterates through all the element and 
    inner loop finds out whether the current index picked by the 
    outer loop is equilibrium index or not. 
    Time complexity of this solution is O(n^2)
*/
int equilibrium_naive(int arr[], int n)
{
    int i, j;
    int leftsum, rightsum;

    /* Check for indexes one by one until an equilibrium
      index is found */
    for ( i = 0; i < n; ++i)
    {
        leftsum = 0;  // initialize left sum for current index i
        rightsum = 0; // initialize right sum for current index i

        /* get left sum */
        for ( j = 0; j < i; j++)
            leftsum  += arr[j];

        /* get right sum */
        for( j = i+1; j < n; j++)
            rightsum += arr[j];

        /* if leftsum and rightsum are same, then we are done */
        if (leftsum == rightsum)
            return i;
      }

    /* return -1 if no equilibrium index is found */
    return -1;
}
  
/*
    Method 2 (Tricky and Efficient)
    The idea is to get total sum of array first. 
    Then Iterate through the array and keep updating the left 
    sum which is initialized as zero. In the loop, we can get 
    right sum by subtracting the elements one by one. Thanks to
    Sambasiva for suggesting this solution and providing code for this.

    1) Initialize leftsum  as 0
    2) Get the total sum of the array as sum
    3) Iterate through the array and for each index i, do following.
        a)  Update sum to get the right sum.  
               sum = sum - arr[i] 
           // sum is now right sum
        b) If leftsum is equal to sum, then return current index. 
        c) leftsum = leftsum + arr[i] // update leftsum for next iteration.
    4) return -1 // If we come out of loop without returning then
                 // there is no equilibrium index
*/
 
int equilibrium(int arr[], int n)
{
    int sum = 0;     // initialize sum of whole array
    int leftsum = 0; // initialize leftsum
    int i;

    /* Find sum of the whole array */
    for (i = 0; i < n; ++i)
        sum += arr[i];

    for( i = 0; i < n; ++i)
    {
        sum -= arr[i]; // sum is now right sum for index i

        if(leftsum == sum)
        return i;

        leftsum += arr[i];
    }
 
    /* If no equilibrium index found, then return 0 */
    return -1;
}
 
int main()
{
    int arr[] = {-7, 1, 5, 2, -4, 3, 0};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    printf("First equilibrium index is %d\n", 
         equilibrium(arr, arr_size));

    return 0;
}
