#include <stdio.h>
int binomial(int n,int m) {
   if(m < 0 || m > n)
      return 0;
   else if(m == 1 || m == n)
      return 1;
   else
      return binomial(n-1, m) + binomial(n-1, m-1);
}

int main(int argc, const char* argv[]) {
   int n, m;
   scanf("%d %d", &n, &m);
   printf("%d", binomial(n, m));
   return 0;
}
