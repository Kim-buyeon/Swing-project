#include<stdio.h>
#include<string.h>
#define CAPACITY 100
#define BUFFER_SIZE 100

char * names[CAPACITY];
char * numbers[CAPACITY];
int n=0;//����Ǿ��ִ� ����� ��

void add();
void find();
void status();
void remove_entry();
int main(void)
{
    char command[BUFFER_SIZE];
    while(1){
        printf("$");
        scanf("%s",command);//������� ��ɹ��� �޾Ƽ� command ��� �迭�� ����
        if(strcmp(command,"add")==0)  //strcmp(���� ù��° ���ڿ�,���� �ι�° ���ڿ�)
            add();//strcmp�Լ��� �� ���ڿ��� �����ϸ� 0�� ��ȯ�Ѵ�.
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
    char buf[BUFFER_SIZE];//ã���� �ϴ� �̸��� buffer�� �Է�
    scanf("%s",buf);

    int i;
    for(i=0;i<n;i++){
        if(strcmp(buf,names[i])==0){//�迭 ������ ��� 0 ����
            printf("%s\n",numbers[i]);
            return;//���⼭ return ������ �ؿ� �ִ� �ڵ���� �������� ����
        }
        printf("no person named'%s'exists.\n",buf);
    }
}

void status(){// �����ִ� ��� ����� ��ȭ��ȣ ���
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
        if(strcmp(buf,names[i])==0){//������ �̸��� ã�� �̸��� �Ȱ����� Ȯ��
            names[i] = names[n-1];
            numbers[i] = numbers[n-1];//�� ������ ����� ������ �ڸ��� �ű��.
            n--;
            printf("'%s was deleted successfully.\n",buf);
            return;
        }
    }
    printf("No person named '%s exists.\n",buf);//�տ��� return �����ʾҴ�.
}