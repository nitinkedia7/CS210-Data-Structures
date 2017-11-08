// 160101048_OA11_2.cpp: Nitin Kedia
// Description: Arrange sequence based on number of occurences using two BST sorts

#include <iostream>
using namespace std;

struct node {
	int key, freq;
	node *left, *right;
};

node *create_node(int key, int freq) {
	node *temp = new node;
	temp->key = key;
	temp->freq = freq;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
void insert(node **pHead, int key, int freq) {
	node *y = NULL;
	node *x = *pHead; 
	while (x != NULL) {
		y = x;
		if (x->freq < freq) {
			x = x->right;
		}
		else if (x->freq == freq && x->key > key) {
			x = x->right;
		}
		else {
			x = x->left;
		}
	}
	node *temp = create_node(key, freq);

	if (y == NULL) {
		*pHead = temp;
		return;
	}
	if (y->freq < freq) {
		y->right = temp;
	}
	else if (y->freq == freq && y->key > key) {
		y->right = temp;
	}
	else y->left = temp;
}

void store_inorder(node *head, int *array, int *i) {
	if (head == NULL) return;
	else {
		store_inorder(head->left, array, i);
		for (int j = 0; j < head->freq; j++) {
			array[*i] = head->key;
			(*i)++;
		} 
		store_inorder(head->right, array, i);
	}
}

void bst_sort(int *array, int *sorted_array, int n) {
	node *head = NULL;
	int key = array[0];
	int freq = 1;
	for (int i = 1; i < n; i++) {
		if (array[i] == key) {
			freq++;
		}
		else {
			insert(&head, key, freq);
			key = array[i];
			freq = 1;
		}
	}
	insert(&head, key, freq);

	int i = 0;
	store_inorder(head, sorted_array, &i);
}

int main() {
	int n;
	cin >> n;

	int in_seq[n];
	for (int i = 0; i < n; i++) {
		cin >> in_seq[i];	
	}

	int inter_seq[n];
	bst_sort(in_seq, inter_seq, n);
	int out_seq[n];
	bst_sort(inter_seq, out_seq, n);

	for (int i = n-1; i >= 0; i--) {
		cout << out_seq[i] << " "; 
	}
	cout << endl;
	return 0;
}