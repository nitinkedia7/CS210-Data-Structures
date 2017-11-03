// 160101048_OA10_1.cpp: Nitin Kedia
// Description: Compare substrings using hashing

#include <iostream>
#include <cmath>
using namespace std;

void hash_value(string str, int *hash) {
	hash[0] = (str[0]-'a')%23;

	int i = 1;
	while (str[i] != '\0') {
		int x = str[i] - 'a';
		hash[i] = ( hash[i-1] * 13 + x ) % 23;
		i++;
	}
}

int hash_substring(int *array, int i, int j) {
	if (i > 0) {
		int a = array[i-1];
		for (int x = i; x <= j; x++) {
			a = ( a * 13 ) % 23;
		}
		return ( array[j] - a + 23) % 23;
	}
	else return array[j];
}

int main() {
	string str;
	cin >> str;
	// process string
	int hash[100000];
	hash_value(str, hash);

	int q;
	cin >> q;

	for (int x = 0; x < q; x++) {
		int i, j, k , l;
		cin >> i >> j >> k >> l;
		int h1 = hash_substring(hash, i-1, j-1);
		int h2 = hash_substring(hash, k-1, l-1);
		// cout << h1 << " " << h2 << endl;
		if (h1 == h2) {
			int y;
			for (y = -1; y < j-i; y++) {
				if (str[i+y] != str[k+y]) {
					cout << "NO" << endl;
					break;
				}
			}
			if (y == j-i) cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
}