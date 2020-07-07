#include <stdio.h>
int binary(int list[], int left, int right, int value) {
   int middle = (left+right)/2;
   if(left > right) return -1;
   else if(list[middle] == value) {
      return middle;
   } else if(list[middle] > value) {
      return binary(list, left, middle-1, value);
   } else {
      return binary(list, middle+1, right, value);
   }
}
int main(int argc, const char* argv[]) {
   int list[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   int value = 7;
   printf("%d", binary(list, 0, 9, value));
   return 0;
}
