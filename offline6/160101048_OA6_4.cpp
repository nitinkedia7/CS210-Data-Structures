// 160101048_OA6_4.cpp: Nitin Kedia
// Description: Implement a binomial heap with CLI interface 

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// struct for each node of bimomial_heap
struct node {
	int key, degree;
	node *lchild, *sibling;
};
// initialise a pointer to node with given key
node *create_node(int key) {
	node *head = new node;
	head->key = key;
	head->degree = 0;
	head->lchild = NULL;
	head->sibling = NULL;
	return head;
}
// show_heap_helper prints the bimomial heap with format
void show_heap_helper(node *head, int depth) {
	if (head->sibling != NULL ) { // print last sibling first
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
		show_heap_helper(head->lchild, depth + 1); // print leftmost child last
}
// wrapper function for show_heap_helper
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
// binomial_merge merges two binomial root lists(already sorted) like merge in mergeSort recursively
void binomial_merge(node *x, node *y, node **pHead) {
	if (x != NULL && y != NULL) {
		if (x->degree <= y->degree) { // both are alive
			*pHead = x;
			binomial_merge(x->sibling, y, &((*pHead)->sibling));
		}
		else {
			*pHead = y;
			binomial_merge(x, y->sibling, &((*pHead)->sibling));
		}
	}
	else {
		if (y != NULL) { // one is dead
			*pHead = y;
			binomial_merge(x, y->sibling, &((*pHead)->sibling));
		}
		else if (x != NULL) {
			*pHead = x;
			binomial_merge(x->sibling, y, &((*pHead)->sibling));			
		}
		else *pHead = NULL; // both are dead
	}
}
// binomial_heap_union makes a binomial_heap from two parent binomial_heaps
node *binomial_heap_union(node *x, node *y) {
	node *head = NULL;
	binomial_merge(x, y, &head); // first merge the parents
	// iteratively consolidating the daughter root list to satisfy binomial heap condition
	// node0, node1, node2, node 3 (if exist) are collinear, node1 iterates through root list
	node *node1 = head;
	node *node0 = NULL;
	while (node1 != NULL) {
		node *node2 = node1->sibling;
		if (node2 != NULL) {
			node *node3 = node2->sibling;
			if (node1->degree != node2->degree) { // if consecutive degree doesn't match move forward
				node0 = node1; 
				node1 = node2;
			}
			else { 
				if (node3 != NULL) { // degree(node1) = degree(node2) = degree(node3) move forward
					if (node2->degree == node3->degree) {
						node0 = node1;
						node1 = node2; 
					}
					else {
						if (node1->key < node2->key) { // degree(node1) = degree(node2) != degree(node3), link node1 & node2 acc. to key
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
					if (node1->key < node2->key) { // degree(node1) = degree(node2) and node3 doesn't exist, link node1 and node2 acc. key 
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
// insert an element to binomial_heap
node *binomial_heap_insert(node *head1, int x) {
	node *head2 = create_node(x); // create a singleton binomial heap
	node *head = binomial_heap_union(head1, head2); // take union with main binomial heap 
	return head;
}
// reverse a singly linked list (childs of min_node in this case)
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
// return and delete minimum element from the heap
int binomial_heap_extractMin(node **pHead) {
	node *prev = NULL;
	node *next = *pHead;

	node *min = *pHead; // find min key in root list, detach it from the list
	node *min_prev = NULL;
	while (next != NULL) {
		if (next->key < min->key) {
			min = next;
			min_prev = prev;
		}
		prev = next;
		next = next->sibling;
	}

	if (min_prev != NULL) min_prev->sibling = min->sibling; // fix connections
	else *pHead = min->sibling;

	int min_key = min->key;
	node *head2 = reverse(min->lchild); // reverse childs of min_node so that they become a new binomial_heap
	delete min;
	*pHead = binomial_heap_union(*pHead, head2); // take union of siblings and root list
	return min_key;
}
// free_binomial_heap function recursively frees memory space previously allocated to now NULL pointers 
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
	char cmd; // command
	int arg;  // argument (if any)
	char flag = '-'; // to print after extracteMin or not, + ON, - OFF
	node *head = NULL;
	cout << "Enter input (press q to quit):" << endl;
	cout << "MAKE_BINOMIAL_HEAP: c" << endl;
	cout << "BINOMIAL_HEAP_INSERT: i" << endl;
	cout << "BINOMIAL_HEAP_EXTRACTMIN: d" << endl;
	cout << "PRINT_EXTRACTMIN: +(ON), -(OFF, default)" << endl;
	cout << "BINOMIAL_HEAP_UNION: u" << endl;
	cout << "PRINT_BINOMIAL_HEAP: S" << endl;
	while (cin >> cmd) {
		if (cmd == '#') cin.ignore(10000, '\n'); // ignore comment line
		else if (cmd == 'c') { // MAKE_BINOMIAL_HEAP: c
			free_binomial_heap(head);
			head = NULL;
		}
		else if (cmd == 'i') {  // BINOMIAL_HEAP_INSERT: i
			cin >> arg;
			head = binomial_heap_insert(head, arg);
		}
		else if (cmd == 'u') { // BINOMIAL_HEAP_UNION: u
			cout << "Only used internally like in insert, extractMin." << endl;
		} 
		else if (cmd == 'd') {	// BINOMIAL_HEAP_EXTRACTMIN: d
			if (head != NULL) {
				arg = binomial_heap_extractMin(&head);
				if (flag == '+') cout << "Minimum extracted: " << arg << endl;
			}
			else cout << "Cannot extractMin from empty heap." << endl;
 		}
		else if (cmd == '+') { // print flag ON
			flag = '+';
			cout << "Print after extractMin: ON" << endl;
		}
		else if (cmd == '-') { // print flag OFF
			flag = '-';
			cout << "Print after extractMin: OFF" << endl;

		}
		else if (cmd == 'S') { // PRINT_BINOMIAL_HEAP: S 
			show_binomial_heap(head);
		}
		else if (cmd == 'q') return 0; // q for quit
	}
}