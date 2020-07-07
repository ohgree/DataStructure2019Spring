#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
struct node {
   int key;
   treePointer parent;
   treePointer leftChild;
   treePointer rightChild;
};

typedef struct _stack_element* stack_element;
struct _stack_element {
   int value;
   struct _stack_element* link;
};

stack_element stack = NULL;
treePointer heap = NULL;
int node_cnt = 0;

/**
 * Create new tree node
 * @param  key    Key value for current node
 * @param  parent Parent node address. Set to NULL if this node is root node.
 * @return        Address of new tree node created.
 */
treePointer new_node(int key, treePointer parent) {
   treePointer new;

   new = malloc(sizeof(struct node));
   new->key = key;
   new->leftChild = new->rightChild = NULL;
   new->parent = parent;

   return new;
}
/**
 * Push value onto stack
 * @param value Integer value to push
 */
void push(int value) {
   stack_element new = malloc(sizeof(struct _stack_element));
   new->value = value;
   new->link = stack;
   stack = new;
}
/**
 * Pop value from stack
 * @return  Popped value
 */
int pop(void) {
   int value;
   stack_element popped;

   if(!stack) {
      fprintf(stderr, "Error popping empty stack\n");
      exit(1);
   }

   popped = stack;
   stack = stack->link;
   value = popped->value;
   free(popped);

   return value;
}

/**
 * Searches for key value in tree starting from root
 * @param  root Start point of the tree
 * @param  key  Value to find
 * @return      1, if key is found
 *              0, if key is not found
 */
int search(treePointer root, int key) {
   if(root) {
      if(root->key == key)
         return 1;
      else
         return search(root->leftChild, key) || search(root->rightChild, key);
   }
   return 0;
}

/**
 * Create new node in heap
 * @param  key Value for node
 * @return     Address of created node
 */
treePointer makeNext(int key) {
   treePointer ptr;
   for(int i=node_cnt+1 ; i>1 ; i/=2)
      push(i%2);
   ptr = heap;
   while(stack) {
      if(pop() == 0) {
         if(!ptr->leftChild) {
            ptr->leftChild = new_node(key, ptr);
         }
         ptr = ptr->leftChild;
      } else {
         if(!ptr->rightChild) {
            ptr->rightChild = new_node(key, ptr);
         }
         ptr = ptr->rightChild;
      }
   }
   node_cnt++;
   return ptr;
}

/**
 * Get last node from heap
 * @return  last node from heap
 */
treePointer getLast(void) {
   treePointer ptr;

   for(int i=node_cnt ; i>1 ; i/=2)
      push(i%2);

   ptr = heap;
   while(stack) {
      if(pop() == 0) {
         ptr = ptr->leftChild;
      } else {
         ptr = ptr->rightChild;
      }
   }
   return ptr;
}

/**
 * Insert new node into heap
 * @param  key Value for new node
 * @return     1 if key is successfully added to heap
 *             0 if key is already in heap
 */
int insert(int key) {
   treePointer ptr;

   if(search(heap, key))
      return 0;

   if(!heap) {
      heap = new_node(key, NULL);
      node_cnt++;
      return 1;
   }

   ptr = makeNext(key);

   // allign heap to meet criteria for max heap
   while(ptr->parent && ptr->parent->key < ptr->key) {
      int temp = ptr->parent->key;
      ptr->parent->key = ptr->key;
      ptr->key = temp;
      ptr = ptr->parent;
   }
   return 1;
}

/**
 * Delete a node from heap, and fetches its value.
 * @param  deleted Pointer for storing deleted key value
 * @return         0 if heap is empty, 1 if deletion was successful
 */
int delete(int* deleted) {
   treePointer ptr, last;

   if(!heap) return 0;

   last = getLast();
   *deleted = heap->key;
   if(last == heap) {
      heap = NULL;
      free(last);
      node_cnt--;
      return 1;
   }
   heap->key = last->key;
   if(last->parent->leftChild == last)
      last->parent->leftChild = NULL;
   else
      last->parent->rightChild = NULL;
   free(last);
   last = NULL;

   ptr = heap;
   while(ptr->leftChild || ptr->rightChild) {
      if(ptr->leftChild && ptr->rightChild) {
         ptr = (ptr->leftChild->key > ptr->rightChild->key) ?
         ptr->leftChild : ptr->rightChild;
      } else if(ptr->leftChild) {
         ptr = ptr->leftChild;
      } else if(ptr->rightChild) {
         ptr = ptr->rightChild;
      }

      if(ptr->parent->key < ptr->key) {
         int temp = ptr->parent->key;
         ptr->parent->key = ptr->key;
         ptr->key = temp;
      } else break;
   }
   node_cnt--;
   return 1;
}

int main(int argc, const char* argv[]) {
   char cmd;
   int key, result;
   while(1) {
      scanf("%c", &cmd);
      if(cmd == 'q') {
         // freeing all nodes
         while(heap)
            delete(&result);
         break;
      }

      if(cmd == 'i') {
         scanf("%d", &key);
         if(insert(key)) {
            printf("Insert %d\n", key);
         } else {
            printf("Exist number\n");
         }
      } else if(cmd == 'd') {
         if(delete(&result)) {
            printf("Delete %d\n", result);
         } else {
            printf("The heap is empty\n");
         }
      }
   }
   return 0;
}
