// 160101048_LT4_1.cpp: Nitin Kedia
// Description: BST tree search, insert, delete

#include <iostream>
using namespace std;

struct node {
	int key;
	node *parent, *left, *right;
};

node *create_node(int key) { // initiailse a isolated node with given key
	node *temp = new node;
	temp->key = key;
	temp->parent = NULL;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

node *search(node *head, int key) {
	if (head == NULL) return NULL; // not found in this subtree 
	else {
		if (head->key == key) return head;
		else if (head->key < key) {
			return search(head->right, key);
		}
		else return search(head->left, key);
	}
}

node *find_min(node *head) { // returns pointer to min node else NULL
	node *min = NULL;
	while (head != NULL) {
		min = head;
		head = head->left; // leftmost node
	}
	return min;
}

node *successor(node *x) { // successor in inorder
	if (x == NULL) return NULL;
	if (x->right != NULL) { // if right subtree exists, return its min
		return find_min(x->right);
	}
	else { // else find youngest ancestor whose left child is also an ancestor of x
		node *y = x->parent;
		while (y->left != x && y != NULL) {
			x = y;
			y = x->parent;
		} // similar to changing subtree in inorder traversal
		return y;
	}
}

void insert(node **pHead, int key) {
	node *y = NULL;
	node *x = *pHead; // find proper place to satisfy BST property
	while (x != NULL) {
		y = x;
		if (x->key < key) {
			x = x->right;
		}
		else {
			x = x->left;
		}
	}
	node *temp = create_node(key);
	temp->parent = y;
	
	if (y == NULL) { // if tree was initially empty
		*pHead = temp;
		return;
	}
	if (y->key < key) {
		y->right = temp;
	}
	else y->left = temp;
}

bool delete_key(node **pHead, int key) {
	node *k = search(*pHead, key); // node to be deleted
	if (k == NULL) return false; // if not present, then cannot be deleted

	node *y = NULL, *x = NULL; 
	if (k->left == NULL || k->right == NULL) { // atmost one child exists, it will simply replace key
		y = k;
	}
	else y = successor(k); // else successor will replace

	if (y->left != NULL) x = y->left; // x is child of y which replaces y
	else x = y->right;

	if (x != NULL) x->parent = y->parent; // change parent
	if (y->parent == NULL) { // adjust root if it is deleted
		*pHead = x;
	}
	else if (y->parent->left == y) { // assign new child
		y->parent->left = x;
	}
	else y->parent->right = x;

	if (y != k) { // if y had both child swap y->key by successor->key
		k->key = y->key;
		delete y;
	}
	return true;
}

void print_inorder(node *head) { // left root right
	if (head == NULL) return;
	else {
		print_inorder(head->left);
		cout << head->key << " ";
		print_inorder(head->right);
	}
	return;
}

int main() {
	node *head = NULL;
	
	string cmd;
	int arg;
	while (1) {
		cin >> cmd;
		if (cmd == "-1") {
			cout << "Inorder: ";
			print_inorder(head);
			cout << endl;
			return 0;
		}
		else if (cmd == "PRINT") {
			cout << "Inorder: ";
			print_inorder(head);
			cout << endl;
			continue;			
		}
		cin >> arg;

		if (cmd == "SEARCH" || cmd == "SERACH") {
			node *temp = search(head, arg);
			if (temp == NULL) {
				cout << arg << " is not found" << endl;
			}
			else cout << arg << " is found" << endl;
		}
		else if (cmd == "INSERT") {
			insert(&head, arg);
			cout << arg << " is inserted" << endl;
		}
		else if (cmd == "DELETE") {
			if (delete_key(&head, arg)) {
				cout << arg << " is deleted" << endl;
			}
			else {
				cout << arg << " cannot be deleted" << endl;
			}
		}
	}
	return 1;
 }