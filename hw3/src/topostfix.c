#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {
   leftp, rightp, plus, minus, times, divide, mod, unary, operand
} precedence;
/**
 * Pops precedence from stack. If stack is empty, prints error and terminates
 * program.
 * @param  stack Array for the stack that will be popped
 * @param  top   Pointer to integer of stack top index (-1 for empty stack)
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
 * Same functionality as pop(), but with integers
 * @param  stack Array for the stack that will be popped
 * @param  top   Pointer to integer of stack top index (-1 for empty stack)
 * @return       Popped value
 */
char pop_int(int* stack, int* top) {
   int value;
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
 * Same functionality as push(), but with integers.
 * @param stack Array for the stack that is used for this procedure.
 * @param top   Pointer to integer value for stack top index
 * @param token Procedence value that needs to be pushed.
 */
void push_int(int* stack, int* top, int token) {
   stack[++(*top)] = token;
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
      case unary: return '#'; break;
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
      case '#': return unary; break;
      default: return operand; break;
   }
}
/**
 * Evaluate postfix expressions
 * @param  expression Postfix expression to evaluate
 * @return            Result in integer.
 */
int eval_postfix(char* expression) {
   int stack[20];
   int top = -1;
   int result;
   int op, arg1, arg2;
   precedence token;

   for(int i=0 ; i<(int)strlen(expression) ; i++) {
      op = expression[i];
      token = getToken(op);
      if(token == operand) {
         push_int(stack, &top, op-'0');
      } else if(token == unary) {
         arg2 = pop_int(stack, &top);
         push_int(stack, &top, -arg2);
      } else {
         arg2 = pop_int(stack, &top);
         arg1 = pop_int(stack, &top);
         switch(token) {
            case plus:
               push_int(stack, &top, arg1+arg2); break;
            case minus:
               push_int(stack, &top, arg1-arg2); break;
            case times:
               push_int(stack, &top, arg1*arg2); break;
            case divide:
               push_int(stack, &top, arg1/arg2); break;
            case mod:
               push_int(stack, &top, arg1%arg2); break;
            default: break;
         }
      }
   }
   if(top != 0) {
      printf("Invalid expression\n");
      exit(1);
   }
   return pop_int(stack, &top);
}
/**
 * Translate infix expression to postfix expression.
 *    Unary operations are included, and are marked as '#' in resulting
 *    expression. Minus operators are identified as unary if it matches
 *    any of the following conditions:
 *    - the operator is the first thing in the expression.
 *    - the operator comes after left parentheses.
 *
 * @param  infix   Infix expression to translate
 * @param  postfix Character array where resulting postfix expressions will be
 *                 written to.
 * @return         String of the postfix expression.
 */
char* to_postfix(char* infix, char* postfix) {
   precedence stack[20];
   char op;
   int top = -1, post_idx = 0, i;
   int f_unary = 0;
   precedence token;
   int isp[8] = {0, 9, 2, 2, 3, 3, 3, 4};
   int icp[8] = {10, 9, 2, 2, 3, 3, 3, 4};
   for(i=0 ; i<(int)strlen(infix) ; i++) {
      op = infix[i];
      token = getToken(op);
      if (token == minus) {
         if(i == 0) {
            f_unary = 1;
            continue;
         } else if(getToken(infix[i-1]) != operand &&
               getToken(infix[i-1]) != rightp) {
            f_unary = 1;
            continue;
         }
      }
      if(token == operand) {
         postfix[post_idx++] = op;
         if(f_unary) {
            postfix[post_idx++] = getOp(unary);
            f_unary = 0;
         }
      } else if(token == rightp) {
         while(stack[top] != leftp) {//check for top validity
            postfix[post_idx++] = getOp(pop(stack, &top));
         }
         pop(stack, &top);
         if(f_unary) {
            postfix[post_idx++] = getOp(unary);
            f_unary = 0;
         }
      } else {
         while(top != -1 && isp[stack[top]] >= icp[token]) {
            postfix[post_idx++] = getOp(pop(stack, &top));
         }
         push(stack, &top, token);
      }
   }
   if(i != (int)strlen(infix)) {
      //error occurred
      return NULL;
   }
   while(top != -1) {
      postfix[post_idx++] = getOp(pop(stack, &top));
   }
   postfix[post_idx] = '\0';
   return postfix;
}
int main(int argc, const char* argv[]) {
   char infix[21], postfix[21];
   int result;

   printf("Input: ");
   scanf("%s", infix);
   if(!to_postfix(infix, postfix)) {
      printf("Invalid expression\n");
      return 0;
   }
   result = eval_postfix(postfix);

   printf("Postfix: %s\n", postfix);
   printf("Result: %d\n", result);
   return 0;
}
