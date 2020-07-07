#include <stdio.h>
void swap(char* x, char* y) {
   char tmp = *x;
   *x = *y;
   *y = tmp;
}
void perm(char* list, int i, int n) {
   int j;
   if(i==n) {
      printf("[");
      for(j=0 ; j<=n ; j++)
         printf("%c", list[j]);
      printf("] ");
   } else {
      for(j=i ; j<=n ; j++) {
         swap(&list[i], &list[j]);
         perm(list, i+1, n);
         swap(&list[i], &list[j]);
      }
   }
}
int main(int argc, const char* argv[]) {
   char list[] = "abcd";
   perm(list, 0, 3);
   return 0;
}
