#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int* fail_fn(char* pattern) {
   int plen = (int)strlen(pattern);
   int* ff = (int*)malloc(sizeof(int)*plen);
   int j = 0;

   ff[0] = 0;
   for(int i=1 ; i<plen ; i++) {
      while(j > 0 && pattern[i] != pattern[j])
         //j: index after last matched char
         j = ff[j-1];
      if(pattern[i] == pattern[j])
         ff[i] = ++j;
      else
         ff[i] = 0;
   }
   return ff;
}
int* pmatch_all(char* string, char* pattern) {
   int j=0, r_cnt=0;
   int plen = strlen(pattern);
   int slen = strlen(string);
   int* ff = fail_fn(pattern);
   int* result = (int*)malloc(sizeof(int)*(slen));
   for(int i=0 ; i<(int)strlen(string) ; i++) {
      while(j>0 && pattern[j] != string[i])
         j = ff[j-1];
      if(pattern[j] == string[i]) {
         if(j == plen-1) {
            result[r_cnt++] = i+1-plen;
            j = ff[j];
         } else {
            j++;
         }
      }
   }
   result[r_cnt] = -1; //sign for end of array
   free(ff);
   printf("%d\n", r_cnt);
   return result;
}
int main(int argc, const char* argv[]) {
   int *result;
   int i=0;
   char str[1000001];
   char pat[1000001];
   scanf(" %[^\n]s", str);
   scanf(" %[^\n]s", pat);

   result = pmatch_all(str, pat);

   while(result[i] != -1) 
      printf("%d\n", 1+result[i++]);

   free(result);
   return 0;
}
