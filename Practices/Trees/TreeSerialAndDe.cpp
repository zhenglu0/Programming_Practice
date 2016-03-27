//
//  TreeSerialAndDe.cpp
//  
//  Modified by 罗铮 on 03/31/14.
//  http://leetcode.com/2010/09/serializationdeserialization-of-binary.html

#include "TreeCommon.h"
#include <iostream>
#include <fstream>      // std::ifstream
#include <string>
#include <sstream>

using namespace std;

// The pre-order traversal code below does all the job to 
// serialize a binary tree, believe it or not!
void writeBinaryTree(node *p, ostream &out) 
{
    if (!p) {
        out << "N ";
    } else {
        out << p->value << " ";
        writeBinaryTree(p->left, out);
        writeBinaryTree(p->right, out);
    }
}

//  Reading the binary tree from the file is similar. 
//  We read tokens one at a time using pre-order traversal. 
//  If the token is a sentinel, we ignore it. If the token is a number, 
//  we insert it to the current node, and traverse to its left child, 
//  then its right child.

void readBinaryTree(node *&p, stringstream &s) 
{
    string token;
    s >> token;
    int value = atoi(token.c_str());

    if (value != 0 && 
        !s.eof()) {
        //cout << "Token " << token << endl;
        p = new node(value);
        readBinaryTree(p->left, s);
        readBinaryTree(p->right, s);
    }
} 

// Driver program to test above functions
int main()
{
    /* Let us construct the tree shown in above diagram */
    node * root = NULL;
    create_binary_tree5(root);

    filebuf fb;
    fb.open ("test.txt",ios::out);
    ostream os(&fb);
    writeBinaryTree(root,os);
    fb.close();

    node *new_root = NULL;
    ifstream ifs ("test.txt", ifstream::in);
    stringstream ss;
    ss << ifs.rdbuf();    
    ifs.close();
    //cout << "SS is " << ss.str()<<endl;
    
    readBinaryTree(new_root,ss);
    fb.open ("test2.txt",ios::out);
    ostream os2(&fb);
    writeBinaryTree(new_root,os2);
    fb.close();

    return 0;
}