//
//  HashingAChar.cpp
//  
//  Created by 罗铮 on 11/14/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <cstdio>

void countNumberOfChar(int A[], const char *c)
{
    if(A[(size_t)*c] == 0)
        A[(size_t)*c] = 1;
    else
        ++A[(size_t)*c];
}

int main(int argc, char * argv[])
{
    const char *str = "YYYY love LL";
    int A[255] = {0};
    printf("%s \n",str);
    
    while(*str != '\0')
        countNumberOfChar(A,str++);
    
    printf("The number of Y is %d \n",A[(size_t)'Y']);
    printf("The number of l is %d \n",A[(size_t)'l']);
    printf("The number of o is %d \n",A[(size_t)'o']);
    printf("The number of v is %d \n",A[(size_t)'v']);
    printf("The number of e is %d \n",A[(size_t)'e']);
    printf("The number of L is %d \n",A[(size_t)'L']);
    printf("The number of M is %d \n",A[(size_t)'M']);
    
    return 0;
}



