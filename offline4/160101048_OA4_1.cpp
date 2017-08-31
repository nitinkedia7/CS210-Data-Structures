// 160101048_OA1_1.cpp: Nitin Kedia
// Description: Sort and Reduce an integer array

#include <iostream>
using namespace std;

// bubbleSort sorts a integer array in ascending order with all optimisations in Bubble Sort
void bubbleSort(int *array, int n) {
	int i, j, k;
	for (i = 0; i < n-1; i++) {
		int isSwap = 0;
		if (i%2 == 0) {
			for (j=(i/2); j<n-1-(i/2); j++) { // sending max to leftmost position
				if (array[j] > array[j+1]) {
					int temp = array[j];
					array[j] = array[j+1];
					array[j+1] = temp;
					isSwap++;
				}
			}
			if (isSwap == 0) break;
		}
		else {
			for (k = n-2-(i/2); k > (i/2); k--) { // sending min to rightmost position
				if (array[k] < array[k-1]) {
					int temp = array[k];
					array[k] = array[k-1];
					array[k-1] = temp;
					isSwap++;
				}
			}
			if (isSwap == 0) break;
		}
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
		bubbleSort(array, n-i); // sort given array decrementing its length progessively 
		for (int j = 0; j < n-1-i ; j++) {
			array[j] = array[j+1]-array[j]; // since array is sorted ascendingly, array[j+1] >= array[j], thus difference will be automatically absolute
		}
	}
	cout << array[0] << endl;
	return 0;
}