// 160101048_3_2.cpp: Nitin Kedia
// Description: Determine if the jungle is good or bad

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// printJungle prints the jungle matrice 
void printJungle(char **jungle, int row, int column) {
	cout << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << jungle[i][j];
		}
		cout << endl; 
	}
}


// checkBoundary returns number boundary L's and also gives the location of last two such L's
int checkBoundary(char **jungle, int row, int column, int boundaryL[2][2]) {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (jungle[i][j] == 'L') {
				if (i == 0 || i == row-1) { // for top and bottom row
					boundaryL[count%2][0] = i; // updating location
					boundaryL[count%2][1] = j;
					count++;
				}
				else if (j == 0 || j == column-1) { // for remaining L's in leftmost & rightmost column
					boundaryL[count%2][0] = i; // updating location
					boundaryL[count%2][1] = j;
					count++;
				}
			}
		}
	}
	return count;
}

// findPath finds the number of paths from entry to exit recursively and stores it in "path"
// Once a L element is visited it changed to M;
// Again if a M element is visited it is changed to T so that no further visits can occur
// Thus, only two visits are permitted at max, more than two visits means a loop and hence multiple paths
// immediate return to previous is not permitted
int findPath(char **jungle, int row, int column, int i, int j, int prevI, int prevJ, int exitI, int exitJ, int *path) {
	
	if (jungle[i][j] == 'L') jungle[i][j] = 'M'; // updating number of visits
	else if (jungle[i][j] == 'M') jungle[i][j] = 'T';	

	if (i == exitI && j == exitJ) { // check if exit has been reached or not
		(*path)++;
		return 0;
	}
	if (i > 0) {
		if (i-1 == prevI && j == prevJ) { // upper element
			// do not return to parent
		}
		else if (jungle[i-1][j] != 'T') {
			findPath(jungle, row, column, i-1, j, i, j, exitI, exitJ, path);
		}
	}
	if (j > 0) {
		if (i == prevI && j-1 == prevJ) { // left element 
			// do not return to parent
		}
		else if (jungle[i][j-1] != 'T') {
			findPath(jungle, row, column, i, j-1, i, j, exitI, exitJ, path);
		}
	}
	if (i < row-1) {
		if (i+1 == prevI && j == prevJ) { // downward element
			// do not return to parent
		}
		else if (jungle[i+1][j] != 'T') {
			findPath(jungle, row, column, i+1, j, i, j, exitI, exitJ, path);
		}
	}

	if (j < column-1) {
		if (i == prevI && j+1 == prevJ) { // right element
			// do not return to parent
		}
		else if (jungle[i][j+1] != 'T') {
			findPath(jungle, row, column, i, j+1, i, j, exitI, exitJ, path);
		}
	}
	return 0;
}

int main() {
	while(1) { // for consecutive input of jungles (matrices)
		int row, column;
		cout << "Enter row and column: ";
		cin >> row >> column;
		
		if (row == 0 && column == 0) break; // end of input
		else if (row == 0 || column == 0) continue; // invalid input

		// jungle is stored as a matrice in 2D-Array of characters
		char **jungle = new char *[row];
		for (int i = 0; i < row; i++) {
			jungle[i] = new char[column];
			for (int j = 0; j < column; j++) {
				cin >> jungle[i][j];
			}
		}
		//printJungle(jungle, row, column);
		int boundaryL[2][2]; // stores location of entry in first row and exit in second row, if applicable
		
		//cout << checkBoundary(jungle, row, column, boundaryL) << " boundary L present." << endl;
		if (checkBoundary(jungle, row, column, boundaryL) == 2) { 
			int path = 0;
			findPath(jungle, row, column, boundaryL[0][0], boundaryL[0][1], row, column, boundaryL[1][0],boundaryL[1][1], &path);// arbitary previous index sent
			if (path == 1) {
				cout << "Submitted!" << endl; // unique path is found
			}
			else {
				cout << "Bad Luck!" << endl;	// multiple paths are present
			}
		}
		else cout << "Bad Luck!" << endl; // number of boundary L's not equal to 2
	}
}
