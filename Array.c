//�ڷᱸ�� �ѿ��� ������ 5���� LAB01 Array ADT ����
//���� �ۼ���: 2023.04.01(��)
//2019313550 �ں���
#include <stdio.h>
#include <string.h> //���ڿ� �Լ��� ����ϱ� ���� �������

int lct = -1; //���� ��ġ�� ��Ÿ���� ���� ���� ����
int size = 0; //�迭�� �����ϴ� �������� ���� ��Ÿ���� ���� ��������
void show(); //��ɾ �����ִ� �Լ�
void insert(char arr[], char data); //�����͸� �߰��ϴ� �Լ�
void traverse_front(int num);//���� ��ġ�� �� ������ �̵���Ű�� �Լ�
void traverse_rear(int num);//���� ��ġ�� �� �ڷ� �̵���Ű�� �Լ�
void delete(char arr[]);//���� ����� �Լ�
void empty(char arr[]);//�迭�� �ʱ�ȭ �ϴ� �Լ�
void get_data(char arr[]);//���� ��ġ�� �����͸� �����ִ� �Լ�
void replace(char arr[],char new_data);//���� ��ġ�� �����͸� �Է°����� ��ȯ��Ű�� �Լ�
void move(char arr[], int index);//���� ��ġ�� �����͸� �Է¹��� index�� ��ġ�� �̵���Ű�� �Լ�
void data_count(char arr[]);//�������� ������ ������ �ε��� ��ȣ�� ����ϴ� �Լ�
void up(char arr[]); //�����͸� �빮�ڷ� ������ִ� �Լ�
void down(char arr[]); //�����͸� �ҹ��ڷ� ������ִ� �Լ�
void change(char arr[]); //�빮���� �����͸� �ҹ��ڷ� ������ְ� �ҹ����� �����͸� �빮�ڷ� ������ִ� �Լ�
void print(char arr[]); //�����͸� ��� ����ϰ� ���� ��ġ�� �����ִ� �Լ�

int main() {
	char my_array[30]; //�����͸� �����ϴ� �迭
	char enter[30]; //��ɾ �Է¹޴� �迭
    show();
    while(1){
        B: printf("��ɾ �Է��ϼ���: ");
        scanf("%s",enter);

        if(enter[0]=='+'){//�����͸� �Է¹޴� ���
            for(int i=0; i<strlen(enter);i++){
                if(enter[i]!='+') {
                    insert(my_array,enter[i]);
                    lct++;
                    size++;
                }
            }
        }
        if(enter[0]=='<'){//���� ��ġ�� �� ������ �̵��ϴ� ���
            int num=0;
            lct=0;
            if(enter[1]=='\0') goto A;//<�� �Է��� ��� ���� ��ġ�� �����Ű�� �����Ϳ� ��ġ�� ���
            if(enter[1]=='-') delete(my_array);//<�ڿ� -�� ���� ��� delete �Լ� ȣ��
            if(enter[1]=='M'){//<�ڿ� M�� ���� ��� move �Լ� ȣ��
                int move_num=0;
                if(enter[2]=='P') {
                    move_num=lct-1;
                    }
                else if(enter[2]=='N') {
                    move_num=lct+1;
                }
                else move_num=enter[2]-'0';
                move(my_array,move_num);
            }            
            for(int i=0; i<size;i++){//<�ڿ� N �Ǵ� P�� ���� ��� �ش��ϴ� �� ��ŭ ���� ��ġ �̵�
                if(enter[i]=='N') num++;
                if(enter[i]=='P') num--;
            }
            traverse_front(num);
        }
        if(enter[0]=='>'){//���� ��ġ�� �� �ڷ� �̵��ϴ� ���
            int num=0;
            lct=size-1;
            if(enter[1]=='\0') goto A;//<�� �Է��� ��� ���� ��ġ�� �����Ű�� �����Ϳ� ��ġ�� ���
            if(enter[1]=='-') delete(my_array);//<�ڿ� -�� ���� ��� delete �Լ� ȣ��
            if(enter[1]=='M'){//<�ڿ� M�� ���� ��� move �Լ� ȣ��
                int move_num=0;
                if(enter[2]=='P') {
                    move_num=lct-1;
                    }
                else if(enter[2]=='N') {
                    move_num=lct+1;
                }
                else move_num=enter[2]-'0';
                move(my_array,move_num);
            }
            for(int i=0; i<size;i++){//<�ڿ� N �Ǵ� P�� ���� ��� �ش��ϴ� �� ��ŭ ���� ��ġ �̵�
                if(enter[i]=='N') num++;
                if(enter[i]=='P') num--;
            }            
            traverse_rear(num);
        }
        if(enter[0]=='-') delete(my_array);//���� ��ġ�� ������ �����ϴ� ���
        if(enter[0]=='E') empty(my_array);//�迭�� �ʱ�ȭ�ϴ� ���
        if(enter[0]=='=') replace(my_array,enter[1]);//���� ��ġ�� �����͸� �Է°����� �ٲٴ� ���
        if(enter[0]=='@'){ //���� ��ġ�� �����͸� �����ִ� ���
            get_data(my_array);
            goto B;
        }
        if(enter[0]=='M') {//���� ��ġ�� �����͸� �Է¹��� index�� ��ġ�� �̵���Ű���� ���
            int move_num=0;
            if(enter[1]=='P') {
                move_num=lct-1;
                }
            else if(enter[1]=='N') {
                move_num=lct+1;
                }
            else move_num=enter[1]-'0';
            move(my_array,move_num);
        }
        if(enter[0]=='L') goto A;//�����͸� ����ϰ�, ���� ��ġ�� �����ִ� ���
        if(enter[0]=='N') data_count(my_array);//�������� ������ ������ �ε��� ��ȣ�� �����ִ� ���
        if(enter[0]=='U') up(my_array);//�����͸� �빮�ڷ� ����� ���
        if(enter[0]=='D') down(my_array);//�����͸� �ҹ��ڷ� ����� ���
        if(enter[0]=='C') change(my_array);//�빮���� �����͸� �ҹ��ڷ� ������ְ� �ҹ����� �����͸� �빮�ڷ� ������ִ� ���
        if(enter[0]=='F') {
            printf("���α׷��� �����մϴ�.\n");
            break;//���α׷� ����
        }
        A: print(my_array);//�ش� ��� ���� �� �迭�� ����� �����Ϳ� ���� ��ġ ���
       }

}

void show(){
    printf("��ɾ �ȳ��� �帮�ڽ��ϴ�.\n");
    printf("+(������): �����͸� �߰��մϴ�.\n");
    printf("<(�߰� ��ɾ�): �迭�� ���� ó������ �� �� �߰� ����� �����մϴ�. �߰� ����� �����ø� �迭�� ���� ó������ ���� ��ġ�� �̵���ŵ�ϴ�.\n");
    printf(">(�߰���ɾ�): �迭�� ���� ���������� �� �� �߰� ����� �����մϴ�. �߰� ����� �����ø� �迭�� ���� ���������� ���� ��ġ�� �̵���ŵ�ϴ�.\n");
    printf("M(�߰� ��ɾ�): ���� ��ġ�� �����ϴ� �����͸� �̵���ŵ�ϴ�.\n");
    printf("�߰� ��ɾ� ����: P: ���� ��ġ ���� ������, N: ���� ��ġ ���� ������, ����: �ε���\n");
    printf("-: ���� ��ġ�� �����͸� �����մϴ�.\n");
    printf("@: ���� ��ġ�� �����͸� ����մϴ�.\n");
    printf("=(������): ���� ��ġ�� �����͸� �Է��Ͻ� �����ͷ� ��ȯ�մϴ�.\n");
    printf("E: �迭�� �ʱ�ȭ�մϴ�.\n");
    printf("N: ������ ������ �ε��� ������ ��ȣ �� ����մϴ�.\n");    
    printf("U: �빮�ڷ� ��ȯ�մϴ�.\n");
    printf("D: �ҹ��ڷ� ��ȯ�մϴ�.\n");
    printf("C: ��ҹ��� ��ȯ\n");
    printf("L: �迭�� ����� ��� �����͸� ����ϰ� ���� ��ġ�� ����մϴ�.\n");
    printf("F: ���α׷��� �����մϴ�.\n\n");
    }
void insert(char arr[], char data) {
	if (lct + 1 == size) arr[lct + 1] = data; //�迭 ���� �����͸� �߰��ϴ� ���
	else //�߰��� �߰��ϴ� ���
		for (int i = size; i > lct+1; i--) arr[i] = arr[i - 1];
		arr[lct + 1] = data;
}
void print(char arr[]) {
	for (int i = 0; i < size; i++) printf("%c ", arr[i]); //������ ���
	if (size) printf("���� ��ġ�� %d��°�� �ִ� %c�Դϴ�.\n",lct+1 ,arr[lct]);
	else printf("empty array\n");//�迭�� �����Ͱ� �������� ���� ��� ���
}
void traverse_front(int num){
    lct=lct+num;//���� ��ġ ����
}
void traverse_rear(int num){
    lct=lct+num;//���� ��ġ ����
}
void delete(char arr[]){
    size--;
    for (int i = lct; i < size; i++) {
		arr[i] = arr[i + 1];
	}
    if (lct>=size) {//���� ��ġ�� �迭�� ũ�⺸�� ū ��� �迭�� ó������ ���ư�
        lct=0;
    }
}
void empty(char arr[]){
    arr[0]='\0';//�迭 �� ���� ��ġ, �迭 ũ�� �ʱ�ȭ
    lct=-1;
    size=0;
}
void get_data(char arr[]){
    printf("���� ��ġ�� �ִ� ���� %c �Դϴ�.\n",arr[lct]);
}
void move(char arr[], int index){
    char tmp;//�ӽ� ���� ����
    if(lct==index) printf("���� ��ġ�Դϴ�!\n");//�ű���� �ϴ� ��ġ�� ���� ��ġ�� ���
    else if (lct>index){//���� ��ġ���� �ε��� ��ȣ�� ���������� �ű���� �Ҷ�
        tmp=arr[lct];
        for(int i=lct;i>index;i--) arr[i]=arr[i-1];
        arr[index]=tmp;
        lct=index;
    }
    else{//���� ��ġ���� �ε��� ��ȣ�� ū ������ �ű���� �Ҷ�
        tmp=arr[lct];
        for(int i=lct;i<index;i++) arr[i]=arr[i+1];
        arr[index]=tmp;
        lct=index;
    }
    }
void replace(char arr[],char new_data){
    arr[lct]=new_data;
}
void up(char arr[]){
    for(int i=0;i<size;i++){//�ƽ�Ű �ڵ带 �̿��� �빮�ڷ� ��ȯ
        if(arr[i]>=97) arr[i]=arr[i]-32;
    }
}
void down(char arr[]){
    for(int i=0;i<size;i++){//�ƽ�Ű �ڵ带 �̿��� �ҹ��ڷ� ��ȯ
        if(arr[i]<=90) arr[i]=arr[i]+32;
    }    
}
void change(char arr[]){
    for(int i=0;i<size;i++){//�ƽ�Ű �ڵ带 �̿��� �빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� ��ȯ
        if(arr[i]<=90) arr[i]=arr[i]+32;
        else if(arr[i]>=97) arr[i]=arr[i]-32;
    } 
}
void data_count(char arr[]){
    printf("�������� ������ %d���̸�, �ε��� ��ȣ�� %d������ �ֽ��ϴ�.\n",size,size-1);
}