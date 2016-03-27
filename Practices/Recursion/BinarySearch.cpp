//
//  BinarySearch.cpp
//
//  Created by 罗铮 on 11/19/12.
//  Modified by 罗铮 on 11/19/12
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <cstdio>
#include <cstdlib>

#define E_TARGET_NOT_IN_ARRAY -1
#define E_ARRAY_UNORDERD -2
#define E_LIMITS_REVERSED -3
#define E_OUT_OF_RANGE -4

int BinarySearch(int* array, int lower, int upper, int target)
{
    int center, range;
    range = upper - lower;

    if(range < 0)
        return E_LIMITS_REVERSED;
    else if(range == 0 && array[lower] != target)
        return E_TARGET_NOT_IN_ARRAY;
    if(array[lower] > array[upper])
        return E_ARRAY_UNORDERD;

    center = range/2 + lower;
    if(target == array[center])
        return center;

    else if(target < array[center])
        return BinarySearch(array,lower,center-1,target);
    else
        return BinarySearch(array,center+1,upper,target);
}

int BinarySearch_iterative(int* array, int lower, int upper, int target)
{
    int center, range;

    if(lower > upper)
        return E_LIMITS_REVERSED;

    while(1)
    {
        range = upper - lower;

        if(range == 0 && array[lower] != target)
            return E_TARGET_NOT_IN_ARRAY;
    
        if(array[lower] > array[upper])
            return E_ARRAY_UNORDERD;

        center = lower + range/2;

        if(target == array[center])
            return center;
        else if(target < array[center])
            upper = center - 1;
        else
            lower = center + 1;
    }
}

int main()
{
    int a[] = {0,1,2,3,4,5,6,7,8,9};
    int size = sizeof(a)/sizeof(*a);

    int b1 = BinarySearch(a,0,9,5);
    int b2 = BinarySearch_iterative(a,0,9,5);
    
    printf("size = %d \n",size);
    printf("b1 = %d \n",b1);
    printf("b2 = %d \n",b2);
    
    return 0;
}


