// 160101048_OA11_1.cpp: Nitin Kedia
// Description: Valid preorder permutations to obtain same BST

#include <iostream>
#include <sstream>
using namespace std;

struct node {
	int key;
	bool mark;
	node *parent, *left, *right;
};

node *create_node(int key) {
	node *temp = new node;
	temp->key = key;
	temp->mark = false;
	temp->parent = NULL;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void insert(node **pHead, int key) {
	node *y = NULL;
	node *x = *pHead;
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
	
	if (y == NULL) { 
		*pHead = temp;
		return;
	}
	if (y->key < key) {
		y->right = temp;
	}
	else y->left = temp;
}

void options(node *head, node **array, int *n) {
	if (head == NULL) return;
	else {
		if (!(head->mark)) {
			array[(*n)++] = head;
		}
		else {
			options(head->left, array, n);
			options(head->right, array, n);
		}
	}
}

void valid_permutation_helper(node *root, node *pres, int n, int *stack, int *top, string *permutations, int *vp) {
	stack[++(*top)] = pres->key;
		
	node *array[n];
	int l = 0;
	options(root, array, &l);

	if (l == 0) {
		(*vp)++;
		// for (int i = 0; i < n; i++) {
		// 	cout << stack[i] << " ";
		// }
		// cout << endl;
		stringstream ss;
		for (int i = 0; i < n; i++) {
			ss << stack[i] << " ";
		}
		ss << "\n";
		*permutations += ss.str();	
	}

	for (int i = 0; i < l; i++) {
		array[i]->mark = true;
		valid_permutation_helper(root, array[i], n, stack, top, permutations, vp);
	}
	pres->mark = false;
	(*top)--;
}

void valid_permutation(node *head, int n, string *permutations, int *vp) {
	head->mark = true;
	int stack[n];
	int top = -1;
	valid_permutation_helper(head, head, n, stack, &top, permutations, vp);
}

int main() {
	int n;
	cin >> n;
	node *head = NULL;
	int preorder[n];
	for (int i = 0; i < n; i++) {
		cin >> preorder[i];
		insert(&head, preorder[i]);
	}

	string permutations = "";
	int vp = 0;
	valid_permutation(head, n, &permutations, &vp);
	
	cout << vp << endl;
	cout << permutations << endl;	
}