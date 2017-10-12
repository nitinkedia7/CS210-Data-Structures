// 160101048_LA4_1.cpp: Nitin Kedia
// Description: Implement a tertnary min-heap

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// finHeap returns the first index if other is larger
int findMin(int *array, int i, int j) {
	if (array[i] <= array[j]) return i;
	else return j;
}
// prints the heap
void print(int *array, int n) {
	if (n == 0) {
		cout << "Empty heap" << endl;
		return;
	}
	for(int i = 0; i < n; i++) {
		cout << array[i]; 
		if (i < n-1) cout << " ";
	}
	cout << endl;
}
// places H[i] in its correct position
void minHeapify(int *H, int n, int i) {
	if (n > 3*i+3) { // all child exist
		int k = findMin(H, 3*i+1, findMin(H, 3*i+2, 3*i+3));
		k = findMin(H, i, k);
		if (k != i) {
			swap(H[i], H[k]);
			minHeapify(H, n, k);
		}
	}
	if (n == 3*i+3) { // only left and middle child exist
		int k = findMin(H, i, findMin(H, 3*i+1, 3*i+2));
		if (k != i) {
			swap(H[i], H[k]);
			minHeapify(H, n, k);
		}
	}
	if (n == 3*i+2) { // only left child exists
		int k = findMin(H, i, 3*i+1);
		if (k != i) {
			swap(H[i], H[k]);
			minHeapify(H, n, k);
		}
	}
}
// to build the heap minHeapify all non-leaf nodes
void buildHeap(int *H, int n) {
	for (int i = (n/3)-1; i >=0; i--) {
		minHeapify(H, n, i);
	}
}

void insert(int *H, int *pn, int x) {
	if (*pn < 100) {
		int i = (*pn);
		(*pn) = (*pn)+1;
		H[i] = x; // append new element into H
		int p = (i-1)/3;
		while (p >= 0) { // make it go up the heap till its parent is no smaller than it
			if (H[i] < H[p]) {
				swap(H[i], H[p]);
				i = p;
				p = (i-1)/3;
			}
			else break;
		}
	}
}
// return root and put last element into root position and minHeapify it
int deleteMin(int *H, int *pn) {
	if (*pn > 0) {
		int min = H[0];
		(*pn) = (*pn)-1;
		int n = (*pn);
		H[0] = H[n];
		minHeapify(H, n, 0);
		return min;
	}
}
// driver function
int main() {
	int n;
	cin >> n;
	int H[100];
	for (int i = 0; i < n; i++) {
		cin >> H[i]; 
	}

	buildHeap(H, n);
	print(H, n);

	char cmd;
	int arg = -1;
	while (cin >> cmd) {
		if (cmd == 'I' || cmd == 'i') {
			cin >> arg;
			if (n < 100) {
				insert(H, &n, arg);
				cout << endl;
				cout << arg << " is inserted" << endl;
				print(H, n);
			}
		}
		else if (cmd == 'D' || cmd == 'd') {
			if (n > 0) {
				arg = deleteMin(H, &n);
				cout << endl;
				cout << arg << " is deleted" << endl;
			}
			print(H, n);
		}
		else if (cmd == 'q') break;
	}
	return 0;
}