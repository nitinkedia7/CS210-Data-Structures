#include <iostream>
using namespace std;

struct node {
	int key, height;
	node *parent, *left, *right;
};

node *create_node(int key) {
	node *temp = new node;
	temp->key = key;
	temp->height = 1;
	temp->parent = NULL;
	temp->left = NULL;
	temp->right = NULL;
}

int max(int x, int y) {
	if (x > y) return x;
	else return y;
}

int height(node *head) {
	if (head == NULL) return 0;
	return head->height;
}

int get_balance(node *head) {
	if (head == NULL) return 0;
	return height(node->left) - height(node->right);
}

void right_rotate(node **pHead) {
	node *head = *pHead;
	node *lchild = head->left;
	head->left = lchild->right;
	lchild->right = head;

	head->height = 1 + max(height(head->left), height(head->right));
	lchild->height = 1 + max(height(lchild->left), height(lchild->right));

	*pHead = lchild;
}

void left_rotate(node **pHead) {
	node *head = *pHead;
	node *rchild = head->right;
	head->right = rchild->left;
	rchild->left = head;

	head->height = 1 + max(height(head->left), height(head->right));
	rchild->height = 1 + max(height(rchild->left), height(rchild->right));

	*pHead = rchild;
}

void insert(node **pHead, int key) {
	node *y = NULL;
	node *x = *pHead;
	while (x != NULL) {
		y = x;
		if (key <= x->key) x = x->left;
		else x = x->right;
	}
	node *temp = create_node(key);
	if (y == NULL) {
		*pHead = temp;
		return;
	}
	else {
		if (key <= y->key) y->left = temp;
		else y->right = temp;
	}
	temp->parent = y;

	while (y != NULL) {
		temp->height = 1 + max(height(temp->left), height(temp->right));
		int balance = get_balance(temp);
		if (balance > 1) {
			if (get_balance(temp->left) >= 0) {
				if (y->right == temp) right_rotate(&(y->right));
				else right_rotate(&(y->left));
			}
			else {
				left_rotate(&)
			}
		}
		else if (balance < -1) {
			if (get_balance(temp->right) <= 0) {
				if (y->right == temp) left_rotate(&(y->right));
				else left_rotate(&(y->left));
			}
			else 

			}

	}
		temp = y;
		y = y->parent;
}