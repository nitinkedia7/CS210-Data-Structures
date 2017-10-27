// 160101048_OA9_2.cpp: Nitin Kedia
// Description: Find minimum number of button presses required to reach target state without any forbidden state in between

#include <iostream>
using namespace std;

struct adj_node {
	int index;
	adj_node *ptr;
};

struct node {
	int color, d, parent;
	int next_states[8];
};

void enqueue(adj_node **pHead, int index) {
	adj_node *temp = new adj_node;
	temp->index = index;
	temp->ptr = *pHead;

	*pHead = temp;
}

int dequeue(adj_node **pHead) {
	if (*pHead != NULL) {
		int n;
		if ((*pHead)->ptr != NULL) {
			adj_node *next = *pHead;
			adj_node *prev = NULL;
			while (next->ptr != NULL) {
				prev = next;
				next = next->ptr;
			}
			prev->ptr = NULL;
			n = next->index;
			delete next;
		}
		else {
			n = (*pHead)->index;
			delete *pHead;
			*pHead = NULL;
		}
		return n;
	}
}

void bfs(node *array, int s) {
	// initial attributes already assigned
	array[s].d = 0;
	array[s].color = 0; // gray
	
	adj_node *queue = NULL;
	enqueue(&queue, s);

	while (queue != NULL) {
		int u = dequeue(&queue);

		for (int i = 0; i < 8; i++) {
			int v = array[u].next_states[i];

			if (array[v].color == -1) {
				array[v].color = 0;
				array[v].d = array[u].d + 1;
				enqueue(&queue, v);
			}
		}
		array[u].color = 1; // black
	}
}
int scan() {
	int n = 0, k = 0, i = 1000;
	while (i > 0) {
		cin >> k;
		n += (k * i);
		i = i/10; 
	}
	return n;
 }

int main() {
	int n;
	cin >> n;

	node array[10000];
	for (int i = 0; i < 10000; i++) {
		int pow1 = 1;

		for (int j = 0; j < 4; j++) {
			int pow2 = pow1*10;
			int k = i % pow2;

			array[i].next_states[2*j] = i - k + (k + pow1 + pow2) % (pow2);
			array[i].next_states[2*j+1] = i - k + (k - pow1 + pow2) % (pow2);
			pow1 = pow2;
		}
	}

	for (int i = 0; i < n; i++) {
		int start = scan(), end = scan();

		for (int k = 0; k < 10000; k++) {
			array[k].parent = -1;
			array[k].color = -1;
			array[k].d = -1;
		}

		int f;
		cin >> f;
		for (int j = 0; j < f; j++) {
			int forbidden = scan();
			array[forbidden].color = 1;
		}
		bfs(array, start);
		cout << array[end].d << endl;
	}
}