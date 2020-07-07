#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"
#define MAX_PEOPLE_NUM 100
#define MAX_NAME_LENGTH 30

typedef struct _node{
   int index;
   struct _node* link;
} node;

node* top[MAX_PEOPLE_NUM] = {0};
char names[MAX_PEOPLE_NUM][MAX_NAME_LENGTH];
int nextIdx = 0;

/**
 * Gets index number of given name
 * @param  name Character string
 * @return      index of name string, or -1 if such index is not found
 */
int getNameIdx(char* name) {
   int idx;

   for(idx=0 ; idx<nextIdx ; idx++) {
      if(!strcmp(name, names[idx]))
         break;
   }
   if(idx == nextIdx) idx = -1;
   return idx;
}
/**
 * Push name index into stack
 * @param stack_idx Index of the stack to push to
 * @param names     Name index to push
 */
void push(int stack_idx, int names) {
   node* new = malloc(sizeof(node));

   new->index = names;
   new->link = top[stack_idx];
   top[stack_idx] = new;
}
/**
 * Pops name index from stack
 * @param  stack_idx Index of the stack to pop
 * @return           Popped name index
 */
int pop(int stack_idx) {
   node* popped;
   int value;

   if(!top[stack_idx]) {
      fprintf(stderr, "Trying to pop an empty stack. Terminating.\n");
      exit(1);
   }

   popped = top[stack_idx];
   value = popped->index;

   top[stack_idx] = top[stack_idx]->link;

   // Avoiding dangling pointers
   free(popped);
   popped = NULL;

   return value;
}
/**
 * Executes command
 * @param in  Input file pointer
 * @param out Output file pointer
 * @param cmd Command in character to execute
 */
void commandHandler(FILE* in, FILE* out, char cmd) {
   char name1[MAX_NAME_LENGTH], name2[MAX_NAME_LENGTH];
   int idx1, idx2, isFriend;
   node *prev;

      if(cmd == 'P') { // Add new person
         fscanf(in, " %s", name1);
         strcpy(names[nextIdx++], name1);
      } else if(cmd == 'F') { // Befriend
         fscanf(in, " %s", name1);
         fscanf(in, " %s", name2);
         idx1 = getNameIdx(name1);
         idx2 = getNameIdx(name2);

         push(idx1, idx2);
         push(idx2, idx1);
      } else if(cmd == 'U') { // Unfriend
         fscanf(in, " %s", name1);
         fscanf(in, " %s", name2);
         idx1 = getNameIdx(name1);
         idx2 = getNameIdx(name2);

         // remove idx2 from idx1 stack
         prev = NULL;
         for(node* ptr = top[idx1] ; ptr != NULL ; ptr = ptr->link) {
            if(prev == NULL) {
               if(ptr->index == idx2) {
                  top[idx1] = ptr->link;
                  free(ptr);
                  break;
               }
            } else if(ptr->index == idx2) {
               prev->link = ptr->link;
               free(ptr);
               break;
            }
            prev = ptr;
         }
         // remove idx1 from idx2 stack
         prev = NULL;
         for(node* ptr = top[idx2] ; ptr != NULL ; ptr = ptr->link) {
            if(prev == NULL) {
               if(ptr->index == idx1) {
                  top[idx2] = ptr->link;
                  free(ptr);
                  break;
               }
            } else if(ptr->index == idx1) {
               prev->link = ptr->link;
               free(ptr);
               break;
            }
            prev = ptr;
         }
      } else if(cmd == 'L') { // List all friends
         fscanf(in, " %s", name1);
         idx1 = getNameIdx(name1);

         if(idx1 == -1) {
            fprintf(out, "None\n");
            return;
         }

         for(node* ptr = top[idx1] ; ptr != NULL ; ptr = ptr->link) {
            fprintf(out, "%s", names[ptr->index]);
            if(ptr->link != NULL) fprintf(out, " ");
         }
         fprintf(out, "\n");
      } else if(cmd == 'Q') { // Check if friends
         fscanf(in, " %s", name1);
         fscanf(in, " %s", name2);
         idx1 = getNameIdx(name1);
         idx2 = getNameIdx(name2);

         isFriend = 0;
         for(node* ptr = top[idx1] ; ptr != NULL ; ptr = ptr->link) {
            if(ptr->index == idx2) {
               isFriend = 1;
               break;
            }
         }
         fprintf(out, "%s\n", isFriend ? "Yes" : "No");
      } else {
         fprintf(stderr, "Incorrect input file format.\n");
         exit(1);
      }
}
int main(int argc, const char* argv[]) {
   FILE* in_fp;
   FILE* out_fp;
   char command;

   if(!(in_fp = fopen(INPUT_FILENAME, "r"))) {
      fprintf(stderr, "Input file not found.\n");
      exit(1);
   }
   if(!(out_fp = fopen(OUTPUT_FILENAME, "w"))) {
      fprintf(stderr, "Cannot open output file.\n");
      exit(1);
   }

   while(fscanf(in_fp, " %c", &command) != EOF) {
      if(command == 'X') break;
      commandHandler(in_fp, out_fp, command);
   }

   fclose(in_fp);
   fclose(out_fp);

   // freeing all stack nodes
   for(int i=0 ; i<nextIdx ; i++) {
      while(top[i] != NULL)
         pop(i);
   }
   return 0;
}
