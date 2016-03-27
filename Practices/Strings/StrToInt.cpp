//
//  StrToInt.cpp
//  
//  Created by 罗铮 on 10/29/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <limits>

using namespace std;

enum Status {kValid = 0, kInvalid};
int g_nStatus = kValid;

///////////////////////////////////////////////////////////////////////
// Convert a string into an integer
// You also need to consider whether it is a signed integer or
// an unsigned integer
// The most important thing is that you need to consider integer over
// flow if it is too big
///////////////////////////////////////////////////////////////////////
int StrToInt(const char* str)
{
    g_nStatus = kInvalid;
    long long num = 0;

    if(str != NULL)
    {
        const char* digit = str;

        // the first char in the string maybe '+' or '-'
        bool minus = false;
        if(*digit == '+')
            digit ++;
        else if(*digit == '-')
        {
            digit ++;
            minus = true;
        }

        // the remaining chars in the string
        while(*digit != '\0')
        {
            if(*digit >= '0' && *digit <= '9')
            {
                num = num * 10 + (*digit - '0');

                // overflow
                if(num > std::numeric_limits<int>::max())
                {
                    num = 0;
                    break;
                }

                digit ++;
            }
            // if the char is not a digit, invalid input
            else
            {
                num = 0;
                break;
            }
        }

        if(*digit == '\0')
        {
            g_nStatus = kValid;
            if(minus)
                num = 0 - num;
        }
    }

    return static_cast<int>(num);
}


int main(int argc, const char * argv[])
{
    // test case 1
    char c1[] = "1234567";
    int i1 = StrToInt(c1);
    cout << "i1 = " << i1 << endl;

    // test case 2
    char c2[] = "-1234567";
    int i2 = StrToInt(c2);
    cout << "i2 = " << i2 << endl;

    // test case 3
    char c3[] = "2147483641111";
    int i3 = StrToInt(c3);
    cout << "i3 = " << i3 << endl;

    // test case 4
    char c4[] = "+1234567";
    int i4 = StrToInt(c4);
    cout << "i4 = " << i4 << endl;

    return 0;
}

