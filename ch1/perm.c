#include <stdio.h>
void swap(char* a, char* b) {
   if(*a==*b) return;
   *a += *b;
   *b = *a-*b;
   *a -= *b;
}
void perm(char list[], int start, int end) {
   if(start == end) {
      printf("[");
      for(int i=0 ; i<=end ; i++) {
         printf("%c", list[i]);
      }
      printf("] ");
      return;
   }
   for(int i=start ; i<=end ; i++) {
      swap(&list[start], &list[i]);
      perm(list, start+1, end);
      swap(&list[start], &list[i]);
   }
}
int main(int argc, const char* argv[]) {
   char list[] = "abcd";
   perm(list, 0, 3);
   return 0;
}
