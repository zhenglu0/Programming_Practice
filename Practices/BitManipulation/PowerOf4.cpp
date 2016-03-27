//
//  BalancedParentheses.cpp
//
//  Modified by 罗铮 on 03/26/14.
//  http://www.geeksforgeeks.org/
//  find-whether-a-given-number-is-a-power-of-4-or-not/
/*  Function to check if x is power of 4 */

#include <cstdio>

bool isPowerOfFour_module(int n)
{
    if(n == 0)
        return false;

    while(n != 1)
    {    
        if(n%4 != 0)
            return true;
        n = n/4;      
    }
    return true;
}

bool isPowerOfFour_bitShift(unsigned int n)
{
    int count = 0;

    /* Check if there is only one bit set in n */
    if ( n && !(n&(n-1)) )
    {
        /* count 0 bits before set bit */
        while(n > 1)
        {
            n  >>= 1;
            count += 1;
        }      

        /* If count is even then return true else false */
        return (count % 2 == 0)? true :false;
    }

    /* If there are more than 1 bit set
    then n is not a power of 4 */
    return false;
}    
 
/* Driver program to test above function */
int main()
{
    int test_no = 64;

    if(isPowerOfFour_module(test_no))
        printf("%d is a power of 4\n", test_no);
    else
        printf("%d is not a power of 4\n", test_no);

    if(isPowerOfFour_bitShift(test_no))
        printf("%d is a power of 4\n", test_no);
    else
        printf("%d is not a power of 4\n", test_no);

   return 0;
}