//
//  Factorial.cpp
//
//  Created by 罗铮 on 11/19/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <cstdio>
#include <cstdlib>

int factorial_recursive(int n)
{
    if(n > 1)
        return factorial_recursive(n-1) * n;
    else
        return 1;
}

int factorial_iterative(int i)
{
    int val = 1;
    for(int n = i; n > 1; --n)
        val *= n;

    return val;

}

void DoAllFactorials(int n, int *results)
{
    results[0] = 1;

    for (int i = 1; i <= n; ++i)
        results[i] = (i+1) * results[i-1];
}

int* AllFactorials(int n)
{
    int *results;
    int length = (n == 0) ? 1 : n;
    results = (int *)malloc(sizeof(int) * length);

    // remember always check whether the memory 
    // allocation is successful!!!
    if(!results)
        return NULL;

    DoAllFactorials(n,results);

    return results;
}

int main()
{
    int size = 5;
    //int num = factorial_recursive(size);
    int num = factorial_iterative(size);

    printf("%d\n",num);

    int *ptr = AllFactorials(size);
    //printf("%ld ",sizeof(ptr)/sizeof(int));

    if (ptr != NULL)
    {
        for(int i = 0; i < size; ++i)    
            printf("%d ",ptr[i]);
        printf("\n");
    }
    

    return 0;
}


