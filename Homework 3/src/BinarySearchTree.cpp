#include "../inc/BinarySearchTree.hpp"

/* Node Class Definition */

Node::Node(Node* parent, long long data){
    this->info = data; 
	left = NULL;
	right = NULL;
    this->parent = parent;
    }

Node::~Node(){
	delete left;
	delete right;
    }


/* Binary Search Tree Class Definition */

BinarySearchTree::BinarySearchTree(){
	root = NULL;
    }

BinarySearchTree::~BinarySearchTree(){
	delete root;
    }

/* Binary Search Tree Methods Definitions */

void BinarySearchTree::insertion(long long data){
	__INSERT(root, data, root);
    }

Node* BinarySearchTree::searching(long long data){
	return __SEARCH(root, data);
    }

void BinarySearchTree::deletion(long long data){
    return __DELETE(root, data);
    }

void BinarySearchTree::showing(long long counter){
    return __SHOW_TREE(root, counter);
    }

/* Binary Search Tree Private Methods Definitions */

void BinarySearchTree::__INSERT(Node*& node, long long data, Node*& parent){

	if(node == NULL){
		node = new Node(parent, data);
	}
    
    else{
        if(data < node->info){ 
            __INSERT(node->left, data, node);
        }
        else{ 
            __INSERT(node->right, data, node);
        }
    }	
}

Node* BinarySearchTree::__SEARCH(Node* node, long long data){

	if(node == NULL){
		return NULL;
	}

	else if(data < node->info){ 
		return __SEARCH(node->left, data);
	}
    else if(data > node->info){ 
        return __SEARCH(node->right, data);
    }	

    else{
        return node; 
    }
}

void BinarySearchTree::__DELETE(Node* node, long long data){
  
	if(node == NULL){	
        cout << "NOT EXIST DATA" << endl;
		return;
	}
	
	else if(data < node->info){ 
        //cout << "LEFT" << endl;
		__DELETE(node->left, data);
	}
    else if(data > node->info){
        //cout << "RIGHT" << endl;
        __DELETE(node->right, data);
    }	
    
    else{
        __DELETE_NODE(node);
    }
    cout << "THE DATA IS: " <<  node->info << endl;
}

void BinarySearchTree::__DELETE_NODE(Node* node){
    
    if(node->left && node->right){
        Node* temp = __SEARCH_MIN(node->right); 
        node->info = temp->info;
        __DELETE_NODE(temp); 
    }
    
    else if(node->left){
        __REMPLACE(node,node->left);
        __DESTROY_NODE(node);
    }
    
    else if(node->right){
        __REMPLACE(node,node->right);
        __DESTROY_NODE(node);
    }
    
    else{
        __REMPLACE(node, NULL);
        __DESTROY_NODE(node);
    }
}

Node* BinarySearchTree::__SEARCH_MIN(Node* node){
  
	if(node == NULL){	
        cout << "NOT EXIST DATA" << endl;
		return NULL;
	}

    if (node->left == NULL){
        return node;
    }
    // Se busca la parte mas izquierda posible
    else{
        return __SEARCH_MIN(node->left);
    }
}

void BinarySearchTree::__REMPLACE(Node* node, Node* remplacement_node){
    
    if(node->parent){
      
        if(node->info == node->parent->left->info){
            node->parent->left = remplacement_node;
        }
      
        else if(node->info == node->parent->right->info){
            node->parent->right = remplacement_node;
        }
    }

    if(remplacement_node){
        remplacement_node->parent= node->parent;
    }
}

void BinarySearchTree::__DESTROY_NODE(Node* node){
    
    node->left = NULL;
    node->right = NULL;

    delete node;
}

void BinarySearchTree::__SHOW_TREE(Node* node, int count){

	if(node == NULL){
		return;
	}

	else{
		__SHOW_TREE(node->right, count+1);
        for(int i = 0; i < count; i++){
            cout << "   ";
        }
        cout << node->info << endl;
        __SHOW_TREE(node->left, count+1);
	}
}
