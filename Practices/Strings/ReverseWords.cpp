//
//  ReverseWords.cpp
//  
//  Created by 罗铮 on 11/18/12.
//  Modified by by 罗铮 on 03/29/14.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// 1. ReverseWords with temporary buffer
//
int ReverseWords1(char str[])
{
    char *buffer;
    int tokenReadPos, wordReadPos, wordEnd, writePos = 0;
    tokenReadPos = (int)strlen(str) - 1;
    buffer = (char *) malloc(tokenReadPos + 2);
    if(!buffer)
        return 0; // ReverseWords failed
    
    while(tokenReadPos >= 0)
    {
        // non-word character
        if(str[tokenReadPos] == ' ')
            buffer[writePos++] = str[tokenReadPos--];
        // word character
        else
        {
            // store position of end of word
            wordEnd = tokenReadPos;
            // scan to next non-word character
            while(tokenReadPos >= 0 && str[tokenReadPos] != ' ')
                tokenReadPos--;
            // tokenReadPos went past the start of the word
            wordReadPos = tokenReadPos + 1;
        }
        // copy the characters of the word
        while(wordReadPos <= wordEnd)
            buffer[writePos++] = str[wordReadPos++];
    }
    // NUL terminate buffer and copy over str
    buffer[writePos] = '\0';
    strcpy(str,buffer);
    
    free(buffer);
    
    return 1; // revsering successful
}


// 2. ReverseWords without temporary buffer
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

void ReverseWords2(char str[])
{
    int start = 0, end = 0, length;
    length = (int)strlen(str);
    
    // reverse the entire string
    ReverseString(str,start,length-1);
    
    while(end < length)
    {
        if(str[end] != ' ')
        {
            start = end;
            while(end < length && str[end] != ' ')
                ++end;
            
            --end;
            // reverse the word
            ReverseString(str,start,end);
        }
        ++end;
    }
}


// 3. ReverseWords with using STL
//
void ReverseWords3(string &s)
{
    vector<string> v;
    string extract;
    istringstream iss(s);
    
    while(iss >> extract)
        v.push_back(extract);
    
    s = "";
    /*
    // 1. we can use a iterator to do that
    for(vector<string>::iterator it = v.end()-1; it != v.begin()-1; --it)
        s = s + *it + " ";
    */
    
    // 2. we can use the vector as a stack
    size_t n = v.size();
    for (size_t i = 0; i < n; ++i)
    {
        s = s + v.back() + " " ;
        v.pop_back();
    }
}

int reverse_words(string &s)
{
    vector<string> v;
    string extract;
    istringstream iss(s);
    while(iss>>extract)
    {
        v.push_back(extract);
    }
    s = "";
    for(vector<string>::iterator it = v.end()-1; 
        it != v.begin()-1; --it)
    {
        s = s+ *it + " ";
    }
    // delete the space in the end
    if (s != "" )
        s.erase(s.end()-1);
    return 0;
}

// 4. ReverseWords without temporary buffer
///////////////////////////////////////////////////////////////////////
// Reverse a string between two pointers
// Input: pBegin - the begin pointer in a string
//        pEnd   - the end pointer in a string
///////////////////////////////////////////////////////////////////////
void Reverse(char *pBegin, char *pEnd)
{
    if(pBegin == NULL || pEnd == NULL)
        return;
    
    while(pBegin < pEnd)
    {
        char temp = *pBegin;
        *pBegin = *pEnd;
        *pEnd = temp;
        
        pBegin++, pEnd--;
    }
}

///////////////////////////////////////////////////////////////////////
// Reverse the word order in a sentence, but maintain the character
// order inside a word
// Input: pData - the sentence to be reversed
///////////////////////////////////////////////////////////////////////
void ReverseSentence(char *pData)
{
    if(pData == NULL)
        return;
    
    char *pBegin = pData;
    char *pEnd = pData;
    
    while(*pEnd != '\0')
        pEnd ++;
    pEnd--;
    
    // Reverse the whole sentence
    Reverse(pBegin, pEnd);
    
    // Reverse every word in the sentence
    pBegin = pEnd = pData;
    
    while(*pBegin != '\0')
    {
        if(*pBegin == ' ')
        {
            pBegin++;
            pEnd++;
            continue;
        }
        // A word is between with pBegin and pEnd, reverse it
        else if(*pEnd == ' ' || *pEnd == '\0')
        {
            Reverse(pBegin, --pEnd);
            pBegin = ++pEnd;
        }
        // pEnd is pointed to the normal character
        else
            pEnd++;
    }
}


// Driver program to test above functions
int main(int argc, char * argv[])
{
    // 1. ReverseWords with temporary buffer
    char c1[] = "YY love LL";
    ReverseWords1(c1);
    printf("ReverseWords1: %s \n",c1);
    
    // 2. ReverseWords without temporary buffer
    char c2[] = "YY love LL";
    //int last_character = sizeof(c2)-2;
    //ReverseString(c2,0,last_character);
    ReverseWords2(c2);
    printf("ReverseWords2: %s \n",c2);
    
    // 3. ReverseWords with using STL
    string s = "YY love LL";
    ReverseWords3(s);
    cout << "ReverseWords3: " << s << endl;
    
    // 4. ReverseWords without temporary buffer
    char c4[] = "YY love LL";
    ReverseSentence(c4);
    printf("ReverseWords4: %s \n",c4);
    
    string str = "YY love LL";
    reverse_words(str);
    cout << "ReverseWords5: " << str 
         << endl;

    return 0;
}



