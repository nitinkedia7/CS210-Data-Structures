// 160101048_OA6_2.cpp: Nitin Kedia
// Description- Minimising average cooking time by using priority queue implemented using using minHeap

#include <iostream>
#include <climits>
using namespace std;

struct customer {
	int o;
	int c;
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
	customer temp;
	temp.c = array[i].c;
	temp.o = array[i].o;
	array[i].c = array[j].c;
	array[i].o = array[j].o;
	array[j].c = temp.c;
	array[j].o = temp.o;
}

void minHeapify(customer *array, int n, int i) {
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

void buildMinHeap(customer *array, int n) {
	for (int i = n/2; i >=0; i--) {
		minHeapify(array, n, i);
	}
}

void decreaseKey(customer *array, int i, customer x) {
	if (x.c < array[i].c) {
		array[i].c = x.c;
		array[i].o = x.o;
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
	array[i].c = INT_MAX;
	array[i].o = INT_MAX;
	
	decreaseKey(array, i, x);
	*pn = *pn+1;
}

customer extractMin(customer *array, int *pn) {
	customer min = array[0];
	array[0] = array[*pn-1];
	minHeapify(array, *pn, 0);
	(*pn)--;
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

	customer array[n];
	for (int i = 0; i < n; i++) {
		cin >> array[i].o >> array[i].c;
	}
	print(array, n);
	quickSort(array, 0, n-1);
	print(array, n);

	customer serve_array[n];
	int i = 0, j = i+1;
	unsigned int time_elapsed = 0;
	serve_array[i] = array[i]; 
	customer priority_queue[n]; int l = 0;
	do {
		time_elapsed += serve_array[i].c;	
		while (j < n && array[j].o <= time_elapsed) {
			priority_queue[l++] = array[j];
			j++;
		}
		buildMinHeap(priority_queue, l);
		// print(priority_queue, l);
		i++;
		if (l > 0) serve_array[i] = extractMin(priority_queue, &l);
		else {
			serve_array[i] = array[i];
			time_elapsed = array[i].c;
		} 
	}while (i < n);
	print(serve_array, n);

	unsigned int time[n] = {serve_array[0].c};
	for (int i = 1; i < n; i++) {
		if (time[i-1] > serve_array[i].o)
		time[i] = time[i-1] + serve_array[i].c;
		else time[i] = serve_array[i].o + serve_array[i].c;
	}
	for (int i = 0; i < n; i++) {
		time[i] -= serve_array[i].o;
	}
	unsigned int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += time[i];
	}
	sum = sum/n;

	cout << sum << endl;
}