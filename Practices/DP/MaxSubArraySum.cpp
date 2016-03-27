//
//  MaxSubArraySum.cpp
//
//  Created by 罗铮 on 10/27/12.
//  Modified on 03/09/14.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <algorithm>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Find the greatest sum of all sub-arrays
// Return value: if the input is valid, return true, otherwise return false
/////////////////////////////////////////////////////////////////////////////
bool FindGreatestSumOfSubArray
(
 int *pData,           // an array
 unsigned int nLength, // the length of array
 int &nGreatestSum     // the greatest sum of all sub-arrays
)

{
    // if the input is invalid, return false
    if((pData == NULL) || (nLength == 0))
        return false;
    
    int nCurSum = nGreatestSum = 0;
    for(unsigned int i = 0; i < nLength; ++i)
    {
        nCurSum += pData[i];
        
        // if the current sum is negative, discard it
        if(nCurSum < 0)
            nCurSum = 0;
        
        // if a greater sum is found, update the greatest sum
        if(nCurSum > nGreatestSum)
            nGreatestSum = nCurSum;
        
    }
    
    
    // if all data are negative, find the greatest element in the array
    if(nGreatestSum == 0)
    {
        nGreatestSum = pData[0];
        for(unsigned int i = 1; i < nLength; ++i)
        {
            if(pData[i] > nGreatestSum)
                nGreatestSum = pData[i];
        }
    }
    
    return true;
}

// Algorithm 1:时间效率为O(n*n*n)
// Brute force
int MaxSubsequenceSum1(const int A[],int N)
{
    int ThisSum = 0 , MaxSum = 0;
    for(int i = 0; i < N; i++)
        for(int j = i; j < N; j++)
        {
            ThisSum = 0;
            for(int k = i ;k < j; k++)
                ThisSum += A[k];
            
            if(ThisSum > MaxSum)
                MaxSum = ThisSum;
        }
    return MaxSum;
}


// Algorithm 1:时间效率为O(n*n)
// Brute force
int MaxSubsequenceSum2(const int A[],int N)
{
    int ThisSum = 0 , MaxSum = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = i; j < N; j++)
        {
            ThisSum += A[j];
            if (ThisSum > MaxSum)
                MaxSum = ThisSum;
        }
        ThisSum = 0;
    }
    return MaxSum;
}


// Algorithm 3:时间效率为O(n*logn)
// Divide and conquer
// 算法3的主要思想：采用二分策略，将序列分成左右两份。
// 那么最长子序列有三种可能出现的情况，即
//【1】只出现在左部分.
//【2】只出现在右部分。
//【3】出现在中间，同时涉及到左右两部分。
// 分情况讨论之。
int MaxSubsequenceSum3(const int A[],int l,int r)
{
    // 左、右部分最大连续子序列值。对应情况【1】、【2】
    int MaxLeftSum, MaxRightSum;
    // 从中间分别到左右两侧的最大连续子序列值，对应case【3】。              
    int MaxLeftBorderSum, MaxRightBorderSum;  
    int LeftBorderSum, RightBorderSum;
    int m, i;
    
    // Base Case
    if(l == r)
        return  A[l] > 0? A[l] : 0;
    
    //【1】只出现在左部分.
    //【2】只出现在右部分。
    m = (l + r) / 2; // we can use m = l + (r - l) / 2 to avoid overflow
    MaxLeftSum = MaxSubsequenceSum3(A,l,m);
    MaxRightSum = MaxSubsequenceSum3(A,m + 1,r);
    
    //【3】出现在中间，同时涉及到左部分。
    MaxLeftBorderSum = 0;
    LeftBorderSum = 0;
    for(i = m; i >= l; i--)
    {
        LeftBorderSum += A[i];
        if(LeftBorderSum > MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    }
    //【3】出现在中间，同时涉及到右部分。
    MaxRightBorderSum = 0;
    RightBorderSum = 0;
    for(i = m + 1; i <= r; i++)
    {
        RightBorderSum += A[i];
        if(RightBorderSum > MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    }
    
    // compare the result
    int max1 = MaxLeftSum > MaxRightSum? MaxLeftSum : MaxRightSum;
    int max2 = MaxLeftBorderSum + MaxRightBorderSum;
    
    // return the max in the max1 and max2
    return max1 > max2? max1 : max2;
}


// Algorithm 4:时间效率为O(n)
// Dynamic Programming
int MaxSubsequenceSum4(const int A[],int N)
{
    int ThisSum = 0, MaxSum = 0;
    for(int j = 0; j < N; j++)
    {
        ThisSum += A[j];
        if(ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if(ThisSum < 0)
            ThisSum = 0;
    }
    return MaxSum;
}

int FindMaxSumOfSubArrayWithIndex(const int A[], int n, int &start, int &end)
{
    int thisSum = 0, maxSum = 0, thisStart = 0;
    start = end = 0;
    bool setStart = true;
    
    for (int i = 0; i < n; ++i)
    {
        thisSum += A[i];
        // the starting postion can only occur when A[i] > 0 
        if (thisSum > 0)
        {
            if (setStart)
            {
                thisStart = i;
                setStart = false;
            }
            if (thisSum > maxSum)
            {
                maxSum = thisSum;
                end = i;
                start = thisStart;
            }
        }
        // when the negtive sign appear, 
        // we need to reset the start position when is is positive
        else if (thisSum < 0)
        {
            thisSum = 0;
            setStart = true;
        }
    }
    return maxSum;
}

int OPT[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
int OPD[8];

// Recursive top_down with memorization
int MSS_ends_at_n_topdown(const int a[],int n)
{
    if (n == 0) return a[0] > 0? a[0]:0;
    if (OPT[n] < 0) {
        int max_sum = max(MSS_ends_at_n_topdown(a,n-1) + a[n], 0);
        OPT[n] = max_sum;
        cout << "OPT[" << n << "] = " << max_sum << endl;
    }

    return OPT[n];
}

int MaxSubsequenceSum_top_down(const int a[],int n)
{
    int max_sum = 0;
    for (int i = 0; i < n; ++i)
        max_sum = max(max_sum,MSS_ends_at_n_topdown(a,i));
    return max_sum;
}

// Dynamic Programming bottom_up
void CalculateOPD(const int a[],int n)
{
    if (a[0] > 0) OPD[0] = a[0];
    else OPD[0] = 0;

    for (int i = 1; i < n; ++i)
        OPD[i] = max(OPD[i-1] + a[i], 0);
}

int MaxSubsequenceSum_bottomup(const int a[],int n)
{
    int max_sum = 0;
    CalculateOPD(a,8);
    
    for (int i = 0; i < n; ++i)
        max_sum = max(max_sum,OPD[i]);

    return max_sum;
}


int main(int argc, const char * argv[])
{
    int greatestSum = 0;
    int a[] = {1, -2, 3, 10, -4, 7, 2, -5};
    
    // #1. O(n)
    FindGreatestSumOfSubArray(a, 8, greatestSum);
    cout << "The Greatest sum of the subarray is " << greatestSum << endl;
    
    // #2. O(n*n*n)
    int greatestSum1 = 0;
    greatestSum1 = MaxSubsequenceSum1(a, 8);
    cout << "The Greatest sum of the subarray is " << greatestSum1 << endl;
    
    // #3. O(n*n)
    int greatestSum2 = 0;
    greatestSum2 = MaxSubsequenceSum2(a, 8);
    cout << "The Greatest sum of the subarray is " << greatestSum2 << endl;
    
    // #4. O(n*logn)
    int greatestSum3 = 0;
    greatestSum3 = MaxSubsequenceSum3(a, 0, 7);
    cout << "The Greatest sum of the subarray is " << greatestSum3 << endl;
    
    // #5. O(n)
    int greatestSum4 = 0;
    greatestSum4 = MaxSubsequenceSum4(a, 8);
    cout << "The Greatest sum of the subarray is " << greatestSum4 << endl;

    // #6. O(n) with index
    int greatestSum5 = 0;
    int start, end;
    greatestSum5 = FindMaxSumOfSubArrayWithIndex(a, 8, start, end);
    cout << "The Greatest sum of the subarray is " << greatestSum5 
         << " start = " << start << " end = " << end << endl;
    
    // #7. Dynamic programming O(n)
    int greatestSum6 = 0;
    greatestSum6 = MaxSubsequenceSum_top_down(a, 8);
    cout << "The Greatest sum of the subarray is " << greatestSum6 << endl;

    // #7. Dynamic programming O(n)
    int greatestSum7 = 0;
    greatestSum7 = MaxSubsequenceSum_bottomup(a, 8);
    cout << "The Greatest sum of the subarray is " << greatestSum7 << endl;

    return 0;
}

