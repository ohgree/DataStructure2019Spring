#include <stdio.h>
#include <string.h>
/**
 * Prints slashed text recursively
 * @param original_string Character array from the input
 * @param ostr_len        Length of original_string
 * @param binary_tree     Binary tree of 0 and 1 in the making.
 *                        Needs to be empty on initial call.
 * @param tree_index      Current index of the tree, where it's empty.
 */
void slash(char original_string[], int ostr_len, int binary_tree[], int tree_index) {
   int i;
   // end condition
   if(ostr_len-1 == tree_index) {
      // prints original_string with translated binary_tree characters between.
      for(i=0 ; i<ostr_len ; i++) {
         printf("%c", original_string[i]);
         if(i < ostr_len-1 && binary_tree[i])
            printf("/");
      }
      printf("\n");
      return;
   }

   // appends 1 or 0 to binary_tree and calls on itself, with index increased.
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
