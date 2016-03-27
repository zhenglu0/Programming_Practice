//
//  Combination.cpp
//
//  Created by 罗铮 on 11/19/12.
//  Copyright (c) 2012 罗铮. All rights reserved.
//  
//  http://zhedahht.blog.163.com/blog/static/2541117420114172812217/

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;


// 1.
/*
 假设我们想在长度为n的字符串中求m个字符的组合。我们先从头扫描字符串的第一个字符。
 针对第一个字符，我们有两种选择：一是把这个字符放到组合中去，
 接下来我们需要在剩下的n-1个字符中选取m-1个字符；
 而是不把这个字符放到组合中去，接下来我们需要在剩下的n-1个字符中选择m个字符。
 这两种选择都很容易用递归实现。
 */
void DoCombination(char* string, int number, vector<char>& result)
{
    if(number == 0)
    {
        for(vector<char>::iterator iter = result.begin(); 
            iter < result.end(); ++ iter)
            cout << *iter;
        
        cout << endl;
        return;
    }
    
    if(*string == '\0')
        return;
    
    result.push_back(*string);
    DoCombination(string + 1, number - 1, result);
    result.pop_back();
    
    DoCombination(string + 1, number, result);
}

void Combination(char* string)
{
    if(string == NULL)
        return;
    
    int length = (int)strlen(string);
    vector<char> result;
    
    for(int i = 1; i <= length; ++ i)
        DoCombination(string, i, result);
}


// 2. Method in the Programming interview exposed
//
void DoCombine(char in[],char out[], int length, 
               int recursLev, int start)
{    
    for(int i = start; i < length; ++i)
    {
        out[recursLev] = in[i];
        out[recursLev + 1] = '\0';
        printf("%s\n",out);
        if(i < length - 1){
            DoCombine(in,out,length,
                      recursLev + 1, i + 1);
        }
    }
}

int Combine(char inString[])
{
    int length;
    char *out;
    length = (int)strlen(inString);
    out = (char *) malloc(length + 1);
    if(!out)
        return -1;

    out[length] = '\0';
    DoCombine(inString,out,length,0,0);
    free(out);
    return 0;
}


// 3. Recursvie solution
//
void printCombination(int A[], char S[], int n)
{
	for(int i = 0; i < n; ++i)
        if(A[i])
            cout << S[i];
	cout << endl;
}

void DoCombination3(int A[], char S[], int n, int i )
{
	if( i == n )
    {
		printCombination(A, S,n);
        return;
    }
    
    A[i] = 0;
    DoCombination3(A,S,n,i+1);
    
    A[i] = 1;
    DoCombination3(A,S,n,i+1);
}


int CombinationRecursively(char str[])
{
    int n = (int)strlen(str);
    int * result = new int[n];
    
    if(!result)
		return -1;
	
    DoCombination3(result,str,n,0);
	
    delete [] result;
    
    return 0;
}


// 4. Non-Recursvie solution
//
void increment(int A[], int n)
{
    if (A[n-1] == 0)
    {
        A[n-1] = 1;
        return;
    }
    
    int i = n-2;
    while (A[i])
        --i;
    
    A[i] = 1;
    for (int j = i+1; j < n; ++j)
        A[j] = 0;
}

int CombinationNonRecursively(char str[])
{
    int n = (int) strlen(str);
    int *result = new int [n];
    
    if (!result)
        return -1;
    
    for (int i = 0; i < n; ++i)
        result[i] = 0;
    
    
    for (int i = 0; i < pow(2.0, n); ++i)
    {
        printCombination(result, str, n);
        increment(result,n);
    }

    delete [] result;
    
    return 0;
}


// 5. We can use the bit shift operation
//
int CombinationByBitShift(char str[])
{
    int n = (int) strlen(str);
    int *result = new int [n];
    
    if (!result)
        return -1;
    
    for (int i = 0; i < n; ++i)
        result[i] = 0;
    
    
    for (int i = 0; i < pow(2.0, n); ++i)
    {
        int k = i;
        int index = n-1;
        for(int j = 0; j < n; ++j)
        {
            result[index--] =  (k & 1);
            k >>= 1;
        }
        printCombination(result, str, n);
    }
    
    delete [] result;
    
    return 0;
}


int main(int argc, const char * argv[])
{
    char str[] = "abc";
    //CombinationRecursively(str);
    //CombinationNonRecursively(str);
    CombinationByBitShift(str);
    //Combine(str);
    return 0;
}

