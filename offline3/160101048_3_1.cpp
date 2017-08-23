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

int main() {
	int k;
	cout << "Enter number of sequences: ";
	cin >> k;
	node *head[k];
	for (int i = 0; i < k; i++) {
		head[i] = NULL;
		int num; char c;
		do {
			scanf("%d%c", &num, &c);
			head[i] = createNode(head[i], num);
		} while(c != '\n');
	}
	for (int i = 0; i < k; i++) {
		printList(head[i]);
	}
	return 0;
}
