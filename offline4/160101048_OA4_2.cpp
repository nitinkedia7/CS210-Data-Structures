// 160101048_OA1_2.cpp: Nitin Kedia
// Description: Maximum fare

#include <bits/stdc++.h>

using namespace std;

struct arrayNode { // structure for storing sparse matrix in array.
	int row, column, value;
};
struct linkedNode { // structure for storing sparse matrix as linkedlist
	int row, column, value;
	linkedNode *down, *right; // for traversal along a column/row
};

// cityIndex assigns each city name a integer index as string manipulation is difficult
int cityIndex(char **cities, int N, char *city) {
	int i;
	for (i=0; i<N; i++) {
		if (strcmp(cities[i], city) == 0) return i; // returns index of the city if it is already present in the string array
		else if (strcmp(cities[i], "\0") == 0) { 	// else add the city to the list and returns its index
			strcpy(cities[i], city);
			return i;
		}
	}
}

// createArrayNode initialises a arrayNode with its row, column and value and returns its pointer
arrayNode *createArrayNode(int row, int column, int value) {
	arrayNode *head = new arrayNode;
	head->row = row;
	head->column = column;
	head->value = value;
	return head;
}
// createLinkedNode also initialises a linkedNode with row, column and value and returns its pointer
linkedNode *createLinkedNode(int row, int column, int value) {
	linkedNode *head = new linkedNode();
	head->row = row;
	head->column = column;
	head->value = value;
	return head;
}

// buildArrayMatrix stores input distance matrix in array representation
void buildArrayMatrix(arrayNode **arrayMatrix, int R, int N, char **cities) {
	for (int i=0; i <= R; i++) {
		if (i == 0) arrayMatrix[i] = createArrayNode(N, N, R); // first node contains number of rows(N), columns(N) and non-empty entries in the matrix
		else {
			char city1[25], city2[25]; int d;
			scanf("%s %s %d", city1, city2, &d);
			int city1Index = cityIndex(cities, N, city1); // find index of the city from cities array
			int city2Index = cityIndex(cities, N, city2);
			arrayMatrix[i] = createArrayNode(city1Index, city2Index, d);
		}	
	}
}

// buildLinkedMatrix stores input fare matrix in linked list representation
void buildLinkedMatrix(linkedNode **linkedMatrix, int F, int N, char **cities) {
	for (int i=0; i<N; i++) {
		linkedMatrix[i] = createLinkedNode(-1, -1, -1); // assign arbitary row, column and values to each header element
		linkedMatrix[i]->down = linkedMatrix[i]; 	// complete circular linkage
		linkedMatrix[i]->right = linkedMatrix[i];
	}
	// scan F fare entries and insert them to the matrix
	for (int i=0; i<F; i++) {
		char city1[25], city2[25]; int f;
		scanf("%s %s %d", city1, city2, &f);
		int row = cityIndex(cities, N, city1); // find index of the city from cities array
		int column = cityIndex(cities, N, city2);

		linkedNode *temp = createLinkedNode(row, column, f);
		
		// adding new node to its respective column
		linkedNode *prevCol, *nextCol;
		prevCol = linkedMatrix[column];
		nextCol = prevCol->down;
		while (nextCol != linkedMatrix[column] && nextCol->row < row) { // navigate to required row in the column
			prevCol = nextCol;
			nextCol = nextCol->down;
		}
		prevCol->down = temp; // link the new mode in the column chain
		temp->down = nextCol;
		
		// adding new node to its respective row
		linkedNode *prevRow, *nextRow;
		prevRow = linkedMatrix[row];
		nextRow = prevRow->right;
		while (nextRow != linkedMatrix[row] && nextRow->column < column) { // navigate to required column in the row
			prevRow = nextRow;
			nextRow = nextRow->right;
		}
		prevRow->right = temp;
		temp->right = nextRow ;
	}
}

// searchFare returns the fare per km between two cities from linkedMatrix or -1 if corresponding entry is not found
int searchFare(linkedNode **linkedMatrix, int city1, int city2) {
	// assuming city1, city2 form a row, column pair
	linkedNode *temp = linkedMatrix[city1];
	do {
		if (temp->column == city2) return temp->value;;
		temp = temp->right;
	}while (temp != linkedMatrix[city1]);
	return -1;
}

int main() {
	int N, R, F;
	cout << "Enter Input:" << endl;
	cin >> N >> R >> F; // scan number of cities N, distance entries R, fare per km entries F
	if (N <= 0) return 0;

	char **cities = new char *[N]; // initialise a string array "cities" which assigns each city name an index [see cityIndex]
	for (int i=0; i<N; i++) {
		cities[i] = new char[25];
		strcpy(cities[i], "\0"); // initialise with null string
	}

	arrayNode *arrayMatrix[R+1];
	buildArrayMatrix(arrayMatrix, R, N, cities);

	linkedNode *linkedMatrix[N];
	buildLinkedMatrix(linkedMatrix, F, N, cities);

	int city1, city2, maxFare = -1;
	// take distance between city1 and city2 from arrayMatrix and find corresponding fare per km from linkedMatrix
	for (int i=1; i<=R; i++) {
		int farepkm;
		farepkm = searchFare(linkedMatrix, arrayMatrix[i]->row, arrayMatrix[i]->column);
		if (farepkm == -1) farepkm = searchFare(linkedMatrix, arrayMatrix[i]->column, arrayMatrix[i]->row);
		// eg- Delhi Dumbai in arrayMatrix and Mumbai Delhi in linkedMatrix
		if (farepkm != -1) {
			int newMaxfare = farepkm * arrayMatrix[i]->value;
			if (newMaxfare > maxFare) { // update maxFare
				maxFare = newMaxfare;
				city1 = arrayMatrix[i]->row;
				city2 = arrayMatrix[i]->column;
			}
		}
	}
	if (maxFare > -1) cout << cities[city1] << " " << cities[city2] << " " << maxFare << endl;
	else cout << "Insufficient Data" << endl;
}