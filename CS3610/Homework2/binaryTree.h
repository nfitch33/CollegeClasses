#ifndef binaryTree
#define binaryTree

#include<string>

struct Btree{
	std::string data;
	Btree* left;
	Btree* right;
};

void inorder(Btree* root);

void add(Btree*& root, std::string item);

int singleParentRecursive(Btree*& root, int counter);

#endif