//
//  RepaceSpace.cpp
//  
//  Created by 罗铮 on 03/22/14.
//  Copyright (c) 2014 罗铮. All rights reserved.

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void removeSpaces_STL(string str)
{
    size_t position = 0;
    for ( position = str.find(" "); position != string::npos; 
           position = str.find(" ",position) ) {
            str.replace(position ,1, "%20");
    }

    cout << str << endl;
}

char* removeSpaces_cstr(char str[])
{
    char *temp = new char [3 * strlen(str) + 1];
    int i = 0, j = 0;
    while (str[i] != '\0') {
        while (str[i] != ' ' && 
               str[i] != '\0') {
            temp[j] = str[i];
            i++;
            j++;
        }
        if (str[i] != '\0') {
            i++; 
            temp[j] = '%';
            temp[j+1] = '2';
            temp[j+2] = '0';
            j += 3;
        }
    }
    temp[j] = '\0';
    return temp;
}

int main()
{
    string inputString;
    cout << "Enter the string:" <<endl;
    getline(cin, inputString);
    
    char * cstr = new char [inputString.length()+1];
    strcpy (cstr, inputString.c_str());
    
    removeSpaces_STL(inputString);
    char *s = removeSpaces_cstr(cstr);
    cout << s << endl;

    delete [] s;
    return 0;
}
