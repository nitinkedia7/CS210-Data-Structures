// 160101048_OA6_1.cpp: Nitin Kedia
// Description: To find whether there exists a alphabetic
// sequence such that each given word is a non-decreasing
// subsequence of it.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// utility function for printing 2D array
void print(int matrix[26][26]) {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			cout << setw(2) << matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

bool checker(int matrix[26][26], int a, int b) { // input is given that position of char a is less than char b, also a != b,
	// Part 1: a < b => matrix[a][b] must be set to 0, if previously it was 1 then it's a contradiction
	if (matrix[a][b] == 1) {
		// print(matrix);
		return false;
	}
	else matrix[a][b] = 0;
	
	// Part 2: b > a => matrix[b][a] must be set to 1, if previously it was 0 then it's a contradiction
	if (matrix[b][a] == 0) {
		// print(matrix);
		return false;
	}
	else matrix[b][a] = 1; 
	
	// Part 3: a < b and if (i < a) => i < b , for every i, check for contradiction
	for (int i = 0; i < 26; i++) {
		if (matrix[a][i] == 1) {
			if (matrix[b][i] == 0) {
				// print(matrix);
				return false;
			}
			else matrix[b][i] = 1;
		}
	}
	
	// Part 4: b > a and if (i > b) => i > a, for every i, check for contradiction
	for (int i = 0; i < 26; i++) {
		if (matrix[b][i] == 0) {
			if (matrix[a][i] == 1) {
				// print(matrix);
				return false;
			}
			else matrix[a][i] = 0;
		}
	}
	// print(matrix);
	return true; // if all test passed, data till now is valid
 }

int main() {
	int n;
	cin >> n;
	// matrix stores the relationship between two alphabets, matrix[a][b] = 1 if a > b, 0 if a < b, -1 if no information or a == b
	int matrix[26][26];
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			matrix[i][j] = -1;
		}
	}
	char word[101];
	for (int i = 0; i < n; i++) {
		scanf("%s", word);
		for (int j = 0; word[j] != '\0'; j++) {
			for (int k = 0; k < j; k++) {
				if (word[k] != word[j]) { // contradiction can only occur for different alphabets
					if (!(checker(matrix, word[k]-'a', word[j]-'a'))) { // no sequence can exist if we get even one contardiction
						cout << "Impossible" << endl;
						return 0;
 					}
				}
			}
		}
	}
	// print(matrix);
	cout << "Possible" << endl; // All relationships can co-exist without any contradictions 
	return 0;
}