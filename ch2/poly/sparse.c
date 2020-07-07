#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
#define COMPARE(x, y) x > y ? 1 : x < y ? -1 : 0

typedef struct {
   float coef;
   int expon;
} polynomial;
polynomial terms[MAX_TERMS];
int avail = 0;

void attach(float coef, int expon) {
   if(avail >= MAX_TERMS) {
      fprintf(stderr, "Error\n");
      exit(1);
   }
   terms[avail].coef = coef;
   terms[avail].expon = expon;
   avail++;
}
void padd(int starta, int finisha, int startb, int finishb, 
      int* startd, int* finishd) {
   float coefficient;
   *startd = avail;
   while(starta <= finisha && startb <= finishb) {
      switch(COMPARE(terms[starta].expon, terms[startb].expon)) {
         case 1:
            attach(terms[starta].coef, terms[starta].expon);
            starta++;
            break;
         case 0:
            coefficient = terms[starta].coef + terms[startb].coef;
            if(coefficient)
               attach(coefficient, terms[starta].expon);
            starta++;
            startb++;
            break;
         case -1:
            attach(terms[startb].coef, terms[startb].expon);
            startb++;
            break;
      }
   }
   for(; starta <= finisha ; starta++) {
      attach(terms[starta].coef, terms[starta].expon);
   }
   for(; startb <= finishb ; startb++) {
      attach(terms[startb].coef, terms[startb].expon);
   }
   *finishd = avail-1;
}
