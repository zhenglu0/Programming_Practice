//
//  Fibonacci.cpp
//  
//  Created by 罗铮 on 8/31/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <cassert>

using namespace std;

// recursive solution of Fibonacci
int fib (int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fib(n-1)+fib(n-2); 
}

// iterative solution of Fibonacci
int fib_iterative(int n)
{
    int sum = 0;
    int previous = 1;
    int before_previous = 0;
    
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    
    for (int i = 2; i <=n; i++)
    {
        sum = before_previous + previous;
        before_previous = previous;
        previous = sum;
    }
    return sum;
}


//
// Calculate Fibonacci number by contraction
///////////////////////////////////////////////////////////////////////
// A 2 by 2 matrix
///////////////////////////////////////////////////////////////////////
struct Matrix2By2
{
    Matrix2By2
    (
     long long m00 = 0,
     long long m01 = 0,
     long long m10 = 0,
     long long m11 = 0
     )
    :m_00(m00), m_01(m01), m_10(m10), m_11(m11)
    {
    }
    
    long long m_00;
    long long m_01;
    long long m_10;
    long long m_11;
};

///////////////////////////////////////////////////////////////////////
// Multiply two matrices
// Input: matrix1 - the first matrix
//        matrix2 - the second matrix
//Output: the production of two matrices
///////////////////////////////////////////////////////////////////////
Matrix2By2 MatrixMultiply
(
 const Matrix2By2& matrix1,
 const Matrix2By2& matrix2
 )
{
    return Matrix2By2(
                      matrix1.m_00 * matrix2.m_00 + matrix1.m_01 * matrix2.m_10,
                      matrix1.m_00 * matrix2.m_01 + matrix1.m_01 * matrix2.m_11,
                      matrix1.m_10 * matrix2.m_00 + matrix1.m_11 * matrix2.m_10,
                      matrix1.m_10 * matrix2.m_01 + matrix1.m_11 * matrix2.m_11);
}

///////////////////////////////////////////////////////////////////////
// The nth power of matrix
// 1  1
// 1  0
///////////////////////////////////////////////////////////////////////
Matrix2By2 MatrixPower(unsigned int n)
{
    assert(n > 0);
    
    Matrix2By2 matrix;
    if(n == 1)
    {
        matrix = Matrix2By2(1, 1, 1, 0);
    }
    else if(n % 2 == 0)
    {
        matrix = MatrixPower(n / 2);
        matrix = MatrixMultiply(matrix, matrix);
    }
    else if(n % 2 == 1)
    {
        matrix = MatrixPower((n - 1) / 2);
        matrix = MatrixMultiply(matrix, matrix);
        matrix = MatrixMultiply(matrix, Matrix2By2(1, 1, 1, 0));
    }
    
    return matrix;
}

///////////////////////////////////////////////////////////////////////
// Calculate the nth item of Fibonacci Series using devide and conquer
///////////////////////////////////////////////////////////////////////
long long fib_matrix(unsigned int n)
{
    int result[2] = {0, 1};
    if(n < 2)
        return result[n];
    
    Matrix2By2 PowerNMinus2 = MatrixPower(n - 1);
    return PowerNMinus2.m_00;
}



int main(int argc, const char * argv[])
{

    // insert code here...
    for (int i = 0; i <= 17; i++)
        cout << fib(i) << " " ;

    cout << endl;
    for (int i = 0; i <= 17; i++)
        cout << fib_iterative(i) << " " ;

    cout << endl;
    for (int i = 0; i <= 17; i++)
        cout << fib_matrix(i) << " " ;

    return 0;
}

