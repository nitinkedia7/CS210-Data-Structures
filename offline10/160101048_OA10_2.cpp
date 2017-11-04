// 160101048_OA10_1.cpp: Nitin Kedia
// Description: Delete all instances of a pattern in a string

#include <iostream>
using namespace std;

int hash_substring(string s) {
	int h = (s[0] - 'a') % 23;
	for (int i = 1; i < s.length(); i++) {
		h = (h * 26 + (s[i] - 'a')) % 23;
	}
	return h;
}

void hash_string(string s, int *hash, int l) {
	hash[0] = hash_substring(s.substr(0,l));

	int power = 1;
	for (int i = 0; i < l; i++) {
		power = (power * 26 ) % 23;
	}

	for (int i = 1; i < s.length()-l+1; i++) {
		hash[i] = (hash[i-1] * 26 + (s[i+l-1] - 'a')) % 23;
		int old_a =  ((s[i-1] - 'a') * power) % 23;
		hash[i] = (hash[i] - old_a + 23) % 23;
	}
}

bool match_string(string s, int hash_s, string p, int hash_p) {
	cout << s << " " << hash_s << " " << p << " " << hash_p << endl;
	if (hash_s == hash_p) {
		if (s == p) return true;
	}
	return false;
}

bool delete_pattern(string s, string p) {
	string ns = s;
	int lp = p.length();
	int hash_p = hash_substring(p);

	do {
		s = ns;
		int ls = s.length();

		int hash[ls];
		hash_string(s, hash, lp);

		ns = "";
		for (int j = 0; j < ls; j++) {
			if (j < ls-lp+1) {
				if (match_string(s.substr(j,lp), hash[j], p, hash_p)) {
					j = j + lp - 1; 
				}
				else {
					ns = ns + s[j];
				}
			}
			else ns = ns + s[j];
		}
		// cout << s << " " << p << " " << ns << endl;
	} while (ns != s && s.length() >= lp);
	cout << ns << endl;
}

int main() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		string s, p;
		cin >> s >> p;
		// cout << s << " " << p;
		delete_pattern(s, p);
	}
}