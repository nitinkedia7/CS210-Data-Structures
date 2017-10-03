// 160101048_OA6_2.cpp: Nitin Kedia
// Description- Minimising average cooking time by using priority queue implemented using using minHeap

#include <iostream>
#include <climits>
using namespace std;

struct customer {
	long long int o;
	long long int c;
};

int findMin(customer *array, int i, int j) {
	if (array[i].c < array[j].c) return i;
	else if (array[i].c  == array[j].c) {
		if (array[i].o < array[j].o) return i;
		else return j;
	}
	else return j;
}

void swapper(customer *array, int i, int j) {
	customer temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void minHeapify(customer *array, int n, int i) {
	if (n > 2*i+2) {
		int k = findMin(array, i, findMin(array, 2*i+1, 2*i+2));
		if (k != i) {
			swapper(array, i, k);
			minHeapify(array, n, k);
		}
	}
	else if (n == 2*i+2) {
		int k = findMin(array, i , 2*i+1);
		if (k != i) {
			swapper(array, i, k);
			minHeapify(array, n, k);
		} 
	}  	
}

void buildMinHeap(customer *array, int n) {
	for (int i = n/2; i >=0; i--) {
		minHeapify(array, n, i);
	}
}

void decreaseKey(customer *array, int i, customer x) {
	if (x.c < array[i].c) {
		array[i] = x;
		int p = (i-1)/2;
		while (p >= 0) {
			if (i == findMin(array, i, p))  {
				swapper(array, i, p);
				i = p;
				p = (i-1)/2;
			}
			else break; 
		}
	}
}
void insert(customer *array, int *pn, customer x) {
	customer *last = array+(*pn);
	last = new customer;
	int i = (*pn);
	array[i].c = LLONG_MAX;
	array[i].o = LLONG_MAX;
	
	decreaseKey(array, i, x);
	*pn = *pn+1;
}

customer extractMin(customer *array, int *pn) {
	customer min = array[0];
	array[0] = array[*pn-1];
	(*pn)--;
	minHeapify(array, *pn, 0);
	return min;
}

void print(customer *array, int n) {
	for (int i = 0; i < n; i++) {
		cout << array[i].o << " " << array[i].c << "	";
	}
	cout << endl;
}
void partition(customer *array, int l, int u, int *p) {
	customer pivot = array[*p];
	swapper(array, l, *p);
	int down = l;
	while (l < u) {
		while (array[l].o <= pivot.o && l < u) l++;
		while (array[u].o > pivot.o) u--;
		if (l < u) {
			swapper(array, l, u);
		}
	}
	swapper(array, down, u);
	*p = u;
}
// quickSort sorts the integer array in ascending order with orden nlogn
void quickSort(customer *array, int l, int u) {
	if (l < u) {
		int p = (u+l)/2; // randomly selecting middle element as pivot
		partition(array, l, u, &p);
		quickSort(array, l, p-1);
		quickSort(array, p+1, u);
	}
}

int main() {
	int n;
	cin >> n;

	customer in_array[n];
	for (int i = 0; i < n; i++) {
		cin >> in_array[i].o >> in_array[i].c;
	}
	print(in_array, n);
	quickSort(in_array, 0, n-1);
	print(in_array, n);

	customer serve_array[n];
	int i = 0, j = i+1;
	long long int time_elapsed = 0, total_wait_time = 0;
	serve_array[i] = in_array[i]; 
	customer priority_queue[n]; int l = 0;
	do {
		if (time_elapsed > serve_array[i].o) time_elapsed += serve_array[i].c;
		else time_elapsed = serve_array[i].o + serve_array[i].c;

		total_wait_time += (time_elapsed - serve_array[i].o);
	
		while (j < n && in_array[j].o <= time_elapsed) {
			priority_queue[l++] = in_array[j];
			j++;
		}
		buildMinHeap(priority_queue, l);
		// print(priority_queue, l);
		i++;
		if (l > 0) serve_array[i] = extractMin(priority_queue, &l);
		// else {
		// 	serve_array[i] = array[i];
		// 	time_elapsed = array[i].c;
		// } 
	}while (i < n);
	print(serve_array, n);

	cout << (total_wait_time/n) << endl;
}