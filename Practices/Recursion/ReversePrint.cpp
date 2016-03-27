//
//  ReversePrint.cpp
//  
//  Created by 罗铮 on 10/27/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

// 从尾到头输出一个字符串；
/*
#include <iostream>
using namespace std;

void fun(char *str)
{
    if (*str != '\0')
    {
        fun(str+1);
        printf("%c", *str);
    }
}

int main(int argc, char *argv[])
{
    char str[] = "abcdefg";
    fun(str);
    return 0;
}
*/

//递归求字符串长度：
#include <iostream>
using namespace std;

int len(char *str)
{
    if (*str != '\0')
        return 1+len(str+1);
    else
        return 0;
}

int main(int argc, char *argv[])
{
    char str[] = "abcdef";
    cout << len(str) << endl;
    return 0;
}