#include <stdio.h>
void push(int n);
int pop();
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }
precedence;
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};
char expr[100] = {0};
precedence stack[100];
int top = -1;
precedence getToken(char* symbol, int* n) {
   *symbol = expr[(*n)++];
   switch(*symbol) {
      case '(': return lparen; break;
      case ')': return rparen; break;
      case '+': return plus; break;
      case '-': return minus; break;
      case '*': return times; break;
      case '/': return divide; break;
      case '%': return mod; break;
      case '\0': return eos; break;
      default: return operand;
   }
}
void printToken(precedence token);
void topostfix(void) {
   char symbol;
   int n = 0;
   precedence token;
   stack[0] = eos;
   for(token = getToken(&symbol, &n) ; token != eos ; 
      token = getToken(&symbol, &n)) {
      if(token == operand) {
         printf("%c", symbol);
      } else if(token == rparen) {
         while(stack[top] != lparen) {
            printToken(pop());
         }
         pop();
      } else {
         while(icp[token] <= isp[stack[top]]) {
            printToken(pop());
         }
         push(token);
      }
   }
   while((token = pop()) != eos) {
      printToken(pop());
   }
   printf("\n");
}
int eval() {
   precedence token;
   char symbol;
   int op1, op2;
   int n=0;
   token = getToken(&symbol, &n);
   while(token != eos) {
      if(token == operand)
         push(symbol-'0');
      else {
         op2 = pop();
         op1 = pop();
         switch(symbol) {
            case plus: push(op1+op2); break;
            case minus : push(op1-op2); break; 
            case times : push(op1*op2); break;
            case divide: push(op1/op2); break;
            case mod : push(op1%op2); break;
         }
      }
      token = getToken(&symbol, &n);
   }
   return pop();
}
