// 160101048_LA5_1.cpp: Nitin Kedia
// Description: Divide a group of wrestlers into good
// and bad guys using BFS, if possible

#include <bits/stdc++.h>
using namespace std;

struct node {
	int rival;
	node *ptr;
};

struct player {
	int color, d, parent, moral;
	node *link;
};

void enqueue(node **pHead, int rival) {
	node *temp = new node;
	temp->rival = rival;
	temp->ptr = *pHead;

	*pHead = temp;
}

int dequeue(node **phead) {
	node *head = *phead;
	if (head != NULL) {
		if (head->ptr != NULL) {
			node *next = head;
			node *prev = NULL;
			while (next->ptr != NULL) {
				prev = next;
				next = next->ptr;
			}
			prev->ptr = NULL;
			return next->rival;
		}
		else {
			int n = head->rival;
			*phead = NULL;
			return n;
		}
	}
}

void assign_moral(player *array, int n, int s) {
	// initial attributes already assigned
	array[s].d = 0;
	array[s].color = 0; // gray
	node *head = NULL;
	enqueue(&head, s);
	while (head != NULL) {
		int u = dequeue(&head);
		node *rlist = array[u].link;
		while (rlist != NULL) {
			int v = rlist->rival;
			if (array[v].color == -1) {
				array[v].color = 0;
				array[v].d = array[u].d + 1;
				enqueue(&head, v);
			}
			rlist = rlist->ptr;
		}
		array[u].color = 1; // black
	}
}

void print(player *array, int n) {
	for (int i = 1; i <= n; i++) {
		node *head = array[i].link;
		cout << array[i].d << "\t";
		while (head != NULL) {
			cout << head->rival << " ";
			head = head->ptr; 
		}
		cout << endl;
	}
}

int main() {
	int n, r;
	cin >> n >> r;

	player array[n+1];
	for (int i = 1; i <= n; i++) {
		array[i].color = -1;
		array[i].d = -1;
		array[i].parent = -1;
		array[i].moral = 1;
		array[i].link = NULL;
	}
	int ri, rj;
	int rival1[r], rival2[r];
	for (int i = 0; i < r; i++) {
		cin >> ri >> rj;
		rival1[i] = ri;
		rival2[i] = rj;
		enqueue(&(array[ri].link), rj);
		enqueue(&(array[rj].link), ri);
	}
	// print(array, n);
	assign_moral(array, n+1, ri);
	// print(array, n);

	for (int i = 0; i < r; i++) {
		int ri = array[rival1[i]].d;
		int rj = array[rival2[i]].d;
		if ((ri-rj)%2 == 0) {
			cout << "Not Possible" << endl;
			return 0;
		}

	}
	int good[r], bad[r];
	int g = 0, b = 0;
	for (int i = 1; i <= n; i++) {
		if ((array[i].d)%2 == 0) good[g++] = i;
		else bad[b++] = i;
	}
	cout << "Good Guys: ";
	for (int i = 0; i < g; i++) {
		cout << good[i] << " ";
	}
	cout << endl;
	cout << "Bad Guys: ";
	for (int i = 0; i < b; i++) {
		cout << bad[i] << " ";
	}
	cout << endl;

}
 