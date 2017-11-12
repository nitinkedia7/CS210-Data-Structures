// 160101048_OA11_2.cpp: Nitin Kedia
// Description: Arrange sequence based on number of occurences first by finding frequency and then sort by frequency

#include <iostream>
using namespace std;

struct node { // struct for each distinct key and its freq
	int key, freq;
	node *left, *right;
};

node *create_node(int key, int freq) { // initialise a node with key and freq
	node *temp = new node;
	temp->key = key;
	temp->freq = freq;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
// first, we find frequency by inserting all keys into a BST, incrementing freq if match is found
void insert_by_key(node** pHead, int key, int freq) {
    node *head = *pHead;
    if (head == NULL) {
    	*pHead = create_node(key, freq); // make root
    	return;
    }
   	if (head->key == key) { // incoming key already present in tree, so increment freq
   		head->freq += freq;
   	}
    else if (key < head->key) { // else insert as a leaf node
        insert_by_key(&(head->left), key, freq);
    }
	else insert_by_key(&(head->right), key, freq);   
}
// Afterward by make BST2 according to frequency of each distict key found from BST1
void insert_by_freq(node** pHead, int key, int freq) {
    node *head = *pHead;
    if (head == NULL) {
    	*pHead = create_node(key, freq); // make root
    	return;
    }
    if (freq < head->freq) { // incoming freq is less
        insert_by_freq(&(head->left), key, freq);
    }
    else if (freq == head->freq && key > head->key) { // incoming freq is same but key is bigger
        insert_by_freq(&(head->left), key, freq);
    }
	else insert_by_freq(&(head->right), key, freq);
}

void inorder(node *head1, node **pHead2) { // inserting elements from BST1 to BST2 in inorder seq
	if (head1 == NULL) return;
	else {
		inorder(head1->left, pHead2);
		insert_by_freq(pHead2, head1->key, head1->freq);
		inorder(head1->right, pHead2);
	}
}

void print_rev_inorder(node *head) { // print BST2 in reverse inorder to sort in decreasing order of occurence
	if (head == NULL) return;
	else {
		print_rev_inorder(head->right);
		for (int i = 0; i < head->freq; i++) { // print each key freq times
			cout << head->key << " ";
		}
		print_rev_inorder(head->left);
	}
}

int main() {
	int n;
	cin >> n;

	int key;
	node *head1 = NULL;
	for (int i = 0; i < n; i++) { // build BST1
		cin >> key;
		insert_by_key(&head1, key, 1);	
	}

	node *head2 = NULL;
	inorder(head1, &head2); // build BST2
	print_rev_inorder(head2); // print BST2
	cout << endl;
}