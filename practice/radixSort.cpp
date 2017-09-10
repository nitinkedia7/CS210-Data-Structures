#include <iostream>

using namespace std;

void countSort(int *array, int n, int p) {
	int count[10] = {0};
	for (int i = 0; i < n; i++) {
		count[(array[i]/p)%10]++;
	}
	for (int i = 1; i < 10; i++) {
		count[i] += count[i-1];
	}
	int answer[n];
	for (int i = n-1; i >= 0; i--) {
		answer[count[(array[i]/p)%10]-1] = array[i];
		count[(array[i]/p)%10]--;
	}
	for (int i = n-1; i >= 0; i--) {
		array[i] = answer[i];
	}
}

void radixSort(int *array , int n, int max) {
	for (int p = 1; max/p > 0; p *= 10) {
		countSort(array, n, p);
	}
}

int main() {
	int n;
	cin >> n;
	int array[n];
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}

	int max = array[0];
	for (int i = 1; i < n; i++) {
		if (array[i] > max) max = array[i];
	}

	radixSort(array, n, max);

	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;

}