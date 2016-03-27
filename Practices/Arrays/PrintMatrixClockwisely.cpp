//
//  PrintMatrixClockwisely.cpp
//  
//  Created by 罗铮 on 11/30/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <iomanip>

using namespace std;

void DoPrintMatrixSequencially(int **A, int r, int c, int x, int y)
{
    if (x > c -1  && y > r -1 )
        return;
    
    if (x == c -1 && y == r -1 )
    {
        cout << A[x][y];
        return;
    }
    
    for (int i = x; i < c; i++)
        cout << A[x][i] << " ";
        
    for (int i = y + 1; i < r; i++)
        cout << A[i][r - 1] << " ";
    
    for (int i = c - 2; i >= x; i--)
        cout << A[r - 1][i] << " ";
    
    for (int i = r - 2; i >= y + 1; i--)
        cout << A[i][x] << " ";
    
    DoPrintMatrixSequencially(A, r - 1,  c - 1, x + 1, y + 1);
    
}

void PrintMatrixClockwisely(int **A, int r, int c)
{
    DoPrintMatrixSequencially(A, r, c, 0, 0);
}

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
    }
    return A;
}


int main(int argc, const char * argv[])
{
    // 1. test 4 * 4 matrix
    int row1 = 4;
    int column1 = 4;
    
    int **A = CreateAMatrix(row1, column1);
    PrintMatrixSequencially(A, row1, column1);
    
    cout << endl << "The clockwise printed matrix is: " << endl;
    
    PrintMatrixClockwisely(A, row1, column1);

    cout << endl << endl;
    
    // 2. test 5 * 5 matrix
    int row2 = 5;
    int column2 = 5;
    
    int **B = CreateAMatrix(row2, column2);
    PrintMatrixSequencially(B, row2, column2);
    
    cout << endl << "The clockwise printed matrix is: " << endl;
    
    PrintMatrixClockwisely(B, row2, column2);

    return 0;
}

