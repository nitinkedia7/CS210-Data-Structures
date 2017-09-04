// minHeap from bottom up
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int minIndex(int *array, int i, int j) {
	if (array[i] < array[j]) return i;
	else return j;
}

void swapper(int *array, int i, int j) {
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void minHeapify(int *array, int n, int i) {
	if (n > 2*i+2) {
		int k;
		k = minIndex(array, i, minIndex(array, 2*i+1, 2*i+2));
		if (k != i) {
			swapper(array, i, k);
			minHeapify(array, n , k);	
		}
	}
	if (n == 2*i+2) {
		int k = minIndex(array, i, 2*i+1);
		if (k != i) {
			swapper(array, i, k);
		}
	}
}

void buildMinHeap(int *array, int n) {
	for (int i = n/2; i >= 0; i--) {
		minHeapify(array, n, i);
	}
}

void heapSort(int *array, int n, int k) {
	buildMinHeap(array, n);
	swapper(array, 0, n-1);

	for (int i = 0; i < k-1; i++) {
		minHeapify(array, n-1-i, 0);
		swapper(array, 0, n-2-i);
	}
}

int main () {
	int n;
	cout << "Enter input:" << endl;
	cin >> n;
	if (n <= 0) return 0;

	int array[n];
	for (int i = 0; i < n; i++) {
		cin >> array[i];
 	}

 	int k;
 	cin >> k;
 	if (k < 0 || k > n) return 0;

 	heapSort(array, n, k);

 	for (int i = 0; i < k; i++) {
 		cout << array[n-1-i] << " ";
 	}
 	cout << endl;
}	