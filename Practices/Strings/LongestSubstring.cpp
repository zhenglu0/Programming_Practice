//
//  LongestSubstringWithoutRepetition.cpp
//  
//  Created by 罗铮 on 12/11/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

void 
LongestSubstringWithoutRepetitionOfChars1(char str[])
{
    int len = (int) strlen(str);
    int i = 0, j = 0;
    int sublen = 0, index = 0, templen = 0;
    char temp[256];
    memset(temp, 0, sizeof(temp));
    
    while(i < len)
    {
        templen = 0;
        memset(temp, 0, sizeof(temp));
        j = i;
        while(j < len)
        {
            temp[(size_t)str[j]]++;
            if(temp[(size_t)str[j]] > 1)
                break;
            templen++;
            j++;
        }
        if(templen > sublen)
        {
            sublen = templen;
            index = i;
        }
        while(str[i] != str[j])
            i++;
        i++;
    }
    for(i = index; i < index + sublen; i++)
        printf("%c", str[i]);
}

void 
LongestSubstringWithoutRepetitionOfChars2(char str[])
{
    int length = (int) strlen(str);
    int i = 0, j = 0, index = 0, sublength = 0;
    int count[256] = {0};
    
    while (i < length)
    {
        while (j < length)
        {
            if (count[(size_t)str[j]] == 0)
            {
                count[(size_t)str[j]]++;
                j++;
            }    
            else
                break;
        }
        if (j - i > sublength)
        {
            sublength = j - i;
            index = i;
        }
        while (str[i] != str[j])
        {
            count[(size_t)str[i]]--;
            i++;
        }
        i++;
        j++;
    }
    for (int i = index; i < index + sublength; i++)
        cout << str[i];
}

int main(int argc, const char * argv[])
{
    //char str[] = "abcdefghaxyzpbn";
    char str[] = "caddbbabccccdexyz";
    printf("Program to find the longest unique "
           "substring in a string\n");
    //scanf("%[^\n]s", str);
    LongestSubstringWithoutRepetitionOfChars1(str);
    printf("\n");
    
    LongestSubstringWithoutRepetitionOfChars2(str);
    printf("\n");
    
    return 0;
}

