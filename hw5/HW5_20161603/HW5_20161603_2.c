#include <stdio.h>
#include <stdlib.h>

typedef struct _tree_node {
   int value;
   struct _tree_node *left, *right;
} tree_node;

typedef struct _stack_node {
   tree_node* node;
   struct _stack_node* link;
} stack_node;

stack_node* stack = NULL;
tree_node* bst = NULL;

/**
 * Push tree node into stack
 * @param node Node to push
 */
void push(tree_node* node) {
   stack_node* new = malloc(sizeof(stack_node));
   new->node = node;
   new->link = stack;
   stack = new;
}

/**
 * Pop tree node from stack
 * @return  Popped tree node
 */
tree_node* pop(void) {
   stack_node* popped;
   tree_node* node;

   if(!stack) {
      fprintf(stderr, "Popping empty stack.\n");
      exit(1);
   }

   popped = stack;
   node = popped->node;
   stack = stack->link;
   free(popped);
   return node;
}

/**
 * Create new tree node
 * @param  value Value of the new node
 * @return       Address of the created node.
 */
tree_node* new_node(int value) {
   tree_node* new;
   new = malloc(sizeof(tree_node));
   new->value = value;
   new->left = new->right = NULL;
   return new;
}

/**
 * construct BST from preorder traversal
 * @param  ptrav Preorder traversal
 * @param  size  Length of ptrav[] array
 * @return       Root node of constructed BST
 */
tree_node* construct_BST(int ptrav[], int size) {
   tree_node* node;

   push(bst = new_node(ptrav[0]));

   for(int i=1 ; i<size ; i++) {
      node = NULL;
      while(stack && ptrav[i] > stack->node->value)
         node = pop();

      if(node) {
         push(node->right = new_node(ptrav[i]));
      } else {
         push(stack->node->left = new_node(ptrav[i]));
      }
   }

   while(!stack)
      pop();

   return bst;
}

/**
 * Print BST in inorder format
 * @param root BST to print
 */
void print_inorder(tree_node* root) {
   if(root) {
      print_inorder(root->left);
      printf("%d ", root->value);
      print_inorder(root->right);
   }
}

/**
 * Print BST in postorder method
 * @param root BST to print
 */
void print_postorder(tree_node* root) {
   if(root) {
      print_postorder(root->left);
      print_postorder(root->right);
      printf("%d ", root->value);
   }
}

/**
 * Free BST from memory
 * @param root BST to free
 */
void free_BST(tree_node* root) {
   if(root) {
      free_BST(root->left);
      free_BST(root->right);
      free(root);
   }
}

int main(int argc, const char* argv[]) {
   int size, *ptrav;

   scanf("%d", &size);

   ptrav = malloc(sizeof(int)*size);
   for(int i=0 ; i<size ; i++) {
      scanf("%d", &ptrav[i]);
   }


   // Checking if there are duplicate value in given traversal
   for(int i=0 ; i<size ; i++)
      for(int j=i+1 ; j<size ; j++)
         if(ptrav[i] == ptrav[j]) {
            printf("cannot construct BST\n");
            return 0;
         }

   construct_BST(ptrav, size);

   printf("Inorder: ");
   print_inorder(bst);
   printf("\n");
   printf("Postorder: ");
   print_postorder(bst);
   printf("\n");

   free_BST(bst);

   return 0;
}
