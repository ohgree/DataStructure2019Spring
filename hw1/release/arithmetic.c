#define NO_SIGN '#'

#include <stdio.h>
#include <string.h>

/**
 * Removes certain number of characters from string head.
 * @param  str   String to remove chars from.
 * @param  count Number of chars to remove.
 * @return       Length of remaining characters.
 */
int remove_strhead(char str[], int count) {
   int idx, new_idx = 0;
   int str_len = strlen(str);
   for(idx=count ; idx < str_len ; idx++) {
      str[new_idx++] = str[idx];
   }
   str[new_idx] = '\0';
   return new_idx;
}
/**
 * Extract number from character array. Reads numbers until it meets its first
 * non-numeric character. Removed read number from character array after.
 * @param  expression Character array that needs to be parsed.
 * @return            Parsed number from array.
 */
int extract_int(char expression[]) {
   int extractedInt = 0;
   int index;
   // breaks loop when expression[index] is non-numeric character.
   for(index=0 ; '0' <= expression[index] && expression[index] <= '9' ; index++) {
      extractedInt = extractedInt*10 + expression[index]-'0';
   }
   remove_strhead(expression, index);

   return extractedInt;
}
/**
 * Recursive function for creating and checking mathematical formula.
 * @param  seq        Sequence of numeric characters from input.
 * @param  seq_len    Length of seq
 * @param  target     Target value that we strive to achieve.
 * @param  sign       Array of characters, consists only of '+','-','*',NO_SIGN
 * @param  sign_index Current index of sign array.
 * @return            0 if all recursions failed to find matching formula for
 *                    target.
 *                    Any positive integers if otherwise.
 */
int print_valid(char seq[], int seq_len, int target, char sign[], int sign_index) {
   int success = 0;

   // end condition for recursion
   if(seq_len-1 == sign_index) {
      int numbers[10], numbers_bak[10];
      int numbers_len, ops_len, olen_bak;
      char ops[10], ops_bak[10];
      char expression[20];
      char exp_bak[20];
      expression[0] = seq[0];
      int exp_idx = 1;

      // create arithmic expression by combining numeric sequence with signs.
      for(int i=0 ; i<seq_len-1 ; i++) {
         // if sign is NO_SIGN, exclude that sign from appending to expression.
         if(sign[i] != NO_SIGN) expression[exp_idx++] = sign[i];
         expression[exp_idx++] = seq[i+1];
      }
      expression[exp_idx] = '\0';

      // exp_bak - backup of expression for future printing
      strcpy(exp_bak, expression);

      int i;
      // extract integers and operations from the expression
      // this is done by extracting integer, and since extract_int removes
      // read numeric characters, the character at index 0 must be the sign.
      numbers[0] = extract_int(expression);
      for(i=0 ; expression[0] != '\0' ; i++) {
         // ops stores mathematical operations
         ops[i] = expression[0];
         remove_strhead(expression, 1);
         // numbers stores numbers inside the expression
         numbers[i+1] = extract_int(expression);
      }

      numbers_len = i+1;
      ops_len = i;
      // backup ops and numbers, for future printing
      for(int i=0 ; i<numbers_len ; i++) {
         numbers_bak[i] = numbers[i];
         ops_bak[i] = ops[i];
      }
      olen_bak = ops_len;

      // calculating multiplication first, since * is preceded before + or -
      for(i=0 ; i<ops_len ; i++) {
         if(ops[i] == '*') { //calculate only if the operation is *
            // save the result in one array and overwrites the other by
            // shifting all elements after it.
            numbers[i+1] *= numbers[i];
            for(int idx=i ; idx<numbers_len-1 ; idx++)
               numbers[idx] = numbers[idx+1];
            numbers_len--; // since two numbers were calculated to make one.
            // same for the operations, since a operator was used
            for(int idx=i ; idx<ops_len-1 ; idx++)
               ops[idx] = ops[idx+1];
            ops_len--;
            i--; // to compensate for reduced overall array length
         }
      }

      // since remaining operations are either + or -, it'll be easier to
      // first change numbers to negative counterparts if its matching operation
      // is -, and then add up all numbers.
      int result = numbers[0];
      for(i=0 ; i<ops_len ; i++) {
         // if matching operation for the number is -, set number to negative
         // and then add up.
         result += (ops[i]=='+') ? numbers[i+1] : -numbers[i+1];
      }

      // if this is the correct formula for the target, print the formula.
      if(result == target) {
         // excluding such cases that has '03' for its numbers.
         for(int i=1 ; i<(int)strlen(exp_bak) ; i++) {
            if(exp_bak[i-1]=='0' && exp_bak[i] <= '9' && '0' <= exp_bak[i])
               return 0;
         }

         // printing the formula
         printf("%c", seq[0]);
         for(int i=0 ; i<seq_len-1 ; i++) {
            if(sign[i] != NO_SIGN) // excluding sign if it is NO_SIGN
               printf("%c", sign[i]);
            printf("%c", seq[i+1]);
         }
         printf("\n");
         return 1;
      } else {
         return 0;
      }
   }

   /**
    * Call next recursive.
    * NOTE: LOGICAL OR operation is not working. Hence using addition.
    *       probably due to how compiler optimises it.
    */
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
   // if no valid formula for target is found, print "None"
   if(!print_valid(numbers_str, strlen(numbers_str), target, arithmic, 0)) {
      printf("None\n");
   }
   return 0;
}
