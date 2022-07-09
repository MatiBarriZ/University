#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <cstddef>
#include <iostream>

using namespace std;

class Node{
public:
	long long info;
	Node* left;
	Node* right;
	Node* parent;
	Node(Node* parent, long long data);
	~Node();
private:
	
};

class BinarySearchTree{
public:

	BinarySearchTree();
	~BinarySearchTree();

	void insertion(long long data); 
	Node* searching(long long data);	
	void deletion(long long data);
	void showing(long long counter);

private:
	Node* root;

	void __INSERT(Node*& node, long long data, Node*& parent);
	Node* __SEARCH(Node* node, long long data);

	void __DELETE(Node* node, long long data);
	void __DELETE_NODE(Node* node);
	Node* __SEARCH_MIN(Node* node);
	void __REMPLACE(Node* node, Node* replacement_node);
	void __DESTROY_NODE(Node* node);

	void __SHOW_TREE(Node* node, int count);
};

#endif