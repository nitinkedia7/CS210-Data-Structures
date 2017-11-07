// 160101048_OA10_1.cpp: Nitin Kedia
// Description: Delete all instances of a pattern in a string using rolling hash

#include <iostream>
using namespace std;

int hash_substring(string s) { // returns hash value of a string
	int h = (s[0] - 'a') % 23;
	for (int i = 1; i < s.length(); i++) {
		h = (h * 26 + (s[i] - 'a')) % 23;
	}
	return h;
}

void hash_string(string s, int *hash, int l) { // hash all substrings of length equal to pattern length
	hash[0] = hash_substring(s.substr(0,l)); // substring of pattern length starting from 0

	int power = 1;
	for (int i = 0; i < l; i++) {
		power = (power * 26 ) % 23;
	}

	for (int i = 1; i < s.length()-l+1; i++) { // next hash values can be calculated on O(1) time using formula
		hash[i] = (hash[i-1] * 26 + (s[i+l-1] - 'a')) % 23; // add new character
		int old_a =  ((s[i-1] - 'a') * power) % 23; // old char to be deleted
		hash[i] = (hash[i] - old_a + 23) % 23; // delete old char
	}
}

bool match_string(string s, int hash_s, string p, int hash_p) { // if same hash, check each char and then return yes, otherwise no
	// cout << s << " " << hash_s << " " << p << " " << hash_p << endl;
	if (hash_s == hash_p) {
		if (s == p) return true;
	}
	return false;
}

bool delete_pattern(string s, string p) { // delete all instances of the pattern in string
	string ns = s;
	int lp = p.length();
	int hash_p = hash_substring(p); // hash value of p

	int ls = ns.length();
	int hash[ls];
	hash_string(ns, hash, lp);

	for (int j = 0; j < ns.length(); j++) { // delete pattern from string
		if (j < ns.length()-lp+1) { // atleast lp characters must remain
			if (match_string(ns.substr(j,lp), hash[j], p, hash_p)) {
				ns.erase(j, lp);

				if (ns.length() < lp) break;
				hash_string(ns, hash, lp); // rehash the deleted string

				for (int k = 0; k <= lp; k++) { // decrement j till j-lp if possible, to check newly generated instances in next iteration
					if (j-1 >= -1) j--;
					else break;
				}
			}
		}
	}
	cout << ns << endl;
}

int main() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) { // for each instance execute delete pattern
		string s, p;
		cin >> s >> p;
		// cout << s << " " << p;
		delete_pattern(s, p);
	}
}