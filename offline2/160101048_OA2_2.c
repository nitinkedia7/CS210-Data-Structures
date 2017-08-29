// Please read "hoffman" as huffman :) 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define node
typedef struct _node {
	char c[100]; // string occuring in Hoffman tree.
	int f; // corresponding frequency
	struct _node *ptr;
	int bit; // 0 for left child, 1 for right child, -1 for root in Hoffman tree
}node;

// initialise a node
node *createNode() {
	node *head = (node *)malloc(sizeof(node));
	head->f = 0;
	head->bit = -1;
	head->ptr = NULL;
	return head;
}
// updateFreq builds frquency list of input characters
node *updateFreq(node *head, char c[]) {
	if (head != NULL) {
		node *temp = head;
		while (temp != NULL) {
			if (strcmp(c, head->c) == 0) {
			(temp->f)++; //increment by 1 if input char is already in list
			break;
			}
		temp = temp->ptr;
		}
		if (temp == NULL) {
			temp = createNode(); // insert new character with freq 1
			strcpy(temp->c, c);
			temp->f = 1;
			temp->ptr = head;
			head = temp;
		}
	}
	if (head == NULL) {
		head = createNode();
		strcpy(head->c, c);
		head->f = 1;
	}
	return head;
}
// helper function for sorting frequency list using BubbleSort
void swapper(node *head) {
	char tempC[100]; int tempF;
	strcpy(tempC, head->c);
	tempF = head->f;

	strcpy(head->c, head->ptr->c);
	head->f = head->ptr->f;

	strcpy(head->ptr->c, tempC);
	head->ptr->f = tempF;
}
// sort function sorts by frequency first,
// for same freq dictionary order is followed.
void sort(node *head, node *tail) {
	node *temp = head;
	if (temp != tail) {
		while (temp->ptr != tail) {
			if (temp->f > temp->ptr->f) swapper(temp);
			else if (temp->f == temp->ptr->f) {
				if (temp->c[0] > temp->ptr->c[0]) swapper(temp);
			}
			temp = temp->ptr;
		}
		tail = temp;
		sort(head, tail); // recursion step for bubblesort
	}
}
// Following function build pseudo-Hoffman Tree recursively
// node->bit reminds which child
void buildHoffTree(node *head) {
	node *temp = head;
	if (temp != NULL) {
		if (temp->ptr != NULL) {
			node *new = createNode();
			strcpy(new->c, temp->c);
			strcat(new->c, temp->ptr->c);
			new->f = temp->ptr->f + temp->f;

			new->ptr = temp->ptr->ptr;
			temp->ptr->ptr = new;

			temp->bit = 0;
			temp->ptr->bit = 1;

			sort(head->ptr->ptr, NULL); // can be further optimsed by using 1 cycle as only one element is out of place
			buildHoffTree(head->ptr->ptr); //recursion step
		}
	}
}
// printCode traverses the pseudo-tree, simultaneously printing the Huffman Encoding for char passed
void printCode(node *head, char c) {
	if (head->ptr != NULL) {
		printCode(head->ptr, c);
		if (strchr(head->c, c) != NULL) {
		printf("%d", head->bit);
		}
	}
}
// printlist prints frequency table at any instant;
void printList(node *head) {
	while (head != NULL) {
		printf("%s:%d %d  ", head->c, head->f, head->bit);
		head = head->ptr;
	}
	if (head == NULL) {
		printf("\n");
	}
}
 
void main() {
	char inputStr[100];
	printf("Enter input sequence:\n");
	scanf("%s", inputStr);
	node *head = NULL;	// head will eventually tranform to pseudo-Huffman Tree
	node *print = NULL; // copy of head used to track input char as head will contain combinations of input char   
	int i = 0;
	while (inputStr[i] != '\0') {
		char c[2];
		c[0] = inputStr[i]; c[1] = '\0';
		head = updateFreq(head, c);
		print = updateFreq(print, c);
		i++;
	}
	//printList(head);
	node *tail = NULL;
	sort(head, tail);
	sort(print, tail); // ensures that in output most infrequent characters occur first
	//printList(head);
	buildHoffTree(head);
	//printList(head);

	if (print != NULL) {
		if (print->ptr == NULL) {
			printf("%c=0\n", print->c[0]);
		} 
		else {
			while (print != NULL) {
				char c = (print->c)[0];
				printf("%c=", c);
				printCode(head, c);
				printf("  ");
				print = print->ptr;
			}
			printf("\n");
		}
	}
}