// 160101048_OA6_1.cpp: Nitin Kedia
// Description: To find whether there exists a alphabetic
// sequence such that each given word is a non-decreasing
// subsequence of it.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// utility function for printing 2D array
void print(int *half_matrix[26]) {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < i; j++) {
			cout << setw(2) << half_matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
bool checker_helper(int *half_matrix[26], int a, int b) {
	// checking that half_matrix[a][b]=0 or half_matrix[b][a]=1 whichever is present in the half_matrix
	if (a > b) {
		if (half_matrix[a][b] == 1) {
			//print(half_matrix);
			return false;
		}
		else half_matrix[a][b] = 0;
	}
	else if (a < b) {
		if (half_matrix[b][a] == 0) {
			//print(half_matrix);
			return false;
		}
		else half_matrix[b][a] = 1; 
	}
	return true;
}

bool checker(int *half_matrix[26], int a, int b) { // input is given that position of char a is less than char b, also a != b,
	// Part 1: char(a) < char(b), this data should be verified from half-half_matrix
	if (!(checker_helper(half_matrix, a, b))) return false;
	// Part 2: char(a) < char(b) and if char(i) < char(a) => char(i) < char(b) , for every i, check for contradiction
	for (int i = 0; i < 26; i++) {
		if (a > i) {
			if (half_matrix[a][i] == 1) {
				 if (!(checker_helper(half_matrix, i, b))) return false;
			}
		}
		else if (a < i) {
			if (half_matrix[i][a] == 0) {
				if (!(checker_helper(half_matrix, i ,b))) return false;
			}
		}
	}
	// Part 3: char(b) > char(a) and if char(i) > char(b) => char(i) > char(a) , for every i, check for contradiction
	for (int i = 0; i < 26; i++) {
		if (b > i) {
			if (half_matrix[b][i] == 0) {
				if (!(checker_helper(half_matrix, a, i))) return false;
			}
		}
		else if (b < i) {
			if (half_matrix[i][b] == 1) {
				if (!(checker_helper(half_matrix, a, i))) return false;
			}
		}
	}
	// print(half_matrix);
	return true; // if all test passed, data till now is valid
 }

int main() {
	int n;
	cin >> n;
	// half_matrix stores the relationship between two alphabets, 
	// for (int a < int b), half_matrix[a][b] = 1 if char(a) > char(b), 0 if char(a) < char(b), -1 if no information or char(a) == char(b)
	// else same info is stored in matrix[b][a], this removes redundancy
	int *half_matrix[26];
	for (int i = 0; i < 26; i++) {
		half_matrix[i] = new int[i];
		for (int j = 0; j < i; j++) {
			half_matrix[i][j] = -1;
		}
	}
	char word[101];
	for (int i = 0; i < n; i++) {
		scanf("%s", word);
		for (int j = 0; word[j] != '\0'; j++) {
			for (int k = 0; k < j; k++) {
				if (word[k] != word[j]) { // contradiction can only occur for different alphabets
					if (!(checker(half_matrix, word[k]-'a', word[j]-'a'))) { // no sequence can exist if we get even one contardiction
						cout << "Impossible" << endl;
						return 0;
 					}
				}
			}
		}
	}
	cout << "Possible" << endl; // All relationships can co-exist without any contradictions 
	return 0;
}