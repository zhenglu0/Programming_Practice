//
//  Permutation.cpp
//  
//  Created by 罗铮 on 11/4/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

inline void swap_char(char *c1, char *c2)
{
    if(c1 != c2)
    {
        char temp = *c1;
        *c1 = *c2;
        *c2 = temp;
    }
}

/////////////////////////////////////////////////////////////////////////
// Print the permutation of a string,
// Input: pStr   - input string
//        pBegin - points to the begin char of string
//                 which we want to permutate in this recursion
/////////////////////////////////////////////////////////////////////////
void Permutation(char* pStr, char* pBegin)
{
    if(!pStr || !pBegin)
        return;

    // if pBegin points to the end of string,
    // this round of permutation is finished,
    // print the permuted string
    if(*pBegin == '\0')
    {
        cout << pStr << endl;
    }
    // otherwise, permute string
    else
    {
        for(char* pCh = pBegin; *pCh != '\0'; ++pCh)
        {
            // swap pCh and pBegin
            swap_char(pCh, pBegin);
            Permutation(pStr, pBegin + 1);
            // restore pCh and pBegin
            swap_char(pBegin,pCh);
        }
    }
}

/////////////////////////////////////////////////////////////////////////
// Get the permutation of a string,
// for example, input string abc, its permutation is
// abc acb bac bca cba cab
/////////////////////////////////////////////////////////////////////////
void Permutation(char* pStr)
{
    Permutation(pStr, pStr);
}

// Method 2
void DoPermute(char in[],char out[], int used[], int length, int recursLev)
{
    int i;
    if(recursLev == length){
        printf("%s\n",out);
        return;
    }
    for(i = 0; i < length; ++i){
        if(used[i])
            continue;

        out[recursLev] = in[i];
        used[i] = 1;
        DoPermute(in,out,used,length,recursLev + 1);
        used[i] = 0;
    }
}

int Permute(char inString[])
{
    int length, i, *used;
    char *out;
    length = strlen(inString);
    out = (char *) malloc(length + 1);
    if(!out){
        return -1;
    }
    out[length] = '\0';
    used = (int *) malloc(sizeof(int) * length);
    if(!used){
        return -1;
    }
    for(i = 0; i < length; ++i){
        used[i] = 0;
    }
    DoPermute(inString,out,used,length,0);
    free(out);
    free(used);
    return 0;
}

// Method 3
void DoPermute(char *inString, char *perString, 
               int len, int level)
{
    if(level == len) {
        perString[len+1] = '\0';
        printf("%s\n",perString);
        return;
    }
    int i;
    for(i = 0; i < len; i++){
        if(perString[i] == '0') {
            perString[i] = inString[level];
            level++;
            DoPermute(inString, perString, len, level);
            level--;
            perString[i] = '0';
        }
    }        
}

int Permute_Own(char *inString)
{
    int len;
    char *perString;
    len = strlen(inString);
    perString = (char *) malloc(len*sizeof(char) + 1);
    if(!perString)
        return -1;
    memset (perString,'0',len);
    DoPermute(inString, perString, len, 0);
    return 0;
}

// Method 4, by using the substr function
void permutation(string prefix, string str) 
{
    int n = str.length();
    if (n == 0) 
        cout << prefix << endl;
    else 
    {
        for (int i = 0; i < n; i++)
            permutation(prefix + str[i], 
                    str.substr(0, i) + str.substr(i+1, n-i-1));
    }
}

void permutation(string str) 
{ 
    permutation("", str); 
}

int main(int argc, const char * argv[])
{
    char str[4] = "abc";
    Permutation(str);
    
    char c[] = "ijk";
    Permute(c);

    string test = "123";
    cout << "STL Function: " << endl;
    sort( test.begin(), test.end() );
    cout << test << endl;
    while( next_permutation(test.begin(), test.end()) )
      cout << test << endl;
    
    cout << "My own Function: " << endl;
    permutation(test);

    return 0;
}

