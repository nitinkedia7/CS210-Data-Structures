#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct _stack{
	float data;
	struct _stack *ptr;
}stack;

stack *createNode() {
	return (stack *) malloc(sizeof(stack));
}

stack *push(stack *s, float d) {
	stack *temp;
	temp = createNode();
	temp->data = d;
	temp->ptr = s;
	return temp;
}

float pop(stack **ptrToS) {
	if (*ptrToS != NULL) {
		float data = (*ptrToS)->data;
		*ptrToS = (*ptrToS)->ptr;
		return data;
	}
	else {
		printf("Incorrect Input\n");
		exit(0);
	}
}

void printList(stack *s) {
	while (s != NULL) {
		printf("%f ", s->data);
		s = s->ptr;
	}
	printf("\n");
}

void main() {
	stack *s = NULL;
	char c[100];
	scanf("%s", c);
	int i = 0;
	while (c[i] != '\0') {
		if (c[i]>='0' && c[i]<='9') {
			float d = c[i]-'0';
			s = push(s,d);
		}
		else if (c[i] == '+') {
			float x = pop(&s);
			float y = pop(&s);
			float d = y+x;
			s = push(s, d);
		}
		else if (c[i] == '-') {
			float x = pop(&s);
			float y = pop(&s);
			float d = y-x;
			s = push(s, d);
		}
		else if (c[i] == '*') {
			float x = pop(&s);
			float y = pop(&s);
			float d = x*y;
			s = push(s, d);
		}
		else if (c[i] == '/') {
			float x = pop(&s);
			float y = pop(&s);
			float d = y/x;
			s = push(s, d);
		}
		else if (c[i] == '$') {
			float x = pop(&s);
			float y = pop(&s);
			float d = pow(y, x);
			s = push(s, d);
		}
		i++;
	}
	if (s != NULL && s->ptr == NULL) {
		float ans = pop(&s);
		printf("%f\n", ans);
	}
	else {
		printf("Incorrect Input\n");
	}
}
