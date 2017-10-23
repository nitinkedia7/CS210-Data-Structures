// 160101048_LT3_1.cpp: Nitin Kedia
// Description: Classify edges in directed graph using dfs stack

#include <bits/stdc++.h>
using namespace std;

struct adj_node {
	char c;
	adj_node *ptr;
};

struct node {
	char c;
	char parent;
	int d, f, color;
	adj_node *link;
};

void push(adj_node **pHead, char c) {
	adj_node *temp = new adj_node;
	temp->c = c;
	temp->ptr = *pHead;
	*pHead = temp;
}

char pop(adj_node **pHead) {
	if (*pHead != NULL) {
		char c = (*pHead)->c;
		*pHead = (*pHead)->ptr;
		return c;
	}
}

void insert(adj_node **pHead, char c) {
	adj_node *temp = new adj_node;
	temp->c = c;
	temp->ptr = NULL;

	if (*pHead == NULL) {
		temp->ptr = NULL;
		*pHead = temp;
		return;
	}

	adj_node *next = *pHead;
	adj_node *prev = NULL;

	while (next != NULL) {
		if (next->c > c) break;
		prev = next;
		next = next->ptr;
	}
	if (next == NULL) {
		prev->ptr = temp;
	}
	else if (prev == NULL) {
		temp->ptr = *pHead;
		*pHead = temp;
		return;
	}
	else {
		temp->ptr = prev->ptr;
		prev->ptr = temp;
	}
}

void print(node *array, int n) {
	for (int i = 0; i < n; i++) {
		cout << array[i].c << " "
			 << array[i].parent << " "
			 << array[i].d << " "
			 << array[i].f << " " << endl;

		adj_node *head = array[i].link;
		while (head != NULL) {
			cout << head->c << " ";
			head = head->ptr; 
		}
		if (head == NULL) cout << "NULL" << endl;	
	}
}

void dfs(node *array, int n) {
	adj_node *stack = NULL;
	int time = 0;
	for (int i = 0; i < n; i++) {
		if (array[i].color == -1) {
			array[i].color = 0;
			array[i].d = ++time;
			char y = 'q'+i;
			push(&stack, y);
			// cout << i << " " << y << endl; 

			while (stack != NULL) {
				char u = stack->c;
				// cout << u-'q' << endl;
				
				adj_node *head = array[u-'q'].link;
				while (head != NULL) {
					char v = head->c;
					// cout << v-'q' << endl;
					if (array[v-'q'].color == -1) {
						array[v-'q'].color = 0;
						array[v-'q'].parent = u;
						array[v-'q'].d = ++time;
						printf("(%c,%c),", u, v);
						push(&stack, v);
						break;
					}
					head = head->ptr;
				}
				if (head == NULL) {
					char x = pop(&stack);
					array[x-'q'].color = 1;
					array[x-'q'].f = ++time;
				} 
			}
		}
	}
 }

void dfs_enhanced(node *array, int n) { // edge type 
	adj_node *type[4] = {NULL};
	for (int i = 0; i < n; i++) {
		array[i].c = 'q'+i;
		array[i].parent = 'a';
		array[i].d = INT_MAX;
		array[i].f = INT_MAX;
		array[i].color = -1;
	}
	// print(array, n);
	adj_node *stack = NULL;
	int time = 0;
	for (int i = 0; i < n; i++) {
		if (array[i].color == -1) {
			array[i].color = 0;
			array[i].d = ++time;
			char y = 'q'+i;
			push(&stack, y);

			while (stack != NULL) {
				char u = stack->c;
				
				adj_node *head = array[u-'q'].link;
				while (head != NULL) {
					char v = head->c;
					if (array[v-'q'].color == -1) {
						array[v-'q'].color = 0;
						array[v-'q'].parent = u;
						array[v-'q'].d = ++time;
						push(&(type[0]), v);
						push(&(type[0]), u);
						push(&stack, v);
						break;
					}
					else if (array[v-'q'].color == 0) {
						push(&(type[1]), v);
						push(&(type[1]), u);
					}
					else if (array[v-'q'].color == 1) {
						if (array[v-'q'].d >= array[u-'q'].d) {
							push(&(type[2]), v);
							push(&(type[2]), u);							
						}
						else {
							push(&(type[3]), v);
							push(&(type[3]), u);
						}
					}
					head = head->ptr;
				}
				if (head == NULL) {
					char x = pop(&stack);
					array[x-'q'].color = 1;
					array[x-'q'].f = ++time;
				} 
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		if (i == 0) cout << "Tree edges: ";
		if (i == 1) cout << "Back edges: ";
		if (i == 2) cout << "Forward edges: ";
		if (i == 3) cout << "Cross edges: ";
		adj_node *head = type[i];
		while (head != NULL) {
			char u = head->c;
			char v = head->ptr->c;
			printf("(%c,%c),", u, v);
			head = head->ptr->ptr;
		}
		cout << endl;
	}
}

void graph(node **ar, int *pn, int *pe) {
	int n, e;
	cin >> n >> e;
	*pn = n; *pe = e;

	node array[n];
	for (int i = 0; i < n; i++) {
		array[i].c = 'q'+i;
		array[i].parent = 'a';
		array[i].d = INT_MAX;
		array[i].f = INT_MAX;
		array[i].color = -1;
		array[i].link = NULL;
	}
	char c1, c2;
	for (int i = 0; i < e; i++) {
		cin >> c1 >> c2;
		insert(&(array[c1-'q'].link), c2);
	}
	// *ar = array;
	// print(array, n);
	cout << "For Part 1: " << endl;
	dfs(array, n);
	cout << endl << "For Part 2: " << endl;
	// print(array, n);
	dfs_enhanced(array, n);
	// print(array, n);
}

int main() {
	node *array = NULL;
	int n = 0, e = 0;
	graph(&array, &n, &e);
	// print(array, n);
	// dfs(array, n);
	// print(array, n);
	// dfs_enhanced(array, n);
	// print(array, n);
}