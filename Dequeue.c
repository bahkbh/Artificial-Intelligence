//�ڷᱸ�� �ѿ��� ������ 8���� LAB04 Deueue ADT ����
//���� �ۼ���: 2023.04.23(��)
//2019313550 �ں���
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {// ������ ���Ǵ� ��� ������ ���� ����ü
    char data;
    struct Node* prev;
    struct Node* next;
} Node;


Node* create_node(char data) {// ���ο� ��带 �����Ͽ� �ʱ�ȭ�ϴ� �Լ�
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

typedef struct Deque {// �� ����ü
    Node* head;
    Node* tail;
    int count;
    int max_size;
} Deque;

void add_front(Deque* deque, char data);//���� front�� �����͸� �����ϴ� �Լ�
void add_rear(Deque* deque, char data);//���� rear�� �����͸� �����ϴ� �Լ�
char delete_front(Deque* deque);//���� front�� ����� �����͸� ��ȯ�ϰ� �����ϴ� �Լ�
char delete_rear(Deque* deque);//���� rear�� ����� �����͸� ��ȯ�ϰ� �����ϴ� �Լ�
void init(Deque* deque);//���� �ʱ�ȭ �ϴ� �Լ�

int is_empty(Deque* deque);//���� ����ִ��� Ȯ���ϴ� �Լ�
int is_full(Deque* deque);//���� ���� �� �ִ��� Ȯ���ϴ� �Լ�
void print(Deque* deque);//���� ����ϴ� �Լ�
char get_front(Deque* deque);//���� front�� ����� �����͸� �����ִ� �Լ�
char get_rear(Deque* deque);//���� rear�� ����� �����͸� �����ִ� �Լ�
int data_count(Deque* deque);//���� ����� �������� ������ �����ִ� �Լ�
void is_member(Deque* deque, char data);//���� �Է��� �����Ͱ� ���°�� �����ϴ��� �˷��ִ� �Լ�
void replace_front(Deque* deque, char data);//���� front�� ���� �Է¹��� ������ ��ü�ϴ� �Լ�
void replace_rear(Deque* deque, char data);//���� rear�� ���� �Է¹��� ������ ��ü�ϴ� �Լ�
void clear(Deque* deque);//���� �ʱ�ȭ �ϴ� �Լ�
int how_many(Deque* deque, char data);//�Է� ���� ���� ���� � �����ϴ� �� �˷��ִ� �Լ�
void remove_duplicate(Deque* deque);//���� �����ϴ� �ߺ��Ǵ� ���� �����ִ� �Լ�
void update(Deque* deque, char direction);//������ �Է¹ް� rear�� ���� front�� �Ű��ְų�, front�� ���� rear�� �Ű��ִ� �Լ�
void show();//��ɾ ����ϴ� �Լ�

int main() {
    Deque deque;
    init(&deque);
    char enter[100];      //��ɾ ����޴� �迭
    show();
    while(1){
        B:
        printf("��ɾ �Է��ϼ���: ");
        scanf("%s",enter);
        for (int i=0;enter[i]!='\0';i++){
            if (enter[i]=='>'){
                i++;
                for (int i=1;enter[i]!='\0';i++){
                if (enter[i]=='+'){
                    add_rear(&deque, enter[i+1]); //���� ������ �߰�
                    i++;
                }
            
                else if (isdigit(enter[i])){ //���ڰ� �Էµ� ��� �ش� ���ڸ�ŭ delete_rear ����
                    int num=(int) enter[i]-'0';
                    for (int i=1; i<num;i++){
                        printf("%c ",delete_rear(&deque));
                    }
                }
                else if (enter[i] == '-') {
                    int dequeued = delete_rear(&deque); // ���� ó���� �߰��� �����͸� ������
                    if (dequeued != -1) { // ���� ������� ������ ���
                        printf("%c ", dequeued);
                    }
                }
                else if (enter[i]=='U'){
                    update(&deque,'>');
                }
                else if (enter[i]=='P'){
                    printf("%c \n",get_rear(&deque));//���� ������ ������ ���
                    goto B;
                }
                else if (enter[i] == '=') {
                    replace_rear(&deque, enter[i + 1]); // ���� ������ ������ ��ü
                    i++;
                }  
                }  }
            else if (enter[i]=='<'){
                i++;
                for (int i=1;enter[i]!='\0';i++){
                if (enter[i]=='+'){
                    add_front(&deque, enter[i+1]); //���� ������ �߰�
                    i++;
                }
            
                else if (isdigit(enter[i])){ //���ڰ� �Էµ� ��� �ش� ���ڸ�ŭ delete_front ����
                    int num=(int) enter[i]-'0';
                    for (int i=1; i<num;i++){
                        printf("%c ",delete_front(&deque));
                    }
                }
                else if (enter[i] == '-') {
                    int dequeued = delete_front(&deque); // ���� ó���� �߰��� �����͸� ������
                    if (dequeued != -1) { // ���� ������� ������ ���
                        printf("%c ", dequeued);
                    }
                }
                else if (enter[i]=='U'){
                    update(&deque,'<');
                }
                else if (enter[i]=='P'){
                    printf("%c \n",get_front(&deque));//���� ������ ������ ���
                    goto B;
                }
                else if (enter[i] == '=') {
                    replace_front(&deque, enter[i + 1]); // ���� ������ ������ ��ü
                }
            }
            }
            else if (enter[i]=='F'){//���� ���� �� �ִ��� Ȯ��
                if(is_full(&deque)){
                    printf("True\n");
                }
                else
                    printf("False\n");
                goto B;
            }
 

            else if (enter[i]=='?'){//�ش� �����Ͱ� ���� �����ϴ��� Ȯ��
            is_member(&deque, enter[i+1]);
            goto B;
            }
                
            else if (enter[i]=='E'){//���� ����ִ��� Ȯ��
                if (is_empty(&deque)) {
                    printf("True\n");
                    }
                else {
                    printf("False\n");
                }
                goto B;
            }

            else if (enter[i]=='C') {//�� �ʱ�ȭ
                clear(&deque);
                goto B;
            }
            else if (enter[i]=='#') {//���� ����� ������ ���� ���
                printf("%d\n",data_count(&deque));
                goto B;
                }

            else if (enter[i]=='@'){
                printf("%d\n",how_many(&deque, enter[i+1]));
                goto B;
            }

            else if (enter[i] == 'R') { // �ߺ� ��� ����
                remove_duplicate(&deque);
            }             
            else if (enter[i]=='*') goto A;//���α׷� ����
            else if (enter[i]=='L') continue;//�� ���
        }
            
            printf("\n");
            print(&deque);//�� ���
            printf("\n");

    }
    A:
    printf("���α׷��� �����մϴ�.\n");
    return 0;
}

void show(){//��ɾ� ���
    printf("��ɹ��� �ȳ��ص帮�ڽ��ϴ�.\n");
    printf("<+(��): front�� ���� �߰��մϴ�.\n");
    printf(">+(��): rear�� ���� �߰��մϴ�.\n");
    printf("<-: front�� ���� �����մϴ�.\n");
    printf(">-: rear�� ���� �����մϴ�.\n");
    printf("<P: front�� ���� �����ݴϴ�.\n");
    printf(">P: rear�� ���� �����ݴϴ�.\n");
    printf("L: ���� ����� ���� ����մϴ�.\n");
    printf("E: ���� ����ִ��� Ȯ���մϴ�.\n");
    printf("F: ���� �� �� �ִ��� Ȯ���մϴ�.\n");
    printf("?(��): ���� �ش� ���� ������ ���Ұ� �����ϴ��� Ȯ���մϴ�.\n");
    printf("#: ���� �����ϴ� ������ ������ ����մϴ�.\n");
    printf("C: ���� �ʱ�ȭ�մϴ�.\n");
    printf(">U: front�� �ִ� �����͸� rear�� �ű�ϴ�.\n");
    printf("<U: rear�� �ִ� �����͸� front�� �ű�ϴ�.\n");
    printf("@(��): ���� �ش� ���� � �����ϴ��� �˷��ݴϴ�.\n");
    printf("R: ���� ����� ���� �� �ߺ��� ���� �����մϴ�..\n");
    printf("*: ���α׷��� �����մϴ�.\n\n");

}
void init(Deque* deque) {//���� �ʱ�ȭ �ϴ� �Լ�
    deque->head = NULL;
    deque->tail = NULL;
    deque->count = 0;
    deque->max_size = 100;
}
void add_front(Deque* deque, char data) {//���� front�� �����͸� �����ϴ� �Լ�
    if (deque->count == deque->max_size) {
        printf("���� ���� �� �ֽ��ϴ�.\n");
        return;
    }
    Node* new_node = create_node(data);
    if (deque->count == 0) {
        deque->head = new_node;
        deque->tail = new_node;
    } else {
        new_node->next = deque->head;
        deque->head->prev = new_node;
        deque->head = new_node;
    }
    deque->count++;
}

void add_rear(Deque* deque, char data) {//���� rear�� �����͸� �����ϴ� �Լ�
    if (deque->count == deque->max_size) {
        printf("���� ���� �� �ֽ��ϴ�.\n");
        return;
    }
    Node* new_node = create_node(data);
    if (deque->count == 0) {
        deque->head = new_node;
        deque->tail = new_node;
    } else {
        deque->tail->next = new_node;
        new_node->prev = deque->tail;
        deque->tail = new_node;
    }
    deque->count++;
}
char delete_front(Deque* deque) {//���� front�� ����� �����͸� ��ȯ�ϰ� �����ϴ� �Լ�
    if (deque->head == NULL) {
        printf("���� ����ֽ��ϴ�.\n");
        return '\0';
    }
    Node* temp_node = deque->head;
    char data = temp_node->data;
    deque->head = temp_node->next;
    if (deque->head == NULL) {
        deque->tail = NULL;
    } else {
        deque->head->prev = NULL;
    }
    free(temp_node);
    deque->count--;
    return data;
}
char delete_rear(Deque* deque) {//���� rear�� ����� �����͸� ��ȯ�ϰ� �����ϴ� �Լ�
    if (deque->tail == NULL) {
        printf("���� ����ֽ��ϴ�.\n");
        return '\0';
    }
    Node* temp_node = deque->tail;
    char data = temp_node->data;
    deque->tail = temp_node->prev;
    if (deque->tail == NULL) {
        deque->head = NULL;
    } else {
        deque->tail->next = NULL;
    }
    free(temp_node);
    deque->count--;
    return data;
}
int is_empty(Deque* deque) {//���� ����ִ��� Ȯ���ϴ� �Լ�
    return deque->count == 0;
}
int is_full(Deque* deque) {//���� ���� �� �ִ��� Ȯ���ϴ� �Լ�
    return deque->count == deque->max_size;
}
void print(Deque* deque) {//���� ����ϴ� �Լ�
    if (deque->count == 0) {
        printf("���� ����ֽ��ϴ�.\n");
        return;
    }
    printf("Deque: ");
    Node* temp_node = deque->head;
    while (temp_node != NULL) {
        printf("%c ", temp_node->data);
        temp_node = temp_node->next;
    }
    printf("\n");
}
char get_front(Deque* deque) {//���� front�� ����� �����͸� �����ִ� �Լ�
    if (deque->head == NULL) {
        printf("���� ����ֽ��ϴ�.\n");
        return '\0';
    }
    return deque->head->data;
}
char get_rear(Deque* deque) {//���� rear�� ����� �����͸� �����ִ� �Լ�
    if (deque->tail == NULL) {
        printf("���� ����ֽ��ϴ�.\n");
        return '\0';
    }
    return deque->tail->data;
}
int data_count(Deque* deque) {//���� ����� �������� ������ �����ִ� �Լ�
    return deque->count;
}
void is_member(Deque* deque, char data) {//���� �Է��� �����Ͱ� ���°�� �����ϴ��� �˷��ִ� �Լ�
    Node* temp_node = deque->head;
    int index = 0;
    while (temp_node != NULL) {
        if (temp_node->data == data) {
            printf("%d\n", index+1);
            return;
        }
        index++;
        temp_node = temp_node->next;
    }
    printf("-1\nã���ô� ���� ���� �������� �ʽ��ϴ�.\n");
}
void replace_front(Deque* deque, char data) {//���� front�� ���� �Է¹��� ������ ��ü�ϴ� �Լ�
    if (deque->head == NULL) {
        printf("���� ����ֽ��ϴ�.\n");
    return;
}
deque->head->data = data;
}
void replace_rear(Deque* deque, char data) {//���� rear�� ���� �Է¹��� ������ ��ü�ϴ� �Լ�
    if (deque->tail == NULL) {
        printf("���� ����ֽ��ϴ�.\n");    
    return;
}
    deque->tail->data = data;
}
void clear(Deque* deque) {//���� �ʱ�ȭ �ϴ� �Լ�
    Node* temp_node = deque->head;
    while (temp_node != NULL) {
        Node* next_node = temp_node->next;
        free(temp_node);
        temp_node = next_node;
    }
    deque->head = NULL;
    deque->tail = NULL;
    deque->count = 0;
}
int how_many(Deque* deque, char data) {//�Է� ���� ���� ���� � �����ϴ� �� �˷��ִ� �Լ�
    int count = 0;
    Node* temp_node = deque->head;
    while (temp_node != NULL) {
        if (temp_node->data == data) {
            count++;
        }
        temp_node = temp_node->next;
    }
    return count;
}
void remove_duplicate(Deque* deque) {//���� �����ϴ� �ߺ��Ǵ� ���� �����ִ� �Լ�
    Node* current = deque->head;
    while (current != NULL) {// ���� ��带 �������� ���� ������ �ߺ��� Ž��
        Node* runner = current->next;
        while (runner != NULL) {
            if (current->data == runner->data) { // �ߺ��� ���� ���� ���
                Node* temp_node = runner;
                runner = runner->next;
                if (temp_node == deque->tail) {// �ߺ��� ��带 ����
                    deque->tail = temp_node->prev;
                }
                if (temp_node->prev == NULL) {
                    deque->head = temp_node->next;
                } else {
                    temp_node->prev->next = temp_node->next;
                }
                if (temp_node->next != NULL) {
                    temp_node->next->prev = temp_node->prev;
                }
                free(temp_node);
                deque->count--;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

void update(Deque* deque, char direction) {//������ �Է¹ް� rear�� ���� front�� �Ű��ְų�, front�� ���� rear�� �Ű��ִ� �Լ�
    if (deque->count < 2) { // ��尡 1�� ������ ���� �������� ����
        return;
    }
    if (direction == '<') { // rear�� ���� front�� �̵���Ű�� ���
        Node* temp_node = deque->tail;
        deque->tail = deque->tail->prev;
        deque->tail->next = NULL;
        temp_node->prev = NULL;
        temp_node->next = deque->head;
        deque->head->prev = temp_node;
        deque->head = temp_node;
    } else if (direction == '>') {{ // front�� ���� rear�� �̵���Ű�� ���
        Node* temp_node = deque->head;
        deque->head = deque->head->next;
        deque->head->prev = NULL;
        temp_node->next = NULL;
        temp_node->prev = deque->tail;
        deque->tail->next = temp_node;
        deque->tail = temp_node;
    } 
    }
    else {// ��ȿ���� ���� ������ �Էµ� ���
        printf("��ȿ�� ������ �ƴմϴ�.\n");
    }
    }
