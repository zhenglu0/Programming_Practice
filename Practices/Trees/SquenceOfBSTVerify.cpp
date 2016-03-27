//
//  VerifySquenceOfBST.cpp
//  
//  Created by 罗铮 on 10/27/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////
// Verify whether a squence of integers are the post order traversal
// of a binary search tree (BST)
// Input: squence - the squence of integers
//        length  - the length of squence
// Return: return ture if the squence is traversal result of a BST,
//         otherwise, return false
///////////////////////////////////////////////////////////////////////
bool verifySquenceOfBST(int squence[], int length)
{
    if(squence == NULL || length <= 0)
        return false;
    
    // root of a BST is at the end of post order traversal squence
    int root = squence[length - 1];
    
    // the nodes in left sub-tree are less than the root
    int i = 0;
    for(; i < length - 1; ++ i)
    {
        if(squence[i] > root)
            break;
    }
    
    // the nodes in the right sub-tree are greater than the root
    int j = i;
    for(; j < length - 1; ++ j)
    {
        if(squence[j] < root)
            return false;
    }
    
    // verify whether the left sub-tree is a BST
    bool left = true;
    if(i > 0)
        left = verifySquenceOfBST(squence, i);
    
    // verify whether the right sub-tree is a BST
    bool right = true;
    if(i < length - 1)
        right = verifySquenceOfBST(squence + i, length - i - 1);
    
    return (left && right);
}

int main(int argc, const char * argv[])
{
    
    int a[7] = {5,7,6,9,11,10,8};
    int b[4] = {7,4,6,5};
    cout << verifySquenceOfBST(a, 7) << endl;
    cout << verifySquenceOfBST(b, 4) << endl;
    
    return 0;
}