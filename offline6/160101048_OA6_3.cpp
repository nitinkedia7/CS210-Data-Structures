// 160101048_OA6_3.cpp: Nitin Kedia
// Description: Find minimum number of steps in corrected sequence

#include <iostream>
using namespace std;

const int MAX_SIZE = 1000;

struct node {
	string cmd;
	int arg;
};

int findMin(int *array, int i, int j) {
	if (array[i] < array[j]) return i;
	else return j;
}

void min_heapify(int *min_heap, int i, int n) {
	if (n >= 2*i+2) {
		int k = -1;
		if (n == (2*i+2)) {
			k = findMin(min_heap, i, 2*i+1);
		}
		else {
			k = findMin(min_heap, i, findMin(min_heap, 2*i+1, 2*i+2));
		}
		if (k != i && k != -1) {
			swap(min_heap[i], min_heap[k]);
			min_heapify(min_heap, k, n);
		}
	}
}

int remove_min(int *min_heap, int *pn) {
	int min = min_heap[0];
	min_heap[0] = min_heap[(*pn)-1];
	min_heapify(min_heap, 0, --(*pn));
	return min;
}

void insert(int *min_heap, int *pn, int arg) {
	int i = (*pn)++;
	min_heap[i] = arg;
	int p = (i-1)/2;
	while (p >= 0 && min_heap[i] < min_heap[p]) {
		swap(min_heap[i], min_heap[p]);
		i = p;
		p = (i-1)/2;
	}
}

void print_seq(node *seq, int n) {
	for (int i = 0; i < n; i++) {
		cout << seq[i].cmd << " ";
		if (seq[i].cmd != "removeMin") cout << seq[i].arg;
		cout << endl; 
	}
}

void find_output_seq(node *i_seq, int i, int n, int *min_heap, int *pl, node *o_seq, int *po) {
	if (i < n) {
		if (i_seq[i].cmd == "insert")  {
			insert(min_heap, pl, i_seq[i].arg);
			o_seq[(*po)].cmd = "insert";
			o_seq[(*po)++].arg = i_seq[i].arg;
		}
		else if (i_seq[i].cmd == "getMin") {
			while ((*pl) >= 0) {
				if ((*pl) == 0) {
					insert(min_heap, pl, i_seq[i].arg);
					o_seq[(*po)].cmd = "insert";
					o_seq[(*po)++].arg = i_seq[i].arg;
				}
				if (i_seq[i].arg == min_heap[0]) {
					o_seq[(*po)].cmd = "getMin";
					o_seq[(*po)++].arg = i_seq[i].arg;
					break;
				}
				else {
					int min = remove_min(min_heap, pl);
					o_seq[(*po)].cmd = "removeMin";
					o_seq[(*po)++].arg = min;
				}
			}
		}
		else if (i_seq[i].cmd == "removeMin") {
			if ((*pl) == 0) {
				insert(min_heap, pl, i_seq[i].arg);
				o_seq[(*po)].cmd = "insert";
				o_seq[(*po)++].arg = i_seq[i].arg;
			}
			int min = remove_min(min_heap, pl);
			o_seq[(*po)].cmd = "removeMin";
			o_seq[(*po)++].arg = min;
		}
		find_output_seq(i_seq, i+1, n, min_heap, pl, o_seq, po);
	}
}

int main() {
	int n;
	cout << "Enter input sequence: " << endl;
	cin >> n;

	node i_seq[n];
	for (int i = 0; i < n; i++) {
		cin >> i_seq[i].cmd;
		if (i_seq[i].cmd == "removeMin") {
			i_seq[i].arg = 0;
		}
		else cin >> i_seq[i].arg; 
	}
	// print_seq(i_seq, n);
	node o_seq[MAX_SIZE];
	int o = 0;

	int min_heap[MAX_SIZE];
	int l = 0;
	
	find_output_seq(i_seq, 0, n, min_heap, &l, o_seq, &o);
	
	cout << endl << "Corrected sequence: " << endl;
	cout << o << endl;
	print_seq(o_seq, o);
}