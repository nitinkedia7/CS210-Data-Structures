// #include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node {
	int key, priority;
	node *parent, *left, *right;
};
node *create_node(int key, int priority) {
	node *temp = new node;
	temp->key = key;
	temp->priority = priority;
	temp->parent = NULL;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

node *find_min(node *head) {
	if (head == NULL) return NULL;
	else return find_min(head->left);
}

node *right_rotate(node *head) {
	if (head == NULL || head->left == NULL) return head;

	node *lchild = head->left;
	head->left = lchild->right;
	if (lchild->right != NULL) lchild->right->parent = head;
	lchild->right = head;
	lchild->parent = head->parent;
	head->parent = lchild;

	return lchild;
}

node *left_rotate(node *head) {
	if (head == NULL || head->right == NULL) return head;

	node *rchild = head->right;
	head->right = rchild->left;
	if (rchild->left != NULL) rchild->left->parent = head;
	rchild->left = head;
	rchild->parent = head->parent;
	head->parent = rchild;

	return rchild;
}
void inorder_traversal(node *head) {
	if (head == NULL) return;
	else {
		inorder_traversal(head->left);
		cout << head->key << " ";
		// cout << head->key << ", " << head->priority << " ";		
		inorder_traversal(head->right);
	}
}


node *treap_insert(node *head, node *parent, int key, int priority) {
	if (head == NULL) {
		head = create_node(key, priority);
		head->parent = parent;
		return head;
	}
	else if (key < head->key) {
		head->left = treap_insert(head->left, head, key, priority);
		// cout << head->left->priority << " " << head->priority << endl;
		if (head->left->priority < head->priority) {
			return right_rotate(head);
		}
		else return head;
	}
	else if (key > head->key) {
		head->right = treap_insert(head->right, head, key, priority);
		if (head->right->priority < head->priority) {
			return left_rotate(head);
		}
		else return head;
	}
	// if (parent == NULL) return;
	// if (parent->priority > head->priority) {
	// 	if (parent->left == head) {
	// 		head = right_rotate(parent);
	// 	}
	// 	else left_rotate(parent);
	// }
} 

node *treap_delete(node *head, int key, int *found) {
	if (head == NULL) {
		*found = 0;
		return head;
	}
	if (head->key > key) {
		head->left = treap_delete(head->left, key, found);
		return head;
	}
	else if (head->key < key) {
		head->right = treap_delete(head->right, key, found);
		return head;
	}
	else {
		// if (head->left == NULL || head->right == NULL) {
		// 	node *temp;
		// 	if (head->left != NULL) temp = head->left;
		// 	else temp = head->right;
		// 	if (temp == NULL) {
		// 		temp = head;
		// 		head == NULL;
		// 	}
		// 	else *head = *temp;
		// 	delete temp;
		// }
		// else {
		// 	node *temp = find_min(head->right);
		// 	head->key = temp->key;
		// 	head->right = treap_delete(head->right, key);
		// }
		if (head->left == NULL && head->right == NULL) {
			*found = 1;
			delete head;
			return NULL;
		}
		else {
			if (head->left != NULL && head->right != NULL) {
				if (head->left->priority < head->right->priority) {
					head = right_rotate(head);
					head->right = treap_delete(head->right, key, found);
					return head;
				}
				else {
					head = left_rotate(head);
					head->left = treap_delete(head->left, key, found);
					return head;
				}
			}
			else if (head->right == NULL) {
				// cout << "yes" << endl;
				head = right_rotate(head);
				// inorder_traversal(head); cout << endl;
				head->right = treap_delete(head->right, key, found);
				return head;
			}
			else if (head->left == NULL) {
				head = left_rotate(head);
				head->left = treap_delete(head->left, key, found);
				return head;
			}
			// return head;
		}
	}
}


bool check_minheap(node *head) {
	if (head == NULL) return true;
	bool left = true;
	if (head->left != NULL) {
		left = (head->priority < head->left->priority) && check_minheap(head->left);
	}
	bool right = true;
	if (head->right != NULL) {
		right = (head->priority < head->right->priority) && check_minheap(head->right);
	}
	return left && right;
}

int main() {
	string cmd;
	int arg;
	node *head = NULL;
	srand(time(NULL));
	while (1) {
		
		cin >> cmd;
		if (cmd == "INSERT") {
			cin >> arg;
			int r = rand() % 100000 + 1;
			head = treap_insert(head, NULL, arg, r);
			inorder_traversal(head); cout << endl;
			if (check_minheap(head)) cout << 1 << endl;
			else cout << 0 << endl;
		}
		else if (cmd == "DELETE") {
			int found = 1;
			cin >> arg;
			head = treap_delete(head, arg, &found);
			// inorder_traversal(head); cout << endl;
			// if (check_minheap(head)) cout << 1 << endl;
			// 	else cout << 0 << endl;
			if (found == 1) {
				inorder_traversal(head); cout << endl;
				if (check_minheap(head)) cout << 1 << endl;
				else cout << 0 << endl;
			}
			else cout << arg << " NOT FOUND" << endl;
		}
		else if (cmd == "-1") break;
		cout << endl;	
	}
	return 0;
}
