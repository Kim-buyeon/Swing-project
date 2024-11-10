#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define CAPACITY 100
#define BUFFER_LENGTH 100
int read_line(FILE *fp,char str[],int n);
void load(char * fileName);
void save(char *fileName);
int search(char*name);
typedef struct person Person;
void print_person(Person p);
void remove_entry(char *name);
void status();
void find(char *name);
void handle_add(char *name);
void add(char *name,char *number,char *email,char *group);
int compose_name(char str[],int limit);

typedef struct person{//person 생략해도 됨 Person으로 rename하기 때문에
    char *name;
    char *number;//구조체 person 정의하면서 그것을 Persond으로 rename 함 t
    char *email;  
    char *group;
}Person;

Person directory[CAPACITY];//typedef 활용했기 떄문에  struct person Person 이렇게 안쓰고 Person 만 사용해서 변수로 사용가능
//키보드에 대한 파일포인터 stdin 이다
int n=0;

int read_line(FILE *fp,char str[],int n){//읽어올 파일,배열,배열의 크기 매개 변수로 지정
    int ch,i=0;

    while((ch = fgetc(fp))!='\n' && ch !=EOF){//키보드 뿐만 아니라 데이터 파일로부터 입력받음
        if (i<n){//overflow가 되지 않게 함 파일로 읽을 떄 null character가 읽히지 않는다
            str[i++] = ch;
        }
        str[i] ='\n';
        return 1;
    }
}

int main(){
    char command_line[BUFFER_LENGTH];//사용자로부터 명령어 읽기
    char *command, *argument;
    char name_str[BUFFER_LENGTH];

    while(1){
        printf("$");
        if(read_line(stdin,command_line,BUFFER_LENGTH)<=0)//stdin keyboard로부터
            continue;//아무것도 입력하지 않고 enter 누름
        command = strtok(command_line," ");//공백문자 기준으로 해서 문자열 나눔

        if(strcmp(command,"read")==0){//read 하면 파일이름이 나와야 하니 다음 토큰은 파일 이름이 된다
            argument = strtok(NULL,"");
            if(argument ==NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            load(argument);
        }
        else if(strcmp(command,"add")==0){
            if(compose_name(name_str,BUFFER_LENGTH)<=0){
                printf("Name required.\n");
                continue;
            }
            handle_add(name_str);
        }
        else if(strcmp(command,"find")==0){
            if(compose_name(name_str,BUFFER_LENGTH)<=0){
                printf("Name required.\n");
                continue;
            }
            find(name_str);
        }
        else if(strcmp(command,"status")==0){
            status();
        }
        else if(strcmp(command,"delete")==0){
            if(compose_name(name_str,BUFFER_LENGTH)<=0){
                printf("Invalid arguments.\n");
                continue;
            }
            remove_entry(name_str);
        }
        else if(strcmp(command,"save")==0){
            argument = strtok(NULL,"");
            if(strcmp(argument,"as")!=0){
                printf("Invalid arguments.\n");
                continue;
            }
            argument = strtok(NULL," ");
            if(argument==NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            save(argument);
        }
        else if(strcmp(command,"exit")==0)
            break;
    }
    return 0;
}
void load(char * fileName){
    char buffer[BUFFER_LENGTH];
    char *name,*number,*email,*group;

    FILE *fp = fopen(fileName,"r");
    if(fp==NULL){
        printf("Open failed.\n");
        return;
    }

    while(1){
        if(read_line(fp,buffer,BUFFER_LENGTH)<=0)
            break;//파일에서 읽을거리가 없을 떄 무한반복문 빠져나옴
        name = strtok(buffer,"#");
        number = strtok(NULL,"#");//업는 경우 하나의 공백으로 저장
        email = strtok(NULL,"#");
        group = strtok(NULL,"#");
        add(name,number,email,group);

    }
    fclose(fp);
}
void save(char *fileName){
    int i;
    FILE *fp = fopen(fileName,"w");
    if(fp==NULL){
        printf("Open failed.\n");
        return;
    }

    for(i=0;i<n;i++){
        fprintf(fp,"%s#",directory[i].name);
        fprintf(fp,"%s#",directory[i].number);
        fprintf(fp,"%s#",directory[i].email);
        fprintf(fp,"%s#\n",directory[i].group);
    }
    fclose(fp);
}
int search(char*name){
    int i;
    for(i=0;i<n;i++){
        if(strcmp(name,directory[i].name)==0){
            return i;
        }
    }
    return -1;
}

void print_person(Person p){//화면상 프린트
    printf("%s:\n",p.name);
    printf("    Phone: %s\n",p.number);
    printf("    Email: %s\n",p.email);
    printf("    Group:%s\n",p.group);

}
void remove_entry(char *name){
    int i= search(name);
    if(i==-1){
        printf("No person named '%s' exists.\n",name);
        return;
    }
    int j=i;
    for(;j<n-1;j++){
        directory[j] = directory[j+1];
    }
    n--;
    printf("'%s'was deleted successfully.\n",name);
}
void status(){
    int i;
    for(i=0;i<n;i++){
        print_person(directory[i]);
    printf("Total %d persons.\n",n);
    }
}
void find(char *name){
    int index =search(name);
    if(index ==-1)
        printf("No person named '%s' exists.\n",name);
    else
        print_person(directory[index]);
}

void handle_add(char *name){
    char number[BUFFER_LENGTH],email[BUFFER_LENGTH],group[BUFFER_LENGTH];
    char empty[]=" ";

    printf("   Phone: ");
    read_line(stdin,number,BUFFER_LENGTH);

    printf("   Email: ");
    read_line(stdin,email,BUFFER_LENGTH);

    printf("   Group: ");
    read_line(stdin,group,BUFFER_LENGTH);

    add(name,(char *)(strlen(number)>0 ? number: empty),(char*)(strlen(email)>0 ? email: empty),(char*)(strlen(group)>0 ? group: empty));
}//존재하지 않은 문자열의 하나의 공백 문자열로 대체한다.
void add(char *name,char *number,char *email,char *group){
    int i=n-1;
    while(i>0 && strcmp(directory[i].name,name)>0){
        directory[i+1] = directory[i];//알파벳 이름 순서대로 정렬,한 사람에 관한 정보가 struct로 다 묶여있음
        i--;
    }
    directory[i+1].name = strdup(name);
    directory[i+1].number = strdup(number);
    directory[i+1].email = strdup(email);
    directory[i+1].group = strdup(group);
    n++;
}
int compose_name(char str[],int limit){
    char *ptr;
    int length =0;//불필요한 공백 제거,하나의 공백으로 축약

    ptr =strtok(NULL," ");//입력라인의 두번쨰 토큰
    if(ptr ==NULL)
        return 0;
    strcpy(str,ptr);//str 복사한거 저장할 공간.ptr 복사할 문자열
    length += strlen(ptr);

    while((ptr= strtok(NULL," "))!=NULL){
        if(length + strlen(ptr)+1<limit){//overflow 방지
            str[length++] = ' ';
            str[length] = '\0';
            strcat(str,ptr);//ptr를 str에 덧붙여줌 마지막이 null문자여야지 똑바로 작동
            length +=strlen(ptr);
        }
    }
    return length;
}