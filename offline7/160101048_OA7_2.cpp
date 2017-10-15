// 160101048_OA7_2.cpp: Nitin Kedia
// Description: Implementation of Fibonacci Heap with CLI

#include <iostream>
#include <cmath>
using namespace std;

struct node { // struct for each node of fibonacci heap
	int degree, key;
	node *parent, *child, *next, *prev;
};

node *create_node(int key) { // initialise a pointer to node with given key
	node *head = new node;
	head->key = key; head->degree = 0;
	head->parent = NULL;
	head->child = NULL;
	head->next = head; head->prev = head;
	return head;
}

void show_heap_helper(node *head, int depth) { // show_heap_helper recursively prints the fibonacci heap in proper format
	if (head != NULL) {
		node *temp = head;
		do {
			for (int i = 0; i <= depth; i++) cout << '\t';
			cout << '{' << temp->key << ',' << temp->degree << '}'<< endl;
			if (temp->child != NULL) { // traverse child(s)
				show_heap_helper(temp->child, depth+1);
			}
			temp = temp->prev;
		} while (temp != head && temp != NULL); // traverse siblings
	}
	return;
}

void show_fib_heap(node *head) { // show_fib_heap complements and drives its helper function
	cout << "Stucture of fibonacci heap rotated 90 degrees anticlockwise:" << endl;
	if (head == NULL) cout << "Empty fibonacci heap." << endl;
	else show_heap_helper(head, 0);
}

node *fib_heap_union(node *head1, node *head2) { // concats two doubly linked lists and also adjusts the min pointer
	node *head = NULL;
	// concat root list of head1 with head2
	if (head1 == NULL) head = head2; // one of the lists is NULL
	else if (head2 == NULL) head = head1;
	else {							 // both lists are not NULL
		node *head1_next = head1->next;
		node *head2_next = head2->next;

		head1->next = head2_next;
		head2_next->prev = head1;

		head2->next = head1_next;
		head1_next->prev = head2;
		if (head1->key < head2->key) head = head1; // head must point to min
		else head = head2;
	}
	return head;
}

void fib_heap_insert(node **pHead, int *pn, int key) { // insert a new key into fibonacci heap 
	node *head1 = *pHead;
	node *head2 = create_node(key); // create a fib_heap with single node key and merge it to main heap
	(*pn)++;
	*pHead = fib_heap_union(head1, head2);
}

node *fib_heap_link(node *y, node *x) { // make x the parent of y
	y->next->prev = y->prev; // remove y from its doubly linked list
	y->prev->next = y->next;

	y->next = y; y->prev = y; // isolate y
	x->child = fib_heap_union(y, x->child); // merge y into child list of x
	y->parent = x;
	x->degree += 1;
	return x;	
}

node *fib_heap_consolidate(node *head, int n) { // transform root list such that no two nodes in it have the same degree 
	int k = floor(log2(n));
	node *array[k+1] = {NULL}; // auxillary array

	node *temp = head; // iterate over the root list
	do {
		node *x = temp; // merge x with other elements of same degree till it becomes a node of unique degree
		temp = temp->next;
		int d = x->degree;
		while (array[d] != NULL) {
			node *y = array[d];
			if (x->key > y->key) {
				node *swap = x;
				x = y;
				y = swap;
			}
			if (head == y) head = head->next; // consolidate distorts the root list, but head must always be in root list
			if (temp == y) temp = temp->next; // same for y
 			x = fib_heap_link(y, x);
			array[d++] = NULL;
		}
		array[d] = x;
	} while (temp != head);

	node *new_head = NULL; // make a new root list from elements of auxillary array
	for (int i = 0; i <= k; i++) {
		if (array[i] != NULL) {
			array[i]->next = array[i]; // isolate array[i]
			array[i]->prev = array[i];
			new_head = fib_heap_union(new_head, array[i]); // insert it into doubly linked list
		}
	}
	return new_head;
}

int fib_heap_extract_min(node **pHead, int *pn) { // return and delete the minimum key from fibonacci heap
	node *head = *pHead;
	if (head != NULL) {
		int min_key = head->key;
		
		node *temp = head->child;
		node *child = temp;
		if (temp != NULL) {
			do {
				temp->parent = NULL; // make parent = NULL for all child of head
				if (temp->key < child->key) child = temp;
				temp = temp->next;
			} while (temp != head->child);

		}

		if (head == head->next) { // if root has single element head then new head is just its child list
			*pHead = child;
		}
		else {
			head->prev->next = head->next; // remove head from root list
			head->next->prev = head->prev;

			*pHead = fib_heap_union(head->next, child); // concat new root list and child list of head and consolidate
			*pHead = fib_heap_consolidate(*pHead, *pn);
		}
		delete head; // free head
		(*pn)--;     // reduce heap size
		return min_key;
	}
}
void free_fib_heap(node *head, node *stop) { // recusively free all nodes of fib heap user defines new heap
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

node *make_fib_heap(node *head) {
	free_fib_heap(head, head);
	return NULL;
}

int main() {
	char cmd; // command
	int arg;  // argument (if any)
	char flag = '-'; // to print after extracteMin or not, + ON, - OFF
	node *head = NULL;
	int n = 0;
	while (cin >> cmd) {
		if (cmd == '#') cin.ignore(10000, '\n'); // ignore comment line
		else if (cmd == 'c') {  // MAKE-FIB-HEAP
			head = make_fib_heap(head);
		}
		else if (cmd == 'i') { // FIB-HEAP-INSERT
			cin >> arg;
			fib_heap_insert(&head, &n, arg);
		}
		else if (cmd == 'u') { // FIB-HEAP-UNION
			cout << "Only used internally like in insert, extractMin." << endl;
		} 
		else if (cmd == 'e') { // FIB-HEAP-EXTRACT-MIN
			if (head != NULL) {
				arg = fib_heap_extract_min(&head, &n);
				if (flag == '+') cout << "Minimum extracted: " << arg << endl;
			}
			else cout << "Cannot extract-min from empty heap." << endl;
 		}
		else if (cmd == '+') {
			flag = '+';
			cout << "Print after extractMin: ON" << endl;
		}
		else if (cmd == '-') {
			flag = '-';
			cout << "Print after extractMin: OFF" << endl;

		}
		else if (cmd == 'S') { // SHOW-FIB-HEAP
			show_fib_heap(head);
		}
		else if (cmd == 'q') return 0; // q for quit
	}
	return 0;
}