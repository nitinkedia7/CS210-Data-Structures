// 160101048_OA5_1.cpp: Nitin Kedia
// Description: Implementation of insertion sort using binary search

#include <iostream>

using namespace std;

// binSearch returns the index where num is to be inserted
// its jurisdiction is from index l to u in array
int binSearch(int *array, int l, int u, int num, int *ptrCmpsn) {
	if (l > u) return l; // following statements ensure that in case of overflow, l is the suitable index
	else {	
		int p = (u+l)/2; // middle element
		
		(*ptrCmpsn)++; // imminent comparison
		if (array[p] > num) { 
			binSearch(array, l, p-1, num, ptrCmpsn);// searching left half
		}
		else {
			binSearch(array, p+1, u, num, ptrCmpsn); // searching right half
		}
		// Note that we eliminated p as an answer but it will be right answer if array[p] <= num and array[p+1] >= num;
		// in such cases, binSearch(array, p, p-1, ptrCmpsn) will be called thereby returning p from 1st statement;   
	}
}

void insertionSort (int *array, int n, int *ptrCmpsn) {
	for (int i = 1; i < n; i++) { // insert i'th element in a suitable place between array[0] to array[i-1]  
		int temp = array[i]; 
		int p = binSearch(array, 0, i-1, temp, ptrCmpsn); // search suitable position;
		if (p > -1) {
			for (int j = i; j > p; j--) { // shift to make room for temp
				array[j] = array[j-1];
			}
			array[p] = temp;
		}
	}
}
// utility function
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
	int cmpsn = 0; // cmpsn (comparison) counts total number of comparisons in binary search
	insertionSort(array, n, &cmpsn); // pass cmpsn by reference
	
	cout << cmpsn << endl;
	printArray(array, n);
}	