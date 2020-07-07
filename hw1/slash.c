#include <stdio.h>
#include <string.h>
void slash(char original_string[], int ostr_len, int binary_tree[], int tree_index) {
   int i;
   if(ostr_len-1 == tree_index) {
      for(i=0 ; i<ostr_len ; i++) {
         printf("%c", original_string[i]);
         if(i < ostr_len-1 && binary_tree[i])
            printf("/");
      }
      printf("\n");
      return;
   }
   binary_tree[tree_index] = 1;
   slash(original_string, ostr_len, binary_tree, tree_index + 1);
   binary_tree[tree_index] = 0;
   slash(original_string, ostr_len, binary_tree, tree_index + 1);
}
int main(int argc, const char* argv[]) {
   char o_string[11];
   int temp_tree[9];
   scanf("%[^\n]10s", o_string);
   slash(o_string, strlen(o_string), temp_tree, 0);
   return 0;
}
