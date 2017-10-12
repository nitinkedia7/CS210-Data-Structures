// 160101048_OA7_2.cpp: Nitin Kedia
// Description: Implementation of Fibonacci Heap

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node {
	int degree, key;
	node *parent, *child, *next, *prev;
	// bool mark;
};

node *create_node(int key) {
	node *head = new node;
	head->key = key; head->degree = 0;
	head->parent = NULL;
	head->child = NULL;
	head->next = head; head->prev = head;
}

void show_heap_helper(node *head, int depth) {
	if (head->next != head) { 
		show_heap_helper(head->next, depth);
	}
	if (head->child != NULL) {
		for (int i = 0; i <= depth; i++) cout << '\t';
		cout << head->key;
		if (head->child == NULL) cout << endl;
	}
	else {
		cout << '\t';
		cout << head->key;
		cout << endl;
	}
	if (head->child != NULL) 
		show_heap_helper(head->child, depth + 1);
}
void show_fib_heap(node *head) {
	cout << "Stucture of fibonacci heap rotated 90 degrees anticlockwise:" << endl;
	if (head == NULL) cout << "Empty fibonnaci heap." << endl;
	else show_heap_helper(head, 0);
}

node *fib_heap_union(node *head1, node *head2) {
	node *head = NULL;
	// concat root list of head1 with head2
	if (head1 == NULL) head = head2;
	else if (head2 == NULL) head = head1;
	else {
		node *head1_next = head1->next;
		node *head2_next = head2->next;

		head1->next = head2->next;
		head2->next->prev = head1;

		head2->next = head1_next;
		head1->next->prev = head2;
		if (head1->key < head2->key) head = head1;
		else head = head2;
	}
	return head;
}

void fib_heap_insert(node **pHead, int *pn, int key) {
	node *head1 = *pHead;
	node *head2 = create_node(key);
	(*pn)++;
	*pHead = fib_heap_union(head1, head2);
}
// make x the parent of y
node *fib_heap_link(node *y, node *x) {
	y->prev->next = y->next;
	y->next->prev = y->prev;

	x->child = fib_heap_union(y, x->child);
	x->degree += 1;
	return x;	
}

node *fib_heap_consolidate(node *head, int n) {
	int k = log2(n);
	node *array[k] = {NULL};

	node *temp = head;
	do {
		node *x = temp;
		int d = x->degree;
		while (array[d] != NULL) {
			node *y = array[d];
			if (x->key < y->key) x = fib_heap_link(y, x);
			else x = fib_heap_link(x, y);
			array[d++] = NULL;
		}
		array[d] = x;
	} while (temp != head);
	node *new_head = NULL;
	for (int i = 0; i < k; i++) {
		if (array[i] != NULL) {
			array[i]->next = array[i];
			array[i]->prev = array[i];
			new_head = fib_heap_union(new_head, array[i]);
		}
	}
	return new_head;
}

int fib_heap_extract_min(node **pHead, int *pn) {
	node *head = *pHead;
	if (head != NULL) {
		int min_key = head->key;
		
		node *temp = head->child;
		node *child = temp;
		if (temp != NULL) {
			do {
				temp->parent = NULL;
				if (temp->key < child->key) child = temp;
			} while (temp != head->child);

		}

		if (head == head->next) head = NULL;
		else {
			head->prev->next = head->next;
			head->next->prev = head->prev;
			head = head->next;
			(*pn)--;
		}
		*pHead = fib_heap_union(head, child);

		*pHead = fib_heap_consolidate(*pHead, *pn);
		return min_key;
	}
}

int main() {
	char cmd; // command
	int arg;  // argument (if any)
	char flag = '-'; // to print after extracteMin or not, + ON, - OFF
	node *head = NULL;
	int n = 0;
	while (cin >> cmd) {
		if (cmd == '#') cin.ignore(10000, '\n'); // ignore comment line
		else if (cmd == 'c') { 
			// free_binomial_heap(head);
			head = NULL;
		}
		else if (cmd == 'i') {
			cin >> arg;
			fib_heap_insert(&head, &n, arg);
		}
		else if (cmd == 'u') {
			cout << "Only used internally like in insert, extractMin." << endl;
		} 
		else if (cmd == 'e') {
			if (head != NULL) {
				arg = fib_heap_extract_min(&head, &n);
				if (flag == '+') cout << "Minimum extracted: " << arg << endl;
			}
			else cout << "Cannot extractMin from empty heap." << endl;
 		}
		else if (cmd == '+') {
			flag = '+';
			cout << "Print after extractMin: ON" << endl;
		}
		else if (cmd == '-') {
			flag = '-';
			cout << "Print after extractMin: OFF" << endl;

		}
		else if (cmd == 'S') {
			show_fib_heap(head);
		}
		else if (cmd == 'q') return 0; // q for quit
	}
}