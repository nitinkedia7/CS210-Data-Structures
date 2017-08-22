#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node *ptr;
}node;

node *createNode() {
	return (node *) malloc(sizeof(node));
}
// Start of Stack functions
node *push(node *s, int d) {
	node *temp = createNode();
	temp->data = d;
	temp->ptr = s;
	s = temp;
	return s;
}

int pop(node **ptrToS) {
	if (*ptrToS != NULL) {
		int data = (*ptrToS)->data;
		*ptrToS = (*ptrToS)->ptr;
		return data;
	}
	else {
		exit(0);
	}
}
// End of Stack Functions
// Start of Queue functions
node *enqueue(node *q, int d) {
	if (q == NULL) {
		node *temp = createNode();
		temp->data = d;
		temp->ptr = NULL;
		q = temp;
	}
	else {
		node *temp = q;
		while (temp->ptr != NULL) {
			temp = temp->ptr;
		}
		temp->ptr = createNode();
		temp->ptr->data = d;
		temp->ptr->ptr = NULL;
	}
	return q;
}
int dequeue(node **ptrToS) {
	if (*ptrToS != NULL) {
		int data = (*ptrToS)->data;
		*ptrToS = (*ptrToS)->ptr;
		return data;
	}
	else {
		exit(0);
	}
}
// End of Queue functions

void printList(node *s) {
	while (s != NULL) {
		printf("%d ", s->data);
		s = s->ptr;
	}
	printf("\n");
}

void main() {
	node *s = NULL;
	node *q1 = NULL;
	node *q2 = NULL;
	node *q3 = NULL;
	int n;
	printf("Enter n: ");
	scanf("%d", &n);
	int i;
	for (i=0; i<n; i++) {
		q1 = enqueue(q1, i+1);
	}
	printf("Enter the permutation: ");
	for (i=0; i<n; i++) {
		int d;
		scanf("%d", &d);
		q2 = enqueue(q2, d);
	}
	//first see q1
	//if not see s
	//again if not, push q1
	//repeat
	
	int comp;
	if (q2 != NULL) comp = dequeue(&q2);
	while (q1 != NULL || s != NULL) {
		if (q1 != NULL && q1->data == comp) {
			q3 = enqueue(q3, dequeue(&q1));
			printf("enqueue(Q2, dequeue(Q1))\n");
			if (q2 != NULL) comp = dequeue(&q2);
		}
		else if (s != NULL && s->data == comp) {
			q3 = enqueue(q3, pop(&s));
			printf("enqueue(Q2, pop(S))\n");
			if (q2 != NULL) comp = dequeue(&q2);
		}
		else {
			s = push(s, dequeue(&q1));
			printf("push(S, dequeue(Q1))\n");
		}
		//Incorrect Indicator
		if (q1 == NULL) {
			if (s != NULL && s->data != comp) {
				printf("\nNot a Stack Permutation: To enqueue %d into Q2, %d has to be enqueued first.\n", comp, s->data);
				printf("Q1 is empty.\n");
				printf("Current Stack: ");printList(s);
				printf("Remaining Permutation: %d ", comp);printList(q2);

			}
		}
	}
}


