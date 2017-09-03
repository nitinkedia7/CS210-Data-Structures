// mergeSort.cpp: Nitin Kedia
// Description: sort an integer array ascendingly using Merge Sort

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void swap(int *array, int i, int j) {
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

int *copy(int *src, int i, int j, int *dest) {
	dest = new int[j-i+2];
	int k;
	for (k = i; k <= j; k++) {
		dest[k-i] = src[k];
	}
	dest[k-i] = INT_MAX;
	return dest;
}

void merge(int *array, int l, int p, int u) {
	int m = p+1-l;
	int n = u-p;
	int *left, *right;
	left = copy(array, l, p, left);
	right = copy(array, p+1, u, right);

	int j = 0, k = 0;
	for (int i = l; i <= u; i++) {
		if (left[j] <= right[k]) {
			array[i] = left[j++];
		}
		else array[i]  = right[k++];
	}

}

void mergeSort(int *array, int l, int u) {
	if (l < u) {
		int p = (l+u)/2;
		mergeSort(array, l, p);
		mergeSort(array, p+1, u);
		merge(array, l, p, u);
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
	
	mergeSort(array, 0, n-1);
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}