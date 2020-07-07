#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int* failure(char* pattern, int* fail) {
   int n, i, j;
   n = strlen(pattern);
   fail[0] = -1;
   for(j=1 ; j<n ; j++) {
      i = fail[j-1];
      while(pattern[j] != pattern[i+1] && i>=0)
         i = fail[i];
      if(pattern[j] == pattern[i+1]) 
         fail[j] = i+1;
      else
         fail[j] = -1;
   }
   return fail;
}
int main(int argc, const char* argv[]) {
   char pat[10];
   int* fail = malloc(sizeof(int)*9);
   scanf("%s", pat);
   failure(pat, fail);
   for(int i=0 ; i<(int)strlen(pat) ; i++) {
      printf("%d ", fail[i]);
   }
   return 0;
}
