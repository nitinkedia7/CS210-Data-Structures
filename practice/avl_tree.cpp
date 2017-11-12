#include <iostream>
using namespace std;

struct node {
	int key, height;
	node *left, *right;
};

node *create_node(int key) {
	node *temp = new node;
	temp->key = key;
	temp->height = 1;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

int max(int x, int y) {
	if (x > y) return x;
	else return y;
}

int height(node *head) {
	if (head == NULL) return 0;
	return head->height;
}

node *right_rotate(node *head) {
	node *lchild = head->left;

	head->left = lchild->right;
	lchild->right = head;

	head->height = 1 + max(height(head->left), height(head->right));
	lchild->height = 1 + max(height(lchild->left), height(lchild->right));

	return lchild;
}

node *left_rotate(node *head) {
	node *rchild = head->right;

	head->right = rchild->left;
	rchild->left = head;

	head->height = 1 + max(height(head->left), height(head->right));
	rchild->height = 1 + max(height(rchild->left), height(rchild->right));

	return rchild;
}

node *insert(node *head, int key) {
	if (head == NULL) {
		return create_node(key);
	}

	if (key <= head->key) {
		head->left = insert(head->left, key);
	}
	else {
		head->right = insert(head->right, key);
	}

	head->height = 1 + max(height(head->left), height(head->right));

	// int diff = height(head->left) - height(head->right);
	// if (diff > 1) {
	// 	if (key <= head->left->key) {			
	// 		return right_rotate(head);
	// 	}
	// 	else {
	// 		// double rotate
	// 		head->left = left_rotate(head->left);
	// 		return right_rotate(head);
	// 	}
	// }
	// else if (diff < -1) {
	// 	if (key > head->right->key) {
	// 		return left_rotate(head);
	// 	}
	// 	else {
	// 		// doudle rotate
	// 		head->right = right_rotate(head->right);
	// 		return left_rotate(head);
	// 	}
	// }
	// return head;
		int diff = height(head->left) - height(head->right);
	if (diff > 1) {
		int diff2 = height(head->left->left) - height(head->left->right);
		if (diff2 >= 0) {			
			return right_rotate(head);
		}
		else {
			// double rotate
			head->left = left_rotate(head->left);
			return right_rotate(head);
		}
	}
	else if (diff < -1) {
		int diff3 = height(head->right->left) - height(head->right->right);
		if (diff3 <= 0) {
			return left_rotate(head);
		}
		else {
			// doudle rotate
			head->right = right_rotate(head->right);
			return left_rotate(head);
		}
	}
	return head;
}

node *find_min(node *head) {
	if (head == NULL || head->left == NULL) return head;
	return head->left; 
}

node *delete_node(node *head, int key) {
	if (head == NULL) return NULL;

	if (key < head->key) {
		head->left = delete_node(head->left, key);
	}
	else if (key > head->key) {
		head->right = delete_node(head->right, key);
	}
	else {
		node *temp;
		if (head->left == NULL || head->right == NULL) {
			if (head->left == NULL) temp = head->right;
			else temp = head->left;
			if (temp == NULL) {
				temp = head;
				head = NULL;
			}
			else *head = *temp;
			delete temp;

		}
		else {
			temp = find_min(head->right);
			head->key = temp->key;
			head->right = delete_node(head->right, temp->key);
		}
	}
	if (head == NULL) return NULL;

	head->height = 1 + max(height(head->left), height(head->right));

	int diff = height(head->left) - height(head->right);
	if (diff > 1) {
		int diff2 = height(head->left->left) - height(head->left->right);
		if (diff2 >= 0) {			
			return right_rotate(head);
		}
		else {
			// double rotate
			head->left = left_rotate(head->left);
			return right_rotate(head);
		}
	}
	else if (diff < -1) {
		int diff3 = height(head->right->left) - height(head->right->right);
		if (diff3 <= 0) {
			return left_rotate(head);
		}
		else {
			// doudle rotate
			head->right = right_rotate(head->right);
			return left_rotate(head);
		}
	}
	return head;
}

void preorder(node *head) {
	if (head == NULL) return;
	else {
		cout << head->key << " ";
		preorder(head->left);
		preorder(head->right); 
	}
}

int main() {
	node *root = NULL;
	root = insert(root, 9);
	preorder(root);
	cout << endl;
	root = insert(root, 5);
	preorder(root);
		cout << endl;
	root = insert(root, 10);
	preorder(root);
		cout << endl;
	root = insert(root, 0);
	preorder(root);
		cout << endl;
	root = insert(root, 6);
	preorder(root);
		cout << endl;
	root = insert(root, 11);
	preorder(root);
		cout << endl;
		root = insert(root, -1);
	preorder(root);
		cout << endl;
		root = insert(root, 1);
	preorder(root);
		cout << endl;
			root = insert(root, 2);
	preorder(root);
		cout << endl;

	root = delete_node(root, 10);
	preorder(root);
	cout << endl;
}