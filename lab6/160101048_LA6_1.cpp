#include <bits/stdc++.h>
using namespace std;

int hash_primary(int k, int m) {
	return k%m;
}

int hash_sec(int k, int m) {
	int hk = k % (m-1);
	return hk+1;
}

int hash_linear(int k, int m, int i) {
	int hk = hash_primary(k, m);
	return hash_primary(hk+i, m);
}

int hash_quad(int k, int m, int i) {
	int hk = hash_primary(k, m);
	return hash_primary(hk + i + 3*i*i, m);
}

int hash_double(int k, int m, int i) {
	int hk = hash_primary(k, m) + i * hash_sec(k, m);
	return hk%m;
}

int insert_linear(int *table, int m, int k, int *l) {
	int i = 0;
	do {
		int j = hash_linear(k, m, i);
		(*l)++;
		if (table[j] == 0 || table[j] == -1) {
			table[j] = k;
			cout << k << " INSERTED AT INDEX " << j << " IN LINEAR PROBING" << endl;
			return 1;
		}
		else i++;
	} while (i < m);
	if (i == m) {
		cout << k << " CANNOT BE INSERTED IN LINEAR PROBING" << endl;
	}
	return 0;
}

int insert_quad(int *table, int m, int k, int *q) {
	int i = 0;
	do {
		int j = hash_quad(k, m, i);
		(*q)++;
		if (table[j] == 0 || table[j] == -1) {
			table[j] = k;
			cout << k << " INSERTED AT INDEX " << j << " IN QUADRATIC PROBING" << endl;
			return 1;
		}
		else i++;
	} while (i < m);
	if (i == m) {
		cout << k << " CANNOT BE INSERTED IN QUADRATIC PROBING" << endl;
	}
	return 0;
}

int insert_double(int *table, int m, int k, int *d) {
	int i = 0;
	do {
		int j = hash_double(k, m, i);
		(*d)++;
		if (table[j] == 0 || table[j] == -1) {
			table[j] = k;
			cout << k << " INSERTED AT INDEX " << j << " IN DOUBLE HASHING" << endl;
			return 1;
		}
		else i++;
	} while (i < m);
	if (i == m) {
		cout << k << " CANNOT BE INSERTED IN DOUBLE HASHING" << endl;
	}
	return 0;
}

int search_linear(int *table, int k, int m) {
	int i = 0;
	int j = 0;
	do {
		j = hash_linear(k, m, i);
		if (table[j] == k) {
			return j;
		}
		else i++;
	} while (table[j] != 0 && i < m);
	return -1;
}

int search_quad(int *table, int k, int m) {
	int i = 0;
	int j = 0;
	do {
		j = hash_quad(k, m, i);
		if (table[j] == k) {
			return j;
		}
		else i++;
	} while (table[j] != 0 && i < m);
	return -1;
}

int search_double(int *table, int k, int m) {
	int i = 0;
	int j = 0;
	do {
		j = hash_double(k, m, i);
		if (table[j] == k) {
			return j;
		}
		else i++;
	} while (table[j] != 0 && i < m);
	return -1;
}

void delete_linear(int *table, int k, int m) {
	int j = search_linear(table, k, m);
	if (j != 0) {
		table[j] = -1;
		cout << k << " IS DELETED FROM INDEX " << j << " IN LINEAR PROBING" << endl;
	}
	else {
		cout << k << " CANNOT BE DELETED IN LINEAR PROBING";
	}
}


void delete_quad(int *table, int k, int m) {
	int j = search_quad(table, k, m);
	if (j != 0) {
		table[j] = -1;
		cout << k << " IS DELETED FROM INDEX " << j << " QUADRATIC PROBING" << endl;
	}
	else {
		cout << k << " CANNOT BE DELETED IN QUADRATIC PROBING";
	}
}

void delete_double(int *table, int k, int m) {
	int j = search_double(table, k, m);
	if (j != 0) {
		table[j] = -1;
		cout << k << " IS DELETED FROM INDEX " << j << " IN DOUBLE HASHING" << endl;
	}
	else {
		cout << k << " CANNOT BE DELETED IN DOUBLE HASHING";
	}
}

void search(int *linear_table, int *quad_table, int *double_table, int k , int m) {
	int a = search_linear(linear_table, k, m);
	int b = search_quad(quad_table, k, m);
	int c = search_double(double_table, k, m);

	if (a != -1) {
		cout << k << " FOUND AT INDEX " << a << " IN LINEAR PROBING" << endl;
	}
	else cout << k << " IS NOT PRESENT IN LINEAR PROBING";

	if (b != -1) {
		cout << k << " FOUND AT INDEX " << b << " IN QADRATIC PROBING" << endl;
	}
	else {
		cout << k << " IS NOT PRESENT IN QUADRATIC PROBING";
	}

	if (c != -1) {
		cout << k << " FOUND AT INDEX " << c << " IN DOUBLE HASHING" << endl;
	}
	else {
		cout << k << " IS NOT PRESENT IN DOUBLE HASHING";
	}
}

int main() {
	int n, m;
	cin >> n >> m;

	int linear_table[m];
	int quad_table[m];
	int double_table[m];

	for (int i = 0; i < m; i++) {
		linear_table[i] = 0;
		quad_table[i] = 0;
		double_table[i]= 0;
	}

	int l = 0, q = 0, d = 0;
	int ins = 0;
	int li = 0, qi = 0, di = 0;   
	for (int i = 0; i < n; i++) {
		string cmd;
		int arg;
		cin >> cmd >> arg;
		if (cmd == "INSERT") {
			// call three insert fn
			li += insert_linear(linear_table, m, arg, &l);
			qi += insert_quad(quad_table, m, arg, &q);
			di += insert_double(double_table, m, arg, &d);
			ins++;
		}
		else if (cmd == "SEARCH") {
			// call the search function
			search(linear_table, quad_table, double_table, arg, m);
		}
		else if (cmd == "DELETE") {
			// call three delete function
			delete_linear(linear_table, arg, m);
			delete_quad(quad_table, arg, m);
			delete_double(double_table, arg, m);			
		}
	}
	printf("TOTAL NUMBER IN COLLISIONS IN LINEAR PROBING %d\n", l-li);
	printf("TOTAL NUMBER IN COLLISIONS IN QUADRATIC PROBING %d\n", q-qi);
	printf("TOTAL NUMBER IN COLLISIONS IN DOUBLE HASHING %d\n", d-di);
	// cout << l << endl;
	// cout << q << endl;
	// cout << d << endl;
	float cl = (l-li);
	float cq = (q-qi);
	float cd = (d-di);

	float rl = cl/ins;
	float rq = cq/ins;
	float rd = cd/ins;
	printf("AVERAGE NUMBER OF REHASHING REQUIRED IS %.2f IN LINEAR PROBING\n", rl);
	printf("AVERAGE NUMBER OF REHASHING REQUIRED IS %.2f IN QUADRATIC PROBING\n", rq);
	printf("AVERAGE NUMBER OF REHASHING REQUIRED IS %.2f DOUBLE HASHING\n", rd);
	return 0;
}