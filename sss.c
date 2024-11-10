#include<stdio.h>
int main(void)
{
    int scores[4][3];
    int i,j;
    int sum=0;
    
    for(i=0;i<4;i++){
        for(j=0;j<3;j++){
            printf("학생 %d의 %d번쨰의 시험 성적:",i+1,j+1);
            scanf("%d",&scores[i][j]);
        }
    }
}