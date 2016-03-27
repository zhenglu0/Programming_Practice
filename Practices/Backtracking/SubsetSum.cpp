//
//  SubsetSum.cpp
//
//  Created by 罗铮 on 03/09/14.
//  Copyright (c) 2014 罗铮. All rights reserved.
// 
//  The backtrack method is from the link
//  http://www.geeksforgeeks.org/backttracking-set-4-subset-sum/

#include <cstdio>      /* printf, scanf, NULL */
#include <cstdlib>     /* malloc, free, rand */

#define ARRAYSIZE(a) (sizeof(a))/(sizeof(a[0]))

static int total_nodes;

// #1
// Using the dynamic programming 

// Returns true if there is a subset of set[] with sun equal 
// to given sum
bool isSubsetSum_topdown(int set[], int n, int sum)
{
   // Base Cases
   if (sum == 0)
     return true;
   if (n == 0 && sum != 0)
     return false;
 
   // If last element is greater than sum, then ignore it
   if (set[n-1] > sum)
     return isSubsetSum_topdown(set, n-1, sum);
 
   /* else, check if sum can be obtained by any of the following
      (a) including the last element
      (b) excluding the last element   */
   return isSubsetSum_topdown(set, n-1, sum) || 
          isSubsetSum_topdown(set, n-1, sum-set[n-1]);
}

// Returns true if there is a subset of set[] with sun equal 
// to given sum
bool isSubsetSum_bottomup(int set[], int n, int sum)
{
    // The value of subset[i][j] will be true 
    // if there is a subset of set[0..j-1] with sum equal to i
    bool subset[sum+1][n+1];
 
    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
      subset[0][i] = true;
 
    // If sum is not 0 and set is empty, then answer is false
    for (int i = 1; i <= sum; i++)
      subset[i][0] = false;
 
     // Fill the subset table in botton up manner
     for (int i = 1; i <= sum; i++)
     {
       for (int j = 1; j <= n; j++)
       {
         subset[i][j] = subset[i][j-1];
         if (i >= set[j-1]) 
            subset[i][j] = subset[i][j] || 
                           subset[i - set[j-1]][j-1];
       }
     }
 
    // uncomment this code to print table
     for (int i = 0; i <= sum; i++)
     {
       for (int j = 0; j <= n; j++)
          printf ("%4d", subset[i][j]);
       printf("\n");
     }
 
     return subset[sum][n];
}

// #2
// Using the backtracking approach
// prints subset found
void printSubset(int A[], int size)
{
    for(int i = 0; i < size; i++)
        printf("%d ", A[i]);
 
    printf("\n");
}

// inputs
// s            - set vector
// t            - tuplet vector
// s_size       - set size
// t_size       - tuplet size so far
// sum          - sum so far
// ite          - nodes count
// target_sum   - sum to be found
void subset_sum(int s[], int t[],
                int s_size, int t_size,
                int sum, int ite,
                int const target_sum)
{
    total_nodes++;

    if( target_sum == sum ) {
        // We found subset
        printSubset(t, t_size);
        // we do the backtracking here
        return;
    } else if (sum > target_sum) {
        // we do the backtracking here
        return;
    }
        
    // generate nodes along the breadth
    for( int i = ite; i < s_size; i++ ) {
        t[t_size] = s[i];
        // consider next level node (along depth)
        subset_sum(s, t, s_size, t_size + 1, 
                   sum + s[i], i + 1, target_sum);
    }
}
 
// Wrapper to print subsets that sum to target_sum
// input is weights vector and target_sum
void generateSubsets(int s[], int size, int target_sum)
{
    int *tuplet_vector = (int *)malloc(size * sizeof(int));
 
    subset_sum(s, tuplet_vector, size, 0, 0, 0, target_sum);
 
    free(tuplet_vector);
}

// Driver program to test above function
int main(int argc, const char * argv[])
{
  int set[] = {3, 34, 4, 12, 5, 2};
  int sum = 9, n = ARRAYSIZE(set);

  // #1
  // Using the dynamic programming 
  if (isSubsetSum_topdown(set, n, sum) == true)
     printf("Found a subset with given sum\n");
  else
     printf("No subset with given sum\n");

  if (isSubsetSum_bottomup(set, n, sum) == true)
     printf("Found a subset with given sum\n");
  else
     printf("No subset with given sum\n");

  // #2
  // Using the backtracking approach
  generateSubsets(set, n, sum);
  printf("Nodes generated %d\n", total_nodes);

  return 0;
}
