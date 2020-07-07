#include <stdio.h>
int fibo(int n) {
   if (n == 0 || n == 1)
      return 1;
   else
      return fibo(n-1)+fibo(n-2);
}
int main(void){
   printf("%d", fibo(5));
   return 0;
}
