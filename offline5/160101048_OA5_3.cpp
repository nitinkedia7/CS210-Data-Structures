// 160101048_OA5_3.cpp: Nitin Kedia
// Description- Make it to Work

#include <iostream>

using namespace std;

struct town {
	int e;
	int *p;
};

void countingSort(int *p, int e) {
	int count[7];
	for (int i = 0; i < 7; i++) {
		count[i] = 0;
	}
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


int cars(town **array, int N, int T, int *nCar) {
	for (int i = 1; i <=N; i++) {
		if (i == T) nCar[T] = 0;
		else {
			countingSort(array[i]->p, array[i]->e);
			for (int j = array[i]->e-1; j > -1; j--) {
				if (array[i]->e > 0) {
					nCar[i]++;
					array[i]->e -= array[i]->p[j];
				}
			}
			if (array[i]->e > 0) return -1;
		}
	}
	return 0;
}

int main() {
	int N, T, E;
	cin >> N >> T >> E;

	town *array[N+1];
	for (int i = 0; i <=N; i++) {
		if (i == 0) array[i] == NULL;
		else {
			array[i] = new town;
			array[i]->e = 0;
			array[i]->p = new int[E];
		}
	}

	for (int i = 0; i < E; i++) {
		int H, P;
		cin >> H >> P;
		(array[H]->p)[array[H]->e] = P; 
		array[H]->e += 1;
	}

	int nCar[N+1];
	for (int i = 0; i <= N; i++) nCar[i] = 0;

	if (cars(array, N, T, nCar) == -1) cout << "IMPOSSIBLE" << endl;
	else {
		for (int i = 1; i <= N; i++) cout << nCar[i] << " "; 
		cout << endl;	
	}
}
