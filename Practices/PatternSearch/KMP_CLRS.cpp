//
//  KMP_CLRS.cpp
//  
//  Created by 罗铮 on 12/2/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <cstring>

using namespace std;

int *ComputerPrefixFunction(char *P)
{
    int m = (int)strlen(P);
    int *Pi = new int[m];
    Pi[0] = -1;
    int k = -1;
    for (int q = 1; q < m; q++)
    {
        while (k >= 0 && P[k + 1] != P[q])
            k = Pi[k];
        
        if (P[k + 1] == P[q])
            k++;
        
        Pi[q] = k;
    }
    return Pi;
}

void KMP_Matcher(char *T, char *P)
{
    int n = (int)strlen(T);
    int m = (int)strlen(P);
    int * Pi = ComputerPrefixFunction(P);
    int q = -1;
    for (int i = 0; i < n; i++)
    {
        while(q >= 0 && P[q + 1] != T[i])
            q = Pi[q];
        
        if(P[q + 1] == T[i])
            q++;
        
        if(q == m - 1)
        {
            cout << "Pattern occurs with shift " << i - m;
            q = Pi[q];
        }
        
    }
}

int main(int argc, const char * argv[])
{
    //char T[] = "bacbababaabcbab";
    char T[] = "bacbababaabababacacbab";
    char P[] = "ababaca";

    KMP_Matcher(T, P);

    cout << endl;
    
    return 0;
}

