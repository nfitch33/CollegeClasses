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

#ifndef BTREE
#define BTREE

#include<string>

struct Bnode{
	std::string data;
	Bnode* left;
	Bnode* right;
};

void inorder(Bnode* root);

void add(Bnode*& root, std::string item);

int size(Bnode* root);

int search(Bnode* root, const std::string& name);

int search_greater(Bnode* root, const std::string& name);

#endif