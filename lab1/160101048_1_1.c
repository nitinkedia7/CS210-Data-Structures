#include <stdio.h>
#include <stdlib.h>

// Define a node
typedef struct _node {
	int data;
	struct _node *ptr;
}node;

node *createNode() {
	return (node *)malloc(sizeof(node));
}
 
node *Create(node *head) {
	while (1) {
		int newData;
		scanf("%d", &newData);
		if (newData == 0) break;
		else {
			// if head is null create a new temp, insert data, assign temp to head.
			// if head is not null, create temp=head, forward temp, insert data.
			if (head == NULL) {
				node *temp = createNode();
				temp->data = newData;
				temp->ptr = NULL;
				head = temp;
			}
			else {
				node *temp = head;
				while (temp->ptr != NULL) {temp = temp->ptr;}
				temp->ptr = createNode();
				temp->ptr->data = newData;
				temp->ptr->ptr = NULL;
			}
		}
	}
	return head;
}


void Print(node *head) {
	while (head != NULL) {
		printf("%d ", head->data);
		head = head->ptr;
	}
	printf("0 \n");
}

node *Reverse(node *head) {
	if (head != NULL) {
		node *temp1 = head->ptr;
		head->ptr = NULL;
		node *temp2;
		while (temp1 != NULL) {
			temp2 = temp1->ptr;
			temp1->ptr = head;
			head = temp1;
			temp1 = temp2;
		}
	}
	return head;
}

void main() {
	node *head = NULL;
	head = Create(head);
	Print(head);
	head = Reverse(head);
	Print(head);
}