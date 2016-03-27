//
//  LongestPalindromic.cpp
//  
//  Modified by by 罗铮 on 03/29/14.
//  http://www.geeksforgeeks.org/
//  dynamic-programming-set-12-longest-palindromic-subsequence/
//  http://leetcode.com/2011/11/longest-palindromic-substring-part-i.html

/*
    1) Optimal Substructure: 
    Let X[0..n-1] be the input sequence of length n and L(0, n-1) 
    be the length of the longest palindromic subsequence of X[0..n-1].

    If last and first characters of X are same, 
    Then L(0, n-1) = L(1, n-2) + 2.
    Else L(0, n-1) = MAX (L(1, n-1), L(0, n-2)).

    Following is a general recursive solution with all cases handled.

    // Everay single character is a palindrom of length 1
    L(i, i) = 1 for all indexes i in given sequence

    // If first and last characters are not same
    If (X[i] != X[j])  L(i, j) =  max{L(i + 1, j),L(i, j - 1)} 

    // If there are only 2 characters and both are same
    Else if (j == i + 1) L(i, j) = 2  

    // If there are more than two characters, and first and last 
    // characters are same
    Else L(i, j) =  L(i + 1, j - 1) + 2 

    2) Overlapping Subproblems
    Following is simple recursive implementation of the LPS problem. 
    The implementation simply follows the recursive structure 
    mentioned above.
*/

#include <cstdio>
#include <cstring>

// A utility function to get max of two integers
int max (int x, int y) { return (x > y)? x : y; }
 
// Returns the length of the longest palindromic subsequence in seq
int lps(char *seq, int i, int j)
{
   // Base Case 1: If there is only 1 character
   if (i == j)
     return 1;
 
   // Base Case 2: If there are only 2 characters and both are same
   if (seq[i] == seq[j] && i + 1 == j)
     return 2;
 
   // If the first and last characters match
   if (seq[i] == seq[j])
      return lps (seq, i+1, j-1) + 2;
 
   // If the first and last characters do not match
   return max( lps(seq, i, j-1), lps(seq, i+1, j) );
}
 
// Returns the length of the longest palindromic subsequence in seq
int lps_DP(char *str)
{
   int n = strlen(str);
   int i, j, cl;
   int L[n][n];  // Create a table to store results of subproblems
 
 
   // Strings of length 1 are palindrome of lentgh 1
   for (i = 0; i < n; i++)
      L[i][i] = 1;
 
    // Build the table. Note that the lower diagonal values of table are
    // useless and not filled in the process. The values are filled in a
    // manner similar to Matrix Chain Multiplication DP solution (See
    // http://www.geeksforgeeks.org/archives/15553). cl is length of
    // substring
    for (cl=2; cl<=n; cl++)
    {
        for (i=0; i<n-cl+1; i++)
        {
            j = i+cl-1;
            if (str[i] == str[j] && cl == 2)
               L[i][j] = 2;
            else if (str[i] == str[j])
               L[i][j] = L[i+1][j-1] + 2;
            else
               L[i][j] = max(L[i][j-1], L[i+1][j]);
        }
    }
 
    return L[0][n-1];
}

/* Driver program to test above functions */
int main()
{
    char seq[] = "forgeeksskeegfor";
    int n = strlen(seq);
    printf ("The length of the LPS is %d\n", lps(seq, 0, n-1));
    printf ("The lnegth of the LPS is %d\n", lps_DP(seq));

    return 0;
}