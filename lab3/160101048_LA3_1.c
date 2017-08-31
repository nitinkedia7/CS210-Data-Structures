#include <stdio.h>
#include <stdlib.h>

// printArray prints first n elements of input interger array
void printArray(int *array, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

// all sort functions sort in ascending order
// also in each sort function, input array is copied and then processed so as not to change the original input array

// bubbleSort0 is a simple implementation of bubble sort algorithm
int bubbleSort0(int *array, int n) {
	int array0[n]; // array copier
	int k;
	for (k = 0; k < n; k++) {
		array0[k] = array[k];
	}
	int i, j;
	for (i = 0; i < n-1; i++) {
		for( j = 0; j < n-1-i; j++) {
			if (array0[j] > array0[j+1]) {
				int temp = array0[j+1];
				array0[j+1] = array0[j];
				array0[j] = temp;
			}
		}
	}
	printf("%d\n", i);
	printArray(array0, n);
	return i; // returning number of outer loop iterations
}

// bubbleSort1 is bubbleSort0 with shredded unneccessary outer loop iterations
void bubbleSort1(int *array, int n, int loop) {
	int array1[n];
	int k;
	for (k = 0; k < n; k++) {
		array1[k] = array[k];
	}
	
	int i, j;
	for (i = 0; i < n-1; i++) {
		int isSwap = 0;
		for( j = 0; j < n-1-i; j++) {
			if (array1[j] > array1[j+1]) {
				int temp = array1[j+1];
				array1[j+1] = array1[j];
				array1[j] = temp;
				isSwap++;
			}
		}
		if (isSwap == 0) break;
	}
	if (i > 0) loop = loop-i-1; // loop now represents difference of iterations between improvement1 and simple bubblesort
	printf("%d\n", loop);
	printArray(array1, n);
}
 
// bubbleSort2 is final improvement over buubleSort1 with opposite successive passes
void bubbleSort2(int *array, int n, int loop) {
	int array2[n];
	int k;
	for (k = 0; k < n; k++) {
		array2[k] = array[k];
	}
	
	int i, j, l;
	for (i = 0; i < n-1; i++) {
		int isSwap = 0;
		if (i%2 == 0) {
			for (j=(i/2); j<n-1-(i/2); j++) {
				if (array2[j] > array2[j+1]) {
					int temp = array2[j];
					array2[j] = array2[j+1];
					array2[j+1] = temp;
					isSwap++;
				}
			}
			if (isSwap == 0) break;
		}
		else {
			for (l = n-2-(i/2); l > (i/2); l--) {
				if (array2[l] < array2[l-1]) {
					int temp = array2[l];
					array2[l] = array2[l-1];
					array2[l-1] = temp;
					isSwap++;
				}
			}
		}
		if (isSwap == 0) break;
	}
	if (i>0) loop = loop-i-1;// loop now represents difference of iterations between improvement2 and simple bubblesort
	printf("%d\n", loop);
	printArray(array2, n);
}

// Input logic is embedded in main()
void main() {
	int n;
	scanf("%d", &n);
	if (n > 0) {
		int array[n];
		int i;
		for (i = 0; i < n; i++) {
			scanf("%d", &array[i]);
		}
		int outerLoop = bubbleSort0(array, n); // simple bubbleSort
		bubbleSort1(array, n, outerLoop); // improvement 1
		bubbleSort2(array, n, outerLoop); // improvement 2
	}
	else printf("Input sequence must have atleast one element.\n");
}