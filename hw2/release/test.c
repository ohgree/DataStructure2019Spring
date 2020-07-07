#include <stdio.h>
#include <stdlib.h>
int main(void) {
   int* a = (int*)malloc(sizeof(int)*5);
   for(int i=0 ; i<5 ; i++) {
      a[i] = i;
   }
   a[5] = 6;
   printf("%d", a[5]);

   return 0;
}
