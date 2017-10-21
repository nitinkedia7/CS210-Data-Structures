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
	int d, f, printed;
	adj_node *link;
};

void enqueue(adj_node **pHead, int index) {
	adj_node *temp = new adj_node;
	temp->index = index;
	temp->ptr = *pHead;

	*pHead = temp;
}

void dfs_visit(node *array, int n, int i, int *ptime) {
	array[i].color = 0;
	array[i].d = ++(*ptime);
	adj_node *head = array[i].link;
	while (head != NULL) {
		int k = head->index;
		if (array[k].color == -1) {
			array[k].parent = i;
			dfs_visit(array, n, k, ptime);
		}
		head = head->ptr;
	}
	array[i].f = ++(*ptime);
	array[i].color = 1;
}

void dfs(node *array, int n) {
	int time = 0;
	for (int i = 0; i <= n; i++) {
		if (array[i].color == -1) {
			dfs_visit(array, n, i, &time);
		}
	}
}

void print_connected(node *array, int n) {
	dfs(array, n);
	for (int i = 1; i <= n; i++) {
		if (array[i].printed == 0) {
			for (int j = 1; j <= n; j++) {
				if (array[j].d >= array[i].d && array[j].f <= array[i].f) {
					array[j].printed = 1;
					cout << j << " ";
				}
			}
			cout << endl;
		}
	}
}

void print(node *array, int n) {
	for (int i = 1; i <= n; i++) {
		cout << i << " " << array[i].d << " " << array[i].f << endl;
		adj_node *head = array[i].link;
		while (head != NULL) {
			cout << head->index << " ";
			head = head->ptr;
		}
		cout << "NULL" << endl << endl;
	}
}

int main() {
	int n, e;
	cin >> n >> e;
	// cout << n << " " << e << endl;

	node array[n+1];
	for (int i = 1; i <= n; i++) {
		array[i].color = -1;
		array[i].d = -1;
		array[i].f = -1;
		array[i].parent = -1;
		array[i].link = NULL;
		array[i].printed = 0;
	}
	int e1, e2;
	for (int i = 0; i < e; i++) {
		scanf("%d, %d", &e1, &e2);
		enqueue(&(array[e1].link), e2);
		enqueue(&(array[e2].link), e1);
	}
	// print(array, n);
	print_connected(array, n);
	// print(array, n);
} 