#include <stdio.h>
void swap(int* a, int* b) {
   if(*a == *b) return;
   *a = *a+*b;
   *b = *a-*b;
   *a = *a-*b;
}
void select_sort(int* n, int len) {
   int min_idx;
   for(int i=0 ; i<len-1 ; i++) {
      min_idx = i;
      for(int j=i+1 ; j<len ; j++) {
         if(n[min_idx] > n[j])
            min_idx = j;
      }
      swap(&n[min_idx], &n[i]);
   }
}
int main(void) {
   int n[10];
   for(int i=0 ; i<10 ; i++) {
      scanf("%d", &n[i]);
   }
   select_sort(n, 10);
   for(int i=0 ; i<10 ; i++) {
      printf("%d ", n[i]);
   }
   return 0;
}
