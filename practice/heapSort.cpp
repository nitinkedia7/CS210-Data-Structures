// heapSort.cpp: Nitin Kedia
// Description - Sort a integer array in ascending order using Heap Sort

#include <iostream>
using namespace std;

int maxIndex(int *array, int i, int j) {
	if (array[i] > array[j]) {
		return i;
	}
	else return j;
}

int swap(int *array, int i, int k) {
	int temp = array[k];
	array[k] = array[i];
	array[i] = temp;
}

void maxHeapify(int *array, int n, int i) {
	if (n > 2*i + 2) {
		int k = maxIndex(array, i, maxIndex(array, 2*i+1, 2*i+2));
		if (k != i) {
			swap(array, i, k);
			maxHeapify(array, n, k);
		}
	}
	else if (n == 2*i+2) {
		int k = maxIndex(array, i, 2*i+1);
		if (k != i) {
			swap(array, i, k);
		}
	}
}

void buildMaxHeap(int *array, int n) {
	for (int i = n/2; i >= 0; i--) {
		maxHeapify(array, n, i);
	}
}

void heapSort(int *array, int n) {
	buildMaxHeap(array, n);
	swap(array, 0, n-1);

	for (int i = 0; i < n-1; i++) {
		maxHeapify(array, n-1-i, 0);
		swap(array, 0, n-2-i);
	}
}

int main() {
	cout << "Enter input:" << endl;
	int n;
	cin >> n;
	int array[n];
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}
	
	heapSort(array, n);
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}