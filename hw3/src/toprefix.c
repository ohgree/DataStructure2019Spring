#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {
   leftp, rightp, plus, minus, times, divide, mod, operand
} precedence;
/**
 * Pops precedence from stack. If stack is empty, prints error and terminates
 * program.
 * @param  stack Array for the stack that will be popped
 * @param  top   Integer of stack top index (-1 for empty stack)
 * @return       Popped value
 */
precedence pop(precedence* stack, int* top) {
   precedence value;
   if(*top <= -1) {
      //fprintf(stderr, "Error: popping empty stack\n");
      printf("Invalid expression\n");
      exit(1);
   }
   value = stack[(*top)--];
   return value;
}
/**
 * Push precedence onto stack.
 * @param stack Array for the stack that is used for this procedure.
 * @param top   Pointer to integer value for stack top index
 * @param token Procedence value that needs to be pushed.
 */
void push(precedence* stack, int* top, precedence token) {
   stack[++(*top)] = token;
}
/**
 * Same functionality as pop(), but the stack consists of strings.
 * @param stack[][] 2-D character array for storing strings as stack.
 * @param top       Pointer to integer representing top index of the stack
 */
char* pop_str(char stack[20][21], int* top) {
   if(*top <= -1) {
      //fprintf(stderr, "Error: popping empty stack\n");
      printf("Invalid expression\n");
      exit(1);
   }
   return stack[(*top)--];
}
/**
 * Same functionality as push(), but the stack consists of strings.
 * @param stack[][]  2-D character array for storing strings as stack.
 * @param top        Pointer to integer representing top index of the stack
 * @param expression String to push into the stack.
 */
void push_str(char stack[20][21], int* top, char* expression) {
   strcpy(stack[++(*top)], expression);
}
/**
 * Get corresponding character for given precedence token
 * @param  token Precedence value that you wish to get character for
 * @return       Character for given precedence.
 */
char getOp(precedence token) {
   switch(token) {
      case leftp: return '('; break;
      case rightp: return ')'; break;
      case plus: return '+'; break;
      case minus: return '-'; break;
      case times: return '*'; break;
      case divide: return '/'; break;
      case mod: return '%'; break;
      default: return -1;
   }
}
/**
 * Does the opposite of getOp. Gets precedence value from given operation char.
 * @param  op Character that needs analysising.
 * @return    Corresponding precedence value for op.
 */
precedence getToken(char op) {
   switch(op) {
      case '(': return leftp; break;
      case ')': return rightp; break;
      case '+': return plus; break;
      case '-': return minus; break;
      case '*': return times; break;
      case '/': return divide; break;
      case '%': return mod; break;
      default: return operand; break;
   }
}
/**
 * Translate infix expression to prefix expression
 * @param  infix  String containing infix expression to translate.
 * @param  prefix Character array where resulting prefix expressions will be
 *                written to.
 * @return        Translated prefix string.
 */
char* to_prefix(char* infix, char* prefix) {
   precedence pstack[20]; //precedence(operator) stack
   precedence token;
   char expstack[20][21]; //expression stack
   int ptop = -1, exptop = -1;
   char str[21], str1[21], str2[21], op;
   int isp[7] = {0, 9, 2, 2, 3, 3, 3};
   int icp[7] = {10, 9, 2, 2, 3, 3, 3};

   for(int i=0 ; i<(int)strlen(infix) ; i++) {
      op = infix[i];
      token = getToken(op);
      if(token == operand) {
         str[0] = op;
         str[1] = '\0';
         push_str(expstack, &exptop, str);
      } else if(token == rightp) {
         while(ptop != -1 && pstack[ptop] != leftp) {
            strcpy(str2, pop_str(expstack, &exptop));
            strcpy(str1, pop_str(expstack, &exptop));
            str[0] = getOp(pop(pstack, &ptop));
            str[1] = '\0';

            strcat(str, strcat(str1, str2));
            push_str(expstack, &exptop, str);
         }
         pop(pstack, &ptop);
      } else {
         if(ptop != -1 && isp[pstack[ptop]] >= icp[token]) {
            strcpy(str2, pop_str(expstack, &exptop));
            strcpy(str1, pop_str(expstack, &exptop));
            str[0] = getOp(pop(pstack, &ptop));
            str[1] = '\0';

            strcat(str, strcat(str1, str2));
            push_str(expstack, &exptop, str);
            push(pstack, &ptop, token);
         } else {
            push(pstack, &ptop, token);
         }
      }
   }
   while(exptop >= 0 && ptop >= 0) {
      strcpy(str2, pop_str(expstack, &exptop));
      strcpy(str1, pop_str(expstack, &exptop));
      str[0] = getOp(pop(pstack, &ptop));
      str[1] = '\0';

      strcat(str, strcat(str1, str2));
      push_str(expstack, &exptop, str);
   }
   if(exptop != 0 || ptop != -1) {
      printf("Invalid expression\n");
      exit(1);
   }
   strcpy(prefix, expstack[exptop]);
   return prefix;
}
int main(int argc, const char* argv[]) {
   char infix[21], prefix[21];

   printf("Infix: ");
   scanf("%s", infix);
   if(!to_prefix(infix, prefix)) {
      printf("Invalid expression\n");
      return 0;
   }
   printf("Prefix: %s\n", prefix);
   return 0;
}
