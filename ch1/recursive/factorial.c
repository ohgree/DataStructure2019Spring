#include <stdio.h>
int f(int n) {
   if(n == 1) return 1;
   else return n*f(n-1);
}
int main(int argc, const char* argv[]) {
   printf("%d", f(10));
   return 0;
}
