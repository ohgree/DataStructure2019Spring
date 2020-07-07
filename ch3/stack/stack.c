#include <stdio.h>
#define MAX_STACK_SIZE 100
typedef struct {
   int key;
} element;
element stack[MAX_STACK_SIZE];
int top = -1;
int IsEmpty(void) { return top == -1; }
int IsFull(void) { return top == MAX_STACK_SIZE-1; }
void stackFull(void);
element stackEmpty(void) {
   return stack[0];
}
void push(element item) {
   if(IsFull())
      stackFull();
   else
      stack[++top] = item;
}
element pop(void) {
   if(IsEmpty())
      return stackEmpty();
   return stack[top--];
}
