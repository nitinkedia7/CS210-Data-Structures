#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	
	cout << 'c' << endl;
	cout << '+' << endl;
	
	srand(time(NULL));
	int arg;
	for (int i = 0; i < n; i++) {
		arg = rand() % 1000*n + 1;
		cout << "i " << arg << endl;
	}
	for (int i = 0; i < n+2; i++) {
		if (i%(n/10) == 0) cout << 'S' << endl;
		cout << 'e' << endl; 
	}
}