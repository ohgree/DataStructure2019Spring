#define NO_SIGN '#'

#include <stdio.h>
#include <string.h>

int remove_strhead(char str[], int count) {
   int idx, new_idx = 0;
   int str_len = strlen(str);
   for(idx=count ; idx < str_len ; idx++) {
      str[new_idx++] = str[idx];
   }
   str[new_idx] = '\0';
   return new_idx;
}
int extract_int(char expression[]) {
   int extractedInt = 0;
   int index;
   for(index=0 ; '0' <= expression[index] && expression[index] <= '9' ; index++) {
      extractedInt = extractedInt*10 + expression[index]-'0';
   }
   remove_strhead(expression, index);

   return extractedInt;
}
int print_valid(char seq[], int seq_len, int target, char sign[], int sign_index) {
   int success = 0;
   // end condition
   if(seq_len-1 == sign_index) {
      char expression[20];
      expression[0] = seq[0];
      int exp_idx = 1;
      for(int i=0 ; i<seq_len-1 ; i++) {
         if(sign[i] != NO_SIGN) expression[exp_idx++] = sign[i];
         expression[exp_idx++] = seq[i+1];
      }
      expression[exp_idx] = '\0';

      int result = extract_int(expression);
      while(expression[0] != '\0') {
         int next_num;
         char operation;
         operation = expression[0];
         remove_strhead(expression, 1);
         next_num = extract_int(expression);
         switch(operation) {
            case '+':
               result += next_num; break;
            case '-':
               result -= next_num; break;
            case '*':
               result *= next_num; break;
         }
      }
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
   scanf("%10s", numbers_str);
   scanf("%d", &target);
   if(!print_valid(numbers_str, strlen(numbers_str), target, arithmic, 0)) {
      printf("None\n");
   }
   return 0;
}
