#include <stdio.h>
 void func1(void);
 void func2(int);
 void func3(void);
 int num= 10;
 int main(void) {
 int num= 20;
 while (1)    {
 int num= 30;
 printf("1.num=%d\n", num);
 if (num> 25) break;
 }
 printf("2.num=%d\n", num);
 func1();
 printf("3.num=%d\n", num);
 func2(num);
 printf("4.num=%d\n", num);
 func3();
 printf("5.num=%d\n", num);
 return 0;
 }
 void func1(void)
 {
 printf("func1) num=%d\n", num);
 num++;
 }
 void func2(int num)
 {
 printf("func2) num=%d\n", num);
 num++;
 }
 void func3(void)
 {
 printf("func3) num=%d\n", num);
 }
