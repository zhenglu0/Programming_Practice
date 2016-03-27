//
//  TreeTraversal.cpp
//  
//  Created  by 罗铮 on 10/30/12.
//  Modified by 罗铮 on 04/01/14.
//  Copyright (c) 2012-2014 罗铮. All rights reserved.

#include "TreeCommon.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 1. DFS recursive traversal
void PreoderTraversal_recursive(node *root)
{
    if(!root)
        return;
    
    cout << root->value << " ";
    PreoderTraversal_recursive(root->left);
    PreoderTraversal_recursive(root->right);
}

void InoderTraversal_recursive(node *root)
{
    if(!root)
        return;
    
    InoderTraversal_recursive(root->left);
    cout << root->value << " ";
    InoderTraversal_recursive(root->right);
}

void PostoderTraversal_recursive(node *root)
{
    if(!root)
        return;
    
    PostoderTraversal_recursive(root->left);
    PostoderTraversal_recursive(root->right);
    cout << root->value << " ";
}

// 2. DFS non-recursive traversal
void PreoderTraversal_nonrecursive(node *root)
{
        vector<node*> nodeStack;
        nodeStack.push_back(root);
        node * currentNode;
		while (!nodeStack.empty())
		{
            currentNode = nodeStack.back();
			nodeStack.pop_back();

			if (currentNode->right)
				nodeStack.push_back(currentNode->right);
            
            if (currentNode->left)
				nodeStack.push_back(currentNode->left);
            
			cout << currentNode->value << " ";
        }
}

void InoderTraversal_nonrecursive(node* root)
{
	vector<node*> nodeStack;
	node *currentNode = root;
	while (true)
	{
		if (currentNode)
		{
            nodeStack.push_back(currentNode);
            currentNode = currentNode->left;
            continue;
		}

		if (nodeStack.empty())
			return;
		
		currentNode = nodeStack.back();
		nodeStack.pop_back();
		cout << currentNode->value << " ";
		currentNode = currentNode->right;
    }
}

void PostoderTraversal_nonrecursive_one_stack(node* root)
{
	if (!root)
		return;
	
	vector<node*> nodeStack;
	node* cur = root;
	while (true)
	{
		if (cur)
		{
			if (cur->right)
			{
				nodeStack.push_back(cur->right);
			}
			nodeStack.push_back(cur);
			cur = cur->left;
			continue;
		}

		if (nodeStack.empty())
			return;

		cur = nodeStack.back();
		nodeStack.pop_back();

		if (cur->right && !nodeStack.empty() && 
			cur->right == nodeStack.back())
		{
			nodeStack.pop_back();
			nodeStack.push_back(cur);
			cur = cur->right;
		}
		else
		{
			cout << cur->value << " ";
			cur = 0;
		}
	}
}

void PostoderTraversal_nonrecursive_two_stack(node *root)
{
    if (!root)
		return;
	
    vector<node *> child;
    vector<node *> parent;
    //Initialization
    child.push_back(root);
    while (!child.empty())
	{
        node *curr = child.back();
        parent.push_back(curr);
        child.pop_back();

        if (curr->left)
			child.push_back(curr->left);

        if (curr->right)
		    child.push_back(curr->right);

    }
    //Printing the post order traversal
    while (!parent.empty())
	{
        cout << parent.back()->value << " ";
        parent.pop_back();
    }
}

// 3. BFS level order search
void LevelOrderTraversal(node *root)
{
	queue<node*> q;
	q.push(root);
	while(!q.empty())
	{
		node *currentNode = q.front();
		q.pop();
		cout << currentNode->value << " ";

		if (currentNode->left)
			q.push(currentNode->left);

		if(currentNode->right)
			q.push(currentNode->right);
	}
}

int main(int argc, char* argv[])
{
    node *root;
    node **p_root = &root;
    create_binary_search_tree(p_root);
	cout << endl;

	// 1. DFS recursive traversal
    // pre-order
    cout << "Pre-order recursive traversal: ";
    PreoderTraversal_recursive(root);
    // in-order
    cout << endl << endl;
    cout << "In-order recursive traversal: ";
    InoderTraversal_recursive(root);
    // post-order
    cout << endl << endl;
    cout << "post-order recursive traversal: ";
    PostoderTraversal_recursive(root);

	// 2. DFS non-recursive traversal
    // pre-order
	cout << endl << endl;
    cout << "Pre-order non-recursive traversal: ";
	PreoderTraversal_nonrecursive(root);
    // in-order
	cout << endl << endl;
    cout << "In-order non-recursive traversal: ";
	InoderTraversal_nonrecursive(root);
	cout << endl << endl;
    cout << "Post-order non-recursive traversal using two stack: ";
	PostoderTraversal_nonrecursive_two_stack(root);
	cout << endl;
    cout << "Post-order non-recursive traversal using one stack: ";
	PostoderTraversal_nonrecursive_one_stack(root);
    
	// 3. BFS level order search
	cout << endl;
    cout << "Level order traversal: ";
	LevelOrderTraversal(root);
    return 0;
}


