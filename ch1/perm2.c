#include <stdio.h>
#include <string.h>
void swap(char* a, char* b) {
   if(a==b) return;
   *a = *a+*b;
   *b = *a-*b;
   *a = *a-*b;
}
void perm(char set[], int len, int n) {
   if(len == n+1) {
      for(int i=0 ; i<len ; i++) {
         printf("%c", set[i]);
      }
      printf("\n");
      return;
   }
   for(int i=n ; i<len ; i++) {
      swap(&set[i], &set[n]);
      perm(set, len, n+1);
      swap(&set[i], &set[n]);
   }
}
int main(void) {
   char set[10];
   scanf("%s", set);
   perm(set, strlen(set), 0);
   return 0;
}
