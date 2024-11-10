#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INIT_CAPACITY 3// 배열의 재할당을 테스트하기위해서 일부러 작은 값으로
#define BUFFER_SIZE 100

char ** names;
char ** numbers;//char * 타입의 배열의 이름으로 char ** 타입의 변수이다
int n=0;//저장되어있는 사람의 수
int capacity = INIT_CAPACITY;

void add(char*name,char*number);
void find(char *name);
void status();
void remove_entry(char*name);
void load(char*);
void save(char *fileName);
int readline(char*,int);
void init_directory();
void process_command();
int read_line(char *,int);
void reallocate();

char delim[] = " ";
int main(void)
{
    init_directory();// 이함수에서 배열 names와 numbers를 생성한다
    process_command();//사용자의 명령을 받아 처리하는 부분을 별개의 함수로 만들었다.
    return 0;
}

void add(char*name,char*number){
    if(n>=capacity)
        reallocate();//배열이 꽉찬 경우 재 할당
    int i = n-1; //n명이면 실제 배열 index는 n-1개 여서 다음과 같이 작성
    while(i>=0 && strcmp(names[i],name)>0){
        names[i+1] = names[i];//i번쨰 있는 사람을 i+1번쨰로 옮김
        numbers[i+1] = numbers[i];
        i--;//이동되어서 다음껄 봐야하므로 1감소 i가 -1이 되면 제일 앞에 추가
    }
    names[i+1] = strdup(name);
    numbers[i+1] = strdup(number);//load 함수가 리턴하면 그 값이 사라져서 strdup사용
    n++;
    
}

void find(char *name){
    int index = search(name);
    if(index ==-1){
        printf("No person named '%s' exist.\n",name);
    }
    else{
      printf("%s\n",numbers[index]);  
    }
}

int search(char *name){
    for(int i=0;i<n;i++){
        if(strcmp(name,names[i])==0){
            return i;
        }
    }
    return -1;
}

void status(){// 현재있는 모든 사람과 전화번호 출력
    for(int i=0;i<n;i++){
        printf("%s %s\n",names[i],numbers[i]);
    printf("Total %d persons.\n",n);
    }
}

void remove_entry(char *name){
    int i = search(name);//search 함수 통해서 사람 유무 찾기 존재하지 않으면 return -1
    if(i ==-1){
        printf("No person named '%s' exists.\n",name);
        return;
    }
    int j=i;
    for(;j<n-1;j++){//n명까지 돌기 위해 n-1로 해놓음
        names[j] = names[j+1];
        numbers[j] = numbers[j+1];
    }
    n--;
    printf("'%s' was deleted successfully.\n",name);
    }
void load(char *fileName){//파일이름을 이미 읽은 상태여서 매개변수로 사용
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    FILE *fp = fopen(fileName,"r");//일기 모드로 오픈 파일에 접근하기 위해 파일 open 
    if(fp==NULL){
        printf("OPEN failed.\n");
        return;
    }

    while((fscanf(fp,"%s,buf1")!=EOF)){//이름 입력
        fscanf(fp,"%s ",buf2);//전화번호 입력
        add(buf1,buf2);//배열에 추가
    }
    fclose(fp);
}

void save(char *fileName){
    int i;
    FILE *fp = fopen(fileName,"w");//파일에 쓸 떄는 "w"모드로 열어야 한다
    if(fp==NULL){
        printf("Open failed.\n");
        return;
    }

    for(i=0;i<n;i++){
        fprintf(fp,"%s %s\n",names[i],numbers[i]);//fp=파일포인터 어떤 파일에 쓰려고 하냐?
    }
    fclose(fp);
}

void init_directory(){
    names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
    numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));//자료형의 크기 만큼 메모리 할당 받는 것이 좋음

}

void process_command(){//단어 단위로 입력받는 것이 아닌 line 별로 입력받는다
    char command_line[BUFFER_SIZE];//한라인을 통채로 읽어오기 위한 버퍼 명령어까지 모두
    char *command,*argument1,*argument2;//tokenizing 하기 위해 있어야 할것
    while(1){
        printf("$ ");
        
        if(read_line(command_line,BUFFER_SIZE)<=0)//명령줄을 통채로 읽는다. enter 치더라도 그 다음줄로 넘어가 명령어 입력가능
            continue;
        command = strtok(command_line,delim);// 공백문자 기준으로 tokenize 해서 첫번쨰 주소의 토큰을 command한다.
        if(command ==NULL)
            continue;
        if(strcmp(command,"read"==0)){//read 뒤에 파일이름이 나와야 한다
            argument1 = strtok(NULL,delim);//read명령에서 두번쨰 토큰은 파일명이다.
            if(argument1 ==NULL){
                printf("FILE name required.\n");
                continue;
            }
            load(argument1);//파일명을 인자로 주면서 호출한다.
        }

        else if(strcmp(command,"add")==0){
            argument1 = strtok(NULL,delim);//명령어에 이어지는 2개의 토큰은 각각 이룸과 전화번호이다.
            argument2 = strtok(NULL,delim);

            if(argument1 ==NULL || argument2==NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            add(argument1,argument2);//이름과 전화번호를 인자로 주면서 add를 호출한다.
            printf("'%s' was added successfully.\n",argument1);
        }
        else if(strcmp(command,"find")==0){
            argument1=strtok(NULL,delim);
            if(argument1==NULL){//앞에사 반환해주는 값이 argument인데 그 값이 null인경우
                printf("Invalid arguments.\n");//이름 치지않고 엔터친 경우
                continue;
            }
            find(argument1);
        }
        else if(strcmp(command,"status")==0){
            status();
        }
        else if(strcmp(command,"delete")==0){
            argument1 = strtok(NULL,delim);
            if(argument1 ==NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            remove_entry(argument1);
        }
        else if(strcmp(command,"save")==0){
            argument1= strtok(NULL,delim);
            argument2 = strtok(NULL,delim);
            
            if(argument1 == NULL || strcmp("as",argument1)!=0||argument2==NULL){
                printf("Invalid command format.\n");
                continue;
            }
            save(argument2);
        }
        else if(strcmp(command,"exit")==0)
            break;

    }
}

int read_line(char str[],int limit){
    //linit: 배열 str의 길이 즉 더 긴 line의 경우에는 뒷부분이 짤린다.
    int ch,i=0;
    while((ch=getchar())!='\n'){
        if(i<limit-1){
            str[i++]=ch;
        }
        str[i]='\n';
        
    }
    return i;
}
void reallocate(){
    int i;//배열의 크기르 늘리는게 아니라 더 큰 배열을 할당받는 것
    capacity *=2;
    char **tmp1 = (char**)malloc(capacity*sizeof(char*));
    char **tmp2 = (char**)malloc(capacity*sizeof(char *));

    for(i=0;i<n;i++){
        tmp1[i] = names[i];
        tmp2[i] = numbers[i];
    }

    free(names);
    free(numbers);

    names = tmp1;//namees와 numbers가 새로운 배열을 가리키도록 한다
    numbers = tmp2;//배열의 이름은 포인터 변수이다.
}