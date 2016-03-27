//
//  UglyNumber.cpp
//
//  Modified on 03/14/14.
//  Copyright (c) 2014 罗铮. All rights reserved.
//  http://zhedahht.blog.163.com/blog/static/2541117420094245366965

#include <cstdio>
#include <cstdlib>

#define bool int
 
/*This function divides a by greatest divisible 
  power of b*/
int maxDivide(int a, int b)
{
    while (a%b == 0)
        a = a/b; 
    return a;
}   
 
/* Function to check if a number is ugly or not */
int isUgly(int no)
{
    no = maxDivide(no, 2);
    no = maxDivide(no, 3);
    no = maxDivide(no, 5);
     
    return (no == 1)? 1 : 0;
}    
 
/* Function to get the nth ugly number*/
int getNthUglyNo_bruteforce(int n)
{
    int i = 1; 
    int count = 1;   /* ugly number count */

    /*Check for all integers untill ugly count 
      becomes n*/
    while (n > count)
    {
        i++;      
        if (isUgly(i))
            count++; 
    }
    return i;
}

/* Function to find minimum of 3 numbers */
unsigned min(unsigned , unsigned , unsigned );
 
/* Function to get the nth ugly number*/
unsigned getNthUglyNo(unsigned n)
{
    unsigned *ugly =
             (unsigned *)(malloc (sizeof(unsigned)*n));
    unsigned i2 = 0, i3 = 0, i5 = 0;
    unsigned next_multiple_of_2 = 2;
    unsigned next_multiple_of_3 = 3;
    unsigned next_multiple_of_5 = 5;
    unsigned next_ugly_no = 1;
    *(ugly+0) = 1;
 
    for(unsigned i=1; i<n; i++)
    {
       next_ugly_no = min(next_multiple_of_2,
                           next_multiple_of_3,
                           next_multiple_of_5);
       *(ugly+i) = next_ugly_no;                    
       if(next_ugly_no == next_multiple_of_2)
       {
           i2 = i2+1;       
           next_multiple_of_2 = *(ugly+i2)*2;
       }
       if(next_ugly_no == next_multiple_of_3)
       {
           i3 = i3+1;
           next_multiple_of_3 = *(ugly+i3)*3;
       }
       if(next_ugly_no == next_multiple_of_5)
       {
           i5 = i5+1;
           next_multiple_of_5 = *(ugly+i5)*5;
       }
    } /*End of for loop (i=1; i<n; i++) */
    return next_ugly_no;
}
 
/* Function to find minimum of 3 numbers */
unsigned min(unsigned a, unsigned b, unsigned c)
{
    if(a <= b)
    {
        if(a <= c)
            return a;
        else
            return c;
    }
    if(b <= c)
        return b;
    else
        return c;
}

// #2 http://zhedahht.blog.163.com/blog/static/2541117420094245366965
int Min(int number1, int number2, int number3)
{
    int min = (number1 < number2) ? number1 : number2;
    min = (min < number3) ? min : number3;
 
    return min;
}

int GetUglyNumber_Solution2(int index)
{
    if(index <= 0)
        return 0;
 
    int *pUglyNumbers = new int[index];
    pUglyNumbers[0] = 1;
    int nextUglyIndex = 1;
 
    int *pMultiply2 = pUglyNumbers;
    int *pMultiply3 = pUglyNumbers;
    int *pMultiply5 = pUglyNumbers;
 
    while(nextUglyIndex < index)
    {
        int min = Min(*pMultiply2 * 2, *pMultiply3 * 3, *pMultiply5 * 5);
        pUglyNumbers[nextUglyIndex] = min;
 
        while(*pMultiply2 * 2 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply2;
        while(*pMultiply3 * 3 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply3;
        while(*pMultiply5 * 5 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply5;
 
        ++nextUglyIndex;
    }
 
    int ugly = pUglyNumbers[nextUglyIndex - 1];

    delete[] pUglyNumbers;
    return ugly;
}
 
/* Driver program to test above functions */
int main()
{
    unsigned no = getNthUglyNo(1500);
    printf("%dth ugly no. is %d \n", 150, no);

    //unsigned no_bf = getNthUglyNo_bruteforce(1500);
    //printf("%dth ugly no. is %d \n", 150, no_bf);

    unsigned no_2 = GetUglyNumber_Solution2(1500);
    printf("%dth ugly no. is %d \n", 150, no_2);
    
    return 0;
}