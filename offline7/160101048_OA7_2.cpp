// 160101048_OA7_2.cpp: Nitin Kedia
// Description: Implementation of Fibonacci Heap

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node {
	int degree, key;
	node *parent, *child, *next, *prev;
};

node *create_node(int key) {
	node *head = new node;
	head->key = key; head->degree = 0;
	head->parent = NULL;
	head->child = NULL;
	head->next = head; head->prev = head;
}
void show_heap_helper(node *head, int depth) {
	if (head != NULL) {
		node *temp = head;
		do {
			for (int i = 0; i <= depth; i++) cout << '\t';
			cout << '{' << temp->key << ',' << temp->degree << '}' << endl;
			if (temp->child != NULL) {
				show_heap_helper(temp->child, depth+1);
			}
			temp = temp->prev;
		} while (temp != head && temp != NULL);
	}
	return;
}

void show_fib_heap(node *head) {
	cout << "Stucture of fibonacci heap rotated 90 degrees anticlockwise:" << endl;
	if (head == NULL) cout << "Empty fibonacci heap." << endl;
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

		head1->next = head2_next;
		head2_next->prev = head1;

		head2->next = head1_next;
		head1_next->prev = head2;
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
	y->next->prev = y->prev;
	y->prev->next = y->next;

	y->next = y; y->prev = y;
	x->child = fib_heap_union(y, x->child);
	y->parent = x;
	x->degree += 1;
	return x;	
}

node *fib_heap_consolidate(node *head, int n) {
	int k = floor(log2(n));
	node *array[k+1] = {NULL};

	node *temp = head;
	do {
		node *x = temp;
		temp = temp->next;
		int d = x->degree;
		while (array[d] != NULL) {
			node *y = array[d];
			if (x->key > y->key) {
				node *swap = x;
				x = y;
				y = swap;
			}
			if (head == y) head = head->next;
			if (temp == y) temp = temp->next;
 			x = fib_heap_link(y, x);
			array[d++] = NULL;
		}
		array[d] = x;
	} while (temp != head);
	node *new_head = NULL;
	for (int i = 0; i <= k; i++) {
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
				temp = temp->next;
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
		if (*pHead != NULL)
			*pHead = fib_heap_consolidate(*pHead, *pn);
		return min_key;
	}
}
void free_fib_heap(node *head, node *stop) {
	if (head != NULL) {
		if (head->next != stop ) {
			free_fib_heap(head->next, stop);
		}
		if (head->child != NULL) {
			free_fib_heap(head->child, head->child);
		}
		// cout << "Deleted " << head->key << endl;
		delete head;		
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
			free_fib_heap(head, head);
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