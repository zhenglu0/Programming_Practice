//
//  LCS.cpp
//  
//  Created by 罗铮 on 11/17/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <cstring>
#include <iostream>

using namespace std;

// directions of LCS generation
enum decreaseDir {kInit = 0, kLeft, kUp, kLeftUp};

/////////////////////////////////////////////////////////////////////////////
// Print a LCS for two strings
// Input: LCS_direction - a 2d matrix which records the direction of
//                        LCS generation
//        pStr1         - the first string
//        pStr2         - the second string
//        row           - the row index in the matrix LCS_direction
//        col           - the column index in the matrix LCS_direction
/////////////////////////////////////////////////////////////////////////////
void LCS_Print(int **LCS_direction,
               char* pStr1, char* pStr2,
               size_t row, size_t col)
{
    if(pStr1 == NULL || pStr2 == NULL)
        return;
    
    size_t length1 = strlen(pStr1);
    size_t length2 = strlen(pStr2);
    
    if(length1 == 0 || length2 == 0 || !(row < length1 && col < length2))
        return;
    
    // kLeftUp implies a char in the LCS is found
    if(LCS_direction[row][col] == kLeftUp)
    {
        if(row > 0 && col > 0)
            LCS_Print(LCS_direction, pStr1, pStr2, row - 1, col - 1);
        
        // print the char
        cout << pStr1[row];
    }
    else if(LCS_direction[row][col] == kLeft)
    {
        // move to the left entry in the direction matrix
        if(col > 0)
            LCS_Print(LCS_direction, pStr1, pStr2, row, col - 1);
    }
    else if(LCS_direction[row][col] == kUp)
    {
        // move to the up entry in the direction matrix
        if(row > 0)
            LCS_Print(LCS_direction, pStr1, pStr2, row - 1, col);
    }
}

/////////////////////////////////////////////////////////////////////////////
// Get the length of two strings' LCSs, and print one of the LCSs
// Input: pStr1         - the first string
//        pStr2         - the second string
// Output: the length of two strings' LCSs
/////////////////////////////////////////////////////////////////////////////
int LCS(char* pStr1, char* pStr2)
{
    if(!pStr1 || !pStr2)
        return 0;
    
    size_t length1 = strlen(pStr1);
    size_t length2 = strlen(pStr2);
    if(!length1 || !length2)
        return 0;
    
    // initiate the length matrix
    int **LCS_length;
    LCS_length = new int* [length1];
    for(size_t i = 0; i < length1; ++i)
        LCS_length[i] = new int[length2];
    
    for(size_t i = 0; i < length1; ++i)
        for(size_t j = 0; j < length2; ++j)
            LCS_length[i][j] = 0;
    
    // initiate the direction matrix
    int **LCS_direction;
    LCS_direction = new int* [length1];
    for(size_t i = 0; i < length1; ++i)
        LCS_direction[i] = new int[length2];
    
    for(size_t i = 0; i < length1; ++i)
        for(size_t j = 0; j < length2; ++j)
            LCS_direction[i][j] = kInit;
    
    for(size_t i = 0; i < length1; ++i)
    {
        for(size_t j = 0; j < length2; ++j)
        {
            if(i == 0 || j == 0)
            {
                if(pStr1[i] == pStr2[j])
                {
                    LCS_length[i][j] = 1;
                    LCS_direction[i][j] = kLeftUp;
                }
                else
                    LCS_length[i][j] = 0;
            }
            // a char of LCS is found,
            // it comes from the left up entry in the direction matrix
            else if(pStr1[i] == pStr2[j])
            {
                LCS_length[i][j] = LCS_length[i - 1][j - 1] + 1;
                LCS_direction[i][j] = kLeftUp;
            }
            // it comes from the up entry in the direction matrix
            else if(LCS_length[i - 1][j] >= LCS_length[i][j - 1])
            {
                LCS_length[i][j] = LCS_length[i - 1][j];
                LCS_direction[i][j] = kUp;
            }
            // it comes from the left entry in the direction matrix
            else
            {
                LCS_length[i][j] = LCS_length[i][j - 1];
                LCS_direction[i][j] = kLeft;
            }
        }
    }
    /*
    for (size_t i = 0; i < length1; ++i)
    {
        for (size_t j = 0; j < length2; ++j)
            cout << LCS_length[i][j] << " ";
        cout << endl;
    }
    
    cout << endl;
    
    for (size_t i = 0; i < length1; ++i)
    {
        for (size_t j = 0; j < length2; ++j)
            cout << LCS_direction[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    */
    
    // print the result
    LCS_Print(LCS_direction, pStr1, pStr2, length1 - 1, length2 - 1);
    
    return LCS_length[length1 - 1][length2 - 1];
}


// Recursive solution without using dynamic programming
// The time complexity is exponential, just like recursive Fibonacci number
// Therefore, we need dynamic programming
int LCSRecursive(char *x, char *y, int i, int j)
{
    if (i < 0 || j < 0)
        return 0;
    
    if (x[i] == y[j])
        return LCSRecursive(x, y, i - 1, j - 1) + 1;
    else
    {
        int c1 = LCSRecursive(x, y, i, j - 1);
        int c2 = LCSRecursive(x, y, i - 1, j);
        return c1 > c2? c1 : c2;
    }
}

int** LCSDP(char *x, char *y)
{
    // check the input
    if(!x || !y)
        return 0;
    
    size_t m = strlen(x);
    size_t n = strlen(y);
    if(!m || !n)
        return 0;
    
    // initiate the length matrix
    int **c;
    c = new int* [m + 1];
    for(size_t i = 0; i <= m; ++i)
        c[i] = new int[n + 1];
    
    for(size_t i = 0; i <= m; ++i)
        c[i][0] = 0;
    for(size_t j = 0; j <= n; ++j)
        c[0][j] = 0;
    
    // Do the calculation and store the result in the table
    for(size_t i = 1; i <= m; ++i)
        for(size_t j = 1; j <= n; ++j)
        {
            if (x[i-1] == y[j-1])
                c[i][j] = c[i - 1][j - 1] + 1;
            else
                c[i][j] = c[i - 1][j] > c[i][j - 1]? c[i - 1][j] : c[i][j - 1];
        }

    return c;
}

int main(int argc, const char * argv[])
{
    char s1[] = "ABCBDAB";  // we can also use char  char s1* = "BDCABA";
    char s2[] = "BDCABA"; // we can also use char  char s2* = "ABCBDAB";
    
    cout << "numberOfCommonChars = " << LCSRecursive(s1, s2, sizeof(s1) - 2,sizeof(s2) - 2) << endl;
    
    int** LCSCount = LCSDP(s1, s2);
    cout << "numberOfCommonChars = " << LCSCount[strlen(s1)][strlen(s2)] << endl;
    
    /*
    // print the counting matrix
    for (size_t i = 0; i <= strlen(s1); ++i)
    {
        for (size_t j = 0; j <= strlen(s2); ++j)
            cout << LCSCount[i][j] << " ";
        cout << endl;
    }
    */
    
    cout << endl;
    int count = LCS(s1, s2);
    cout << endl << "numberOfCommonChars = " << count << endl;
    
    return 0;
}

