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
	head->key = key;
	head->degree = 0;
	head->lchild = NULL;
	head->sibling = NULL;
	return head;
}

void show_heap_helper(node *head, int depth) {
	if (head->sibling != NULL ) {
		show_heap_helper(head->sibling, depth);
	}
	if (head->lchild != NULL) {
		for (int i = 0; i <= depth; i++) cout << '\t';
		cout << head->key;
		if (head->lchild == NULL) cout << endl;
	}
	else {
		cout << '\t';
		cout << head->key;
		cout << endl;
	}
	if (head->lchild != NULL) 
		show_heap_helper(head->lchild, depth + 1);
}
void show_binomial_heap(node *head) {
	cout << "Stucture of binomial heap rotated 90 degrees anticlockwise:" << endl;
	if (head == NULL) cout << "Empty binomial heap." << endl;
	else show_heap_helper(head, 0);
}

// makes x the parent of y
void binomial_link(node *x, node *y) {
	y->sibling = x->lchild;
	x->lchild = y;
	x->degree += 1;
}
void binomial_merge(node *x, node *y, node **pHead) {
	if (x != NULL && y != NULL) {
		if (x->degree <= y->degree) {
			*pHead = x;
			binomial_merge(x->sibling, y, &((*pHead)->sibling));
		}
		else {
			*pHead = y;
			binomial_merge(x, y->sibling, &((*pHead)->sibling));
		}
	}
	else {
		if (y != NULL) {
			*pHead = y;
			binomial_merge(x, y->sibling, &((*pHead)->sibling));
		}
		else if (x != NULL) {
			*pHead = x;
			binomial_merge(x->sibling, y, &((*pHead)->sibling));			
		}
		else *pHead = NULL;
	}
}
node *binomial_heap_union(node *x, node *y) {
	node *head = NULL;
	binomial_merge(x, y, &head);

	node *node1 = head;
	node *node0 = NULL;
	while (node1 != NULL) {
		node *node2 = node1->sibling;
		if (node2 != NULL) {
			node *node3 = node2->sibling;
			if (node1->degree != node2->degree) {
				node0 = node1; 
				node1 = node2;
			}
			else { 
				if (node3 != NULL) {
					if (node2->degree == node3->degree) {
						node0 = node1;
						node1 = node2; 
					}
					else {
						if (node1->key < node2->key) {
							binomial_link(node1, node2);
							node1->sibling = node3;
						}
						else {
							binomial_link(node2, node1);
							if (node0 == NULL) head = node2;
							else node0->sibling = node2;
							node1 = node2;
						}
					}
				}
				else {
					if (node1->key < node2->key) {
						binomial_link(node1, node2);
						node1->sibling = node3;
					}
					else {
						binomial_link(node2, node1);
						if (node0 == NULL) head = node2;
						else node0->sibling = node2;
						node1 = node2;
					}
				}
			}
		}
		else {
			node0 = node1;
			node1 = node2;
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
		node *temp1 = head->sibling;
		head->sibling = NULL;
		node *temp2;
		while (temp1 != NULL) {
			temp2 = temp1->sibling;
			temp1->sibling = head;
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
	node *min_prev = NULL;
	while (next != NULL) {
		if (next->key < min->key) {
			min = next;
			min_prev = prev;
		}
		prev = next;
		next = next->sibling;
	}

	if (min_prev != NULL) min_prev->sibling = min->sibling;
	else *pHead = min->sibling;

	int min_key = min->key;
	node *head2 = reverse(min->lchild);
	delete min;
	*pHead = binomial_heap_union(*pHead, head2);
	return min_key;
}

void free_binomial_heap(node *head) {
	if (head != NULL) {
		if (head->sibling != NULL ) {
			free_binomial_heap(head->sibling);
		}
		if (head->lchild != NULL) {
			free_binomial_heap(head->lchild);
		}
		// cout << "Deleted " << head->key << endl;
		delete head;		
	}
}

int main() {
	char cmd;
	int arg;
	char flag = '-';
	node *head = NULL;
	cout << "Enter input (press q to quit):" << endl;
	cout << "Print after ectractMin is initally OFF." << endl;
	while (1) {
		cin >> cmd;
		if (cmd == '#') cin.ignore(10000, '\n');
		else if (cmd == 'c') {
			free_binomial_heap(head);
			head = NULL;
		}
		else if (cmd == 'u') {}
		else if (cmd == 'i') {
			cin >> arg;
			head = binomial_heap_insert(head, arg);
		}
		else if (cmd == 'd') {
			if (head != NULL) {
				arg = binomial_heap_extractMin(&head);
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
			show_binomial_heap(head);
		}
		else if (cmd == 'q') return 0;
	}
}