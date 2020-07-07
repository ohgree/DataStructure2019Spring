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
   if(*top <= -1) { //popping empty stack
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
   stack[++(*top)] = token; // push token into stack
}
/**
 * Same functionality as pop(), but the stack consists of strings.
 * @param stack[][] 2-D character array for storing strings as stack.
 * @param top       Pointer to integer representing top index of the stack
 */
char* pop_str(char stack[20][21], int* top) {
   if(*top <= -1) { //popping empty stack
      printf("Invalid expression\n");
      exit(1);
   }
   return stack[(*top)--];
}
/**
 * Same functionality as push(), but the stack consists of strings.
 * @param stack[][]  2-D character array for storing strings as stack.
 * @param top        Pointer to integer representing top index of the stack
 * @param expression Null-terminated string to push into the stack.
 */
void push_str(char stack[20][21], int* top, char* expression) {
   strcpy(stack[++(*top)], expression); // since token is null-terminated string
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
 * Translate infix expression to prefix expression. This is done by utilising
 * two stacks, one for operators, and one for expressions(+operands).
 * @param  infix  String containing infix expression to translate.
 * @param  prefix Character array where resulting prefix expressions will be
 *                written to.
 * @return        Translated prefix string.
 */
char* to_prefix(char* infix, char* prefix) {
   precedence pstack[20]; //precedence(operator) stack
   precedence token;
   char expstack[20][21]; //expression(operand) stack
   int ptop = -1, exptop = -1;
   char str[21], str1[21], str2[21], op;
   // isp and icp order: leftp, rightp, plus, minus, times, divide, mod
   // operand is missing in these arrays since it shouldn't really be a thing
   int isp[7] = {0, 9, 2, 2, 3, 3, 3};
   int icp[7] = {10, 9, 2, 2, 3, 3, 3};

   for(int i=0 ; i<(int)strlen(infix) ; i++) {
      op = infix[i];
      token = getToken(op);
      if(token == operand) {
         // push all operands
         str[0] = op;
         str[1] = '\0'; // make token into null-terminated string
         push_str(expstack, &exptop, str);
      } else if(token == rightp) {
         while(ptop != -1 && pstack[ptop] != leftp) {
            // pop & push until left parentheses
            strcpy(str2, pop_str(expstack, &exptop));
            strcpy(str1, pop_str(expstack, &exptop));
            str[0] = getOp(pop(pstack, &ptop));
            str[1] = '\0'; // make token into null-terminated string

            // concat into the form: <operation> <string1> <string2>
            strcat(str, strcat(str1, str2));
            push_str(expstack, &exptop, str);
         }
         pop(pstack, &ptop);
      } else {
         if(ptop != -1 && isp[pstack[ptop]] >= icp[token]) {
            // pop two expressions from stack
            strcpy(str2, pop_str(expstack, &exptop));
            strcpy(str1, pop_str(expstack, &exptop));
            str[0] = getOp(pop(pstack, &ptop));
            str[1] = '\0'; // token into null-terminated string

            // concat into the form: <operation> <string1> <string2>
            strcat(str, strcat(str1, str2));
            push_str(expstack, &exptop, str);
            push(pstack, &ptop, token);
         } else {
            push(pstack, &ptop, token);
         }
      }
   }
   while(exptop >= 0 && ptop >= 0) {
      // pop two expressions from stack
      strcpy(str2, pop_str(expstack, &exptop));
      strcpy(str1, pop_str(expstack, &exptop));
      str[0] = getOp(pop(pstack, &ptop));
      str[1] = '\0'; // token into null-terminated string

      // concat into the form: <operation> <string1> <string2>
      strcat(str, strcat(str1, str2));
      push_str(expstack, &exptop, str);
   }
   if(exptop != 0 || ptop != -1) {
      // check if the process did not end correctly
      printf("Invalid expression\n");
      exit(1);
   }
   // copy to prefix string.
   strcpy(prefix, expstack[exptop]);
   return prefix;
}
int main(int argc, const char* argv[]) {
   char infix[21], prefix[21];

   printf("Infix: ");
   scanf("%s", infix);

   if(!to_prefix(infix, prefix)) { // translate infix to prefix
      printf("Invalid expression\n");
      return 0;
   }
   printf("Prefix: %s\n", prefix);
   return 0;
}
