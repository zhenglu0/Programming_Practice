//
//  atoi&itoa.cpp
//
//  Created by 罗铮 on 11/18/12.
//  Modified by 罗铮 on 04/09/14.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

#define MAX_DIGITS_INT 10

using namespace std;

// 1. str_to_int & int_to_str using c library
//
int str_to_int_c(char c[])
{
    int num = 0;
    sscanf (c,"%d",&num);
    return num;
}

void int_to_str_c(int num, char str[])
{
    sprintf (str, "%d", num);
}


// 2. str_to_int & int_to_str using stringstream c++
//
int str_to_int_cpp(string s)
{
    int num = 0;
    istringstream iss(s);
    iss >> num;
    return num;
}

void int_to_str_cpp(int num, string &s)
{
    ostringstream oss;
    oss << num;
    s = oss.str();
}


// 3. str_to_int & int_to_str self written
//
int str_to_int(char str[])
{
    int i = 0, isNeg = 0;
    long int num = 0;
    
    if(str[0] == '-')
    {
        isNeg = 1;
        i = 1;
    }
    while(str[i])
    {
        num *= 10;
        num += (str[i++] - '0');

        // overflow
        if(num > std::numeric_limits<int>::max())
        {
            cout << "OVERFLOW!!" << endl;
            num = 0;
            break;
        }
            
    }
    if(isNeg)
        num *= -1;
    
    return (int)num;
}

// Always remember to check the positive or
// negtive sign
void int_to_str(int num, char str[])
{
    int i = 0, j = 0, isNeg = 0;
    char temp[MAX_DIGITS_INT + 2];
    if(num < 0)
    {
        num *= -1;
        isNeg = 1;
    }
    do
    {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    } while(num);
    
    if(isNeg)
        temp[i++] = '-';
    
    while(i > 0)
        str[j++] = temp[--i];

    str[j] = '\0';
}


int main(int argc, const char * argv[])
{
    
    // 1. str_to_int & int_to_str using c library
    //
    printf("1. str_to_int & int_to_str using c library \n");
    char str1 [20] = "5201314";
    int n = str_to_int_c(str1);
    printf("%d\n",n+1);
    
    char c [20];
    int_to_str_c(n-1,c);
    printf("%s\n",c);
    
    
    // 2. str_to_int & int_to_str using stringstream c++
    //
    cout << endl << "2. str_to_int & int_to_str " 
                    "using stringstream c++ " << endl;
    string str2 = "-5201314";
    int i2 = str_to_int_cpp(str2);
    cout << i2 << endl;
    
    int l = 880614;
    string m;
    int_to_str_cpp(l,m);
    string k = m + " LL";
    cout << k << endl;
    
    
    // 3. str_to_int & int_to_str self written
    //
    cout << endl << "3. str_to_int & int_to_str self written " << endl;
    char str3[] = "2147483641111";
    int i3 = str_to_int(str3);
    cout << i3 << endl;
    
    //int a = 0;
    int a = -888;
    // for the itoa, if the integer is bigger than 2^32, it will overflow, 
    // the itoa function itself does not have any problem
    //int a = 429496729622;
    
    char s[MAX_DIGITS_INT];
    // 4. test int_to_str
    int_to_str(a,s);
    printf("%s\n",s);
    
    return 0;
}



