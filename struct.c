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
    strcpy(s.name,"ȫ�浿");
    s.grade = 4.3;

    printf("�й�: %d\n",s.number);
    printf("�̸�: %d\n",s.name);
    printf("����: %lf\n",s.grade);


}