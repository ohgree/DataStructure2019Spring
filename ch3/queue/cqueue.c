#include <stdio.h>
#define MAX_QUEUE_SIZE 100
typedef struct {
   int key;
} element;
element queue[MAX_QUEUE_SIZE];
int rear=-1;
int front=-1;
int IsEmptyQ() { return rear == front; }
int IsFullQ() { return (rear+1)%MAX_QUEUE_SIZE == front; }
void addq(element item) {
   rear = (rear+1)%MAX_QUEUE_SIZE;
   if(IsEmptyQ())
      return;
   queue[rear] = item;
}
element deleteq() {
   if(IsEmptyQ())
      return queue[0];
   front = (front+1)%MAX_QUEUE_SIZE;
   return queue[front];
}
