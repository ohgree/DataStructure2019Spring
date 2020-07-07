#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUES 10
typedef struct {
   int key;
} element;
typedef struct queue* queue_pointer;
typedef struct queue {
   element data;
   queue_pointer link;
}queue;
queue_pointer front[MAX_QUEUES] = {0}, rear[MAX_QUEUES];
void addq(int i, element item) {
   queue_pointer new = malloc(sizeof(queue));
   new->data = item;
   new->link = NULL;
   if(front[i]) rear[i]->link = new;
   else front[i] = new;
   rear[i] = new;
}
element deleteq(int i) {
   queue_pointer deleted = front[i];
   element item;
   item = deleted->data;
   front[i] = front[i]->link;
   free(deleted);
   deleted = NULL;
   return item;
}
