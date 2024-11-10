#include<stdio.h>
#include<stdlib.h>
struct student{
    int number;
    char name[10];
    double grade;
};

int main(void)
{
    struct student s;

    s.number = 20230001;
    strcpy(s.name,"홍길동");
    s.grade = 4.3;

    printf("학번: %d\n",s.number);
    printf("이름: %d\n",s.name);
    printf("학점: %lf\n",s.grade);


}