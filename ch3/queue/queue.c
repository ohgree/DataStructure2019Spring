#include <stdio.h>
#define MAX_QUEUE_SIZE 100
typedef struct {
   int key;
} element;
element queue[MAX_QUEUE_SIZE];
int rear=-1;
int front=-1;
int IsEmptyQ() { return rear == front; }
int IsFullQ() { return rear == MAX_QUEUE_SIZE-1; }
void addq(element item) {
   if(IsFullQ())
      return;
   queue[++rear] = item;
}
element deleteq() {
   if(IsEmptyQ())
      return queue[0];
   return queue[++front];
}
