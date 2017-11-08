// 160101048_OA11_1.cpp: Nitin Kedia
// Description: Valid preorder permutations to obtain same BST

#include <iostream>
using namespace std;

struct node {
	char key;
	node *parent, *left, *right;
};

node *create_node(char key) {
	node *temp = new node;
	temp->key = key;
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

node *successor(node *x) {
	if (x == NULL) return NULL;
	if (x->left != NULL) {
		return x->left;
	}
	else if (x->right != NULL) {
		return x->right;
	}
	else {
		node *y = x->parent;
		while (y != NULL && y->left != x) {
			x = y;
			y = x->parent;
		}
		if (y == NULL) return NULL;
		else return y->right;
	}
}

node *predecessor(node *x) {
	if (x == NULL || x->parent == NULL) return NULL;
	else {
		node *y = x->parent;
		while (y != NULL) {
			x = y;
			y = y->left;
		}
		if (x->right != NULL) return x->right;
		else return x;
	}
}

string preorder(node *head, node *x) {
	string seq = "";
	while (head != x) {
		seq += head->key;
		head = successor(head);
	}
	return seq;
}

int nodes(node *head) {
	if (head == NULL) return 0;
	else {
		return 1 + nodes(successor(head));
	}
}

string modify_string(string prefix, string test, char key, int n) {
	string ans = "";
	int m = test.length();
	// cout << "m = " << m << endl;
	// cout << "n = " << n << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j += n) {
			ans += prefix;
			ans += test.substr(j,i);
			ans += key;
			ans += test.substr(j+i, n-i);
		}
	}
	// cout << test << endl;
	// cout << ans << endl;
	return ans;
}

void valid_permutation(node *root, node *head, string *ans) {
	if (head == NULL) return;
	else {
		*ans += head->key;	
		valid_permutation(root, successor(head), ans);

		if (successor(head) != NULL && predecessor(head) != NULL) {
			string ans1 = "";
			// *ans += preorder(root, head);
			valid_permutation(successor(head), successor(head), &ans1);
			int n = nodes(successor(head)); 
			// *ans += head->key;
			*ans += modify_string(preorder(root, head), ans1, head->key, n);
		}
	}
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

	string ans = "";
	valid_permutation(head, head, &ans);
	// cout << ans << endl;
	cout << ans.length()/n << endl;
	int i = 0;
	while (i < ans.length()) {
		cout << ans[i] << " ";
		if (i % n == n-1) cout << endl;
		i++;
	}
	cout << ans.length()/n << endl;
}
