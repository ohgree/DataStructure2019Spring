#include <stdio.h>
#include <string.h>
int failure[10];
void ff(char* pat) {
   int i, j, n = strlen(pat);
   failure[0] = -1;
   for(i=1 ; i<n ; i++) {
      j = failure[i-1];
      while(pat[j+1] != pat[i] && j != -1)
         j = failure[j];
      if(pat[j+1] == pat[i])
         failure[i] = j+1;
      else
         failure[i] = -1;
   }
}
int find(char* string, char* pat) {
   int i=0, j=0;
   int slen, plen;
   slen = strlen(string);
   plen = strlen(pat);
   while(i<slen && j<plen) {
      if(pat[j] == string[i]){
         i++;
         j++;
      } else if(j == 0) {
         i++;
      } else {
         j = failure[j-1]+1;
      }
   }
   
   return (j == plen) ? i-plen : -1;
}
int main(void) {
   char str[20];
   char pat[20];
   scanf("%s", str);
   scanf("%s", pat);
   ff(pat);
   for(int i=0 ; i<10 ; i++) {
      printf("%d ", failure[i]);
   }
   printf("\n");
   
   printf("%d\n", find(str, pat));
   return 0;
}
