#include <iostream>
using namespace std;

struct adj_node {
	int index;
	adj_node *ptr;
};

struct node {
	int color, parent, d, f;
	adj_node *head;
};

void push(adj_node **pHead, int i) {
	adj_node *temp = new adj_node;
	temp->index = i;
	temp->ptr = *pHead;
	*pHead = temp;
}

int pop(adj_node **pHead) {
	if (*pHead != NULL) {
		int index = (*pHead)->index;
		*pHead = (*pHead)->ptr;
		return index;
	}
}

void dfs_stack(node *array, int n) {
	adj_node *stack = NULL;

	int time = 0; 

	for (int i = 1; i <= n; i++) {
		if (array[i].color == -1) {
			push(&stack, i);
			while (stack != NULL) {
				int u = pop(&stack);
				if (array[u].color == -1) {
					array[u].d = ++time;
					array[u].color = 0;
				}
				
				adj_node *head = array[u].head;
				while (head != NULL) {
					if (array[head->index].color == -1) {
						array[head->index].parent = u;
						push(&stack, head->index);
					}
					head = head->ptr;
				}
			}
		}
	}
}

void print(node *array, int n) { // to print adjacency list
	for (int i = 1; i <= n; i++) {
		cout << i << " " << array[i].parent << " " << array[i].d << endl;
		adj_node *head = array[i].head;
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

	node array[n+1];
	for (int i = 0; i <= n; i++) {
		array[i].color = -1; // white
		array[i].d = -1;
		array[i].f = -1;
		array[i].parent = -1;
		array[i].head = NULL;
	}

	int e1, e2;
	for (int i = 0; i < e; i++) {
		cin >> e1 >> e2;
		push(&(array[e1].head), e2);	 
	}

	dfs_stack(array, n);
	print(array, n);
}
