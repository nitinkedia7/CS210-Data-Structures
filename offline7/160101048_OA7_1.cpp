// 160101048_OA7_1.cpp: Nitin Kedia
// Description: Find k smallest element in ternary min-heap, and elements smaller than a given number

#include <iostream>
using namespace std;

/* Functions for main (input) heap start here */

void print(int *array, int n) { // prints the heap array
	cout << endl;
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

int findMin(int *array, int i, int j) { // findMin compares two array positions and returns the index of smaller key
	if (array[i] <= array[j]) return i;
	else return j;
}

void minHeapify(int *H, int n, int i) { // places a heap element in its correct position
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

void buildHeap(int *H, int n) { // build heap by minHeapifying all non-leaf nodes
	for (int i = (n/3); i >=0; i--) {
		minHeapify(H, n, i);
	}
}

/* Functions for auxillary priority queue start here */
// This auxillary PQ contains index of main heap where candidates for i'th smallest munber reside

int findMin(int *H, int *PQ, int i, int j) { // findMin compares two array positions and returns the index of smaller key
	if (H[PQ[i]] <= H[PQ[j]]) return i;
	else return j;
}

void minHeapifyPQ(int *H, int *PQ, int n, int i) { // places a heap element in its correct position
	int k = -1;
	if (n > 3*i+3) { // all child exist
		k = findMin(H, PQ, 3*i+1, findMin(H, PQ, 3*i+2, 3*i+3));
		k = findMin(H, PQ, i, k);
	}
	else if (n == 3*i+3) { // only left and middle child exist
		k = findMin(H, PQ, i, findMin(H, PQ, 3*i+1, 3*i+2));
	}
	else if (n == 3*i+2) { // only left child exists
		k = findMin(H, PQ, i, 3*i+1);
	}
	if (k != -1) {
		if (k != i) {
			swap(PQ[i], PQ[k]);
			minHeapifyPQ(H, PQ, n, k);
		}
	}
}

void insert(int *H, int *PQ, int *pn, int index) { // insert a new element into priority queue
	int i = (*pn);
	(*pn) = (*pn)+1;
	PQ[i] = index; // append new element into PQ
	int p = (i-1)/3;
	while (p >= 0) { // make it go up the heap till its parent is no smaller than it
		if (H[PQ[i]] < H[PQ[p]]) {
			swap(PQ[i], PQ[p]);
			i = p;
			p = (i-1)/3;
		}
		else break;
	}
}

int deleteMin(int *H, int *PQ, int *pn) { // return root and put last element into root position and minHeapify it
	if (*pn > 0) {
		int min = PQ[0];
		(*pn) = (*pn)-1;
		int n = (*pn);
		PQ[0] = PQ[n];
		minHeapifyPQ(H, PQ, n, 0);
		return min;
	}
}

void ksmallest(int *H, int n, int k) { // print the smallest k elements in main heap
	if (k <= n) {
		int candidates[2*k+1]; // declare auxillary priority queue
		int l = 0;
		insert(H, candidates, &l, 0); // first insert root index since it will contain smallest element in the heap 
		cout << endl;
		for (int i = 0; i < k; i++) {
			int min = deleteMin(H, candidates, &l); // extract index of i'th smallest element in the heap
			cout << H[min] << " ";	
			// insert the child(s) of the extracted element in PQ
			if (n > 3*min+1) insert(H, candidates, &l, 3*min + 1);
			if (n > 3*min+2) insert(H, candidates, &l, 3*min + 2);
			if (n > 3*min+3) insert(H, candidates, &l, 3*min + 3);
		}
		cout << endl;
		print(H, n); // print main heap to show it is untouched
	}
}

void printsmall_helper(int *H, int n, int i, int a) { // helper function for recursively printing elements smaller than a
	if (i < n) {
		if (H[i] <= a) {
			cout << H[i] << " "; // enter a subtree only if its root is smaller than a since if root is bigger all other members are also bigger
			printsmall_helper(H, n, 3*i+1, a);
			printsmall_helper(H, n, 3*i+2, a);
			printsmall_helper(H, n, 3*i+3, a);
		}
	}
}

void printsmall(int *H, int n, int a) { // initialise helper function from root of main heap
	printsmall_helper(H, n, 0, a);
	cout << endl;
	print(H, n); // print main heap to show it is untouched
}

int main() {
	int n;
	cin >> n;
	int H[n];
	for (int i = 0; i < n; i++) {
		cin >> H[i];
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