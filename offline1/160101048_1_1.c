#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node *ptr;
}node;

node *createNode() {
	return (node *)malloc(sizeof(node));
}
// isCircular returns a pointer inside the circle if list contains a cycle, else returns NULL
node *isCircular(node *head) {
	if (head != NULL) {
		node *temp1 = head;
		node *temp2 = head;
		while(1) {
			if (temp2 != NULL && temp2->ptr != NULL) temp2 = temp2->ptr->ptr;
			else return NULL;
			if (temp1 != NULL) temp1 = temp1->ptr;
			else return NULL;
			if (temp1 == temp2 ) {
				return temp1;
			}

		}
	}
}

node *insertStart(node *head,int num2) {
	node *temp = createNode();
	temp->data = num2;
	temp->ptr = head;
	return temp;
}

node *insertEnd(node *head, int num2) {
// only works for a linear linked list.
	if (head != NULL) {
		node *stop = isCircular(head);
		if (stop == NULL) {
			node *temp = head;
			while (temp->ptr != NULL) {
				temp = temp->ptr;
			}
			temp->ptr = createNode();
			temp->ptr->data = num2;
			temp->ptr->ptr = NULL;
		}
		else {
			printf("Incorrect Input: Link list has evolved into circular, hence insert at END is not defined.\n");
			exit(0);
		}
	}
	else {
		head = insertStart(head, num2);
	}
	return head;
}

void insertBetween(node *p, node*q, int num2) {
	node *temp = createNode();
	temp->data = num2;
	temp->ptr = q;
	p->ptr = temp;
}
// search returns the pointer the data if found, else returns NULL
node *search(node *head, int num) {
	node *stop = isCircular(head);
	if (stop == NULL) {
		node *temp = head;
		while (temp != NULL) {
			if (temp->data == num) {
				return temp;
			}
			temp = temp->ptr;
		}
	}

	else {
		node *temp = head;
		int i = 0;
		while (1) {
			if (temp->ptr == stop && i==1) break;
			if (temp->data == num){
				return temp;
			}
			if (temp->ptr == stop) i++;
				temp = temp->ptr;
			}
	}
	return NULL;
}

void main() {
	node *head = NULL;
	int num1;
	printf("Enter the sequence:\n");
	while (1) {
		scanf("%d", &num1);
		if (num1 == -1) break;
		else {
			int num2,num3;
			scanf("%d %d", &num2, &num3);
			if (num1 == 0) head = insertStart(head, num2);
			
			if (num3 == 0) head = insertEnd(head, num2);
			
			if (num1 != 0 && num3 != 0) {
				node *p = search(head, num1);
				node *q = search(head, num3);
				if (p != NULL && q != NULL) {
					insertBetween(p, q, num2);
				}
				else printf("Could not insert %d as atleast one of num1,num2 is not found.\n", num2);
			}
		}
	}
	scanf("%d", &num1);
	node *final = search(head, num1);
	if (final != NULL) printf("FOUND\n");
	else printf("NOT FOUND\n");
}