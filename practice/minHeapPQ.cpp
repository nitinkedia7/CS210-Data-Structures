// Implementation of priority queue using minHeap

#include <iostream>
#include <climits>

using namespace std;

int findMin(int *array, int i, int j) {
	if (array[i] < array[j]) return i;
	else return j;
}

void minHeapify(int *array, int n, int i) {
	if (n > 2*i+2) {
		int k = findMin(array, i, findMin(array, 2*i+1, 2*i+2));
		if (k != i) {
			swap(array[i], array[k]);
			minHeapify(array, n, k);
		}
	}
	else if (n == 2*i+2) {
		int k = findMin(array, i , 2*i+1);
		if (k != i) {
			swap(array[i], array[k]);
			minHeapify(array, n, k);
		} 
	}  	
}

void buildMinHeap(int *array, int n) {
	for (int i = n/2; i >=0; i--) {
		minHeapify(array, n, i);
	}
}

int search(int *array, int n, int i, int x) {
	if (i < n) {
		if (array[i] == x) return i;
		search(array, n, 2*i+1, x);
		search(array, n, 2*i+2, x);
		return -1;
	}
	else return -1;	
}

void decreaseKey(int *array, int i, int x) {
	if (x < array[i]) {
		array[i] = x;
		int p = (i-1)/2;
		while (p >= 0) {
			if (array[i] < array[p]) {
				swap(array[i], array[p]);
				i = p;
				p = (i-1)/2;
			}
			else break; 
		}
	}
}

void insert(int *array, int *pn, int x) {
	int *last = array+(*pn);
	last = new int;
	int i = (*pn);
	array[i] = INT_MAX;
	
	decreaseKey(array, i, x);
	*pn = *pn+1;
}

int extractMin(int *array, int *pn) {
	int min = array[0];
	array[0] = array[*pn-1];
	minHeapify(array, *pn, 0);
	(*pn)--;
	return min;
}

void deleteKey(int *array, int *pn, int i) {
	//int i = search(array, *pn, 0, x);
	// if (i != -1) {
	// 	array[i] = INT_MAX;
	// 	minHeapify(array, *pn, i);
	// 	*pn--;
	// }
	decreaseKey(array, i, INT_MIN);
	extractMin(array, pn);

}

int *merge(int *array1, int n1, int *array2, int n2) {
	int array[n1+n2];
	for (int i = 0; i < n1; i++) {
		array1[i] = array1[i];
	}
	for (int i = n1; i < n1+n2; i++) {
		array[i] = array2[i-n1];
	}

	buildMinHeap(array, n1+n2);
	return array;
}
void print(int *array, int n) {
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	int *array = new int[n];
	for (int i =0; i < n; i++) {
		cin >> array[i];
	}
	buildMinHeap(array, n);

	cout << array[0] << endl;
	cout << extractMin(array, &n) << endl;
	print(array, n);
	insert(array, &n, -1);
	print(array, n);
	decreaseKey(array, 4, -2);
	print(array, n);
	insert(array, &n, 5);
	print(array, n);
	decreaseKey(array, 1, -3);
	print(array, n);
	deleteKey(array, &n, 3);
	print(array, n);
}