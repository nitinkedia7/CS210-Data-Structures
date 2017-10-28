// 160101048_OA9_1.cpp: Nitin Kedia
// Description: Tower of cubes

#include <iostream>
using namespace std;

struct adj_cube {
	int index, face;
	adj_cube *ptr;
};

struct cube {
	int visit_color[6], d[6], parent[6];
	int face_colors[6];
	adj_cube *link[6];
};

void prepend(adj_cube **pHead, int index, int face) {
	adj_cube *temp = new adj_cube;
	temp->index = index;
	temp->face = face;
	temp->ptr = *pHead;

	*pHead = temp;
}

struct queue {
	int front, rear;
	int array[500][2];
};

void enqueue(queue *q, int index, int face) {
	(q->array)[(q->rear)++][0] = index;
	(q->array)[(q->rear)][1] = face;	
}

void dequeue(queue *q, int *index, int *face) {
	*index = (q->array)[(q->front)++][0];
	*face = (q->array)[(q->front)][1];
}

void bfs(node *array, int n) {
	// initial attributes already assigned
	
	array[0].d[0] = 0;
	array[0].visit_color[0] = 0; // gray
	
	queue q;
	q.front = 0;
	q.rear = 0;
	enqueue(q, 0, 0);
	
	while (q.front < q.rear) {
		int ui, uf;
		dequeue(&q, &ui, &uf);

		node *head = array[ui].link[uf];
		while (head != NULL) {
			int vi = head->index;
			int vf = head->face;

			if (array[vi].visit_color[vf] == -1) {
				array[vi].visir_color[vf] = 0;
				array[vi].d[vf] = array[u].d[uf] + 1;
				enqueue(&head, vi, (vf/2)*2); // send opposite face 
			}
			head = head->ptr;
		}
		array[ui].visit_color[uf] = 1; // black
	}
}

void build_graph(cube *array, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			for (int k = 0; k < 6; k++) {
				int color1 = array[j].face_colors[k];
				for (int l = 0; l < 6; l++) {
					int color2 = array[i].face_colors[l];
					if (color1 == color2) {
						prepend(&(array[i].link[l]), j, k);
					}
				}
			}
		}
	}
}

int main() {
	int n;
	do {
		cin >> n;
		cube array[n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				cin >> array[i].face_colors[j];
			}
		}
		// initialise attributes
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				array[i].visit_color[j] = -1; // white
				array[i].d[j] = -1;
				array[i].parent[j] = -1;
				array[i].link[i] = NULL;
			}
		}
		build_graph(array, n);
		bfs(array, n);
	}	
}