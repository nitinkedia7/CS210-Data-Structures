#include <stdio.h>
#include <stdlib.h>
//define structure of a node
typedef struct _node{
	int data;
	struct _node *left;
	struct _node *right;
	//struct node *parent;
}node;
//create a new node with given data
node *createNode(int num) {
	node *root = (node *)malloc(sizeof(node));
	root->data = num;
	root->left = NULL;
	root->right = NULL;
	return root;
	//root->parent = <pass ptr to parent node as argument>;
}
//part b- print preorder, inorder, postorder.
void printPreorder(node * root) {
	if (root != NULL) {
		printf("%d ", root->data);
		printPreorder(root->left);
		printPreorder(root->right);
	}
}
void printInorder(node * root) {
	if (root != NULL) {
		printInorder(root->left);
		printf("%d ", root->data);
		printInorder(root->right);
	}
}
void printPostorder(node * root) {
	if (root != NULL) {
		printPostorder(root->left);
		printPostorder(root->right);
		printf("%d ", root->data);
	}
}
//part c- print the leaf nodes of input tree
//alternatively, check if given node is leaf, if yes, print;
void printLeafNodes(node *root) {
	if (root != NULL) {
		if (root->left == NULL && root->right == NULL) {
			printf("%d ", root->data);
		}
		else {
			printLeafNodes(root->left);
			printLeafNodes(root->right);
		}
	}
}
//part a- create whole tree from input sequence in context;
//implemente dsearch to find num2 and return its ptr;
node* searchNumber(int num, node *start) {
	if (start != NULL) {
		if (start->data == num) {return start;}
		else {
			node *temp = searchNumber(num,start->left);
			if (temp == NULL){
				temp = searchNumber(num,start->right);
			}
			return temp;		
		}	
	}
	else return NULL;
}
//input logic is embedded in makeTree();
//Assumptions: no other character except l/R is passed;
//	n2 is always present except for the first line;
node *makeTree() {
	int num1, num2; char position;
	node *root = NULL;
	printf("Enter the Sequence:\n");
	scanf("%d", &num1);
	if (num1 != -1) {
		root = createNode(num1);
		scanf(" %c %d", &position, &num2);//adhere to format
		while (1) {
			scanf("%d", &num1);
			if (num1 == -1) break;
			scanf(" %c %d", &position, &num2);//adhere to format
			node *parent = searchNumber(num2, root);
			if (position == 'L' && parent->left == NULL) {
				parent->left = createNode(num1);
			}
			else if (position == 'R' && parent->right == NULL) {
				parent->right = createNode(num1);
			}
			else printf("\n%d is ignored", num1);
		}
	
	}
	return root;
}
void main() {
	node *root = NULL;
	root = makeTree();
	printf("Inorder: "); printInorder(root);
	printf("\nPreorder: "); printPreorder(root);
	printf("\nPostorder: "); printPostorder(root);
	printf("\nLeaf Nodes: "); printLeafNodes(root);
	printf("\n");
}