//
//  ConvertToWords.cpp
//  
//  Created by 罗铮 on 12/11/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

/* Program to print a given number in words. The program handles
   numbers from 0 to 9999 */

#include <cstdio>
#include <cstring>
#include <cstdlib>

/* A function that prints given number in words */
void convert_to_words(const char *num)
{
    int len = strlen(num);  // Get number of digits in given number
    
    /* Base cases */
    if (len == 0) {
        fprintf(stderr, "empty string\n");
        return;
    }
    if (len > 4) {
        fprintf(stderr, "Length more than 4 is not supported\n");
        return;
    }
    
    /* The first string is not used, it is to make array indexing simple */
    const char *single_digits[] = { "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine"};
    
    /* The first string is not used, it is to make array indexing simple */
    const char *two_digits[] = {"", "ten", "eleven", "twelve", "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    
    /* The first two string are not used, they are to make array indexing simple*/
    const char *tens_multiple[] = {"", "", "twenty", "thirty", "forty", "fifty",
        "sixty", "seventy", "eighty", "ninety"};
    
    const char *tens_power[] = {"hundred", "thousand"};
    
    /* Used for debugging purpose only */
    printf("\n%s: ", num);
    
    /* For single digit number */
    if (len == 1) {
        printf("%s\n", single_digits[*num - '0']);
        return;
    }
    
    /* Iterate while num is not '\0' */
    while (*num != '\0') {
        
        /* Code path for first 2 digits */
        if (len >= 3) {
            if (*num -'0' != 0) {
                printf("%s ", single_digits[*num - '0']);
                printf("%s ", tens_power[len-3]); // here len can be 3 or 4
            }
            --len;
        }

        /* Code path for last 2 digits */
        else {
            /* Need to explicitly handle 10-19. Sum of the two digits is
             used as index of "two_digits" array of strings */
            if (*num == '1') {
                int sum = *num - '0' + *(num + 1)- '0';
                printf("%s\n", two_digits[sum]);
                return;
            }
            
            /* Need to explicitely handle 20 */
            else if (*num == '2' && *(num + 1) == '0') {
                printf("twenty\n");
                return;
            }
            
            /* Rest of the two digit numbers i.e., 21 to 99 */
            else {
                int i = *num - '0';
                printf("%s ", i? tens_multiple[i]: "");
                ++num;
                if (*num != '0')
                    printf("%s ", single_digits[*num - '0']);
            }
        }
        ++num;
    }
}

/* Driver program to test above function */
int main(int argc, const char * argv[])
{
    convert_to_words("9923");
    convert_to_words("523");
    convert_to_words("89");
    convert_to_words("8989");
    
    return 0;
}


