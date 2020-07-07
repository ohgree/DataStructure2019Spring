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
int shift_to_index(int* array, int length, int index) {
   for(int i=index ; i<length-1 ; i++) {
      array[i] = array[i+1];
   }
   return length-1;
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
      int numbers[10], numbers_bak[10];
      int numbers_len, ops_len, olen_bak;
      char ops[10], ops_bak[10];
      char expression[20];
      char exp_bak[20];
      expression[0] = seq[0];
      int exp_idx = 1;
      for(int i=0 ; i<seq_len-1 ; i++) {
         if(sign[i] != NO_SIGN) expression[exp_idx++] = sign[i];
         expression[exp_idx++] = seq[i+1];
      }
      expression[exp_idx] = '\0';

      strcpy(exp_bak, expression);
      //int result = extract_int(expression);

      int i;
      numbers[0] = extract_int(expression);

      for(i=0 ; expression[0] != '\0' ; i++) {
         ops[i] = expression[0];
         remove_strhead(expression, 1);
         numbers[i+1] = extract_int(expression);
      }

      numbers_len = i+1;
      ops_len = i;
      for(int i=0 ; i<numbers_len ; i++) {
         numbers_bak[i] = numbers[i];
         ops_bak[i] = ops[i];
      }
      olen_bak = ops_len;

      //printf("%d|%d|%s\n", numbers_len, ops_len, expression);
      for(i=0 ; i<ops_len ; i++) {
         if(ops[i] == '*') {
            numbers[i+1] *= numbers[i];
            for(int idx=i ; idx<numbers_len-1 ; idx++)
               numbers[idx] = numbers[idx+1];
            numbers_len--;
            for(int idx=i ; idx<ops_len-1 ; idx++)
               ops[idx] = ops[idx+1];
            ops_len--;
            i--;
         }
      }

      int result = numbers[0];
      for(i=0 ; i<ops_len ; i++) {
         result += (ops[i]=='+') ? numbers[i+1] : -numbers[i+1];
      }
      /*
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
      */
      if(result == target) {
         //printf("%s\n", exp_bak);
         for(int i=1 ; i<(int)strlen(exp_bak) ; i++) {
            if(exp_bak[i-1]=='0' && exp_bak[i] <= '9' && '0' <= exp_bak[i])
               return 0;
         }
         /*
         printf("%s|%s|", ops_bak, numbers_bak);
         printf("%d", numbers[0]);
         for(int i=0 ; i<olen_bak ; i++) {
            printf("%c%d", ops_bak[i], numbers_bak[i+1]);
         }
         printf("\n");
         */
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
