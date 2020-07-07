#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char pat[] = "abaabab";
int failure[10];
void fail() {
   int i, j, n;
   n = strlen(pat);
   failure[0] = -1;
   for(int i=1 ; i<n ; i++) {
      j = failure[i-1];
      while(pat[i] != pat[j+1] && j >= 0)
         j = failure[j];
      if(pat[i] == pat[j+1])
         failure[i] = j+1;
      else
         failure[i] = -1;
   }
}
int main(int argc, const char* argv[]) {
   fail();
   for(int i=0 ; i<(int)strlen(pat) ; i++) {
      printf("%d", failure[i]);
   }
   return 0;
}
