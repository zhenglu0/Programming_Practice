//
//  FirstNonRepeated.cpp
//  
//  Created by 罗铮 on 11/18/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <map>           // red-black tree implementation
#include <unordered_map> // hash function implementation
#include <string>
#include <cstring>

using namespace std;

char firstNonRepeated1(string str)
{
    unordered_map<char,int> m;
    unordered_map<char,int>::iterator it;
    int length = (int)str.length();
    char c;

    for(int i = 0; i < length; ++i)
    {
        c = str[i];
        it = m.find(c);
        if(it != m.end())
            it->second = it->second+1;
        else
            //m.insert(pair<char,int>(c,1) );
            m[c] = 1;
    }
    for(int i = 0; i < length; ++i)
    {
        c = str[i];
        if(m.find(c)->second == 1)
            return c;
    }
    return '\0';
}

char firstNonRepeated2(string str)
{
    map<char,int> m;
    map<char,int>::iterator it;
    size_t length = str.length();
    char c;

    for(size_t i = 0; i < length; ++i)
    {
        c = str[i];
        it = m.find(c);
        if(it != m.end())
            it->second = it->second+1;
        else
            //m.insert(pair<char,int>(c,1) );
             m[c] = 1;
    }
    for(size_t i = 0; i < length; ++i)
    {
        c = str[i];
        if(m.find(c)->second == 1)
            return c;
    }
    return '\0';
}

char firstNonRepeated3(const char *str)
{
    int m[256] = {0};
    size_t l = strlen(str);

    // fill the map
    for (size_t i = 0; i < l; ++i)
        m[(size_t)str[i]] += 1;

    for (size_t i = 0; i < l; ++i)
        if (m[(size_t)str[i]] == 1)
            return str[i];

    return '\0';
}

int main(int argc, char * argv[])
{
    string s = "YY LLOOVVEE LUO";

    // #1 unordered_map
    char c1 = firstNonRepeated1(s);
    cout << "The first non repeated character by using unordered_map is " 
         << c1 << endl;

    // #2 map(ordered_map)
    char c2 = firstNonRepeated2(s);
    cout << "The first non repeated character by using map(ordered_map) is " 
         << c2 << endl;

    // #3 array
    const char *str = s.c_str();
    char c3 = firstNonRepeated3(str);
    cout << "The first non repeated character by using array is " 
         << c3 << endl;

    return 0;
}

