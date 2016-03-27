//
//  SnakeSequence.cpp
//  
//  Modified by 罗铮 on 03/18/14.
//  Program to print SnakeSequence

#include <vector>
#include <iostream>

using namespace std;

int a[3][5] = { { 1,  3, 2,  1,  0 }, 
                { -9, 7, 1, -1, -1 }, 
                { 1,  5, 0,  1, -2 } };


void snakeseq(int rows,int columns,int x,int y,
              vector<int> &vec, vector<int> &snapshot)
{
    vec.push_back(a[x][y]);
    
    if (vec.size() > snapshot.size())
        snapshot = vec;

    if(x < rows && y < columns) {
        if( (a[x][y] == a[x][y+1]+1)  ||  
            (a[x][y] == a[x][y+1]-1))
            snakeseq(rows,columns,x,y+1,vec,snapshot);

        if( (a[x][y] == a[x+1][y]+1)  || 
            (a[x][y] == a[x+1][y]-1))
            snakeseq(rows,columns,x+1,y,vec,snapshot);
    }
    
    vec.pop_back();
}

int main () 
{
    int rows = 3, columns = 5, max = 0;
    vector<int> vec,snapshot,result;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            snakeseq(rows,columns,i,j,vec,snapshot);
            if ((int)snapshot.size() > max)
                result = snapshot;
        }
    }

    for (size_t i = 0; i < result.size(); ++i)
        cout << result[i] << " ";
    cout << endl;

    return 0;
}