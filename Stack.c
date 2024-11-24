//�ڷᱸ�� �ѿ��� ������ 7���� LAB03 Stack ADT ����
//���� �ۼ���: 2023.04.10(��)
//2019313550 �ں���
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{   // ���� ��� ����ü ����
    char data;         // ��忡 ����� ������
    struct node *next; // ���� ��带 ����Ű�� ������
} Node;

typedef struct stack {// ���� ����ü ���� 
    Node* top;  // ������ ���� ��� ���
    int size;   // ���ÿ� ����� ��� ����
    int max;    // ������ �ִ� ũ��
} Stack;

void initStack(Stack* s, int max);// ���� �ʱ�ȭ �Լ�

int is_full(Stack* s);// ������ �� á���� Ȯ���ϴ� �Լ�
void push(Stack* s, char data);// ���ÿ� �����͸� �߰��ϴ� �Լ�
char pop(Stack* s);// ���ÿ��� �����͸� �����ϰ� ��ȯ�ϴ� �Լ�
char peek(Stack* s);// ���ÿ��� ���� ��ܿ� �ִ� �����͸� ��ȯ�ϴ� �Լ�
int element_count(Stack* s);// ������ ũ�⸦ ��ȯ�ϴ� �Լ�
void clear(Stack* s);// ������ ���� �Լ�
void print(Stack* s);// ���ÿ� ����� �����͸� ����ϴ� �Լ�
void top(Stack *s);//top�� �ִ� ���� ��ġ�� ��ȯ�ϴ� �Լ�
void replace(Stack* s, char data);// ������ top�� �ִ� �����͸� ��ü�ϴ� �Լ�
void show();//��ɾ��� ������ ����ϴ� �Լ�
int is_member(Stack* s, char data);//���ÿ� ����ִ� ������ Ȯ���ϴ� �Լ�

//������ ���
int is_empty(Stack* s);// ������ ���1: ������ ����ִ��� Ȯ���ϴ� �Լ�
int count_data(Stack* s, char data);// ������ ���2: ���ÿ� �ߺ��Ǵ� �����Ͱ� � �ִ��� Ȯ���ϴ� �Լ�
void reverse_stack(Stack* s);// ������ ���3: ���ÿ� ����� ������ �������ϴ�.
int find_element(Stack* s, char data);// ������ ���4: �Է��� ���� ���ÿ� ���°�� �����ϴ��� �˷��ݴϴ�.

int main() {
    int max;         // ������ �ִ� ũ�⸦ ������ ����
    Stack s;         
    show();         
    int parsed;    
    char input[100]; // ������ ũ�⸦ ����޴� �迭

    while (1){                                           
        printf("������ �ִ� ũ�⸦ �Է��ϼ���: "); 
        fgets(input, sizeof(input), stdin);        // ���ڿ� �Է�
        parsed = sscanf(input, "%d", &max);        // ������ ����ȯ�Ͽ� max ������ ����
        if (parsed == 1){         
            break;
        }
        else{                
            printf("������ ũ��� ������ �Է��ϼž� �մϴ�.\n");
        }
    }

    initStack(&s, max);   //Stack ����
    char enter[100];      //��ɾ ����޴� �迭
    while(1){
        B:
        printf("��ɾ �Է��ϼ���: ");
        scanf("%s",enter);
        for (int i=0;enter[i]!='\0';i++){
            if (enter[i]=='+'){
                push(&s, enter[i+1]); //���ÿ� ������ �߰�
                i++;
            }
            else if (isdigit(enter[i])){ //���ڰ� �Էµ� ��� �ش� ���ڸ�ŭ pop ����
                int num=(int) enter[i]-'0';
                for (int i=1; i<num;i++){
                    printf("%c ",pop(&s));
                }
            }
            else if (enter[i]=='P'){
                printf("\n");
                printf("%c \n",peek(&s));//���� ������ ������ ���
                printf("\n");
                goto B;
            }
            else if (enter[i]=='-'){
                printf("%c ",pop(&s));//���� ������ ������ ��� �� ����
            }
                        
            else if (enter[i]=='F'){//������ ���� �� �ִ��� Ȯ��
                if(is_full(&s)){
                    printf("\n");
                    printf("True\n");
                    printf("\n");
                }
                else
                    printf("\n");
                    printf("False\n");
                    printf("\n");
                goto B;
            }
            else if (enter[i]=='?'){//�ش� �����Ͱ� ���ÿ� �����ϴ��� Ȯ��
                if (is_member(&s, enter[i+1])){
                    printf("\n");
                    printf("True\n");
                    printf("\n");
                    goto B;
                }
                else {
                    printf("\n");
                    printf("False\n");
                    printf("\n");
                    goto B;
            }
            }
            else if (enter[i]=='E'){//������ ����ִ��� Ȯ��
                if (is_empty(&s)) {
                    printf("\n");
                    printf("True\n");
                    printf("\n");
                    }
                else {
                    printf("\n");
                    printf("False\n");
                    printf("\n");
                }
                goto B;
            }
            else if (enter[i]=='=') replace(&s,enter[i+1]);//���� ������ ������ ��ü
            else if (enter[i]=='C') {//���� �ʱ�ȭ
                clear(&s);
            }
            else if (enter[i]=='#') {//���� ���� ���
                printf("\n");
                printf("%d\n",element_count(&s));
                printf("\n");
                goto B;
                }
            else if (enter[i]=='T') {//���� ������ ������ ��, ��ġ ���
                top(&s);
                goto B;
            }
            else if (enter[i] == '@') {//�Է¹��� ������ ���� ���
            char data;
            sscanf(&enter[i + 1], "%c", &data);
            printf("\n");
            printf("%c�� ���ÿ� %d�� �ֽ��ϴ�.\n", data, count_data(&s, data));
            printf("\n");
            goto B;
        }
            else if (enter[i] == 'R') {//���� ������
                reverse_stack(&s);
        }
            else if (enter[i] == 'W') {//�Է¹��� �����Ͱ� ���ÿ� ���°�� �ִ��� ���
            int position = find_element(&s, enter[i+1]);
            if (position != -1) {
                printf("\n");
                printf("Top�� ������ 1���̶�� �Ͽ��� �� \n");
                printf("%c�� ������ %d��° ��ġ�� �����մϴ�.\n",enter[i+1], position+1);
                printf("\n");
            } else {
                printf("\n");
                printf("�ش� �����ʹ� ���ÿ� �������� �ʽ��ϴ�.\n");
                printf("\n");
            }
            i++;
            goto B;
        }        
            else if (enter[i]=='*') goto A;//���α׷� ����
            else if (enter[i]=='L') continue;//���� ���
        }
        
        printf("\n");
        print(&s);//���� ���
        printf("\n");

    }
    A:
    printf("���α׷��� �����մϴ�.\n");
    return 0;
}
void show(){//��ɾ� �ȳ�
    printf("��ɹ��� �ȳ��ص帮�ڽ��ϴ�.\n");
    printf("+(��): ���ÿ� ���� �߰��մϴ�.\n");
    printf("-: ���� �������� �߰��� �� �����մϴ�.\n");
    printf("P: ���� �������� �߰��� ���� �����ݴϴ�.\n");
    printf("T: ���� �������� �߰��� ���� ������ ũ�⸦ �����ݴϴ�.\n");
    printf("=(��): ���� ������ ���Ҹ� �Է��Ͻ� ������ ��ü�մϴ�.\n");
    printf("#: ���ؿ� �����ϴ� ������ ������ ����մϴ�.\n");
    printf("C: ������ �ʱ�ȭ�մϴ�.\n");
    printf("E: ������ ����ִ��� Ȯ���մϴ�.\n");
    printf("F: ������ �� �� �ִ��� Ȯ���մϴ�.\n");
    printf("?(��): ���ÿ� �ش� ���� ������ ���Ұ� �����ϴ��� Ȯ���մϴ�.\n");
    printf("@(��): ���ÿ� �ش� ���� ������ ���Ұ� � �����ϴ��� �˷��ݴϴ�.\n");
    printf("R: ���ÿ� ����� ������ �������ϴ�.\n");
    printf("W(��): ���ÿ� ���� ���°�� ��ġ�ϴ��� ����մϴ�.\n");
    printf("L: ���ÿ� ����� ���� ���� ��ġ�� ����մϴ�.\n");
    printf("*: ���α׷��� �����մϴ�.\n\n");
}
void initStack(Stack* s, int max) {//���� �ʱ�ȭ
    s->top = NULL;
    s->size = 0;
    s->max = max;
}
int is_empty(Stack* s) {//������ ����ִ��� Ȯ��
    return s->top == NULL;
}
int is_full(Stack* s) {//������ ���� �� �ִ��� Ȯ��
    return s->size == s->max;
}
void push(Stack* s, char data) {//���ÿ� ������ �߰�
    if (is_full(s)) {
        printf("\n");
        printf("Error: Stack is Full.\n");
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}
char pop(Stack* s) {
    if (is_empty(s)) {//������ ������� ���
        printf("\n");
        printf("Error: Nothing to pop.\n");
        return 0;
    }
    Node* temp = s->top;//������ ������ ���
    char data = temp->data;
    s->top = temp->next;
    s->size--;
    free(temp);
    return data;
}
char peek(Stack* s) {
    if (is_empty(s)) {//������ ������� ���
        printf("\n");
        printf("Error: Nothing to peek.\n");
        return 0;
    }
    return s->top->data; //���� ������ ������ ���
}
int element_count(Stack* s) {
    return s->size; //���� ���� ���
}
void clear(Stack* s) {
    while (!is_empty(s)) {//������ ��� �� �� �� ���� ���ÿ� ����� ������ pop
        pop(s);
    }
}
void print(Stack* s) {
    if (is_empty(s)) {
        printf("Stack is empty.\n");
        return;
    }

    Stack temp;
    initStack(&temp, s->max);
    int i = 0;
    char* temp_str = (char*)malloc((s->size + 1) * sizeof(char));

    while (!is_empty(s)) {    // ���� ���ÿ��� ���Ҹ� �ӽ� ���ÿ� �ű�鼭 ���ڿ��� ����
        char top_element = pop(s);
        push(&temp, top_element);
        temp_str[i++] = top_element;
    }

    temp_str[i] = '\0';

    for (int j = strlen(temp_str) - 1; j >= 0; j--){    // ���ڿ��� �������� ���
        printf("%c ", temp_str[j]);
    }
    
    while (!is_empty(&temp)) {    // �ӽ� ������ ���Ҹ� �ٽ� ���� �������� �ű�
        push(s, pop(&temp));
    }
    printf("(TOP: %c)\n", peek(s));

    free(temp_str);
}
void top(Stack *s){
    printf("\n");
    printf("(%d, %c)\n",element_count(s),peek(s));
    printf("\n");
}
void replace(Stack* s, char data) {
    if (is_empty(s)) {
        printf("\n");
        printf("Error: Nothing to replace\n");
        return;
    }
    s->top->data = data;
}
int is_member(Stack* s, char data) {
    Stack temp;
    initStack(&temp, s->max);
    int found = 0;

    while (!is_empty(s)) {    // ���� ���ÿ��� ���Ҹ� ã���鼭 �ӽ� ���ÿ� �ű�
        char top_element = pop(s);
        push(&temp, top_element);

        if (top_element == data) {
            found = 1;
            break;
        }
    }

    while (!is_empty(&temp)) {    // �ӽ� ������ ���Ҹ� �ٽ� ���� �������� �ű�
        push(s, pop(&temp));
    }

    return found;
}

int count_data(Stack* s, char data) {
    Stack temp;
    initStack(&temp, s->max);
    int count = 0;

    while (!is_empty(s)) {    // ���� ���ÿ��� ���Ҹ� ã���鼭 �ӽ� ���ÿ� �ű�
        char top_element = pop(s);
        push(&temp, top_element);

        if (top_element == data) {
            count++;
        }
    }

   
    while (!is_empty(&temp)) { // �ӽ� ������ ���Ҹ� �ٽ� ���� �������� �ű�
        push(s, pop(&temp));
    }

    return count;
}
void reverse_stack(Stack* s) {
    Stack temp1;
    Stack temp2;
    initStack(&temp1, s->max);
    initStack(&temp2, s->max);


    while (!is_empty(s)) {    // ���� ������ ���Ҹ� temp1 ���ÿ� �ű�
        push(&temp1, pop(s));
    }


    while (!is_empty(&temp1)) {    // temp1 ������ ���Ҹ� temp2 ���ÿ� �ű�
        push(&temp2, pop(&temp1));
    }


    while (!is_empty(&temp2)) {    // temp2 ������ ���Ҹ� ���� �������� �ű�
        push(s, pop(&temp2));
    }
}
int find_element(Stack* s, char data) {
    Stack temp;
    initStack(&temp, s->max);
    int position = -1;
    int index = 0;

    while (!is_empty(s)) {    // ���� ���ÿ��� ���Ҹ� ã���鼭 �ӽ� ���ÿ� �ű�
        char top_element = pop(s);
        push(&temp, top_element);

        if (top_element == data) {
            position = index;
            break;
        }

        index++;
    }

    while (!is_empty(&temp)) {    // �ӽ� ������ ���Ҹ� �ٽ� ���� �������� �ű�
        push(s, pop(&temp));
    }

    return position;
}