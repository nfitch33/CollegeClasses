#include "binaryTree.h"

#include<iostream>
#include<stack>
#include<fstream>
#include<string>

using namespace std;

void inorder(Btree* root){
	if(root != NULL){
		inorder(root -> left);
		cout << root -> data << endl;
		inorder(root -> right);
	}
}

void add(Btree*& root, string item){
	if(root == NULL){
		root = new Btree;
		root -> data = item;
		root -> left = root -> right = NULL;
	}
	else if (item <= root -> data)
		add(root -> left, item);
	else
		add(root -> right, item);
}

int singleParentRecursive(Btree*& root){
    if(root == nullptr){
        return 0;
    }
    if(root->left == nullptr && root->right != nullptr){
        return 1 + singleParentRecursive(root->right);
    }
    else if(root->left != nullptr && root->right == nullptr){
        return 1 + singleParentRecursive(root->left);
    }
    else{
        return singleParentRecursive(root->left) + singleParentRecursive(root->right);
    }
}

int singleParentIterative(Btree*& root){
	stack<Btree*> stack;
	Btree* current = root;
	int count = 0;

	while(current != nullptr && stack.empty() == false){
		while(current != nullptr){
			stack.push(current);
			current = current -> left;
		}

		current = stack.top();

		stack.pop();

		if(current->left != nullptr && current->right == nullptr){
			count++;
		}
		else if(current->left == nullptr && current-> right != nullptr){
			count++;
		}

		current = current -> right;
	}
	return count;
}