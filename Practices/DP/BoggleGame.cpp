//
//  BoggleGame.cpp
//  
//  Modified by 罗铮 on 03/13/14.
//  http://exceptional-code.blogspot.com
//  2012/02/solving-boggle-game-recursion-previousfix.html

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 6; // max length of a word in the board

char in[N * N + 1]; // max length of a word
char board[N+1][N+2]; // keep room for a newline and null char at the end
char previous[N * N + 1];
bool dp[N * N + 1][N][N];

// direction X-Y delta pairs for adjacent cells
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};
bool visited[N][N];

bool checkBoard(char* word, int curIndex, int r, int c, int wordLen)
{
    if (curIndex == wordLen - 1)
    {
        //cout << "Returned TRUE!!" << endl;
        return true;
    }
    
    int ret = false;
        
    for (int i = 0; i < 8; ++i)
    {
        int newR = r + dx[i];
        int newC = c + dy[i];
        
        if (newR >= 0 && newR < N && newC >= 0 && newC < N && 
            !visited[newR][newC] && word[curIndex+1] == board[newR][newC])
        {
            ++curIndex;
            visited[newR][newC] = true;
            
            ret = checkBoard(word, curIndex, newR, newC, wordLen);
            if (ret)
                break;
                
            --curIndex;
            visited[newR][newC] = false;
        }
    }
    
    return ret;            
}

int main(int argc, char* argv[])
{
    
    int i, j, k, l;
    
    FILE* fDict = fopen("dict.txt","r");
    FILE* fBoard = fopen("tmp2.txt","r");
    
    for(i = 0; i < N; ++i)
        fgets(board[i], N+2, fBoard);
    
    strcpy(previous,"");
    int pLen = 0;
    
    while(fgets(in, N*N + 1, fDict))
    {
        int len = strlen(in);
        if (in[len-1] == '\n')
        {
            in[len-1] = '\0'; // remove the trailing newline
            --len;
        }
        
        if (len < 3)
            continue; // we only want words longer than 3 or more letter
            
        for(i = 0; i < len && i < pLen; ++i)
        {
            if(previous[i] != in[i])
                break;
        }
        // little optimization: building on previousious word
        //  (will benefit if the word list is sorted)
        int firstMismatch = i; 
        
        if(firstMismatch==0)
        {
            for(i = 0; i < 6; ++i)
            {
                for(j = 0; j < 6; ++j)
                {
                    if(board[i][j] == in[0])
                        dp[0][i][j] = true;
                    else
                        dp[0][i][j] = false;
                }
            }
            firstMismatch = 1;
        }
        
        for(k = firstMismatch; k < len; ++k)
        {
            for(i=0;i<6;++i)
            {
                for(j=0;j<6;++j)
                {    
                    dp[k][i][j] = false;
                            
                    if(board[i][j] != in[k])
                        continue;
                        
                    for(l= 0; l < 8 && !dp[k][i][j]; ++l)
                    {
                        int ti = i + dx[l];
                        int tj = j + dy[l];
                        
                        if(ti < 0 || ti >= 6 || tj < 0 || tj >= 6)
                            continue;
                        
                        if (dp[k-1][ti][tj])
                            dp[k][i][j] = true;
                    }
                }
            }   
        }
        
        // check if the word is tagged as found in the dp table
        bool flag = false;
        for(i = 0; i < 6 && !flag; ++i)
        {
            for(j = 0; j < 6 && !flag; ++j)
            {
                if(dp[len-1][i][j])
                    flag =true;
            }
        }
        
        // dp table says its there, but make sure its in the board and 
        // it does not repeat a location in the board
        if(flag)
        {
            //cout << "Checking word: " << in << endl;
            bool verified = false;
            
            for (i = 0; i < N && !verified; ++i)
            {
                for (j = 0; j < N && !verified; ++j)
                {
                    if (in[0] != board[i][j])
                        continue;
                        
                    memset(visited, false, sizeof(visited));
                    visited[i][j] = true;
                    
                    if (checkBoard(in, 0, i, j, len))
                    {
                        cout << in << endl;
                        break;
                    }
                }
            }
        }
        
        strcpy(previous,in);
        pLen=len;
            
    }
    
    return 0;
}
