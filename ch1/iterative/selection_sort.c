#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

#include <stdio.h>
int main(int argc, const char* argv[]) {
   int list[10] = {6, 1, 2, 7, 10, 4, 9, 8, 5, 3};
   int n = 10;
   int i, j, min_index, tmp;

   for(i=0 ; i<n ; i++) {
      printf("%d ", list[i]);
   }
   printf("\n");

   for(i=0 ; i<n-1 ; i++) {
      min_index = i;
      for(j=i+1 ; j<n ; j++) {
         if(list[min_index] > list[j]) {
            min_index = j;
         }
      }
      SWAP(list[i], list[min_index], tmp);
   }

   for(i=0 ; i<n ; i++) {
      printf("%d ", list[i]);
   }
   printf("\n");

   return 0;
}
