#include <bits/stdc++.h>

using namespace std;

struct binTree {
	int key, degree;
	struct binTree *lchild, *sibling, *parent;
};

binTree *createNode(int key) {
	binTree *head = new binTree;
	head->degree = 0;
	head->lchild = NULL;
	head->sibling = NULL;
	head->parent = NULL;
}

void binomialLink (binTree *x, binTree *y) {
	y->parent = x;
	y->sibling = x->lchild;

	x->lchild = y;
	(x->degree)++;
}

void merge(binTree *head) {
	if (head != NULL) {
		if (head->sibling != NULL) {
			binTree *node2 = head->sibling;
			if (head->degree != node2->degree) merge(head->next);
			
			else if (node2->sibling != NULL) {
				binTree *node3 = node2->sibling;
				if (node2->degree != node3->degree) {
					if (head->key < node2->key) binomialLink(head, node2);
					else binomialLink(node2, head);
				}
				else merge(node2); 
			}
		}
	}
}

void insert(binTree **head, int x) {
	binTree *y = createNode(x);
	y->sibling = *head;
	*head = y;
	merge(*head);
}

int extractMin(binTree *head) {
	binTree *prev = NULL;
	binTree *next = head;

	binTree *min = head;
	while (next != NULL) {
		if (next->key < min->key) min = next;
		prev = next;
		next = next->sibling;
	}

	


}