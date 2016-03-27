//
//  Presort.cpp
//  
//  Created by 罗铮 on 11/18/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <map>           // red-black tree implementation
#include <unordered_map> // hash function implementation
#include <string>
#include <cstring>
#include <algorithm>     // std::sort

using namespace std;


bool element_unique_hash(string str)
{
    unordered_map<char,int> m;
    unordered_map<char,int>::iterator it;
    size_t length = str.length();
    char c;

    for(size_t i = 0; i < length; ++i)
    {
        c = str[i];
        it = m.find(c);
        if(it != m.end())
            it->second = it->second+1;
        else
            m.insert(pair<char,int>(c,1) );
    }
    for(size_t i = 0; i < length; ++i)
    {
        c = str[i];
        if(m.find(c)->second != 1)
            return false;
    }
    return true;
}

bool element_unique_hash2(string str)
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
            m.insert(pair<char,int>(c,1) );
    }
    for(size_t i = 0; i < length; ++i)
    {
        c = str[i];
        if(m.find(c)->second != 1)
            return false;
    }
    return true;
}


bool element_unique_hash3(const char *str)
{
    int m[256] = {0};
    size_t l = strlen(str);

    // fill the map
    for (size_t i = 0; i < l; ++i)
        m[(size_t)str[i]] += 1;

    for (size_t i = 0; i < l; ++i)
        if (m[(size_t)str[i]] != 1)
            return false;

    return true;
}

bool element_unique_sort(string str)
{
    // using default comparison (operator <):
    std::sort (str.begin(), str.end());  
    for (size_t i = 0; i < str.length()-1; ++i) {
        if (str[i] == str[i+1])
            return false;
    }         
    return true;

}

char mode_sort(string str)
{
    // using default comparison (operator <):
    std::sort (str.begin(), str.end());  
    size_t i = 0, mode_frequency = 0;
    char mode_value;
    while (i < str.length()) {
        size_t run_length = 1;
        char run_value = str[i];
        while(i + run_length < str.length() && 
              str[i+run_length] == run_value) {
            run_length++;
        }
        if (run_length > mode_frequency) {
            mode_frequency = run_length;
            mode_value = run_value;
        }
        i = i + run_length;
    }
    return mode_value;
}

char mode_hash(string str)
{
	unordered_map<char,size_t> m;
    unordered_map<char,size_t>::iterator it;
    size_t length = str.length();
    char c, mode_value = str[0];
    size_t mode_frequency = 0;

    for(size_t i = 0; i < length; ++i) {
        c = str[i];
        it = m.find(c);
        if(it != m.end()) {
            it->second = it->second+1;
            if (it->second > mode_frequency) {
                mode_frequency = it->second;
                mode_value = c;
            }
        } else {
            m.insert(pair<char,int>(c,1));
        }
    }
    return mode_value;
}

int main(int argc, char * argv[])
{
    string s = "Phoeb LikElUO";

    // #1 unordered_map
    //cout << "String uniqueness is " << boolalpha << 
    //        element_unique_hash(s) << endl;

    // #2 map(ordered_map)element_unique_hash2(s);
    cout << "String uniqueness is " << boolalpha << 
            element_unique_hash2(s) << endl;

    // #3 array
    const char *str = s.c_str();
    cout << "String uniqueness is " << boolalpha << 
            element_unique_hash3(str) << endl;

    // #4 sorting
    cout << "String uniqueness is " << boolalpha << 
            element_unique_sort(s) << endl;

    string m = "1:w011:w011:w011:w011:w011:w011:w011:w011:w011:w011:w01";
    // #1 sorting
    cout << "String mode is " <<  
            mode_sort(m) << endl;

    // #2 hasing
    cout << "String mode is " <<  
            mode_hash(m) << endl;

    return 0;
}

