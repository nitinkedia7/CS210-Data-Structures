// 160101048_OA11_1.cpp: Nitin Kedia
// Description: Valid preorder permutations to obtain same BST

#include <iostream>
using namespace std;

struct node {
	char key;
	bool mark;
	node *parent, *left, *right;
};

node *create_node(char key) {
	node *temp = new node;
	temp->key = key;
	temp->mark = false;
	temp->parent = NULL;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void insert(node **pHead, char key) {
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

void valid_permutation_helper(node *head, node *pres, int n, string *ans, string *all) {
	*ans += pres->key;
		
	node *array[n];
	int l = 0;
	options(head, array, &l);

	if (l == 0) *all += *ans;

	for (int i = 0; i < l; i++) {
		array[i]->mark = true;
		valid_permutation_helper(head, array[i], n, ans, all);
	}
	pres->mark = false;
	*ans = (*ans).substr(0, (*ans).length()-1);
}

void valid_permutation(node *head, int n, string *ans, string *all) {
	head->mark = true;
	valid_permutation_helper(head, head, n, ans, all);
}

int main() {
	int n;
	cin >> n;
	node *head = NULL;
	int preorder[n];
	for (int i = 0; i < n; i++) {
		cin >> preorder[i];
		insert(&head, preorder[i]+'0');
	}

	string ans = "", all = "";
	valid_permutation(head, n, &ans, &all);
	
	cout << all.length()/n << endl;
	int i = 0;
	while (i < all.length()) {
		cout << all[i] << " ";
		if (i % n == n-1) cout << endl;
		i++;
	}
}