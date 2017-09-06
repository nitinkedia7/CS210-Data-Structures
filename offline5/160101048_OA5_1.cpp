// 160101048_OA5_1.cpp: Nitin Kedia
// Description: Implementation of insertion sort using binary search

#include <iostream>

using namespace std;

int binSearch(int *array, int l, int u, int num, int *ptrCmpsn) {
	if (l <= u) {	
		int p = (u+l)/2;
		(*ptrCmpsn)++;
		if (array[p] < num) {
			if (l == u) return l+1;
			binSearch(array, p+1, u, num, ptrCmpsn);
		}
		else {
			if (l == u) return l;
			binSearch(array, l, p, num, ptrCmpsn);
		}  
	}
	else return -1;
}

void insertionSort (int *array, int n, int *ptrCmpsn) {
	for (int i = 1; i < n; i++) {
		int temp = array[i];
		int p = binSearch(array, 0, i-1, temp, ptrCmpsn);
		if (p > -1) {
			for (int j = i; j > p; j--) {
				array[j] = array[j-1];
			}
			array[p] = temp;
		}
	}
}

void printArray(int *array, int n) {
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

int main() {
	cout << "Enter input:" << endl;
	int n;
	cin >> n;

	int array[n];
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}
	int cmpsn = 0;
	insertionSort(array, n, &cmpsn);
	
	cout << cmpsn << endl;
	printArray(array, n);
}	