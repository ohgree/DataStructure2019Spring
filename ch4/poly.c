#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUES 10
typedef struct poly_node* poly_pointer;
typedef struct poly_node {
   int coef;
   int expon;
   poly_pointer link;
} poly_node;
poly_pointer a, b;
poly_pointer avail = NULL;
void attach(int coefficient, int exponent, poly_pointer* ptr) {
   poly_pointer new;
   new = malloc(sizeof(poly_node));
   new->coef = coefficient;
   new->expon = exponent;
   new->link = NULL;
   (*ptr)->link = new;
   *ptr = new;
}
void erase(poly_pointer *ptr) {
   poly_pointer temp;
   while(*ptr) {
      temp = *ptr;
      *ptr = (*ptr)->link;
      free(temp);
   }
}
poly_pointer padd(poly_pointer a, poly_pointer b) {
   poly_pointer c, rear, temp;
   int sum;
   rear = malloc(sizeof(poly_node));
   c = rear;
   while(a && b) {
      if(a->expon < b->expon) {
         attach(b->coef, b->expon, &rear);
         b=b->link;
      } else if(a->expon == b->expon) {
         sum = a->coef + b->coef;
         attach(sum, a->expon, &rear);
         a=a->link;
         b=b->link;
      } else {
         attach(a->coef, a->expon, &rear);
         a=a->link;
      }
   }
   if(a) {
      for(; a ; a = a->link)
         attach(a->coef, a->expon, &rear);
   }
   if(b) {
      for(; b ; b = b->link)
         attach(b->coef, b->expon, &rear);
   }
   rear->link = NULL;
   temp = c;
   c = c->link;
   free(temp);
   return c;
}
poly_pointer get_node(void) {
   poly_pointer node;
   if(avail) {
      node = avail;
      avail = avail->link;
   } else {
      node = malloc(sizeof(poly_node));
   }
   return node;
}
poly_pointer cpadd(poly_pointer a, poly_pointer b) {
   poly_pointer c, rear;
   rear = get_node(); //zero polynomial
   int sum, done = 0;
   poly_pointer starta = a, startb = b; //
   a = a->link; //
   b = b->link; //
   c = rear;
   c->expon = -1;
   do {
      if(a->expon < b->expon) {
         attach(b->coef, b->expon, &rear);
         b=b->link;
      } else if(a->expon == b->expon) {
         if(starta == a) done = 1;
         sum = a->coef + b->coef;
         attach(sum, a->expon, &rear);
      } else {
         attach(a->coef, a->expon, &rear);
         a=a->link;
      }
   } while(!done);
   rear->link = c;
   
   return c;
}
void ret_node(poly_pointer ptr) {
   ptr->link = avail;
   avail = ptr;
}
void cerase(poly_pointer* ptr) {
   poly_pointer temp;
   if(*ptr) {
      temp = (*ptr)->link;
      (*ptr)->link = avail;
      avail = temp;
      *ptr = NULL;
   }
}
