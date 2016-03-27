//
//  RotateImageInplace.cpp
//  
//  Created by 罗铮 on 12/7/12.
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
    }
    return A;
}

// 1. Recursive solution
//
void DoRotateImage(int **A, int n, int m)
{
    if (m > n / 2)
        return;
    
    for (int i = m; i < n - m; i++)
    {
        int temp = A[m][i];
        A[m][i] = A[n - i][m];
        A[n - i][m] = A[n - m][n - i];
        A[n - m][n - i] = A[i][n - m];
        A[i][n - m] = temp;
    }
    DoRotateImage(A, n, m + 1);
}

void RotateImageRecursively(int **A, int n)
{
    DoRotateImage(A, n - 1, 0);
}


// 2. Iterative solution
//
void RotateImageIteratively(int **A, int n)
{
    int m = 0;
    n--;
    while ( m <= n / 2)
    {
        for (int i = m; i < n - m; i++)
        {
            int temp = A[m][i];
            A[m][i] = A[n - i][m];
            A[n - i][m] = A[n - m][n - i];
            A[n - m][n - i] = A[i][n - m];
            A[i][n - m] = temp;
        }
        m++;   
    }
}


int main(int argc, const char * argv[])
{
    // 1. test 3 * 3 matrix
    int n1 = 3;
    
    int **A = CreateAMatrix(n1, n1);
    PrintMatrixSequencially(A, n1, n1);
    //RotateImageRecursively(A, n1);
    RotateImageIteratively(A, n1);
    cout << endl << "The Matrix after rotate is: " 
         << endl << endl;
    PrintMatrixSequencially(A, n1, n1);
    
    cout << endl << "********************" 
         << endl << endl;
    
    // 2. test 4 * 4 matrix
    int n2 = 4;
    
    int **B = CreateAMatrix(n2, n2);
    PrintMatrixSequencially(B, n2, n2);
    //RotateImageRecursively(B, n2);
    RotateImageIteratively(B, n2);
    cout << endl << "The Matrix after rotate is: " 
         << endl << endl;
    PrintMatrixSequencially(B, n2, n2);
    
    
    cout << endl << "********************" 
         << endl << endl;
    
    // 3. test 4 * 4 matrix
    int n3 = 5;
    
    int **C = CreateAMatrix(n3, n3);
    PrintMatrixSequencially(C, n3, n3);
    //RotateImageRecursively(C, n3);
    RotateImageIteratively(C, n3);
    cout << endl << "The Matrix after rotate is: " 
         << endl << endl;
    PrintMatrixSequencially(C, n3, n3);
    
    return 0;
}

