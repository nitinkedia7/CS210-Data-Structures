// 160101048_OA6_2.cpp: Nitin Kedia
// Description- Minimising average cooking time by using priority queue implemented using using minHeap

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// struct for storing individual customer in_time and cooking_time
struct customer {
	long long int o;
	long long int c;
};
// findMin returns the customer who arrived earlier than the other
int findMin(customer *array, int i, int j) {
	if (array[i].c < array[j].c) return i;
	else if (array[i].c  == array[j].c) {
		if (array[i].o < array[j].o) return i;
	}
	return j;
}
/* Priority Queue subroutines start here */
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

void insert(customer *array, int *pn, customer x) {
	int i = (*pn);
	array[i] = x;
	int p = (i-1)/2;
	while (p >= 0) {
		if (i != p && i == findMin(array, i, p))  {
			swap(array[i], array[p]);
			i = p;
			p = (i-1)/2;
		}
		else break;
	}
	(*pn)++;
}

customer extractMin(customer *array, int *pn) {
	customer min = array[0];
	array[0] = array[*pn-1];
	
	minHeapify(array, --(*pn), 0);
	return min;
}
/* Priority Queue subroutines ends here */

void print(customer *array, int n) {
	for (int i = 0; i < n; i++) {
		cout << array[i].o << " " << array[i].c << "	";
	}
	cout << endl;
}
/* Quicksort subroutines start here */
void partition(customer *array, int l, int u, int *p) {
	customer pivot = array[*p];
	swap(array[l], array[*p]);
	int down = l;
	while (l < u) {
		while (array[l].o <= pivot.o && l < u) l++;
		while (array[u].o > pivot.o) u--;
		if (l < u) {
			swap(array[l], array[u]);
		}
	}
	swap(array[down], array[u]);
	*p = u;
}
// quickSort sorts customers by in_time
void quickSort(customer *array, int l, int u) {
	if (l < u) {
		int p = (u+l)/2; // randomly selecting middle element as pivot
		partition(array, l, u, &p);
		quickSort(array, l, p-1);
		quickSort(array, p+1, u);
	}
}
/* Quicksort subroutines end here */

int main() {
	int n;
	cout << "Enter Input: " << endl;
	cin >> n;
	if (n <= 0) return 0;

	customer in_array[n]; // scanning incoming customers
	for (int i = 0; i < n; i++) {
		cin >> in_array[i].o >> in_array[i].c;
	}
	quickSort(in_array, 0, n-1); // sorting customers by in_time

	int i = 0, j = i+1;
	long long int current_time = 0, wait_time = 0;

	customer serve_array[n];
	serve_array[i] = in_array[i]; // serve_array maintains customers by the order in which they were served

	customer priority_queue[n]; int l = 0; // initialising an empty priority queue

	// order i'th customer in serve_array is being cooked,
	// we insert all customers who arrive before this order will be cooked in a priority queue
	// now the extractMin customer is the choice for minimising total average waiting time
	// repeat, but if a customer arrives at a time when no cake is being cooked, the cycle essentially starts again;  
	do {
		if (current_time > serve_array[i].o) current_time += serve_array[i].c;
		else current_time = serve_array[i].o + serve_array[i].c;

		wait_time += (current_time - serve_array[i].o);

		while (j < n && in_array[j].o <= current_time) {
			insert(priority_queue, &l, in_array[j++]);
		}		
		
		i++;
		if (l > 0) serve_array[i] = extractMin(priority_queue, &l);
		else {
			serve_array[i] = in_array[i];
			j = i+1;
		}
	} while (i < n);

	cout << "Minimum average waiting time:" << endl;
	long long int avg_wait_time = (wait_time/n);
	cout << avg_wait_time << endl;
	return 0;
}