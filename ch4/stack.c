#include <stdio.h>
#include <stdlib.h>
#define MAX_STACKS 10
typedef struct {
   int key;
} element;
typedef struct stack* stack_pointer;
typedef struct stack {
   element data;
   stack_pointer link;
}stack;
stack_pointer top[MAX_STACKS] = {0};
void push(int i, element item) {
   stack_pointer new = malloc(sizeof(stack));
   new->data = item;
   new->link = top[i];
   top[i] = new;
}
element pop(int i) {
   stack_pointer popped = top[i];
   element result;
   top[i] = top[i]->link;
   result = popped->data;
   free(popped);
   popped = NULL;
   return result;
}
