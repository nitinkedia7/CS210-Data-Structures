// 160101048_OA7_1.cpp: Nitin Kedia
// Description: Find k smallest element in tertnary min-heap,
//  			elements smaller than a given number

#include <bits/stdc++.h>
using namespace std;
struct node {
	int key, index;
};
// finHeap returns the first index if other is larger
int findMin(node *array, int i, int j) {
	if (array[i].key <= array[j].key) return i;
	else return j;
}
// prints the heap
void print(node *array, int n) {
	cout << endl << "Heap Structure:" << endl;
	if (n == 0) {
		cout << "Empty heap" << endl;
		return;
	}
	for(int i = 0; i < n; i++) {
		cout << array[i].key; 
		if (i < n-1) cout << " ";
	}
	cout << endl;
}
// places H[i] in its correct position
void minHeapify(node *H, int n, int i) {
	int k = -1;
	if (n > 3*i+3) { // all child exist
		k = findMin(H, 3*i+1, findMin(H, 3*i+2, 3*i+3));
		k = findMin(H, i, k);
	}
	else if (n == 3*i+3) { // only left and middle child exist
		k = findMin(H, i, findMin(H, 3*i+1, 3*i+2));
	}
	else if (n == 3*i+2) { // only left child exists
		k = findMin(H, i, 3*i+1);
	}
	if (k != -1) {
		if (k != i) {
			swap(H[i], H[k]);
			minHeapify(H, n, k);
		}
	}
}
// to build the heap minHeapify all non-leaf nodes
void buildHeap(node *H, int n) {
	for (int i = (n/3); i >=0; i--) {
		minHeapify(H, n, i);
	}
}

void insert(node *H, int *pn, int key, int index) {
	if (*pn < 100) {
		int i = (*pn);
		(*pn) = (*pn)+1;
		H[i].key = key; // append new element into H
		H[i].index = index;
		int p = (i-1)/3;
		while (p >= 0) { // make it go up the heap till its parent is no smaller than it
			if (H[i].key < H[p].key) {
				swap(H[i], H[p]);
				i = p;
				p = (i-1)/3;
			}
			else break;
		}
	}
}
// return root and put last element into root position and minHeapify it
node deleteMin(node *H, int *pn) {
	if (*pn > 0) {
		node min = H[0];
		(*pn) = (*pn)-1;
		int n = (*pn);
		H[0] = H[n];
		minHeapify(H, n, 0);
		return min;
	}
}

void ksmallest(node *H, int n, int k) {
	if (k <= n) {
		node candidates[n];
		int l = 0;
		insert(candidates, &l, H[0].key, 0); 
		cout << endl << k << " smallest elements: " << endl;
		for (int i = 0; i < k; i++) {
			node min = deleteMin(candidates, &l);
			cout << min.key << " ";	
			if (n > 3*min.index+1) insert(candidates, &l, H[3*min.index + 1].key, 3*min.index + 1);
			if (n > 3*min.index+2) insert(candidates, &l, H[3*min.index + 2].key, 3*min.index + 2);
			if (n > 3*min.index+3) insert(candidates, &l, H[3*min.index + 3].key, 3*min.index + 3);
		}
		cout << endl;
		print(H, n);
	}
}

void printsmall_helper(node *H, int n, int i, int a) {
	if (i < n) {
		if (H[i].key <= a) {
			cout << H[i].key << " ";
			printsmall_helper(H, n, 3*i+1, a);
			printsmall_helper(H, n, 3*i+2, a);
			printsmall_helper(H, n, 3*i+3, a);
		}
	}
}
void printsmall(node *H, int n, int a) {
	cout << "Elements smaller than " << a << ":" << endl;
	printsmall_helper(H, n, 0, a);
	cout << endl;
	print(H, n);
}
// driver function
int main() {
	int n;
	cin >> n;
	node H[n];
	for (int i = 0; i < n; i++) {
		cin >> H[i].key;
		H[i].index = -1; 
	}

	buildHeap(H, n);
	print(H, n);

	int k;
	cin >> k;
	ksmallest(H, n, k);

	int a;
	cin >> a;
	printsmall(H, n, a);
	return 0;
}