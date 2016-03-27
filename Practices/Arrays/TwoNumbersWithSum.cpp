//
//  FindTwoNumbersWithSum.cpp
//  
//  Created by 罗铮 on 10/27/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

///////////////////////////////////////////////////////////////////////
// Find two numbers with a sum in a sorted array
// Output: ture is found such two numbers, otherwise false
///////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

bool FindTwoNumbersWithSum
(
 int data[],           // a sorted array
 unsigned int length,  // the length of the sorted array
 int sum,              // the sum
 int& num1,            // the first number, output
 int& num2             // the second number, output
)

{
    bool found = false;
    if(length < 1)
        return found;
    
    int ahead = length - 1;
    int behind = 0;
    
    while(ahead > behind)
    {
        long long curSum = data[ahead] + data[behind];
        
        // if the sum of two numbers is equal to the input
        // we have found them
        if(curSum == sum)
        {
            num1 = data[behind];
            num2 = data[ahead];
            found = true;
            break;
        }
        // if the sum of two numbers is greater than the input
        // decrease the greater number
        else if(curSum > sum)
            ahead --;
        // if the sum of two numbers is less than the input
        // increase the less number
        else
            behind ++;
    }
    
    return found;
}

int main(int argc, const char * argv[])
{
    int data[] = {1, 3, 4, 5, 7, 8, 9};
    int a;
    int b;
    cout << FindTwoNumbersWithSum(data, 7, 5, a, b) << endl;
    cout << "a = "<< a << endl;
    cout << "b = "<< b << endl;
    
    return 0;
}

