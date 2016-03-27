/******************************************************************************/
/* 
 *  isAnagram.cpp
 *  IsAnagram
 *
 *  Created by 罗铮 on 11/25/12.
 *  Copyright (c) 2012 罗铮. All rights reserved.
 *
 * Determines if two C-strings (null-terminated character arrays) are anagrams
 * of each other.  Returns 1 if they are, and 0 if they are not.
 *
 * The function creates an array to store tallies of the characters contained in
 * each string.  It then runs through each, tallying the occurences of all
 * characters (all alphabetical characters are converted to lower-case as they
 * are tallied, so that case is inconsequential).  It then compares the counts
 * of all of the alphabetical characters only (excluding all others, such as
 * numerical characters, whitespace, punctuation, etc.).  If the counts for all
 * of these characters are equal between the two strings, then the strings are
 * anagrams of each other.
 *
 *
 * Dependencies: requires "string.h" for strlen() and "ctype.h" for the tolower().
 *
 *
 * Example call:
 *
 * char* str1="internet anagram server";
 * char* str2="I, rearrangement servant";
 *
 * if ( isAnagram(str1, str2) ) cout << "Yes, they are anagrams of each other."
 * ----
 * Yes, they are anagrams of each other.
 */

#include <cstring>
#include <cctype>
#include <cstdio>
#include <cstdlib>

// #1 By Hashing
int isAnagramByHashing(const char* str1, const char* str2)
{
    
    //  initialize two arrays to hold character counts
    int count1[256] = {0};
    int count2[256] = {0};
    
    //  run through each string and tally every character according to its
    //  ASCII value
    for (int i = 0; i < (int)strlen(str1); ++i)
        count1[tolower(str1[i])]++;

    for (int i = 0; i < (int)strlen(str2); ++i)
        count2[tolower(str2[i])]++;

    
    //  run the arrays and check if the value of the elements corresponding to
    //  lower-case characters are equal
    int countIsEqual = 1;
    for (int i = 97; i < 122; ++i)
        if (count1[i] != count2[i]) {
            countIsEqual=0;
            break;
        }
    
    //  return 1 if the strings are anagrams, 0 if not
    if (!countIsEqual)
        return 0;
    else
        return 1;
}

int compare(const void *a, const void *b)
{
    return *(char*)a - *(char*)b;
}

// #2 By Sorting
int isAnagramBySorting(const char* a, const char* b)
{
    
    if (strlen(a) != strlen(b))
        return 0;
    
    // delcare char pointers, maybe we should check 
    // whether memory allocation is successful
    char *str1 = (char*)malloc(strlen(a) + 1);
    char *str2 = (char*)malloc(strlen(b) + 1);
    
    // copy the content of a and b
    strcpy(str1, a);
    strcpy(str2, b);
    
    // sort the string
    qsort(str1,strlen(str1),sizeof(char),compare);
    qsort(str2,strlen(str2),sizeof(char),compare);
    
    int isAnagram = 1;
    
    for (int i = 0; i < (int)strlen(str1); ++i) {
        if (str1[i] != str2[i]) {
            isAnagram = 0;
            break;
        }
    }
    
    // free memory
    free(str1);
    free(str2);
    
    return isAnagram;
}


int main(int argc, const char * argv[])
{
    char str1[] = "iceman";
    char str2[] = "cinema";
    
    // 1. Hasing method, time complexity O(n), 
    // extra space required
    if (isAnagramByHashing(str1, str2))
        printf("Two words are anagrams \n");
    else
        printf("Two words are NOT anagrams \n");
    
    // 2. Sorting Method, time complexity O(nlogn)
    if (isAnagramBySorting(str1, str2))
        printf("Two words are anagrams \n");
    else
        printf("Two words are NOT anagrams \n");
    
    return 0;
}

