#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <string.h>

struct sex_type {
   enum tag_field {female, male} sex;
   union {
      int children;
      int beard;
   } u;
};
typedef struct {
   int month;
   int day;
   int year;
} date;

struct {
   char name[10];
   int age;
   float salary;
} person;
struct human {
   char name[10];
   int age;
   float salary;
};
typedef struct {
   char name[10];
   int age;
   float salary;
   date dob;
} humanBeing;

int human_equal(humanBeing h1, humanBeing h2) {
   if(h1.age == h2.age && h1.salary == h2.salary && !strcmp(h1.name, h2.name)){
      return TRUE;
   }
   return FALSE;
}

int main(int argc, const char* argv[]) {
   strncpy(person.name, "ASD", 10);
   person.age = 12;
   person.salary = 0;

   struct human human1;
   human1.age=17;

   humanBeing human2;
   human2.age=17;
   return 0;
}
