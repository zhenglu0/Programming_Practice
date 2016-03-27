//
//  PrintTelephoneWords.cpp
//
//  Created by 罗铮 on 12/3/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <cstdio>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define PHONE_NUMBER_LENGTH 3

char GetCharKey(int telephoneKey, int place)
{
    char keypad[8][3] =
    {
        {'A','B','C'},
        {'D','E','F'},
        {'G','H','I'},
        {'J','K','L'},
        {'M','N','O'},
        {'P','R','S'},
        {'T','U','V'},
        {'W','X','Y'}
    };

    if(telephoneKey >= 2 && telephoneKey <= 9 && place >= 1 && place <= 3)
        return keypad[telephoneKey -2][place-1];
    else if (telephoneKey == 1 || telephoneKey == 0)
    {
        char c = '0' + telephoneKey;
        return c;
    } else
        return '\0';
}

const char* getKeyChar(int num) {
    if (num == 2)
        return "ABC";
    else if (num == 3)
        return "DEF";
    else if (num == 4)
        return "GHI";
    else if (num == 5)
        return "JKL";
    else if (num == 6)
        return "MNO";
    else if (num == 7)
        return "PRS";
    else if (num == 8)
        return "TUV";
    else if (num == 9)
        return "WXY";
    else
        return "1";
}

// 1. The recursive solution for PrintTelephoneWords
//
void DoPrintTelephoneWords(int PhoneNum[], int curDigit, char result[])
{
    int i;
    if(curDigit == PHONE_NUMBER_LENGTH)
    {
        printf("%s\n",result);
        return;
    }
    for(i = 1; i <= 3; i++)
    {
        result[curDigit] = GetCharKey(PhoneNum[curDigit],i);
        DoPrintTelephoneWords(PhoneNum, curDigit + 1, result);
        if(PhoneNum[curDigit] == 0 || PhoneNum[curDigit] == 1)
            break;
    }
}

void PrintTelephoneWordsRecursively(int phoneNum[])
{
    char result[PHONE_NUMBER_LENGTH + 1];
    result[PHONE_NUMBER_LENGTH] = '\0';
    DoPrintTelephoneWords(phoneNum,0,result);
}


// 2. The iterative solution for PrintTelephoneWords
//
void PrintTelephoneWordsIteratively1(int PhoneNum[])
{
    char result[PHONE_NUMBER_LENGTH + 1];
    int i;
    for(i = 0; i < PHONE_NUMBER_LENGTH ; i++)
        result[i] = GetCharKey(PhoneNum[i],1);

    result[PHONE_NUMBER_LENGTH] = '\0';

    while(1)
    {
        printf("%s\n", result);

        for(i = PHONE_NUMBER_LENGTH - 1; i >= -1; i--)
        {
            if (i == -1)
                return;

            if(GetCharKey(PhoneNum[i],3) == result[i] ||
               PhoneNum[i] == 0 || PhoneNum[i] == 1)
            {
                result[i] = GetCharKey(PhoneNum[i],1);
            }
            else if (GetCharKey(PhoneNum[i],1) == result[i])
            {
                result[i] = GetCharKey(PhoneNum[i],2);
                break;
            }
            else if (GetCharKey(PhoneNum[i],2) == result[i])
            {
                result[i] = GetCharKey(PhoneNum[i],3);
                break;
            }
        }
    }
}


// 3. The iterative solution for PrintTelephoneWords
//
void PrintResult(int result[], int PhoneNum[])
{
    int i;
    for (i = 0; i < PHONE_NUMBER_LENGTH; i++)
    {
        if (result[i] != -1)
            printf("%c",GetCharKey(PhoneNum[i], result[i]));
        else
            printf("%c",GetCharKey(PhoneNum[i], 1));
    }
    printf("%c",'\n');
}

int IncreaseResult(int result[])
{
    int index = PHONE_NUMBER_LENGTH - 1;

    while (index >= 0 && result[index] == -1)
        index--;

    // 0 means false
    if (index == -1)
        return 0;

    int carry = 0;

    if (result[index] != 3)
        result[index]++;
    else
    {
        result[index--] = 1;
        carry = 1;
    }

    while (carry && index >= 0 && (result[index] == -1 || result[index] == 3))
    {
        if (result[index] == 3)
            result[index] = 1;
        index--;
    }

    // 0 means false, 1 means true
    if (carry && index == -1)
        return 0;
    else if (carry)
    {
        result[index]++;
        return 1;
    }
    return 1;
}

void PrintTelephoneWordsIteratively2(int PhoneNum[])
{
    int result[PHONE_NUMBER_LENGTH];
    // initialize the result array
    int i;
    for (i = 0; i < PHONE_NUMBER_LENGTH; i++)
    {
        if (PhoneNum[i] != 1 && PhoneNum[i] != 0)
            result[i] = 1;
        else
            result[i] = -1;
    }
    // print the fist result
    PrintResult(result, PhoneNum);
    // increment the result and print the array
    while (IncreaseResult(result))
        PrintResult(result, PhoneNum);
}

// 4. The recursive solution for PrintTelephoneWords in a different method
//
void doPrintTelephoneWords(int phoneNum[], int n, char permutations[]) {
    if (n == PHONE_NUMBER_LENGTH) {
        permutations[n] = '\0';
        printf("%s \n",permutations);
        return;
    }
    const char *characters = getKeyChar(phoneNum[n]);
    size_t length = strlen(characters), i;
    for (i = 0; i < length; i++) {
        permutations[n] = characters[i];
        doPrintTelephoneWords(phoneNum, n+1, permutations);
    }
}

void printTelephoneWords(int phoneNum[]) {
    char permutations[PHONE_NUMBER_LENGTH+1];
    doPrintTelephoneWords(phoneNum, 0, permutations);
}

int main(int argc, const char * argv[])
{
    int phoneNum[] = {3,1,5};

    // 1.
    printf("%s","The recursive solution \n");
    PrintTelephoneWordsRecursively(phoneNum);

    // 2.
    printf("%s","The iterative solution1 \n");
    PrintTelephoneWordsIteratively1(phoneNum);

    // 3.
    printf("%s","The iterative solution2 \n");
    PrintTelephoneWordsIteratively2(phoneNum);

    // 4.
    printf("%s","The recursive solution2 \n");
    printTelephoneWords(phoneNum);

    return 0;
}

