// 160101048_OA6_4.cpp: Nitin Kedia
// Description: Implement a binomial heap with CLI interface 

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node {
	int key, degree;
	node *lchild, *sibling;
};

node *create_node(int key) {
	node *head = new node;
	head->degree = 0;
	head->lchild = NULL;
	head->sibling = NULL;
	return head;
}

// makes x the parent of y
void binomial_link(node *x, node *y) {
	y->sibling = x->lchild;
	x->lchild = y;
	(x->degree)++;
}
void binomial_merge(node *x, node *y, node **pHead) {
	if (x != NULL && y != NULL) {
		if (x->key < y->key) {
			*pHead = x;
			binomial_merge(x->sibling, y, &(*pHead->sibling));
		}
		else {
			*pHead = y;
			binomial_merge(x, y->sibling, &(*pHead->sibling));
		}
	}
	else {
		if (y != NULL) {
			*pHead = y;
			binomial_merge(x, y->sibling, &(*pHead->sibling));
		}
		else if (x != NULL) {
			*pHead = x;
			binomial_merge(x->sibling, y, &(*pHead->sibling));			
		}
		else *pHead = NULL;
	}
}
node *binomial_heap_union(node *x, node *y) {
	node *head = NULL;
	head = binomial_merge(x, y, &head);

	node *node1 = head;
	node *node0 = create_node(INT_MAX);
	node0->sibling = node1;
	while (node1 != NULL) {
		if (node1->sibling != NULL) {
			node *node2 = node1->sibling;
			if (node1->degree != node2->degree) {
				node0 = node1; 
				node1 = node2;
			}
			else {
				node *node3 = node2->sibling;
				if (node3 != NULL) {
					if (node2->degree == node3->degree) {
						node0 = node1;
						node1 = node2; 
					}
				}
				else {
					if (node1->key < node2->key) {
						binomial_ink(node1, node2);
						node1->sibling = node3;
					}
					else {
						binomial_link(node2, node1);
						node0->sibling = node2;
						node1 = node2;
					}
				}
			}
		}
	}
	return head;
}

node *binomial_heap_insert(node *head1, int x) {
	node *head2 = create_node(x);
	node *head = binomial_heap_union(head1, head2);
	return head;
}

node *reverse(node *head) {
	if (head != NULL) {
		node *temp1 = head->ptr;
		head->ptr = NULL;
		node *temp2;
		while (temp1 != NULL) {
			temp2 = temp1->ptr;
			temp1->ptr = head;
			head = temp1;
			temp1 = temp2;
		}
	}
	return head;
}
int binomial_heap_extractMin(node **pHead) {
	node *prev = NULL;
	node *next = *pHead;

	node *min = *pHead;
	while (next != NULL) {
		if (next->key < min->key) min = next;
		prev = next;
		next = next->sibling;
	}

	if (prev != NULL) prev->sibling = min->sibling;
	else *pHead = min->sibling;

	int min_key = min->key;
	node *head2 = min->lchild;
	// free min
	head2 = reverse(head2);
	*pHead = binomial_heap_union(*pHead, head1)
}

