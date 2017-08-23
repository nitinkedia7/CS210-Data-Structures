// 160101048_3_1.cpp: Nitin Kedia
// Description: a program that merges k ordered sequences

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// node for each element of input sequence(s)
struct node {
	int data;
	node *next;
};
node *createNode(node *head, int input_num) {
	if (head == NULL) {
		node *temp = new node;
		temp->data = input_num;
		temp->next = NULL;
		head = temp;
	}
	else {
		node *temp = head;
		while (temp->next != NULL) temp = temp->next;
		temp->next = new node;
		temp->next->data = input_num;
		temp->next->next = NULL;
	}
	return head;
}
void printList(node *head) {
	while (head != NULL) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}
/* Construction of Winner Tree */
int searchOrigin(node *tree[], int n) {
	int i = 0;
	while (i < n-1) {
		if (tree[i] == tree[2*i+1]) i = 2*i+1;
		else i = 2*i+2;
	}
	return i;
}

node *match(node *contestant1, node *contestant2) {
	if (contestant1 == NULL && contestant2 == NULL) {
		return NULL;
	}
	else if (contestant1 == NULL && contestant2 != NULL) {
		return contestant2;
	}
	else if (contestant1 != NULL && contestant2 == NULL) {
		return contestant1;
	}	
	else {
		if (contestant1->data < contestant2->data) {
			return contestant1;	
		}
		else {
			return contestant2;
		}
	}
}

void afterRound1(node **tree, int i) {
	if (i > -1) {
		if (i%2 == 0) i = (i/2)-1;
		else i = (i/2);
		tree[i] = match(tree[2*i+1], tree[2*i+2]);
		afterRound1(tree, i);
	}
}

node *winnerTree(node **head, int n) {
	node *mergedHead = NULL;
	
	node *tree[2*n-1]; // playground
	for (int i = n-1; i<2*n-1; i++) {
		tree[i] = head[i-n+1];
	}
	for (int i = n-2; i > -1; i--) {
		tree[i] = match(tree[2*i+1], tree[2*i+2]);
	}
	
	while (tree[0] != NULL) {
		mergedHead = createNode(mergedHead, tree[0]->data);
		int i = searchOrigin(tree, n);
		tree[i] = tree[i]->next;
		afterRound1(tree, i);
	}
	return mergedHead;
}

int main() {
	int k;
	cout << "Enter number of sequences: ";
	cin >> k;
	int n;
	for (n=0; ; n++) {
		if (pow(2, n) >= k) {
			n = pow(2, n);
			break;
		}
	}
	node *head[n];
	for (int i = 0; i < k; i++) {
		head[i] = NULL;
		int num; char c;
		do {
			scanf("%d%c", &num, &c);
			head[i] = createNode(head[i], num);
		} while(c != '\n');
	}
	for (int i = k; i < n; i++) {
		head[i] = NULL;
	}
	for (int i = 0; i < n; i++) {
		printList(head[i]);
	}
	node *mergedHead = winnerTree(head, n);
	printList(mergedHead);
	return 0;
}
