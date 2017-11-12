#include <iostream>
using namespace std;

struct node {
	int key, height;
	node *left, *right;
};

node *create_node(int key) {
	node *temp = new node;
	temp->key = key;
	temp->height = 1;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

int max(int x, int y) {
	if (x > y) return x;
	else return y;
}

int height(node *head) {
	if (head == NULL) return 0;
	return head->height;
}

node *right_rotate(node *head) {
	node *lchild = head->left;

	head->left = lchild->right;
	lchild->right = head;

	head->height = 1 + max(height(head->left), height(head->right));
	lchild->height = 1 + max(height(lchild->left), height(lchild->right));

	return lchild;
}

node *left_rotate(node *head) {
	node *rchild = head->right;

	head->right = rchild->left;
	rchild->left = head;

	head->height = 1 + max(height(head->left), height(head->right));
	rchild->height = 1 + max(height(rchild->left), height(rchild->right));

	return rchild;
}

node *insert(node *head, int key) {
	if (head == NULL) {
		return create_node(key);
	}

	if (key <= head->key) {
		head->left = insert(head->left, key);
	}
	else {
		head->right = insert(head->right, key);
	}

	head->height = 1 + max(height(head->left), height(head->right));

	int diff = height(head->left) - height(head->right);
	if (diff > 1) {
		if (key <= head->left->key) {			
			return right_rotate(head);
		}
		else {
			// double rotate
			head->left = left_rotate(head->left);
			return right_rotate(head);
		}
	}
	else if (diff < -1) {
		if (key > head->right->key) {
			return left_rotate(head);
		}
		else {
			// doudle rotate
			head->right = right_rotate(head->right);
			return left_rotate(head);
		}
	}
	return head;
}

void preorder(node *head) {
	if (head == NULL) return;
	else {
		cout << head->key << " ";
		preorder(head->left);
		preorder(head->right); 
	}
}

int main() {
	node *root = NULL;
	root = insert(root, 10);
	preorder(root);
	cout << endl;
	root = insert(root, 20);
	preorder(root);
		cout << endl;
	root = insert(root, 30);
	preorder(root);
		cout << endl;
	root = insert(root, 40);
	preorder(root);
		cout << endl;
	root = insert(root, 50);
	preorder(root);
		cout << endl;
	root = insert(root, 25);
	preorder(root);
		cout << endl;
}