// 160101048_OA8_1.cpp: Nitin Kedia
// Description: Print disjoint connected set of nodes in an undirected graph and cycles occuring in it.

#include <iostream>
using namespace std;

struct adj_node { // struct for storing linked list in each element of adjacency list
	int index;
	adj_node *ptr;
};

struct node { // struct for each element in each member of adjacency list
	int color, parent, component; // component specifies the component number number in which a element belongs
	adj_node *link;
};

void enqueue(adj_node **pHead, int index) { // utility function for appending into a linked list
	adj_node *temp = new adj_node;
	temp->index = index;
	temp->ptr = NULL;	
	if (*pHead == NULL) {
		*pHead = temp;
	}
	else {
		adj_node *prev = *pHead, *next = (*pHead)->ptr;
		while (next != NULL) {
			prev = next;
			next = next->ptr;
		}
		prev->ptr = temp;
	}
}

void dfs_visit(node *array, int n, int i, adj_node **cycle_head, int *pcycles) { // recursive function of DFS traversal of graph
	array[i].color = 0; // gray
	adj_node *head = array[i].link;
	while (head != NULL) {
		int k = head->index;
		if (array[k].color == -1) { // traverse unvisited adj nodes of a node;
			array[k].parent = i;
			array[k].component = array[i].component; // k is in same component as i since k is child of i in DFS tree 
			dfs_visit(array, n, k, cycle_head, pcycles);
		}
		else if (array[i].parent != k && array[k].color == 0) { // edge to a grey element in the same recursive stack means a cycle
				enqueue(cycle_head, k); // store two adjacent elements of cycle for future reproduction
				enqueue(cycle_head, i);	
				(*pcycles)++;
		}
		head = head->ptr;
	}
	array[i].color = 1; // black
}

void dfs(node *array, int n, int *pcomponent, adj_node **cycle_head, int *pcycles) { // driver for dfs_visit
	for (int i = 0; i <= n; i++) {
		if (array[i].color == -1) {
			array[i].component = ++(*pcomponent); // each dfs_visit from dfs means a new component;
			dfs_visit(array, n, i, cycle_head, pcycles);
		}
	}
}

void print_connected(node *array, int n, int component) { // print nodes setwise each having a distinct component number
	adj_node **ans = new adj_node*[component+1];
	for (int i = 0; i <= component; i++) {
		ans[i] = NULL;
	}
	
	for (int i = 1; i <= n; i++) { // partition nodes by component number
		enqueue(&(ans[array[i].component]), i);
	}

	cout << "The number of component(s): " << component << endl; 
	for (int i = 1; i <= component; i++) { // print components
		adj_node *head = ans[i];
		cout << "component" << i << ": ";
		while (head != NULL) {
			cout << head->index << " ";
			head = head->ptr;
		}
		cout << endl;
	}
}

void print_path(node *array, int n, int i, int j) { // given two adj members of a cycle print the cycle
	if (i == j) {
		cout << j << " ";
		return;
	}
	print_path(array, n, i, array[j].parent);
	cout << j << " ";
}

void print_cycles(node *array, int n, adj_node *cycle_head, int cycles) { // print each cycle stored in cycle_head
	cout << "The number of cycle(s): " << cycles << endl;
	for (int i = 1; i <= cycles; i++) {
		cout << "cycle" << i << ": "; 
		print_path(array, n, cycle_head->index, cycle_head->ptr->index);
		cout << cycle_head->index << endl; // print 1 in 1 4 3 1
		cycle_head = cycle_head->ptr->ptr; // cycle_head contains even number of elements as enqueue is done in pairs
	}
}

// void print(node *array, int n) { // to print adjacency list
// 	for (int i = 1; i <= n; i++) {
// 		cout << i << " " << array[i].parent << endl;
// 		adj_node *head = array[i].link;
// 		while (head != NULL) {
// 			cout << head->index << " ";
// 			head = head->ptr;
// 		}
// 		cout << "NULL" << endl << endl;
// 	}
// }

int main() {
	cout << "Enter input (do not use comma in edges): " << endl;
	int n, e;
	cin >> n >> e; // scan number of nodes and edges 

	node array[n+1];
	for (int i = 1; i <= n; i++) { // initialise array
		array[i].color = -1;
		array[i].parent = -1;
		array[i].link = NULL;
		array[i].component = 0;
	}

	int e1, e2; // scan edges
	int cycles = 0;    // to store number of cycles
	adj_node *cycle_head = NULL; // to store cycles
	for (int i = 0; i < e; i++) {
		cin >> e1 >> e2;
		if (e1 != e2) {
			enqueue(&(array[e1].link), e2);
			enqueue(&(array[e2].link), e1);
		}
		else {
			cycles++;
			enqueue(&(cycle_head), e1);
			enqueue(&(cycle_head), e2);
		}
	}
		
	int component = 0; // to specify component number of each element

	dfs(array, n, &component, &cycle_head, &cycles);
	// print(array, n);
	print_connected(array, n, component);
	print_cycles(array, n, cycle_head, cycles);
} 