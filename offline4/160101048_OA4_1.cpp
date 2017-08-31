// 160101048_OA1_1.cpp: Nitin Kedia
// Description: Sort and Reduce an integer array

#include <iostream>
#include <cstdlib>
using namespace std;

// quickSort sorts the integer array in ascending order with orden nlogn
void swap(int *array, int i, int j) {
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void partition(int *array, int l, int u, int *p) {
	int pivot = array[*p];
	swap(array, l, *p);
	int down = l;
	while (l < u) {
		while (array[l] <= pivot && l < u) l++;
		while (array[u] > pivot) u--;
		if (l < u) {
			swap(array, l, u);
		}
	}
	swap(array, down, u);
	*p = u;
}

void quickSort(int *array, int l, int u) {
	if (l < u) {
		int p = (u+l)/2;
		partition(array, l, u, &p);
		quickSort(array, l, p-1);
		quickSort(array, p+1, u);
	}
}

int main() {
	int n;
	cout << "Enter length of array: ";
	cin >> n;
	if (n < 1) {
		cout << "Input array must not be empty." << endl;
		return 0;
	}
	cout << "Enter the array: ";
	int array[n];
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}
	for (int i = 0; i < n; i++) {
		quickSort(array, 0, n-i-1); // sort given array decrementing its length progessively 
		for (int j = 0; j < n-1-i ; j++) {
			array[j] = array[j+1]-array[j]; // since array is sorted ascendingly, array[j+1] >= array[j], thus difference will be automatically absolute
		}
	}
	cout << array[0] << endl;
	return 0;
}