#include <stdio.h>
#include <stdlib.h>
int bin_search(int* list, int len, int searchnum) {
   int left, right, middle;
   left = 0;
   right = len-1;
   while(left <= right) {
      middle = (left+right)/2;
      if(list[middle] < searchnum) {
         left = middle+1;
      } else if(list[middle] > searchnum) {
         right = middle-1;
      } else {
         return middle;
      }
   }
   return -1;
}
int main(void) {
   int* list;
   int len, searchnum;
   scanf("%d", &searchnum);
   scanf("%d", &len);
   list = (int*)malloc(sizeof(int)*len);
   for(int i=0 ; i<len ; i++) {
      scanf("%d", &list[i]);
   }
   printf("%d", bin_search(list, len, searchnum));
   return 0;
}
