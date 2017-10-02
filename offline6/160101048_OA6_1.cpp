// 160101048_OA6_1.cpp: Nitin Kedia
// Description: To find whether there exists a alphabetic
// sequence such that each given word is a non-decreasing
// subsequence of it.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


bool insert(char *array, char c) {
	int i = 0;
	while (array[i] != '\0') {
		if (array[i++] == c) return false;
	}
	if (array[i] == '\0') {
		array[i] = c;
		array[i+1] = '\0';
		return true;
	}
}

bool find_conflict_helper(char before[26][25], char c, char *well) {
	int i = c-'a';
	int j = 0;
	while (before[i][j] != '\0') {
		if (!(insert(well, before[i][j]))) return true;
		find_conflict_helper(before, before[i][j], well);
		j++;
	}
	if (before[i][j] == '\0') {
		int k = 0;
		while (well[k] != '\0') k++;
		if (k > 0) well[--k] = '\0';
	}
}

bool find_conflict(char before[26][25]) {
	for (int i = 0; i < 26; i++) {
		char well[100];
		well[0] = '\0';
		if (find_conflict_helper(before, 'a'+i, well)) return true;
	}
	return false;
}

int main() {
	int n;
	cin >> n;
	// scan and store the words in a 2D array
	char words[n][100];
	for (int i = 0; i < n; i++) {
		scanf("%s", words[i]);
	}

	char before[26][25];
	for (int i = 0; i < 26; i++) {
		before[i][0] = '\0';
	}

	for (int i = 0; i < n; i++) {
		int l = strlen(words[i]);
		for (int j = 0; j < l; j++) {
			for (int k = 0; k < j; k++) {
				if (words[i][j] != words[i][k]) {
					insert(before[words[i][j]-'a'], words[i][k]);
				}
			}
		}
	}
	if (find_conflict(before)) cout << "Impossible" << endl;
	else cout << "Possible" << endl;
	return 0;
}