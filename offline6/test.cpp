// 160101048_OA6_1.cpp: Nitin Kedia
// Description: To find whether there exists a alphabetic
// sequence such that each given word is a non-decreasing
// subsequence of it.

// Example - ab bc ca
// a > {c}
// b > {a}
// c > {b}
// Now we find a > c & c > b & b > a, we arrive at a previous letter hence Impossible

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// insert function inserts a char to a character array and returns true, only if the new char wasn't present before
bool insert(char *array, char c) {
	int i = 0;
	while (array[i] != '\0') {
		if (array[i++] == c) return false;
	}
	array[i] = c;
	array[i+1] = '\0';
	return true;
}

// find_conflict_helper recursively goes inside the list of char that are less than the given char till it reaches the least character or if it reaches
// a previous character, we arrive at a contradiction
bool find_conflict_helper(char d_table[26][25], char c, char *d_seq) {
	int i = c-'a';
	int j = 0;
	while (d_table[i][j] != '\0') {
		if (!(insert(d_seq, d_table[i][j]))) return true;
		find_conflict_helper(d_table, d_table[i][j], d_seq);
		j++;
	}
	int k = 0;
	while (d_seq[k] != '\0') k++;
	if (k > 0) d_seq[--k] = '\0';
	else return false;
}
// driver function for find_conflict_helper
bool find_conflict(char d_table[26][25]) {
	for (int i = 0; i < 26; i++) {
		char d_seq[100];
		d_seq[0] = '\0';
		if (find_conflict_helper(d_table, 'a'+i, d_seq)) return true;
	}
	return false;
}

int main() {
	int n;
	cin >> n;
	// parse the words to build the list of character(s) lesser than a given character for all characters
	char d_table[26][25];
	for (int i = 0; i < 26; i++) d_table[i][0] = '\0';
	
	char word[101];
	for (int i = 0; i < n; i++) {
		scanf("%s", word);
		for (int j = 0; word[j] != '\0'; j++) {
			for (int k = 0; k < j; k++) {
				if (word[j] != word[k]) {
					insert(d_table[word[j]-'a'], word[k]);
				}
			}
		}
	}

	if (find_conflict(d_table)) cout << "Impossible" << endl;
	else cout << "Possible" << endl;
	return 0;
}