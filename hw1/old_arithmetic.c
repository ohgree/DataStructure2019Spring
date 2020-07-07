#define NO_SIGN '#'

#include <stdio.h>
#include <string.h>
int print_valid(char seq[], int seq_len, int target, char sign[], int sign_index) {
   int success = 0;
   // end condition
   if(seq_len-1 == sign_index) {
      //calculating result
      int carry = 0;
      int result = 0, first_sign_index;
      int first_num = 0;
      for(first_sign_index=0 ; first_sign_index<seq_len ; first_sign_index++) {
         if(sign[first_sign_index] != NO_SIGN) break;
      }
      printf("fsi=%d ", first_sign_index);
      for(int i=0 ; i<=first_sign_index ; i++) {
         first_num = first_num*10 + seq[i]-'0';

      }
      result = first_num;

      printf("%d ", first_num);
      for(int index=first_sign_index ; index<seq_len-1 ; index++) {
         printf("%c", sign[index]);
         printf("%d", carry*10 + seq[index+1]-'0');
         if(sign[index] == NO_SIGN) {
            carry = carry*10 + seq[index+1]-'0';
            continue;
         } else if(sign[index] == '+') {
            result += carry*10 + seq[index+1]-'0';
         } else if(sign[index] == '-') {
            result -= carry*10 + seq[index+1]-'0';
         } else if(sign[index] == '*') {
            result *= carry*10 + seq[index+1]-'0';
         }
         carry = 0;
      }
      printf("=%d\n", result);
      if(result == target) {
         printf("%c", seq[0]);
         for(int i=0 ; i<seq_len-1 ; i++) {
            if(sign[i] != NO_SIGN)
               printf("%c", sign[i]);
            printf("%c", seq[i+1]);
         }
         printf("\n");
         return 1;
      } else {
         return 0;
      }
   }

   //LOGICAL OR operation is not working. probably due to gcc's wonderful optimisation.
   //onto the next recursive
   sign[sign_index] = '+';
   success += print_valid(seq, seq_len, target, sign, sign_index+1);

   sign[sign_index] = '-';
   success += print_valid(seq, seq_len, target, sign, sign_index+1);

   sign[sign_index] = '*';
   success += print_valid(seq, seq_len, target, sign, sign_index+1);

   sign[sign_index] = NO_SIGN;
   success += print_valid(seq, seq_len, target, sign, sign_index+1);

   return success;
}
int main(int argc, const char* argv[]) {
   char numbers_str[11], arithmic[9];
   int target;
   scanf("%[^\n]10s", numbers_str);
   scanf("%d", &target);
   if(!print_valid(numbers_str, strlen(numbers_str), target, arithmic, 0)) {
      printf("None\n");
   }
   return 0;
}
