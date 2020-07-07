#include <stdio.h>
#include <stdlib.h>
int** make2dArray(int rows, int cols) {
   int** arr;
   arr = (int**)malloc(sizeof(int*)*rows);
   for(int i=0 ; i<rows ; i++) {
      arr[i] = (int*)malloc(sizeof(int)*cols);
   }
   return arr;
}
