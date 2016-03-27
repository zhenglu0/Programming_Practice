//
//  Search2DArray.cpp
//  
//  Created by 罗铮 on 12/11/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <iomanip>

using namespace std;

void PrintMatrixSequencially(int **A, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << setw(2) << A[i][j] << " ";

        cout << endl;
    }
}

int **CreateAMatrix(int r, int c)
{
    int **A = new int* [r];
    int n = 1;
    for (int i = 0; i < r; i++)
    {
        int *B = new int [c];
        for (int j = 0; j < c; j++)
        {
            B[j] = n;
            n++;
        }
        A[i] = B;
        n++;
    }
    return A;
}

bool DoSearch2DArray(int **A, int m, int n, int v, 
                     int &x, int &y, int i, int j)
{
    if (i > m - 1 || j < 0)
    {
        x = -1;
        j = -1;
        return false;
    }
    
    if (v == A[i][j])
    {
        x = i;
        y = j;
        return true;
    }
    
    if (v > A[i][j])
        return DoSearch2DArray(A, m, n, v, x, y, i + 1, j);
    else
        return DoSearch2DArray(A, m, n, v, x, y, i, j - 1);
    
}

bool Search2DArrayRecursively(int **A, int m, int n, 
                              int v, int &x, int &y)
{
    return DoSearch2DArray(A, m, n, v, x, y, 0, n - 1);
}


bool Search2DArrayIteratively(int **A, int m, int n, 
                              int v, int &x, int &y)
{
    int i = 0;
    int j = n - 1;
    
    while (i <= m - 1 && j >= 0)
    {
        if (v == A[i][j])
        {
            x = i;
            y = j;
            return true;
        }
        if (v > A[i][j])
            i++;
        else
            j--;
    }
    
    x = -1;
    y = -1;
    return false;
}


int main(int argc, const char * argv[])
{
    // 1. test 3 * 4 matrix
    int row1 = 3;
    int column1 = 4;
    
    int **A = CreateAMatrix(row1, column1);
    PrintMatrixSequencially(A, row1, column1);
    int x1, y1;
    int v1 = 7;
    
    cout << endl ;
    if (Search2DArrayRecursively(A, row1, column1, v1, x1, y1))
        cout << "The value " << v1 << " is found," 
             << " x = " << x1 << " y = " << y1 << endl;
    if (Search2DArrayIteratively(A, row1, column1, v1, x1, y1))
        cout << "The value " << v1 << " is found," 
             << " x = " << x1 << " y = " << y1 << endl;
    cout << endl << endl;
    
    // 2. test 4 * 5 matrix
    int row2 = 5;
    int column2 = 5;
    
    int **B = CreateAMatrix(row2, column2);
    PrintMatrixSequencially(B, row2, column2);
    
    int x2, y2;
    int v2 = 20;
    
    cout << endl ;
    if (Search2DArrayRecursively(B, row2, column2, v2, x2, y2))
        cout << "The value " << v2 << " is found," 
             << " x = " << x2 << " y = " << y2 << endl;
    
    if (Search2DArrayIteratively(B, row2, column2, v2, x2, y2))
        cout << "The value " << v2 << " is found," 
             << " x = " << x2 << " y = " << y2 << endl;
    
    return 0;
}



