// 160101048_OA10_1.cpp: Nitin Kedia
// Description: Compare substrings using hashing by Rabin Karp Algorithm

#include <iostream>
using namespace std;

void hash_value(string str, int *hash) { // for each index i calculate the hash value of the substring from 0 to i
	hash[0] = (str[0]-'a')%23;

	int i = 1;
	while (str[i] != '\0') {
		int x = str[i] - 'a';
		hash[i] = (hash[i-1] * 26 + x) % 23; // formula for calculating h,i from h,i-1
		i++;
	}
}

int hash_substring(int *array, int i, int j) { // now that hash upto each index calculated, h<i,j> can be calculated easily
	if (i > 0) {
		int a = array[i-1];
		for (int x = i; x <= j; x++) { // power calculated using loop and mod in each iteration to avoid int overflow
			a = (a * 26) % 23;
		}
		return (array[j] - a + 23) % 23;
	}
	else return array[j];
}

int main() {
	string str;
	cin >> str;

	int hash[100000]; // hash<0,i> value array
	hash_value(str, hash); 	// calculate hash<0,i>

	int q;
	cin >> q;

	for (int x = 0; x < q; x++) {
		int i, j, k , l;
		cin >> i >> j >> k >> l;
		int h1 = hash_substring(hash, i-1, j-1); // hash<i,j>
		int h2 = hash_substring(hash, k-1, l-1); // hash<k,l>

		if (h1 == h2) { // two substrings may be equal if hash value is equal, characterwise checking has to be done
			int y;
			for (y = -1; y < j-i; y++) {
				if (str[i+y] != str[k+y]) {
					cout << "NO" << endl;
					break;
				}
			}
			if (y == j-i) cout << "YES" << endl;
		}
		else { // if unequal hash value then obviously different substrings
			cout << "NO" << endl;
		}
	}
}