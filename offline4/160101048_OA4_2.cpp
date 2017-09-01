// 160101048_OA1_2.cpp: Nitin Kedia
// Description: Maximum fare

#include <bits/stdc++.h>

using namespace std;

struct arrayNode {
	int row, column, value;
};
struct linkedNode {
	int row, column, value;
	linkedNode *down, *right;
};
int cityIndex(char **cities, int N, char *city) {
	int i;
	for (i=0; i<N; i++) {
		if (strcmp(cities[i], "\0") == 0) break;
		else if (strcmp(cities[i], city) == 0) return i;
	}
	strcpy(cities[i], city);
	return i;
}

arrayNode *createArrayNode(int row, int column, int value) {
	arrayNode *head = new arrayNode;
	head->row = row;
	head->column = column;
	head->value = value;
	return head;
}
linkedNode *createLinkedNode(int row, int column, int value) {
	linkedNode *head = new linkedNode();
	head->row = row;
	head->column = column;
	head->value = value;
	return head;
}

void buildLinkedMatrix(linkedNode **linkedHeads, int F, int N, char **cities) {
	for (int i=0; i<N; i++) {
		linkedHeads[i] = createLinkedNode(-1, -1, -1);
		linkedHeads[i]->down = linkedHeads[i];
		linkedHeads[i]->right = linkedHeads[i];
	}
	for (int i=0; i<N; i++) {
		printf("%s ", cities[i]);
	}printf("\n");

	for (int i=0; i<F; i++) {
		char city1[25], city2[25]; int f;
		scanf("%s %s %d", city1, city2, &f);
		int row = cityIndex(cities, N, city1);
		int column = cityIndex(cities, N, city2);
		cout << row << " " << column << " " << endl;

		linkedNode *temp = createLinkedNode(row, column, f);
		linkedNode *prev1, *next1;
		prev1 = linkedHeads[column];
		next1 = prev1->down;
		while (next1 != linkedHeads[column] && next1->row < row) {
			prev1 = next1;
			next1 = next1->down;
		}


		//cout << i << endl;
		linkedNode *prev, *next;
		prev = linkedHeads[row];
		next = prev->right;
		while (next != linkedHeads[row] && next->column < column) {
			prev = next;
			next = next->right;
		}
		prev1->down = temp;
		temp->down = next1;
		prev->right = temp;
		temp->right = next;
		cout << prev1->down->row << " " << prev1->down->column << endl;
		cout << temp->down->row << " " << temp->down->column << endl;
		cout << prev->right->row << " " << prev->right->column << endl;
		cout << temp->right->row << " " << temp->right->column << endl;

	}
}
int search(linkedNode **linkedHeads, int row, int column) {
	linkedNode *prev, *next;
	prev = linkedHeads[row];
	next = prev->right;
	while (next != linkedHeads[row] && prev->column < column) {
		prev = next;
		next = next->right;
	}
	if (prev->column == column) {
		return prev->value;
	}
	else return -1;
}
void print(linkedNode **linkedHeads, int N) {
			linkedNode *prev, *next;
	for (int i = 0; i<N; i++) {

		prev = linkedHeads[i];
		next = prev->right;
		cout << prev->row << " " << prev->column << " "  << prev->value << endl;
		while (next != linkedHeads[i]) {
			cout << prev->row << " " << prev->column << " "  << prev->value << endl; 
			prev = next;
			next = next->right;
		}
	}
	for (int i=0; i<N; i++) {
		prev = linkedHeads[i];
		next = prev->down;
		cout << prev->row << " " << prev->column << " "  << prev->value << endl;
		while (next != linkedHeads[i]) {
			cout << prev->row << " " << prev->column << " "  << prev->value << endl; 
			prev = next;
			next = next->down;
		}
	}
}

int main() {
	int N, R, F;
	cin >> N >> R >> F;

	char **cities = new char *[N];
	for (int i=0; i<N; i++) {
		cities[i] = new char[25];
		strcpy(cities[i], "\0");
	}

	arrayNode *arrayMatrix[R+1];
	arrayMatrix[0] = createArrayNode(N, N, R);
	for (int i=1; i <= R; i = i+1) {
		char city1[25], city2[25]; int d;
		scanf("%s %s %d", city1, city2, &d);
		int city1Index = cityIndex(cities, N, city1);
		int city2Index = cityIndex(cities, N, city2);
		arrayMatrix[i] = createArrayNode(city1Index, city2Index, d);
	}
	cout << "array matrix built" << endl;
	for (int i=0; i<N; i++) {
		printf("%s ", cities[i]);
	}printf("\n");
	linkedNode *linkedMatrix[N];
	buildLinkedMatrix(linkedMatrix, F, N, cities);
	//print(linkedMatrix, N);

	int c1, c2, maxFare = 0;
	for (int i=1; i<=R; i++) {
		// cout << maxFare << " " << endl;
		cout << arrayMatrix[i]->row << " " << arrayMatrix[i]->column << " " << endl;
		int farepkm = search(linkedMatrix, arrayMatrix[i]->row, arrayMatrix[i]->column);
		if (farepkm == -1) {
			farepkm = search(linkedMatrix, arrayMatrix[i]->column, arrayMatrix[i]->row);
		}
		if (farepkm != -1) {
			cout << farepkm << " " << endl;
			if (farepkm*arrayMatrix[i]->value > maxFare) {
				maxFare = farepkm*arrayMatrix[i]->value;
				c1 = arrayMatrix[i]->row; c2 = arrayMatrix[i]->column;
				cout << c1 << " " << c2 << " " << maxFare << endl;
			}
		}
	}
	cout << cities[c1] << " " << cities[c2] << " " << maxFare << endl;
}
