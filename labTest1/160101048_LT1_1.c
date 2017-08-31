#include <stdio.h>
#include <stdlib.h>

// Define a node
typedef struct _node{
	int data;
	struct _node *left;
	struct _node *right;
	int isRightThread; //indicate leaf node with right thread
}node;

// createNode assignes space to ptr
node *createNode() {
	return (node *)malloc(sizeof(node));
}
// setLeft inserts a threaded left child to (was)threaded node
void setLeft(node *p, int d) {
	if (p != NULL) {
		if (p->left == NULL) {
			node *r = createNode();
			r->data = d;
			r->left = NULL;
			r->right = p;
			r->isRightThread = 1;

			//p->isRightThread = 0;
			//p->right == NULL;
			p->left = r;
		}
	}
}
// setRight inserts a threaded right child to (was)threaded node
void setRight(node *p, int d) {
	if (p != NULL) {
		if (p->isRightThread == 1) {
			node *r = createNode();
			r->data = d;
			r->left = NULL;
			r->right = p->right;
			r->isRightThread = 1;

			p->isRightThread = 0;
			p->right = r;
		}
	}
}
// Part b- Inorder traversal in threaded binary tree without stack or recursion
void printInorder(node *p) {
	printf("\nInorder: ");
	node *q;
	do {
		q == NULL;
		while(p != NULL) {
			q = p;
			p = p->left;
		}
		if(p == NULL) {
			printf("%d ", q->data);
			p = q;
			p = p->right;
		}
		while(q->isRightThread == 1 && p != NULL) {
			printf("%d ", p->data);
			q = p;
			p = p->right;
		}
		q = p;
	} while(q != NULL);
}
// Part a- create threaded binary tree from input sequence;
// searchNum finds num2 and returns its ptr;
node *search(node *p, int d) {
	node *q;
	do {
		q = NULL;
		while(p != NULL) {
			q = p;
			p = p->left;
		}
		if(p == NULL) {
			if (q->data == d) return q;
			p = q;
			p = p->right;
		}
		while(q->isRightThread == 1 && p != NULL) {
			if (p->data == d) return p;
			q = p;
			p = p->right;
		}
		q = p;
	} while(q != NULL);
	return NULL;
}

// buildTree() creates a threaded binary tree;
node *buildTree() {
	int num1, num2; char position;
	node *root = NULL;
	printf("Enter the Sequence:\n");
	scanf("%d", &num1);
	if (num1 != -1) {
		root = createNode();
		root->data = num1;
		root->left = NULL;
		root->isRightThread = 1;
		root->right = NULL;
		scanf(" %c %d", &position, &num2);//as per format
		while (1) {
			scanf("%d", &num1);
			if (num1 == -1) break;
			scanf(" %c %d", &position, &num2);//adhere to format
			node *parent = search(root, num2);
			if (position == 'L' && parent->left == NULL) {
				setLeft(parent, num1);
			}
			else if (position == 'R' && parent->isRightThread == 1) {
				setRight(parent, num1);
			}
			else printf("\n%d is ignored", num1);
		}
	}
	return root;
}
void main() {
	node *root = NULL;
	root = buildTree();
	printInorder(root);
	printf("\n");
}