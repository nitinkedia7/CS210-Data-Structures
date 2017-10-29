// 160101048_OA9_2.cpp: Nitin Kedia
// Description: Find minimum number of button presses required to reach target state without any forbidden state in between
// 				Distance from start to any state calculated using BFS will give number of buttons to be pressed

#include <iostream>
using namespace std;

struct node { // struct for each possible state of the machine and its attributes
	int color, d;
	int next_states[8]; // exactly 8 elements can be reached by pressing only one button in current state
};

struct queue { // queue for BFS
	int front, rear;
	int array[10000];
};

void enqueue(queue *q, int x) {
	(q->array)[(q->rear)++] = x;
}

int dequeue(queue *q) {
	return (q->array)[(q->front)++]; 
}

int convert(int array[4]) { // convert four digits into integer
	int n = 0;
	for (int i = 3; i >= 0; i--) {
		n *= 10;
		n += array[i];
	}
	return n;
}

void bfs(node *array, int s, int e) { // calculate distance wrt initial state
	// initial attributes already assigned
	array[s].d = 0; // distance = 0
	array[s].color = 0; // gray
	
	queue q; // initialise queue
	q.front = 0;
	q.rear = 0;
	enqueue(&q, s);

	while (q.front < q.rear) { // queue is not empty
		int u = dequeue(&q);

		for (int i = 0; i < 8; i++) { // visit adjacent nodes of u
			int v = array[u].next_states[i];

			if (array[v].color == -1) {
				array[v].color = 0; // grey
				array[v].d = array[u].d + 1; // d[v] = d[u]+1
				if (v == e) return; // if final state is found in betwwen, no need to continue further
				enqueue(&q, v);
			}
		}
		array[u].color = 1; // black
	}
}

void scan(int array[4]) { // scans four space separated integers into array
	for (int i = 3; i >= 0; i--) {
		cin >> array[i];
	}
}

int main() {
	int n;
	cin >> n;
	// build adjacency list
	node array[10000];
	for (int i = 0; i < 10000; i++) { // find immediate next states by manipulating digits
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
			array[i].next_states[j] = convert(aux_array[j]); // convert all next into integer
		}
	}

	for (int i = 0; i < n; i++) {
		int start[4], end[4];
		scan(start);
		scan(end);

		for (int k = 0; k < 10000; k++) { // initialise attributes
			array[k].color = -1; // white
			array[k].d = -1;
		}

		int f;
		cin >> f;
		for (int j = 0; j < f; j++) { // to skip forbidden states make them black before BFS, so we don't visit them
			int forbidden[4];
			scan(forbidden);
			array[convert(forbidden)].color = 1;
		}
		bfs(array, convert(start), convert(end));
		cout << array[convert(end)].d << endl; // distance of end w.r.t start is the answer because BFS gives shortest path
		// in case final state is unreachable, d is already initialised to -1
	}
}