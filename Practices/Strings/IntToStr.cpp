//
//  itoa.cpp
//  
//  Modified by by 罗铮 on 03/29/14.

#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>

#define MAX_DIGITS_INT 10

using namespace std;

// #1. C++ API inplementation
int str_to_int_cxx(string s)
{
    int num = 0;
    istringstream iss(s);
    iss >> num;
    return num;
}

void int_to_str_cxx(int num, string &s)
{
    ostringstream oss;
    oss << num;
    s = oss.str();
}

// #2. C API inplementation
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

// #3. C code inplementation
int str_to_int_bad(char str[])
{
    int i = 0, isNeg = 0, num = 0;
    if(str[0] == '-')
    {
        isNeg = 1;
        i = 1;
    }
    while(str[i])
    {
        num *= 10;
        num += (str[i++] - '0');
    }
    if(isNeg)
    {
        num *= -1;
    }
    return num;
}

void int_to_str_original(int num, char str[])
{
    int i = 0, j = 0, isNeg = 0;
    char temp[MAX_DIGITS_INT + 2];
    if(num < 0)
    {
        num *= -1;
        isNeg = 1;
    }
    while(num)
    {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    }
    if(isNeg)
    {
        temp[i++] = '-';
    }
    while(i > 0)
    {
        str[j++] = temp[--i];
    }
    str[j] = '\0';
}

void int_to_str_revised(int num, char str[])
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
    {
        temp[i++] = '-';
    }
    while(i > 0)
    {
        str[j++] = temp[--i];
    }
    str[j] = '\0';
}


// Driver program to test above functions
int main(int argc, char * argv[])
{
    // C++ API
    string s_cxx = "-5201314";
    int j = str_to_int_cxx(s_cxx);
    int a =  j + 1;
    cout << a << endl;

    int l = 880614;
    string m;
    int_to_str_cxx(l,m);
    string k = m + " LL";
    cout << k << endl;

    // C API
    char str [20] = "5201314";
    int n = str_to_int_c(str);
    printf("%d\n",n+1);

    char c [20];
    int_to_str_c(n-1,c);
    printf("%s",c);

    // C program
    int i = 0;
    char s[MAX_DIGITS_INT];
    int_to_str_original(i,s);
    printf("%s\n",s);

    int_to_str_revised(i,s);
    printf("%s\n",s);

    return 0;
}
