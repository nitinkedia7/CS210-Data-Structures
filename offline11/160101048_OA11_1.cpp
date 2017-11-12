// 160101048_OA11_1.cpp: Nitin Kedia
// Description: Valid preorder permutations to obtain same BST
// Note: Count is printed at last

#include <iostream>
// #include <sstream> /* uncomment to store permuations and print count first */
using namespace std;

struct node { // BST node
	int key;
	bool mark; // will be used to find possible options at each stage
	node *parent, *left, *right;
};

node *create_node(int key) { // initialise node with given key
	node *temp = new node;
	temp->key = key;
	temp->mark = false;
	temp->parent = NULL;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void insert(node **pHead, int key) { // insert a key into a BST
	node *y = NULL;
	node *x = *pHead;
	while (x != NULL) { // find the parent of the new node to be made
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
	// make temp the child of y
	if (y == NULL) {
		*pHead = temp; // root adjustment-
		return;
	}
	if (y->key < key) {
		y->right = temp;
	}
	else y->left = temp;
}

/* In a valid permuation, all the ancestors of a node appear before the node itself */
// options finds the topmost non-marked nodes (to satisfy above condition) in the tree from left side to right side of the tree to obtain patterns lexicographically;
// Each option when placed after present node give rise to a unique permutation
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
	pres->mark = true; // mark present node because it is already in stack
	stack[++(*top)] = pres->key; // insert present node into permutation stack
		
	node *array[n]; // array contains the nodes which can come right after present node
	int l = 0;
	options(root, array, &l);

	if (l == 0) { // print permuation stack if no further options remain
		(*vp)++;
		for (int i = 0; i < n; i++) {
			cout << stack[i] << " ";
		}
		cout << endl;
		// stringstream ss;  /* uncomment to store permuations and print count first */
		// for (int i = 0; i < n; i++) {
		// 	ss << stack[i] << " ";
		// }
		// ss << "\n";
		// *permutations += ss.str();	
	}
	for (int i = 0; i < l; i++) { // explore all options i.e. putting each option right after present node and continuing recursively
		valid_permutation_helper(root, array[i], n, stack, top, permutations, vp);
	}
	pres->mark = false; // unmark present node so it can be part of next possibility
	(*top)--; // remove last element from stack
}

void valid_permutation(node *root, int n, string *permutations, int *vp) {
	int stack[n]; // stack for storing each permutation
	int top = -1;
	valid_permutation_helper(root, root, n, stack, &top, permutations, vp);
}

int main() {
	int n;
	cin >> n;
	node *head = NULL;
	int preorder[n];
	for (int i = 0; i < n; i++) { // make the BST from given preorder
		cin >> preorder[i];
		insert(&head, preorder[i]);
	}
	cout << endl;
	string permutations = "";
	int count = 0;
	valid_permutation(head, n, &permutations, &count); // print valid permuations lexicographically
	 
	cout << count << endl;
	// cout << permutations << endl;	
}