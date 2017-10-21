// 160101048_OA8_1.cpp: Nitin Kedia
// Description: Print disjoint connected set of nodes in an undirected graph and cycles occuring in it.

#include <bits/stdc++.h>
using namespace std;

struct adj_node {
	int index;
	adj_node *ptr;
};

struct node {
	int color, parent;
	int component;
	adj_node *link;
};

void enqueue(adj_node **pHead, int index) {
	adj_node *temp = new adj_node;
	temp->index = index;
	temp->ptr = *pHead;

	*pHead = temp;
}

void print_path(node *array, int n, int i, int j) {
	if (i == j) {
		cout << j << " ";
		return;
	}
	print_path(array, n, i, array[j].parent);
	cout << j << " ";
}

void dfs_visit(node *array, int n, int i, adj_node **cycle_head) {
	array[i].color = 0;
	adj_node *head = array[i].link;
	while (head != NULL) {
		int k = head->index;
		if (array[k].color == -1) {
			array[k].parent = i;
			array[k].component = array[i].component;
			dfs_visit(array, n, k, cycle_head);
		}
		else if (array[i].parent != k) {
			if (array[k].color == 0) {
				enqueue(cycle_head, i);
				enqueue(cycle_head, k);
			}
		}
		head = head->ptr;
	}
	array[i].color = 1;
}

void dfs(node *array, int n, int *pcomponent, adj_node **cycle_head) {
	for (int i = 0; i <= n; i++) {
		if (array[i].color == -1) {
			array[i].component = ++(*pcomponent);
			dfs_visit(array, n, i, cycle_head);
		}
	}
}

void print_connected(node *array, int n, int component) {
	adj_node **ans = (adj_node**)calloc(component+1, sizeof(adj_node*));
	
	for (int i = 1; i <= n; i++) {
		enqueue(&(ans[array[i].component]), i);
	}
	for (int i = 1; i <= component; i++) {
		adj_node *head = ans[i];
		cout << "component" << i << ": ";
		while (head != NULL) {
			cout << head->index << " ";
			head = head->ptr;
		}
		cout << endl;
	}
}

void print_cycles(node *array, int n, adj_node *head) {
	if (head == NULL) {
		cout << "No cycle exists." << endl;
		return;
	} 
	int i = 0;
	while (head != NULL) {
		cout << "cycle" << ++i << ": "; 
		print_path(array, n, head->index, head->ptr->index);
		cout << head->index << endl;
		head = head->ptr->ptr;
	}
}

// void print(node *array, int n) {
// 	for (int i = 1; i <= n; i++) {
// 		cout << i << " " << array[i].parent << endl;
// 		adj_node *head = array[i].link;
// 		while (head != NULL) {
// 			cout << head->index << " ";
// 			head = head->ptr;
// 		}
// 		cout << "NULL" << endl << endl;
// 	}
// }

int main() {
	int n, e;
	cin >> n >> e;
	// cout << n << " " << e << endl;

	node array[n+1];
	for (int i = 1; i <= n; i++) {
		array[i].color = -1;
		array[i].parent = -1;
		array[i].link = NULL;
		array[i].component = 0;
	}
	int e1, e2;
	for (int i = 0; i < e; i++) {
		cin >> e1 >> e2;
		// scanf("%d, %d", &e1, &e2);
		enqueue(&(array[e1].link), e2);
		enqueue(&(array[e2].link), e1);
	}
		
	int component = 0;
	adj_node *cycle_head = NULL;
	dfs(array, n, &component, &cycle_head);
	// print(array, n);
	print_connected(array, n, component);
	print_cycles(array, n, cycle_head);
} 