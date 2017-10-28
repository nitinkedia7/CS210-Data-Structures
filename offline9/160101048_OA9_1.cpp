// 160101048_OA9_1.cpp: Nitin Kedia
// Description: Tower of cubes

#include <iostream>
using namespace std;

struct adj_cube {
	int index, face;
	adj_cube *ptr;
};

struct cube {
	int visit_color[6], d[6], f[6], parent[6][2];
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

int opposite_face(int face) {
	if (face % 2 == 0) return face+1;
	else return face-1;
}
void max_subtree(cube *array, int n, int ui, int uf) {
	int opp_face = opposite_face(uf);
	adj_cube *head = array[ui].link[opp_face];

	int h = 0;
	while (head != NULL) {
		int vi = head->index;
		int vf = head->face;
		if (array[vi].visit_color[vf] == 1) {
			if (array[vi].f[vf] > h) {
				h = array[vi].f[vf];
			}
		}
		head = head->ptr;
	}
	array[ui].f[uf] = h+1;	
}



void dfs_visit(cube *array, int n, int index, int face) {
	array[index].visit_color[face] = 0;
	// if (array[index].d[face] < *d)
	// 	array[index].d[face] = ++(*d);

	int opp_face = opposite_face(face);
	
	adj_cube *head = array[index].link[opp_face];
	while (head != NULL) {
		int vi = head->index;
		int vf = head->face;
		if (array[vi].visit_color[vf] == -1) {
			array[vi].parent[vf][0] = index;
			array[vi].parent[vf][1] = face;
			// array[vi].d[vf] = array[index].d[face]+1; 
			dfs_visit(array, n, vi, vf);
		}
		// else if (array[vi].visit_color[vf] == 1) {
		// 	int wi = array[vi].parent[vf][0];
		// 	int wf = array[vi].parent[vf][1];
		// 	if (wi != -1 && wf != -1) {
		// 		if (array[index].d[face] > array[wi].d[wf]) {
		// 			array[vi].parent[vf][0] = index;
		// 			array[vi].parent[vf][1] = face;
		// 			array[vi].d[vf] = array[index].d[face]+1;
		// 		}
		// 	}
		// }
		head = head->ptr;
	}
	array[index].visit_color[face] = 1;
	// find maximum height subtree below it
	max_subtree(array, n, index, face);
	// --(*d); // stack is breaking
}

void dfs(cube *array, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 6; j++) {
			if (array[i].visit_color[j] == -1) {
				array[i].d[j] = 1;
				dfs_visit(array, n, i, j);
			}
		}
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

void print(cube *array, int n) {
	for (int i = 0; i < n; i++) {
		cout << "cube" << i+1 << " ";
		for (int j = 0; j < 6; j++) {
			cout << array[i].d[j] << "," << array[i].f[j] << "\t";
		}
		cout << endl;
	}
}

void output_helper(cube *array, int n, int ui, int uf) {
	cout << ui+1;
	if (uf == 0) cout << " front";
	else if (uf == 1) cout << " back";
	else if (uf == 2) cout << " left";
	else if (uf == 3) cout << " right";
	else if (uf == 4) cout << " top";
	else  cout << " bottom";
	cout << endl;

	adj_cube *head = array[ui].link[opposite_face(uf)];
	while (head != NULL) {
		int vi = head->index;
		int vf = head->face;
		if (array[vi].f[vf] == array[ui].f[uf]-1) {
			output_helper(array, n, vi, vf);
			break;
		}
		head = head->ptr;
	}
}

void output(cube *array, int n) {
	// cout << array[5].parent[4][0] << " " << array[5].parent[4][1] << endl;
	int ui = 0, uf = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 6; j++) {
			if (array[i].f[j] > array[ui].f[uf]){
				ui = i; uf = j;
			}
		}
	}
	cout << array[ui].f[uf] << endl;
	output_helper(array, n, ui, uf);
}

int main() {
	int n;
	int c = 1;
	while (c) {
		cin >> n;
		if (n == 0) return 0;
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
				array[i].parent[j][0] = -1;
				array[i].parent[j][1] = -1;
				array[i].link[j] = NULL;
			}
		}
		build_graph(array, n);
		dfs(array, n);
		// print(array, n);
		cout << "Case #" << c++ << endl;
		output(array, n);
		cout << endl;
	}	
}