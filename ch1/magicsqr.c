#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 15

int main(void) {
   static int square[MAX_SIZE][MAX_SIZE];
   int i, j, row, column;
   int count;
   int size;
   printf("Size:");
   scanf("%d", &size);
   if(size<1 || size>MAX_SIZE) {
      fprintf(stderr, "Error\n");
      exit(1);
   }
   if(!(size%2)) {
      fprintf(stderr, "Error\n");
      exit(1);
   }
   for(i=0 ; i<size ; i++) {
      for(j=0 ; j<size ; j++) {
         square[i][j] = 0;
      }
   }

   square[0][(size-1)/2] = 1;
   i = 0;
   j = (size-1)/2;
   for(count = 2 ; count <= size*size ; count++) {
      row = (i-1 < 0) ? size-1 : i-1;
      column = (j-1 < 0) ? size-1 : j-1;
      if(square[row][column]) {
         i++;
         i%=size;
      } else {
         i = row;
         j = column;
      }
      square[i][j] = count;
   }

   for(i=0 ; i<size ; i++) {
      for(j=0 ; j<size ; j++) {
         printf("%3d", square[i][j]);
      }
      printf("\n");
   }
}
