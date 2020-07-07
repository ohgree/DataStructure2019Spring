#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"

typedef enum {head, entry} tagfield;
typedef struct matrix_node* matrix_pointer;
struct entry_node {
   int row;
   int col;
   int value;
};
struct matrix_node {
   matrix_pointer down;
   matrix_pointer right;
   tagfield tag;
   union {
      matrix_pointer next;
      struct entry_node entry;
   } u;
};
matrix_pointer hdnode[MAX_SIZE];

matrix_pointer new_node() {
   matrix_pointer new = malloc(sizeof(struct matrix_node));
   return new;
}
matrix_pointer mtranspose(matrix_pointer header) {
   matrix_pointer tnode;
   int num_rows, num_cols;
   num_rows = header->u.entry.row;
   num_cols = header->u.entry.col;

   tnode = new_node();
   tnode->tag = entry;
   tnode->u.entry.row = num_cols;
   tnode->u.entry.col = num_rows;

   return tnode;
}
matrix_pointer mread() {
   int num_rows, num_cols, num_terms, num_heads, i;
   int row, col, value, current_row;
   matrix_pointer temp, last, node;

   printf("Enter the number of rows, columns and number of nonzero terms:");
   scanf("%d %d %d", &num_rows, &num_cols, &num_terms);
   num_heads = (num_cols > num_rows) ? num_cols : num_rows;

   node = new_node();
   node->tag = entry;
   node->u.entry.row = num_rows;
   node->u.entry.col = num_cols;
   
   if(!num_heads)
      node->right = node;
   else {
      for(int i=0 ; i<num_heads ; i++) {
         temp = new_node();
         hdnode[i] = temp;
         hdnode[i]->tag = head;
         hdnode[i]->right = temp;
         hdnode[i]->u.next = temp;
      }
      current_row = 0;
      last = hdnode[0];
      for(int i=0 ; i<num_terms ; i++) {
         printf("Enter row, column and value:");
         scanf("%d %d %d", &row, &col, &value);
         if(row > current_row) {
            last->right = hdnode[current_row];
            current_row = row;
            last = hdnode[row];
         }
         temp = new_node();
         temp->tag = entry;
         temp->u.entry.value = value;
         temp->u.entry.row = row;
         temp->u.entry.col = col;
         last->right = temp;
         last = temp;

         hdnode[col]->u.next->down = temp;
         hdnode[col]->u.next = temp;
      }
      last->right = hdnode[current_row];

      for(i=0 ; i<num_cols ; i++) {
         hdnode[i]->u.next->down = hdnode[i];
      }

      for(i=0 ; i<num_heads-1 ; i++)
         hdnode[i]->u.next = hdnode[i+1];
      hdnode[num_heads-1]->u.next = node;
      node->right = hdnode[0];
   }
   return node;
}
void mwrite(matrix_pointer node) {
   int i;
   matrix_pointer temp, head = node->right;

   /*printf("\n num_rows=%d, num_cols=%d\n", 
         node->u.entry.row, node->u.entry.col);
   printf("The matrix by row, column, and value:\n\n");*/

   printf("%d %d %d\n",
      node->u.entry.row, node->u.entry.col, node->u.entry.value);

   for(i=0 ; i < node->u.entry.row ; i++) {
      for(temp=head->right ; temp!=head ; temp=temp->right)
         printf("%d %d %d\n",
               temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
      head = head->u.next;
   }
}
int main(int argc, const char* argv[]) {
   matrix_pointer node=mread();
   mwrite(node);
   return 0;
}
