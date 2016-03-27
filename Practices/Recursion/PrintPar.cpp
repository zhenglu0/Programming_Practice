//
//  PrintPar.cpp
//  
//  Created by 罗铮 on 11/4/12.
//  Modified by 罗铮 on 04/02/14.
//  Copyright (c) 2012 罗铮. All rights reserved.
//  http://www.geeksforgeeks.org/print-all-combinations-of-balanced-parentheses/

#include <iostream>
#include <cstdio>

#define MAX_SIZE 100

using namespace std;

void DoPrint(int l, int r, char * str, int count, int num)
{
    if (l == 0 && r == 0)
    {
        for (int i = 0; i < 2 * num; i++)
            cout << str[i];
        cout << endl;
    }    
    else
    {
        if (l > 0 && (r == num || l <= r))
        {
            str[count] = '(';
            DoPrint(l-1, r, str, count+1, num);
        }
        if (r - l > 0)
        {
            str[count] = ')';
            DoPrint(l, r-1, str, count+1, num);
        }
    }
    
}

void PrintPar(int count)
{
    char * str = new char[2 * count];

    if (count > 0)
        DoPrint(count,count,str,0,count);
}

void _printParenthesis(int pos, int n, int open, int close)
{
    static char str[MAX_SIZE];     

    if(close == n) 
    {
        printf("%s \n", str);
        return;
    }
    else
    {
        if(open > close) {
            str[pos] = ')';
            _printParenthesis(pos+1, n, open, close+1);
        }
        if(open < n) {
            str[pos] = '(';
            _printParenthesis(pos+1, n, open+1, close);
        }
    }
}

/* Wrapper over _printParenthesis()*/
void printParenthesis(int n)
{
    if(n > 0)
        _printParenthesis(0, n, 0, 0);
    return;
}   


/* driver program to test above functions */
int main(int argc, const char * argv[])
{
    int i = 3;
    // #1 
    PrintPar(i);
    cout << endl;
    // #2
    printParenthesis(i);

    return 0;
}

