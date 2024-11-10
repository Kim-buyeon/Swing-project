#include<stdio.h>
#include<string.h>
#define CAPACITY 100
#define BUFFER_SIZE 100

char * names[CAPACITY];
char * numbers[CAPACITY];
int n=0;//저장되어있는 사람의 수

void add();
void find();
void status();
void remove_entry();
int main(void)
{
    char command[BUFFER_SIZE];
    while(1){
        printf("$");
        scanf("%s",command);//사용자의 명령문을 받아서 command 라는 배열에 저장
        if(strcmp(command,"add")==0)  //strcmp(비교할 첫번째 문자열,비교할 두번째 문자열)
            add();//strcmp함수는 두 문자열이 동일하면 0을 반환한다.
        else if(strcmp(command,"find")==0)
            find();
        else if(strcmp(command,"status")==0)
            status();
        else if(strcmp(command,"delete")==0)
            remove_entry();
        else if(strcmp(command,"exit")==0)
            break;
    }
    return 0;
}

void add(){
    char buf1[BUFFER_SIZE],buf2[BUFFER_SIZE];
    scanf("%s",buf1);
    scanf("%s",buf2);

    names[n]=strdup(buf1);
    numbers[n]=strdup(buf2);
    n++;

    printf("%s was added successfully\n",buf1);
}

void find(){
    char buf[BUFFER_SIZE];//찾고자 하는 이름을 buffer에 입력
    scanf("%s",buf);

    int i;
    for(i=0;i<n;i++){
        if(strcmp(buf,names[i])==0){//배열 동일한 경우 0 츨력
            printf("%s\n",numbers[i]);
            return;//여기서 return 함으로 밑에 있는 코드까지 도달하지 못함
        }
        printf("no person named'%s'exists.\n",buf);
    }
}

void status(){// 현재있는 모든 사람과 전화번호 출력
    for(int i=0;i<n;i++){
        printf("%s %s\n",names[i],numbers[i]);
    printf("Total %d persons.\n",n);
    }
}

void remove_entry(){
    char buf[BUFFER_SIZE];
    scanf("%s",buf);

    int i;
    for(i=0;i<n;i++){
        if(strcmp(buf,names[i])==0){//삭제할 이름이 찾는 이름과 똑같은지 확인
            names[i] = names[n-1];
            numbers[i] = numbers[n-1];//멘 마지막 사람을 삭제된 자리로 옮긴다.
            n--;
            printf("'%s was deleted successfully.\n",buf);
            return;
        }
    }
    printf("No person named '%s exists.\n",buf);//앞에서 return 되지않았다.
}