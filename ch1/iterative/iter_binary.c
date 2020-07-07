#include <stdio.h>
int main(int argc, const char* argv[]) {
   int left=0, right=9, middle, searching = 6;
   int olist[10] = {1, 3, 4, 5, 6, 7, 9, 10, 11, 12};
   while(left <= right) {
      middle = (left+right)/2;
      if(olist[middle] == searching) {
         printf("%d", middle);
         break;
      } else if(olist[middle] < searching) {
         left = middle+1;
      } else {
         right = middle-1;
      }
   }
   printf("nop!");
   return 0;
}
