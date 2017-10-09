// 160101048_MS_1.cpp: Nitin Kedia
// Description: Implement a modified version of Merge Sort which uses binary Insertin Sort for sub-arrays less than THRESHOLD size

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void randomArray(int *array, int n) {
	for (int i = 0; i < n; i++) {
		array[i] = rand(); 
	}
}

void print(int *array, int l, int u) {
	for (int i = l; i <= u; i++) {
		cout << array[i] << endl;
	}
}

int binarySearch(int *array, int l, int u, int num, int *pCmp) {
	if (l <= u) {
		int m = (l+u)/2;

		(*pCmp)++;
		if (array[m] >= num) {
			binarySearch(array, l, m-1, num, pCmp);
		}
		else {
			binarySearch(array, m+1, u, num, pCmp);
		}
	}
	else return l;
}

void insertionSort(int *array, int l, int u, int *pCmp) {
	for (int i = l+1; i <= u; i++) {
		int temp = array[i];
		int p = binarySearch(array, l, i-1, temp, pCmp);
		for (int j = i; j > p; j--){
			array[j] = array[j-1];
		}
		array[p] = temp;
	}
}

void copy(int *array, int l, int u, int *newArray) {
	int i;
	for (i = l; i <=u; i++) {
		newArray[i-l] = array[i];
	}
	newArray[i-l] = INT_MAX;
}

void merge(int *array, int l, int m, int u, int *pCmp) {
	int left[m-l+2];
	int right[u-m+1];

	copy(array, l, m, left);
	copy(array, m+1, u, right);

	int j = 0; int k = 0;
	for (int i = l; i <= u; i++) {
		(*pCmp)++;
		if (left[j] < right[k]) {
			array[i] = left[j++];
		}
		else array[i] = right[k++];
	}
} 

void mergeSort(int *array, int l, int u, int THRESHOLD, int *pCmp) {
	int n = u-l+1;
	if (l < u) {
		if (n < THRESHOLD) {
			insertionSort(array, l, u, pCmp);
		}
		else {
			int m = (l+u)/2;
			mergeSort(array, l, m, THRESHOLD, pCmp);
			mergeSort(array, m+1, u, THRESHOLD, pCmp);
			merge(array, l, m, u, pCmp);
		}
	}
}

int main() {
	// int n;
	// cin  >> n;
	// int array[n];
	// for (int i = 0; i < n; i++) {
	// 	cin >> array[i];
	// }
	// print(array, 0, n-1);
	// int cmp = 0;
	// int THRESHOLD;
	// cout << "Enter Threshold:" << endl; 
	// cin >> THRESHOLD;
	// // mergeSort(array, n, THRESHOLD, &cmp);
	// mergeSort(array, 0, n-1, THRESHOLD, &cmp);
	// print(array, 0, n-1);

	int n;
	cout << "Enter length of random loop:" << endl;
	cin >> n; 
	int array[n];
	randomArray(array, n);

	int cmp = 0;
	int THRESHOLD = 55;
	mergeSort(array, 0, n-1, THRESHOLD, &cmp);
	cout << cmp << " comparisons" << endl;
	print(array, 0, n-1);
}