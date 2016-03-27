//
//  ConvertBTtoDL.cpp
//
//  Modified by 罗铮 on 05/12/14.
//  Copyright (c) 2014 罗铮. All rights reserved.
//  http://zhedahht.blog.163.com/blog/static/254111742007127104759245/
/*
 　题目：输入一棵二元查找树，将该二元查找树转换成一个排序的双向链表。
   要求不能创建任何新的结点，只调整指针的指向。
 
 　　比如将二元查找树
     10
     / \
    6  14
    /\  /\
   4 8 12 16

 转换成双向链表
 
 4=6=8=10=12=14=16。
 
 分析：本题是微软的面试题。很多与树相关的题目都是用递归的思路来解决，本题也不例外。
 下面我们用两种不同的递归思路来分析。
 
思路一：当我们到达某一结点准备调整以该结点为根结点的子树时，
先调整其左子树将左子树转换成一个排好序的左子链表，再调整其右子树转换右子链表。
最近链接左子链表的最右结点（左子树的最大结点）、当前结点和右子链表的最左结点（右子树的最小结点）。
从树的根结点开始递归调整所有结点。
 
思路二：我们可以中序遍历整棵树。按照这个方式遍历树，比较小的结点先访问。如果我们每访问一个结点，
假设之前访问过的结点已经调整成一个排序双向链表，我们再把调整当前结点的指针将其链接到链表的末尾。
当所有结点都访问过之后，整棵树也就转换成一个排序双向链表了。
*/

#include <iostream>

using namespace std;

//首先我们定义二元查找树结点的数据结构如下：
struct Node // a node in the binary search tree
{
    int          value; // value of node
    Node  *left;  // left child of node
    Node  *right; // right child of node
};

/*
//思路一对应的代码：
///////////////////////////////////////////////////////////////////////
// Covert a sub binary-search-tree into a sorted double-linked list
// Input: pNode - the head of the sub tree
//        asRight - whether pNode is the right child of its parent
// Output: if asRight is true, return the least node in the sub-tree
//         else return the greatest node in the sub-tree
///////////////////////////////////////////////////////////////////////
Node* ConvertNode(Node* pNode, bool asRight)
{
    if(!pNode)
        return NULL;
    
    Node *pLeft = NULL;
    Node *pRight = NULL;
    
    // Convert the left sub-tree
    if(pNode->left)
        pLeft = ConvertNode(pNode->left, false);
    
    // Connect the greatest node in the left sub-tree to the current node
    if(pLeft)
    {
        pLeft->right = pNode;
        pNode->left = pLeft;
    }
    
    // Convert the right sub-tree
    if(pNode->right)
        pRight = ConvertNode(pNode->right, true);
    
    // Connect the least node in the right sub-tree to the current node
    if(pRight)
    {
        pNode->right = pRight;
        pRight->left = pNode;
    }
    
    Node *pTemp = pNode;
    
    // If the current node is the right child of its parent,
    // return the least node in the tree whose root is the current node
    if(asRight)
    {
        while(pTemp->left)
            pTemp = pTemp->left;
    }
    // If the current node is the left child of its parent,
    // return the greatest node in the tree whose root is the current node
    else
    {
        while(pTemp->right)
            pTemp = pTemp->right;
    }
    
    return pTemp;
}

///////////////////////////////////////////////////////////////////////
// Covert a binary search tree into a sorted double-linked list
// Input: the head of tree
// Output: the head of sorted double-linked list
///////////////////////////////////////////////////////////////////////
Node* Convert(Node* pHeadOfTree)
{
    // As we want to return the head of the sorted double-linked list,
    // we set the second parameter to be true
    return ConvertNode(pHeadOfTree, true);
}
*/


//思路二对应的代码：
///////////////////////////////////////////////////////////////////////
// Covert a sub binary-search-tree into a sorted double-linked list
// Input: pNode -           the head of the sub tree
//        pLastNodeInList - the tail of the double-linked list
///////////////////////////////////////////////////////////////////////
void ConvertNode(Node* pNode, Node*& pLastNodeInList)
{
    if(pNode == NULL)
        return;
    
    Node *pCurrent = pNode;
    
    // Convert the left sub-tree
    if (pCurrent->left != NULL)
        ConvertNode(pCurrent->left, pLastNodeInList);
    
    // Put the current node into the double-linked list
    pCurrent->left = pLastNodeInList;
    if(pLastNodeInList != NULL)
        pLastNodeInList->right = pCurrent;
    
    pLastNodeInList = pCurrent;
    
    // Convert the right sub-tree
    if (pCurrent->right != NULL)
        ConvertNode(pCurrent->right, pLastNodeInList);
}

///////////////////////////////////////////////////////////////////////
// Covert a binary search tree into a sorted double-linked list
// Input: pHeadOfTree - the head of tree
// Output: the head of sorted double-linked list
///////////////////////////////////////////////////////////////////////
Node* Convert_Solution(Node* pHeadOfTree)
{
    Node *pLastNodeInList = NULL;
    ConvertNode(pHeadOfTree, pLastNodeInList);
    
    // Get the head of the double-linked list
    Node *pHeadOfList = pLastNodeInList;
    while(pHeadOfList && pHeadOfList->left)
    {
        cout << pHeadOfList->value << " ";
        pHeadOfList = pHeadOfList->left;
    }
    cout << endl;
    return pHeadOfList;
}

int CreateBST(Node* &root)
{
    // first level node
    root = new Node();
    if(!root)
        return -1;
    root->value = 10;
    
    // second level node
    Node *child1 = new Node();
    if(!child1)
        return -1;
    child1->value = 6;
    Node *child2 = new Node();
    if(!child2)
        return -1;
    child2->value = 14;
    root->left = child1;
    root->right = child2;
    
    // third level node
    // left subtree
    Node *child1_1 = new Node();
    if(!child1_1)
        return -1;
    child1_1->value = 4;
    child1_1->left = 0;
    child1_1->right = 0;
    Node *child1_2 = new Node();
    if(!child1_2)
        return -1;
    child1_2->value = 8;
    child1_2->left = 0;
    child1_2->right = 0;
    child1->left = child1_1;
    child1->right = child1_2;
    // right subtree
    Node *child2_1 = new Node();
    if(!child2_1)
        return -1;
    child2_1->value = 12;
    child2_1->left = 0;
    child2_1->right = 0;
    Node *child2_2 = new Node();
    if(!child2_2)
        return -1;
    child2_2->value = 16;
    child2_2->left = 0;
    child2_2->right = 0;
    child2->left = child2_1;
    child2->right = child2_2;

	return 0;
}

int main(int argc, const char * argv[])
{
    Node* root = new Node();
    CreateBST(root);
    
    Node* head = Convert_Solution(root);
    
    while(head && head->right)
    {
        cout << head->value << " ";
        head = head->right;
    }
    cout << endl;

    return 0;
}

