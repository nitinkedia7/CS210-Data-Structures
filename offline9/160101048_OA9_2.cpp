// 160101048_OA9_2.cpp: Nitin Kedia
// Description: Find minimum number of button presses required to reach target state without any forbidden state in between

#include <iostream>
using namespace std;

struct node {
	int color, d;
	int next_states[8];
};

struct queue {
	int front, rear;
	int array[10000];
};

void enqueue(queue *q, int x) {
	(q->array)[(q->rear)++] = x;
}

int dequeue(queue *q) {
	return (q->array)[(q->front)++]; 
}

int convert(int array[4]) {
	int n = 0;
	for (int i = 3; i >= 0; i--) {
		n *= 10;
		n += array[i];
	}
	return n;
}

void bfs(node *array, int s, int e) {
	// initial attributes already assigned
	array[s].d = 0;
	array[s].color = 0; // gray
	
	queue q;
	q.front = 0;
	q.rear = 0;
	enqueue(&q, s);

	while (q.front < q.rear) {
		int u = dequeue(&q);

		for (int i = 0; i < 8; i++) {
			int v = array[u].next_states[i];

			if (array[v].color == -1) {
				array[v].color = 0;
				array[v].d = array[u].d + 1;
				if (v == e) return;
				enqueue(&q, v);
			}
		}
		array[u].color = 1; // black
	}
}

void scan(int array[4]) {
	for (int i = 3; i >= 0; i--) {
		cin >> array[i];
	}
}

int main() {
	int n;
	cin >> n;

	node array[10000];
	for (int i = 0; i < 10000; i++) {
		int n = i;
		int digits[4];
		for (int j = 0; j < 4; j++) {
			digits[j] = n%10;
			n = n/10;
		}
		int aux_array[8][4];
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 4; k++) {
				aux_array[j][k] = digits[k];
			}
		}
		aux_array[0][0] = (digits[0]+1)%10;
		aux_array[1][0] = (digits[0]+9)%10;
		aux_array[2][1] = (digits[1]+1)%10;
		aux_array[3][1] = (digits[1]+9)%10;
		aux_array[4][2] = (digits[2]+1)%10;
		aux_array[5][2] = (digits[2]+9)%10;
		aux_array[6][3] = (digits[3]+1)%10;
		aux_array[7][3] = (digits[3]+9)%10;

		for (int j = 0; j < 8; j++) {
			array[i].next_states[j] = convert(aux_array[j]);
		}
	}

	for (int i = 0; i < n; i++) {
		int start[4], end[4];
		scan(start);
		scan(end);

		for (int k = 0; k < 10000; k++) {
			array[k].color = -1;
			array[k].d = -1;
		}

		int f;
		cin >> f;
		for (int j = 0; j < f; j++) {
			int forbidden[4];
			scan(forbidden);
			array[convert(forbidden)].color = 1;
		}
		bfs(array, convert(start), convert(end));
		cout << array[convert(end)].d << endl;
	}
}