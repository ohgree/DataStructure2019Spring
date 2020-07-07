#include <stdio.h>
int fibo(int n) {
   int val1 = 0, val2 = 1, tmp;
   if(n == 0) return 0;
   if(n == 1) return 1;
   for(int i=2 ; i<=n ; i++) {
      tmp = val1 + val2;
      val1 = val2;
      val2 = tmp;
   }
   return val2;
}
int main(int argc, const char* argv[]) {
   printf("%d", fibo(30));
   return 0;
}
