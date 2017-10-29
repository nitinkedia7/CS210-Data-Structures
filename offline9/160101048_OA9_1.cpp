// 160101048_OA9_1.cpp: Nitin Kedia
// Description: Tower of cubes using DFS

// Ordered pair (cube, face) denote a distinct node. "f" is the maximum height of the tower that can be formed if (cube, face) is topmost

#include <iostream>
using namespace std;

struct adj_cube { // struct for adjacent nodes in a linked list
	int index, face;
	adj_cube *ptr;
};

struct cube { // struct for each cube
	int visit_face[6], f[6], face_color[6]; // a cube can be uniquely visited through six faces, so all properties are in array[6]
	adj_cube *link[6];
};

void insert(adj_cube **pHead, int index, int face) { // insert into front of a link list
	adj_cube *temp = new adj_cube;
	temp->index = index;
	temp->face = face;
	temp->ptr = *pHead;

	*pHead = temp;
}

int opposite_face(int face) { // return opposite_face, [0:front, 1:back, 2:left, 3:right, 4:top, 5:bottom]
	if (face % 2 == 0) return face+1;
	else return face-1;
}

void dfs_visit(cube *array, int n, int index, int face, int *mi, int *mf) {
	array[index].visit_face[face] = 0; // grey

	int opp_face = opposite_face(face); // color of bottom face should be same as top face of lower cube
	adj_cube *head = array[index].link[opp_face];
	while (head != NULL) { // 
		int vi = head->index;
		int vf = head->face;
		if (array[vi].visit_face[vf] == -1) { 
			dfs_visit(array, n, vi, vf, mi, mf); // visit, if white
		}
		if (array[index].f[face] <= array[vi].f[vf]) {
			array[index].f[face] = array[vi].f[vf] + 1; // maintain f 
		}
		if (array[*mi].f[*mf] < array[index].f[face]) { // maintain the node with maximum f
			*mi = index;
			*mf = face;
		}
		head = head->ptr;
	}
	array[index].visit_face[face] = 1; // black
}

void dfs(cube *array, int n, int *mi, int *mf) { // dfs gives f for every face of every cube
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 6; j++) {
			if (array[i].visit_face[j] == -1) {
				dfs_visit(array, n, i, j, mi, mf);
			}
		}
	}
}

void build_graph(cube *array, int n) { // a directed edge is made between a face of lighter cube to a same coloured face of a heavier cube
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			for (int k = 0; k < 6; k++) {
				for (int l = 0; l < 6; l++) {
					if (array[j].face_color[k] == array[i].face_color[l]) {
						insert(&(array[i].link[l]), j, k);
					}
				}
			}
		}
	}
}

void print_output(cube *array, int n, int ui, int uf) {
	cout << ui+1; // print cube number and face which will be at top
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
		if (array[vi].f[vf] == array[ui].f[uf]-1) { // next cube will same color as opposite face of ui and f one less than upper cube
			print_output(array, n, vi, vf);
			break;
		}
		head = head->ptr;
	}
}

int main() {
	int n;
	int c = 1;
	while (1) {
		cin >> n;
		if (n == 0) return 0;
		cube array[n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				cin >> array[i].face_color[j]; // scan face colors
			}
		}
		// initialise attributes of adjacency list
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				array[i].visit_face[j] = -1; // white
				array[i].f[j] = 1; // default 1 (eg for isolated node)
				array[i].link[j] = NULL;
			}
		}
		build_graph(array, n); // make edges
		int mi = 0, mf = 0; // mi, mf denote the node with maximum f
		dfs(array, n, &mi, &mf); 
		
		cout << "Case #" << c++ << endl;
		cout << array[mi].f[mf] << endl; // print maximum height
		print_output(array, n, mi, mf);  // print cube sequence in tower
		cout << endl;
	}	
}