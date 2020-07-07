#include <stdio.h>
#define MAX_STACK_SIZE 100
#define EXIT_ROW 20
#define EXIT_COL 20
typedef struct {
   short int row;
   short int col;
   short int dir;
} element;
element stack[MAX_STACK_SIZE];
int top=-1;
typedef struct {
   short int vert;
   short int horiz;
} offsets;
offsets move[8];
int mark[MAX_STACK_SIZE][MAX_STACK_SIZE] = {0};
int maze[MAX_STACK_SIZE][MAX_STACK_SIZE] = {0};
element pop() {
   return stack[top--];
}
void push(element pos) {
   stack[++top].row = pos.row;
   stack[top].col = pos.col;
   stack[top].dir = pos.dir;
}
void path(void) {
   int i, row, col, nextRow, nextCol, dir, found=0;
   element position;
   mark[1][1] = 1;
   top = 0;
   stack[0].row = stack[0].col = 1;
   stack[0].dir = 0;
   while(top > -1 && !found) {   
      position = pop();
      row = position.row;
      col = position.col;
      dir = position.dir;
      while(dir < 8 && !found) {
         nextRow = row+move[dir].vert;
         nextCol = col+move[dir].horiz;
         if(nextRow == EXIT_ROW && nextCol == EXIT_COL) {
            found = 1;
         } else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
            mark[nextRow][nextCol] = 1;
            position.row = row;
            position.col = col;
            position.dir = ++dir;
            push(position);
            row = nextRow;
            col = nextCol;
            dir = 0;
         }
         dir++;
      }
   }
   if(found) {
      printf("The path is: \n");
      printf("row col\n");
      for(i=0 ; i<top ; i++) {
         printf("%2d%5d\n", stack[i].row, stack[i].col);
      }
      printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
   } else {
      printf("The maze does not have a path");
   }
}
