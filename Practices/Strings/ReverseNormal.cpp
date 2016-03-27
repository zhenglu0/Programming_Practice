//
//  ReverseNormal.cpp
//  
//  Created by 罗铮 on 03/22/14.
//  Copyright (c) 2014 罗铮. All rights reserved.

#include <cstdio>
#include <cstdlib>

// ReverseWords without temporary buffer
//
void ReverseString(char str[], int start, int end)
{
    char temp;
    while(end > start)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        ++start;
        --end;
    }
}

bool isCharacter(char c) 
{
    if (( c > 64 && c < 91 ) ||
        ( c > 96 && c < 123 ))
        return true;
    else 
        return false;
}

void ReverseWords(char str[])
{
    int start = 0, end = 0, p = 0;
    
    // filter out these none characters first
    while (!isCharacter(str[p]))
        p++;
    start = p;

    while (str[p] != '\0') {
        // pass all the characters and reverse them
        while (isCharacter(str[p]))
            p++;
        end = p -1;
        ReverseString(str, start, end);
        // pass all none charachers    
        while (!isCharacter(str[p]) &&
               str[p] != '\0')
            p++;
        start = p;
    }
}


int main(int argc, char * argv[])
{
    // ReverseWords with temporary buffer
    char c[] = "*() Phoebe l*ve  LZ! Verym&ch  ...";
    printf("OriginalWords: %s \n",c);
    
    ReverseWords(c);
    printf("ReverseWords:  %s \n",c);
    
    return 0;
}



