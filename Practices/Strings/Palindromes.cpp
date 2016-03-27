//
//  LongestPalindromic.cpp
//  
//  Created by 罗铮 on 12/10/12.
//  Modified by by 罗铮 on 04/12/14.
//  
//  http://www.geeksforgeeks.org/longest-palindromic-substring-set-2/
//  http://leetcode.com/2011/11/longest-palindromic-substring-part-i.html
//  http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
//  http://www.felix021.com/blog/read.php?2040

/*
    We can find the longest palindrome substring in (n^2) time with O(1) 
    extra space. The idea is to generate all even length and odd length 
    palindromes and keep track of the longest palindrome seen so far.

    Step to generate odd length palindrome:
    Fix a centre and expand in both directions for longer palindromes.

    Step to generate even length palindrome
    Fix two centre ( low and high ) and expand in both 
    directions for longer palindromes.
*/
    
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

bool isPalindrome(char *str, int l, int r)
{
    if (!str)
        return true;
    
    while (l <= r)
    {
        if (str[l] != str[r])
            return false;
        l++;
        r--;
    }
    return true;
}

void findLongestPalindrome(char *str)
{
    int lengthOfLongestPalindrome = 0, start, end;
    int length = (int) strlen(str);
    
    for (int i = 0; i < length; i++)
    {
        for (int j = i; j < length; j++)
        {
            if (isPalindrome(str, i, j))
            {
                if (j - i > lengthOfLongestPalindrome)
                {
                    lengthOfLongestPalindrome = j - i;
                    start = i;
                    end = j;
                }
            }
            
        }
    }
    for (int i = start; i <= end; i++)
        cout << str[i];
}


int findNumberofPalindromes(char *str)
{
    int count = 0;
    int length = (int) strlen(str);
    
    for (int i = 0; i < length; i++)
        for (int j = i; j < length; j++)
            if (isPalindrome(str, i, j))
                count++;
    return count;
}


int expandAroundCenter(char * str, int l, int r, int &start, int &end)
{
    int n = (int) strlen(str);
    while (l >= 0 && r <= n - 1 && str[l] == str[r])
    {
        l--;
        r++;
    }
    start = ++l;
    end = --r;
    return r - l + 1;
}

void findLongestPalindrome2(char *str)
{
    int n = (int)strlen(str);
    int longest = 0, start, end, l, r;
    for (int i = 0; i < n - 1; i++)
    {
        int v1 = expandAroundCenter(str, i, i, l, r);
        int v2 = expandAroundCenter(str, i, i + 1, l, r);
        if (v1 > longest)
        {
            start = l;
            end = r;
            longest = v1;
        }
        if (v2 > longest)
        {
            start = l;
            end = r;
            longest = v2;
        }
    }
    for (int i = start; i <= end; i++)
        cout << str[i];
}

// A O(n^2) time and O(1) space program to find the 
// longest palindromic substring
// A utility function to print a substring str[low..high]
void printSubStr(char* str, int low, int high)
{
    for( int i = low; i <= high; ++i )
        printf("%c", str[i]);
}
 
// This function prints the longest palindrome substring (LPS)
// of str[]. It also returns the length of the longest palindrome
int longestPalSubstr(char *str)
{
    int maxLength = 1;  // The result (length of LPS)
 
    int start = 0;
    int len = strlen(str);
 
    int low, high;
 
    // One by one consider every character as center point of 
    // even and length palindromes
    for (int i = 1; i < len; ++i)
    {
        // Find the longest even length palindrome with center points
        // as i-1 and i.  
        low = i - 1;
        high = i;
        while (low >= 0 && high < len && str[low] == str[high])
        {
            if (high - low + 1 > maxLength)
            {
                start = low;
                maxLength = high - low + 1;
            }
            --low;
            ++high;
        }
 
        // Find the longest odd length palindrome with center 
        // point as i
        low = i - 1;
        high = i + 1;
        while (low >= 0 && high < len && str[low] == str[high])
        {
            if (high - low + 1 > maxLength)
            {
                start = low;
                maxLength = high - low + 1;
            }
            --low;
            ++high;
        }
    }
 
    printf("Longest palindrome substring is: ");
    printSubStr(str, start, start + maxLength - 1);
 
    return maxLength;
}

// An O(N) Solution (Manacher’s Algorithm):
// Transform S into T.
// For example, S = "abba", T = "^#a#b#b#a#$".
// ^ and $ signs are sentinels appended to each end to avoid bounds checking
string preProcess(string s) {
    int n = s.length();

    if (n == 0) 
        return "^$";
    string ret = "^";
    
    for (int i = 0; i < n; i++)
        ret += "#" + s.substr(i, 1);

    ret += "#$";
    return ret;
}
 
string longestPalindrome(string s) {
    string T = preProcess(s);
    int n = T.length();
    int *P = new int[n];
    int C = 0, R = 0;

    // The core part of the algorithm
    for (int i = 1; i < n-1; i++) {
        // equals to i' = C - (i-C)
        int i_mirror = 2 * C - i;

        /*
        Let’s summarize the key part of 
        this algorithm as below:

        if P[ i' ] ≤ R – i,
        then P[ i ] ← P[ i' ]
        else P[ i ] ≥ P[ i' ] 
             or we can say that
             P[ i ] = P[ i' ] = R – i. 

        Which we have to expand past the right 
        edge (R) to find P[ i ].
        */
        //P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;

        if (R > i)
            P[i] = min(R-i, P[i_mirror]);
        else 
            P[i] = 0;

        // Attempt to expand palindrome centered at i
        while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
            P[i]++;

        // If palindrome centered at i expand past R,
        // adjust center based on expanded palindrome.
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }

    // Find the maximum element in P.
    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 1; i < n-1; i++) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }
    delete[] P;

    return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
}


// Driver program to test above functions
int main(int argc, const char * argv[])
{
    char str[] = "luoaababbaccabbmekanx";
    findLongestPalindrome(str);
    cout << endl;
    findLongestPalindrome2(str);
    cout << endl << "The number of palindrome is " 
         << findNumberofPalindromes(str) << endl;

    char str2[] = "forgeeksskeegfor";
    printf("\nLength is: %d\n", longestPalSubstr( str2 ) );

    string p = longestPalindrome(string(str2));
    cout << "Manacher’s Algorithm: " << p << endl;
    return 0;
    
}

