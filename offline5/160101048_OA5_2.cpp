// 160101048_OA5_2.cpp: Nitin Kedia
// Description: Calculation of number of inversions in array S using mergeSort 
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Utility function for copying part to source array to dest array; 
int *copyArray(int *src, int i, int j, int *dest) {
	dest = new int[j-i+2]; // last element will be INT_MAX, so length is one more than required
	int k;
	for (k = i; k <= j; k++) {
		dest[k-i] = src[k];
	}
	dest[k-i] = INT_MAX; // to simplify mergeArray, else we have to impose appropriate boundary conditions
	return dest;
}

// mergeArray merges two sorted daughter arrays into a single sorted array
// we are passing inv (counter for inversion pairs) by reference
void mergeArray(int *array, int l, int p, int u, int *pInv) {
	int *left, *right; 
	left = copyArray(array, l, p, left); // copying daughter arrays to be eventually copied back to parent array in proper order
	right = copyArray(array, p+1, u, right);

	int j = 0, k = 0;
	for (int i = l; i <= u; i++) {
		if (left[j] > right[k]) {
			array[i] = right[k++];
			(*pInv) += (p+1-l)-j; // each time a element x from right array is copied to main array instead of all other elements of left array
								  // we get n unique inversion pairs where n = number of remaining elements in left array 				 
		}
		else array[i]  = left[j++];
	}
}

// mergeSort uses divide and conquer steps
void mergeSort(int *array, int l, int u, int *pInv) {
	if (l < u) {
		int p = (l+u)/2;
		mergeSort(array, p+1, u, pInv); // recursively sort right part
		mergeSort(array, l, p, pInv); 	// recursively sort left part
		mergeArray(array, l, p, u, pInv); // merge left and right part
	}
}

int main() {
	cout << "Enter input:" << endl;
	int n;
	cin >> n;
	if (n <= 0) return 0;
	int array[n];
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}
	
	int inv = 0; // initialise number of inversions with 0 and pass it by reference to merge steps 
	mergeSort(array, 0, n-1, &inv);

	cout << inv << endl; // print number of inversions
}