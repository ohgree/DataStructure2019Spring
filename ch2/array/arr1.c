#define MAX_SIZE 100
#include <stdio.h>
float sum(float[], int);
float input[MAX_SIZE], answer;
int main(int argc, const char* argv[]) {
   for(int i=0 ; i<MAX_SIZE ; i++) {
      input[i] = i;
   }
   answer = sum(input, MAX_SIZE);
   printf("The sum is: %f\n", answer);
   return 0;
}
float sum(float list[], int n) {
   float sum = 0;
   for(int i=0 ; i<n ; i++) {
      sum += list[i];
   }
   return sum;
}
