#include <stdio.h>
#include <stdlib.h>
#define IS_EMPTY(ptr) (!(ptr))

typedef struct list_node* list_pointer;
typedef struct list_node{
   int data;
   list_pointer link;
} list_node;
list_pointer ptr=NULL;
void insert(list_pointer* ptr, list_pointer node) {
   /*
   list_pointer temp;
   temp = malloc(sizeof(list_node));
   if(!temp) {
      fprintf(stderr, "Memory full\n");
      exit(1);
   }
   if(*ptr) {
      ptr->link = 
   }*/
}
void delete(list_pointer *ptr, list_pointer trail, list_pointer node) {
   if(trail) {
      trail->link = node->link;
   } else {
      *ptr = (*ptr)->link;
   }
   free(node);
}
void merge(list_pointer x, list_pointer y, list_pointer* z) {
   list_pointer last;
   last = malloc(sizeof(list_node));
   *z = last;
   while( x && y ) {
      if(x->data <= y->data) {
         last->link = x;
         last = x;
         x = x->link;
      } else {
         last->link = y;
         last = y;
         y = y->link;
      }
   }
   if(x) last->link = x;
   if(y) last->link = y;
   last = *z;
   *z = last->link;
   free(last);
   last = NULL;
}
