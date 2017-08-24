// 160101048_3_2.cpp: Nitin Kedia
// Description: Determine if the jungle is good or bad

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// printJungle prints the jungle
void printJungle(char **jungle, int row, int column) {
	cout << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << jungle[i][j];
		}
		cout << endl; 
	}
}


// checkBoundary returns number of 'L' present in boundary;
int checkBoundary(char **jungle, int row, int column, int boundaryL[2][2]) {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (jungle[i][j] == 'L') {
				if (i == 0 || i == row-1) {
					boundaryL[count%2][0] = i;
					boundaryL[count%2][1] = j;
					count++;
				}
				else if (j == 0 || j == column-1) {
					boundaryL[count%2][0] = i;
					boundaryL[count%2][1] = j;
					count++;
				}
			}
		}
	}
	return count;
}

int findPath(char **jungle, int row, int column, int i, int j, int prevI, int prevJ, int exitI, int exitJ, int *path) {
	if (jungle[i][j] == 'L') jungle[i][j] = 'M';
	else if (jungle[i][j] == 'M') jungle[i][j] = 'T';	

	if (i == exitI && j == exitJ) {
		(*path)++;
		return 0;
	}
	if (i > 0) {
		if (i-1 == prevI && j == prevJ) {
			// do not return to parent
		}
		else if (jungle[i-1][j] != 'T') {
			findPath(jungle, row, column, i-1, j, i, j, exitI, exitJ, path);
		}
	}
	if (j > 0) {
		if (i == prevI && j-1 == prevJ) {
			// do not return to parent
		}
		else if (jungle[i][j-1] != 'T') {
			findPath(jungle, row, column, i, j-1, i, j, exitI, exitJ, path);
		}
	}
	if (i < row-1) {
		if (i+1 == prevI && j == prevJ) {
			// do not return to parent
		}
		else if (jungle[i+1][j] != 'T') {
			findPath(jungle, row, column, i+1, j, i, j, exitI, exitJ, path);
		}
	}

	if (j < column-1) {
		if (i == prevI && j+1 == prevJ) {
			// do not return to parent
		}
		else if (jungle[i][j+1] != 'T') {
			findPath(jungle, row, column, i, j+1, i, j, exitI, exitJ, path);
		}
	}
	return 0;
}

int main() {
	while(1) { // for repititive input of jungles (matrices)
		int row, column;
		cout << "Enter row and column: ";
		cin >> row >> column;
		
		if (row == 0 && column == 0) break; // end of input
		else if (row == 0 || column == 0) continue; // invalid input

		// jungle is stored in a 2D-Array of characters
		char **jungle = new char *[row];
		for (int i = 0; i < row; i++) {
			jungle[i] = new char[column];
			for (int j = 0; j < column; j++) {
				cin >> jungle[i][j];
			}
		}
		//printJungle(jungle, row, column);
		int boundaryL[2][2];
		//cout << checkBoundary(jungle, row, column, boundaryL) << " boundary L present." << endl;
		if (checkBoundary(jungle, row, column, boundaryL) == 2) { 
			int path = 0;
			findPath(jungle, row, column, boundaryL[0][0], boundaryL[0][1], row, column, boundaryL[1][0],boundaryL[1][1], &path);
			if (path == 1) {
				cout << "Submitted!" << endl;
			}
			else {
				cout << "Bad Luck!" << endl;	
			}
		}
		else cout << "Bad Luck!" << endl;
	}
}
