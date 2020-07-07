#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
#define MAX_ROWS 10
#define MAX_COLS 10
typedef struct {
   int row;
   int col;
   int value;
} term;
term a[MAX_TERMS];

void transpose(term a[], term b[]) {
   int n, currentb;
   n = a[0].value;
   b[0].row = a[0].row;
   b[0].col = a[0].col;
   b[0].value = n;
   
   if(n) {
      currentb = 1;
      for(int i=0 ; i<a[0].col ; i++) {
         for(int j=1 ; j<=n ; j++) {
            if(a[j].col == i) {
               b[currentb].row = a[j].col;
               b[currentb].col = a[j].row;
               b[currentb].value = a[j].value;
               currentb++;
            }
         }
      }
   }
}
void fast_transpose(term a[], term b[]) {
   int row_terms[MAX_COLS], starting_pos[MAX_TERMS];
   int num_cols = a[0].col, num_terms = a[0].value;
   int j;
   b[0].row = a[0].col;
   b[0].col = a[0].row;
   b[0].value = a[0].value;
   if(num_terms) {
      for(int i=0 ; i<num_cols ; i++)
         row_terms[i] = 0;
      for(int i=1 ; i<=num_terms ; i++)
         row_terms[a[i].row]++;
      starting_pos[0] = 1;
      for(int i=1 ; i<num_cols ; i++)
         starting_pos[i] = starting_pos[i-1] + row_terms[i-1];
      for(int i=1 ; i<=num_terms ; i++) {
         j = starting_pos[a[i].col]++;
         b[j].row = a[i].col;
         b[j].col = a[i].row;
         b[j].value = a[i].value;
      }
   }
}
void storesum(term d[], int* totald, int row, int column, int* sum) {
   if(*sum){
      if(*totald < MAX_TERMS) {
         d[++*totald].row = row;
         d[*totald].col = column;
         d[*totald].value = *sum;
         *sum = 0;
      } else {
         fprintf(stderr, "Number of terms exceeded %d\n", MAX_TERMS);
         exit(1);
      }
   }
}
void mmult(term a[], term b[], term d[]) {
   int column, totalb = b[0].value, totald = 0;
   int rows_a = a[0].row, cols_a = a[0].col, totala = a[0].value;
   int cols_b = b[0].col;
   int row_begin = 1, row = a[1].row, sum = 0;
   term new_b[MAX_TERMS];
   if(cols_a != b[0].row) {
      fprintf(stderr, "Incompatible matrices\n");
      exit(1);
   }
   fast_transpose(b, new_b);
   a[totala+1].row = rows_a;
   new_b[totalb+1].row = cols_b;
   new_b[totalb+1].col = -1;

   for(int i=1 ; i<= totala; ) {
      column = new_b[1].row;
      for(int j=1 ; j<=totalb+1 ;) {
         if(a[i].row != row) {
            storesum(d, &totald, row, column, &sum);
            i = row_begin;
            for(; new_b[j].row == column ; j++);
            column = new_b[j].row;
         } else if(new_b[j].row != column) {
            storsum(d, &totald, row, column, &sum);
            i = row_begin;
            column = new_b[j].row;
         } else {
            switch(COMPARE(a[i].col, new_b[j].col)) {
               case -1: i++; break;
               case 0: sum += (a[i++].value * new_b[j++].value); break;
               case 1: j++; break;
            }
         }
      }
      for(; a[i].row == row ; i++);
      row_begin = i;
      row = a[i].row;
   }
   d[0].row = rows_a;
   d[0].col = cols_b;
   d[0].value = totald;
}
