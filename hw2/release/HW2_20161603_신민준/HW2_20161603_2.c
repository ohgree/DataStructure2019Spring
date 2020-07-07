#define INT_MAX 2147483637
#define INT_MIN -2147483648

#include <stdio.h>
#include <stdlib.h>
/**
 * Finds if array has consecutive natural numbers.
 * If an array is consecutive, it satisfies following two conditions.
 *    1. Array's maximum number-minimum number == array length-1
 *    2. Every element in the array is unique
 * @param  arr Pointer to array holding natural numbers.
 * @param  len Length of the array
 * @return     1 if given array is consecutive
 *             0 if given array is not consecutive
 */
int is_consecutive(int* arr, int len) {
   int max=INT_MIN, min=INT_MAX;
   int* marker;

   if(len <= 0)
      return 0;

   // gets maximum & minimum numbers from the array
   for(int i=0 ; i<len ; i++) {
      if(arr[i] > max)
         max=arr[i];
      if(arr[i] < min)
         min=arr[i];
   }

   if(max-min == len-1) { // condition 1: max-min == array length-1
      marker = calloc(len, sizeof(int)); // allocates space initialized with 0
      // condition 2: check if all elements are unique
      for(int i=0 ; i<len ; i++) {
         if(marker[arr[i]-min] == 1) {
            // duplicate elements found
            free(marker);
            return 0;
         }
         marker[arr[i]-min] = 1;
      }
      free(marker);
      return 1;
   }
   return 0;
}
int main(int argc, const char* argv[]) {
   int* array;
   int array_length;

   scanf(" %d", &array_length);

   // allocate space depending on the array_length given
   array = (int*)malloc(sizeof(int)*array_length);
   for(int i=0 ; i<array_length ; i++) {
      scanf(" %d", &array[i]);
   }

   // print 1 if consecutive, 0 otherwise
   printf("%d\n", is_consecutive(array, array_length));
   free(array);

   return 0;
}
