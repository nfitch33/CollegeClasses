/*
	CS 2401 Binary Tree Lab

	This file contains a struct definition for a binary tree node that stores strings.
	The inorder traversal, add, and size functions are already done for you.

	The add function inserts nodes in such a way that it creates a binary search tree.
	This means that:
		* All nodes to the left of the current node are less than or equal to the current node
		* All nodes to the right of the current node are greater than the current node

	You need to fill in the main and functions required in the lab document.
*/

#include "btreelab.h"

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void inorder(Bnode* root){
	if(root != NULL){
		inorder(root -> left);
		cout << root -> data << endl;
		inorder(root -> right);
	}
}

void add(Bnode*& root, string item){
	if(root == NULL){
		root = new Bnode;
		root -> data = item;
		root -> left = root -> right = NULL;
	}
	else if (item <= root -> data)
		add(root -> left, item);
	else
		add(root -> right, item);
}

int size(Bnode* root){
	if(root == NULL)
		return 0;
	else
		return size(root -> left) + size(root -> right) + 1;
}

//Implement these

int search(Bnode* root, const string& name){
	int size = 0;
	if(root == nullptr) return size;
	if(root->data == name){
		size++;
	}
	size += search(root->left, name);
	size += search(root->right, name);
	return size;
}

int search_greater(Bnode* root, const string& name){
	int s = 0;
	if(root == nullptr) return 0;
	if(name < root->data){
		s += size(root->right);
		s += search_greater(root->left, name);
		s += 1;
	}
	else{
		s += search_greater(root->right, name);
	}
	return s;
}