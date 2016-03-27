//
//  StrStr.cpp
//  
//  Created by 罗铮 on 12/1/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <cstdio>
#include <cstring>

// 2.
// 在字符串中查找指定字符串的第一次出现，不能找到则返回NULL
char* strstr1(char *string, char *substring)
{
    if (string == NULL || substring == NULL)
        return NULL;
    
    int lenstr = (int)strlen(string);
    int lensub = (int)strlen(substring);
    
    if (lenstr < lensub)
        return NULL;
    
    int i,j;
    
    int len = lenstr - lensub;
    for (i = 0; i <= len; i++)   //复杂度为O(m*n)
    {
        for (j = 0; j < lensub; j++)
        {
            if (string[i+j] != substring[j])
                break;
        }
        if (j == lensub)
            return string + i;
    }
    return NULL;
}


// 3. StrStr without using the strlen
//
char *strstr2(char *src, char *sub)
{
    if (src == NULL || sub == NULL)
        return NULL;
    
    char *pSrc = src;
    char *pSub = sub;
    
    while (pSrc != '\0')
    {
        char* pSrcTemp = pSrc;
        
        while (*pSrc == *pSub)
        {
            if (*(pSub + 1) == '\0')
                return pSrcTemp;
            
            if (*(pSrc + 1) == '\0' && 
                *(pSub + 1) != '\0')
                return NULL;
            
            pSrc++;
            pSub++;
        }
        
        pSrc = pSrcTemp;
        pSub = sub;
        pSrc++;
    }
    
    return NULL;
}


// 4. StrStr without using the strlen
//
char *strstr3(char *T, char *P)
{
    int i,j;
    
    for (i = 0; T[i] != '\0'; i++)
    {
        for (j = 0; 
            T[i+j] != '\0' && P[j] != '\0' && T[i+j]==P[j]; 
            j++)
        {
            if (P[j + 1] == '\0')
                return T + i;
        }
    }
    
    return NULL;
}

int main(int argc, const char * argv[])
{
    // 1. test system strstr
    //
    char str[] = "This is a simple string\n";
    char *pch = strstr (str,"simple");
    strncpy (pch,"sample",6);
    puts (str);
    
    // 2. the strstr by using strlen
    //
    char str2[] = "This is a simple string\n";
    char* pch2 = strstr1 (str2,"simple");
    strncpy (pch2,"sample",6);
    puts (str2);
    
    // 3. the strstr by using strlen
    //
    char str3[] = "This is a simple string\n";
    char* pch3 = strstr2 (str3,"simple");
    strncpy (pch3,"sample",6);
    puts (str3);
    
    // 4. the strstr by using strlen
    //
    char str4[] = "This is a simple string\n";
    char* pch4 = strstr3 (str4,"simple");
    strncpy (pch4,"sample",6);
    puts (str4);
    
    return 0;
}