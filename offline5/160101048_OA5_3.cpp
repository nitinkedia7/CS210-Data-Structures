// 160101048_OA5_3.cpp: Nitin Kedia
// Description- Make it to Work

#include <iostream>

using namespace std;

// town is a structure for each town containing number of employees from that town and array of their cars;
struct town {
	int e;
	int *p;
};

town *createTown(int E) {
	town *head = new town;
	head->e = 0;
	head->p = new int[E]; // no town has cars greater than total number of employees, so E is an upper bound to number of cars;
}

// countingSort is used because 0 <= P <= 6;
void countingSort(int *p, int e) {
	int count[7] = {0};
	for (int i = 0; i < e; i++) {
		count[p[i]]++;
	}
	for (int i = 1; i < 7; i++) {
		count[i] += count[i-1];
	}
	int sortedP[e];
	for (int i = e-1; i > -1; i--) {
		sortedP[count[p[i]]-1] = p[i];
		count[p[i]]--;
	}
	for (int i = 0; i < e; i++) {
		p[i] = sortedP[i];
	}
}

// cars function returns 0 if IMPOSSIBLE, else 1; 
int cars(town **array, int N, int T, int *nCar) {
	for (int i = 1; i <=N; i++) {
		if (i == T) nCar[T] = 0; // no car is required from the town where office is located
		else {
			// for minimum number of cars from each town, large cars have to be filled first, hence the sort by capacity
			countingSort(array[i]->p, array[i]->e);
			
			for (int j = array[i]->e-1; j > -1; j--) { // starting from largest car
				if (array[i]->e > 0) { // if there are employees to be taken use the car, increment number of cars from that town
					nCar[i]++;
					array[i]->e -= array[i]->p[j]; /// update number of remaining employees
				}
			}
			if (array[i]->e > 0) return 0; // insufficient number of cars as some employees are left behind
		}
	}
	return 1; // all employees reach office
}

// Input logic is embedded in main() and processing is done by other functions
int main() {
	cout << "Enter input:" << endl;
	int N, T, E;
	cin >> N >> T >> E; // total number of towns, office Town, total number of employees

	town *array[N+1] = {NULL}; // i'th element of array points to node of i'th town 
	for (int i = 1; i <=N; i++) array[i] = createTown(E);

	for (int i = 0; i < E; i++) { // employee details
		int H, P;
		cin >> H >> P;
		(array[H]->p)[array[H]->e] = P; // updating passenger capacity  of e'th employee 
		array[H]->e += 1;
	}

	int nCar[N+1] = {0}; // nCar stores minimum number of cars from each town;
	// print output based on response from cars function
	if (cars(array, N, T, nCar) == 0) cout << "IMPOSSIBLE" << endl;
	else {
		for (int i = 1; i <= N; i++) cout << nCar[i] << " "; 
		cout << endl;	
	}
}