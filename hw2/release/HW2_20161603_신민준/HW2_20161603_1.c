#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Failure function for Knuth–Morris–Pratt algorithm.
 *    failure function is also created using KMP algorithm.
 *    failure function's element value is the exact index to look for next.
 * @param  pattern Pattern string to find failure function for
 * @return         Failure function for given pattern
 */
int* fail_fn(char* pattern) {
   int plen = (int)strlen(pattern);
   int* ff = (int*)malloc(sizeof(int)*plen);
   int j = 0;

   ff[0] = 0;
   for(int i=1 ; i<plen ; i++) { // i: index for pattern 1
      while(j > 0 && pattern[i] != pattern[j])
         // j: index for pattern 2, which is used for comparing
         j = ff[j-1];
      if(pattern[i] == pattern[j])
         ff[i] = ++j;
      else
         ff[i] = 0;
   }
   return ff; // this pointer needs to be free'd after
}
/**
 * Find all index of pattern in string using Knuth–Morris–Pratt algorithm
 * @param  string  Pointer of string to find pattern in
 * @param  pattern Pointer of pattern string to find
 * @return         Pointer to array holding all indexes of found patterns.
 *                 The end of array is noted with value -1
 */
int* pmatch_all(char* string, char* pattern) {
   int j=0, r_cnt=0;
   int plen = strlen(pattern);
   int slen = strlen(string);
   int* ff = fail_fn(pattern);
   int* result = (int*)malloc(sizeof(int)*(slen+1));

   for(int i=0 ; i<(int)strlen(string) ; i++) { // i: index for string
      while(j>0 && pattern[j] != string[i]) // j: index for pattern
         // change pattern's index if characters did not match
         j = ff[j-1];
      if(pattern[j] == string[i]) {
         if(j == plen-1) {
            // reached end of pattern -> found pattern
            result[r_cnt++] = i+1-plen; // record index in result
            j = ff[j]; // go for another match
         } else {
            j++;
         }
      }
   }
   result[r_cnt] = -1; // end of array is signified by -1

   free(ff); // freeing failure function, as it was malloc'ed in fail_fn()
   return result;
}
int main(int argc, const char* argv[]) {
   int *result;
   int i=0;
   char str[31];
   char pat[31];

   scanf(" %[^\n]s", str);
   scanf(" %[^\n]s", pat);

   result = pmatch_all(str, pat);

   while(result[i] != -1) // printing results
      printf("%d\n", result[i++]);

   free(result); // freeing result, as it was allocated in pmatch_all()
   return 0;
}
