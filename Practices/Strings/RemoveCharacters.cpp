//
//  RemoveCharacters.cpp
//  
//  Created by 罗铮 on 11/18/12.
//  Modified by 罗铮 on 03/29/14.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <cstring>

using namespace std;

void RemoveChars(char str[], char remove[])
{
    int src, dst, removeArray[256];

    // 1. zero all element in the array
    for(int i = 0; i < 256; ++i)
    {
        removeArray[i] = 0;
    }

    // 2. set true for chars to be removed
    src = 0;
    while(remove[src])
    {
        removeArray[(size_t)remove[src]] = 1;
        src++;
    }
    // 3. Copy char unless it must be removed
    src = dst = 0;
    /*
    do
    {
        if(!removeArray[str[src]])
        {
            str[dst++] = str[src];
        }
    } while(str[src++]);
    */

    while(1)
    {
        if(!removeArray[(size_t)str[src]])
        {
            str[dst] = str[src];
            ++dst;
        }
        if(!str[src])
        {
            break;
        }
        ++src;
    }
}

void RemoveChars1(char str[], char remove[])
{
    int src, dst, removeArray[256];
    
    // 1. zero all element in the array
    for(int i = 0; i < 256; ++i)
    {
        removeArray[i] = 0;
    }
    
    // 2. set true for chars to be removed
    src = 0;
    while(remove[src])
    {
        removeArray[(size_t)remove[src]] = 1;
        src++;
    }
    // 3. Copy char unless it must be removed
    src = dst = 0;
    do
    {
        if(!removeArray[(size_t)str[src]])
            str[dst++] = str[src];
        
    } while(str[src++]);
    
    /*
    while(true)
    {
        if(!removeArray[str[src]])
        {
            str[dst] = str[src];
            ++dst;
        }
        if(!str[src])
        {
            break;
        }
        ++src;
    }*/
}

void RemoveChars2(char str[], char remove[])
{
    int r[256] = {0};
    size_t src = 0, dst = 0;
    
    for (size_t i = 0; i < strlen(remove); ++i)
        r[(size_t)remove[i]] = 1;
    
    while (dst <= strlen(str))
    {
        // if str[dst] is in the table, we skip it
        if (r[(size_t)str[dst]])
            ++dst;
        // if it is not in the table, we copy the dst to source
        else
            str[src++] = str[dst++];
    }
}


int main(int argc, char * argv[])
{
    char c[] = "YyYy loyvye LyLy.";
    char r[] = "y";

    //RemoveChars(c,r);
    //cout << c;

    cout << "Before remove : " << c << endl;
    //RemoveChars1(c,r);
    RemoveChars2(c,r);
    cout << "After remove: " << c << endl;
    
    return 0;
}



