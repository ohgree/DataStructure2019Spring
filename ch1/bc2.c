#include <stdio.h>
int bc(int n, int m) {
   if(m == 0 || n == m) return 1;
   return bc(n-1, m) + bc(n-1, m-1);
}
int main(int argc, const char* argv[]) {
   printf("%d", bc(10, 5));
   return 0;
}
