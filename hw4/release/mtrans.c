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
matrix_pointer hdnode_t[MAX_SIZE];

/**
 * returns one newly allocated node
 * @return node created
 */
matrix_pointer new_node() {
   matrix_pointer new = malloc(sizeof(struct matrix_node));
   return new;
}
/**
 * Transposes given sparse matrix
 * @param  header pointer to header node for the sparse matrix to transpose
 * @return        pointer to header node of the transposed sparse matrix
 */
matrix_pointer mtranspose(matrix_pointer header) {
   matrix_pointer tnode, last, temp;
   int num_rows, num_cols, num_terms, num_heads;
   int row, col, value;

   num_rows = header->u.entry.row;
   num_cols = header->u.entry.col;
   num_terms = header->u.entry.value;

   tnode = new_node();
   tnode->tag = entry;
   tnode->u.entry.row = num_cols;
   tnode->u.entry.col = num_rows;
   tnode->u.entry.value = num_terms;

   num_heads = (num_rows > num_cols) ? num_rows : num_cols;

   for(int i=0 ; i<num_heads ; i++) {
      temp = new_node();
      hdnode_t[i] = temp;
      hdnode_t[i]->tag = head;
      hdnode_t[i]->right = temp;
      hdnode_t[i]->u.next = temp;
   }
   for(int i=0 ; i<num_heads ; i++) {
      last = hdnode_t[i];
      // read hdnode[i] column-wise, while writing to hdnode_t[i]
      // row-wise, with the row and column value exchanged.
      for(matrix_pointer ptr = hdnode[i]->down ;
            ptr != hdnode[i] ; ptr = ptr->down) {
         row = ptr->u.entry.row;
         col = ptr->u.entry.col;
         value = ptr->u.entry.value;

         temp = new_node();
         temp->tag = entry;
         temp->u.entry.row = col;
         temp->u.entry.col = row;
         temp->u.entry.value = value;
         last->right = temp;
         last = temp;

         hdnode_t[row]->u.next->down = temp;
         hdnode_t[row]->u.next = temp;
      }
      last->right = hdnode_t[i]; // finishing row-wise circular structure
      for(int i=0 ; i<num_heads ; i++) {
         // finishing column-wise circular structure
         hdnode_t[i]->u.next->down = hdnode_t[i];
      }
   }

   // Set u.next to point to next header node, in circular structure
   for(int i=0 ; i<num_heads-1 ; i++)
      hdnode_t[i]->u.next = hdnode_t[i+1];
   hdnode_t[num_heads-1]->u.next = tnode;
   tnode->right = hdnode_t[0];

   return tnode;
}
/**
 * read sparse matrix from INPUT_FILENAME
 * @return pointer to the head node read
 */
matrix_pointer mread() {
   int num_rows, num_cols, num_terms, num_heads, i;
   int row, col, value, current_row;
   matrix_pointer temp, last, node;
   FILE* fp;
   if(!(fp = fopen(INPUT_FILENAME, "r"))) {
      fprintf(stderr, "Input file is not found. Terminating.\n");
      exit(1);
   }

   fscanf(fp, "%d %d %d", &num_rows, &num_cols, &num_terms);
   num_heads = (num_cols > num_rows) ? num_cols : num_rows;

   node = new_node();
   node->tag = entry;
   node->u.entry.row = num_rows;
   node->u.entry.col = num_cols;
   node->u.entry.value = num_terms;

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
         fscanf(fp, "%d %d %d", &row, &col, &value);
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
   fclose(fp);
   return node;
}
/**
 * Writes the content of sparse matrix to OUTPUT_FILENAME
 * @param node Pointer to head node of sparse matrix
 */
void mwrite(matrix_pointer node) {
   int i;
   matrix_pointer temp, head = node->right;
   FILE* fp;

   if(!(fp = fopen(OUTPUT_FILENAME, "w"))) {
      fprintf(stderr, "Error while writing output to file.\n");
      exit(1);
   }

   fprintf(fp, "%d %d %d\n",
      node->u.entry.row, node->u.entry.col, node->u.entry.value);

   for(i=0 ; i < node->u.entry.row ; i++) {
      for(temp=head->right ; temp!=head ; temp=temp->right)
         fprintf(fp, "%d %d %d\n",
               temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
      head = head->u.next;
   }
   fclose(fp);
}
int main(int argc, const char* argv[]) {
   matrix_pointer node, tnode, temp;
   int num_heads;

   node = mread();
   tnode = mtranspose(node);
   mwrite(tnode);

   // freeing nodes
   num_heads = (node->u.entry.row > node->u.entry.col) ?
      node->u.entry.row : node->u.entry.col;
   for(int i=0 ; i<num_heads ; i++) {
      // freeing initial sparse matrix
      for(matrix_pointer ptr = hdnode[i]->right ; ptr != hdnode[i] ; ){
         temp = ptr;
         ptr = ptr->right;
         free(temp);
      }
      // freeing transposed sparse matrix
      for(matrix_pointer ptr = hdnode_t[i]->right ; ptr != hdnode_t[i] ; ){
         temp = ptr;
         ptr = ptr->right;
         free(temp);
      }
   }
   return 0;
}
