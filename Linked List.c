//�ڷᱸ�� �ѿ��� ������ 6���� LAB02 Linked List ADT ����
//���� �ۼ���: 2023.04.04(ȭ)
//2019313550 �ں���
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>            
 
typedef struct Node {// ���Ḯ��Ʈ ��� ����ü
    char data;            // ���� ������
    struct Node *next;    // ���� ��带 ����Ű�� ������
} Node;
typedef struct List {// ���Ḯ��Ʈ ����ü
    Node *head;    // ����Ʈ�� ���� ��带 ����Ű�� ������
    int size;      // ����Ʈ�� ũ��
} List;
void show(); //��ɾ ����ϴ� �Լ�
void initList(List *list);// ����Ʈ �ʱ�ȭ �Լ�
void addTail(List *list, char data);// ����Ʈ �������� ��� �߰� �Լ�
void add(List *list, int index, char data);//����Ʈ�� ���ϴ� ��ġ�� ��� �߰� �Լ�
void addFirst(List* list, char data);//����Ʈ�� ���� ó���� ��� �߰� �Լ�
void traverse_front();//���� ��ġ�� ����Ʈ�� ���� ó������ �̵���Ű�� �Լ�
void traverse_rear();//���� ��ġ�� ����Ʈ�� ���� ���������� �̵���Ű�� �Լ�
void traverse_next();//���� ��ġ�� �������� �̵���Ű�� �Լ�
void traverse_prev();//���� ��ġ�� �������� �̵���Ű�� �Լ�
void delete(List *list, int index);//Ư�� ��ġ�� ��带 ������Ű�� �Լ�
void print(List *list);//����Ʈ ��ü�� ���� ��ġ�� ��½�Ű�� �Լ�
Node *check_get_data(List *list, int index);// �ε����� �ش��ϴ� ��� ��ȯ �Լ�
void get_data(List *list, int index);// �ε����� �ش��ϴ� ��� ��� �Լ�
void is_Empty(List *list);//����Ʈ�� ����ִ��� Ȯ�����ִ� �Լ�
void data_count(List *list);//����Ʈ�� ����� ���� Ȯ�����ִ� �Լ�
int findtheindex(List *list, char value);//Ư�� ����� ��ġ�� Ȯ�����ִ� �Լ�
void is_member(List *list, char value);//Ư�� ����� ���� ����Ʈ�� �����ϴ��� Ȯ�����ִ� �Լ�
void clear(List *list); // ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�
void replace(List *list, int index, char data);//Ư�� �ε����� ���� ��ȯ���ִ� �Լ�
void up(List *list);//�ڽŸ��� ���, ����Ʈ�� �Էµ� ����� ���� �빮�ڷ� ��ȯ���ִ� �Լ�
void down(List *list);//�ڽŸ��� ���, ����Ʈ�� �Էµ� ����� ���� �ҹ��ڷ� ��ȯ���ִ� �Լ�
void tog(List *list);//�ڽŸ��� ���, ����Ʈ�� �Էµ� ����� ���� �빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� ��ȯ���ִ� �Լ�
int count(List* list, char data);//�ڽŸ��� ���, �Է��� �����Ͱ� ����Ʈ�� ��� �����ϴ��� �˷��ִ� �Լ�
void get_index(List* list, char data);//�ڽŸ��� ���, �Է��� �����Ͱ� ����Ʈ�� ���°�� �����ϴ��� �˷��ִ� �Լ�
int lct=-1;//���� ��ġ�� Ȯ���ϱ� ���� ��������
int cnt=0;//����Ʈ�� ũ�⸦ Ȯ���ϱ� ���� ��������



int main() {
    List list;//����Ʈ ����
    initList(&list); //����Ʈ �ʱ�ȭ
    show();
    C:
    while(1){
        char enter[30]={0};//��ɾ �Է¹޴� �迭
        printf("��ɾ �Է��ϼ���:  ");
        scanf("%s",&enter);
        int i=0;
        while (enter[i] != '\0'){// �Է¹��� �迭�� ���� ���� ������ �ݺ�
            if (enter[i] == '+'){
                if (lct + 1 == cnt){              
                    addTail(&list, enter[i + 1]); // ����Ʈ�� ���� ��� �߰�
                    i++;                          
                }
                else{                                  
                    add(&list, lct + 1, enter[i + 1]); // lct+1 ��ġ�� ��� �߰�
                    i++;                               
                }
            }
            else if (enter[i] == '<'){
                traverse_front(); // ����Ʈ�� ù��° ������ ���
                if (enter[i + 1] == '+'){     
                    addFirst(&list, enter[i + 2]); // ����Ʈ�� ù��° ��ġ�� ��� �߰�
                    traverse_front();              
                    i = i + 2;                     
                }
            }
            else if (enter[i] == '>') traverse_rear(); 
            else if (enter[i] == 'N') traverse_next(); 
            else if (enter[i] == 'P') traverse_prev(); 
            else if (isdigit(enter[i]) & enter[i + 1] == '='){
                lct = (int)enter[i] - 49;          // lct�� �Էµ� ���ڸ� ����
                replace(&list, lct, enter[i + 2]); // lct ��ġ�� ��带 �Էµ� ������ ��ü
                i++;                              
                goto A;                            
            }
            else if (isdigit(enter[i])){
                lct = (int)enter[i] - 49; // lct�� �ش� ���ڸ� ����
                get_data(&list, lct);     // �ش� ���ڿ� �ش��ϴ� ������ ���
                i++;                    
                goto C;                  
            }
            else if (enter[i] == '-')delete (&list, lct); 
            if (enter[i] == '='){                  
                replace(&list, lct, enter[i + 1]); // �ش� ���ڿ� �ش��ϴ� �����͸� �Էµ� ���ڿ� ���� ���ڿ��� ��ü
                i++;                              
            }
            else if (enter[i] == 'E'){
                is_Empty(&list); // ����Ʈ�� ����ִ��� Ȯ��
                goto C;          
            }
            else if (enter[i] == '#'){
                data_count(&list); // ����Ʈ�� ����� �������� ���� ���
                goto C;            
            }
            else if (enter[i] == '?') is_member(&list, enter[i + 1]); 
            else if (enter[i] == 'C'){
                clear(&list); // ����Ʈ �ʱ�ȭ
                goto C;       
            }
            else if (enter[i]=='U') up(&list);
            else if (enter[i]=='D') down(&list);
            else if (enter[i]=='T') tog(&list);
            else if (enter[i]=='H'){
                printf("%d\n",count(&list,enter[i+1]));
                goto C;
            }            
            else if (enter[i]=='W') {
                get_index(&list,enter[i+1]);
                goto C;
                }
            else if (enter[i]=='G'){
                get_data(&list,lct);
                
                i++;
                goto C;


            } 
            else if (enter[i]=='L') goto A;
            else if (enter[i]=='*') goto B;
            i++;
        }
        A:
        print(&list);
    }

    B:
    printf("���α׷��� �����մϴ�.\n");
    return 0;
}

void show(){
    printf("��ɹ��� �ȳ��ص帮�ڽ��ϴ�.\n");
    printf("+(��): ����Ʈ�� �� �߰��մϴ�.\n");
    printf("<: ���� ��ġ�� ���� ����Ʈ�� ���� ó������ �̵��մϴ�.\n");
    printf(">: ���� ��ġ�� ���� ����Ʈ�� ���� ���������� �̵��մϴ�.\n");
    printf("(����): ���� ��ġ�� �Է��Ͻ� ��ġ�� �̵��մϴ�.\n");
    printf("-: ���� ��ġ�� ��带 �����մϴ�.\n");
    printf("G: ���� ��ġ�� �����͸� �����ݴϴ�.\n");
    printf("L: ���Ḯ��Ʈ�� ����� ��� �����Ϳ� ���� ��ġ�� ����մϴ�..\n");
    printf("=(��): ���� ��ġ�� ��带 �Է��� ������ ��ȯ�մϴ�.\n");
    printf("E: ���Ḯ��Ʈ�� ��� �ִ��� Ȯ���մϴ�.\n");
    printf("#: ���Ḯ��Ʈ�� ����� �������� ������ ����մϴ�.\n");
    printf("?(��): �Է��� ���� ���Ḯ��Ʈ�� ���°�� �����ϴ��� ����մϴ�.\n");
    printf("C: ���Ḯ��Ʈ �ʱ�ȭ �մϴ�.\n");
    printf("W(��): �Է��� ���� ���Ḯ��Ʈ�� ����� ��ġ�� ����մϴ�.\n");
    printf("U: ���Ḯ��Ʈ ���� �����͸� �빮�ڷ� ��ȯ�մϴ�.\n");
    printf("D: ���Ḯ��Ʈ ���� �����͸� �ҹ��ڷ� ��ȯ�մϴ�.\n");
    printf("T: ���Ḯ��Ʈ ���� �����͸� �빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� ��ȯ�մϴ�.\n");    
    printf("H(��): �Է��� ���� ����Ʈ�� � �����ϴ��� �˷��ݴϴ�..\n");
    printf("*: ���α׷��� �����մϴ�.\n"); //�� ��ɺ� ����
}
void initList(List *list) {
    list->head = NULL;    // ����Ʈ�� ���� ��带 NULL�� �ʱ�ȭ
    list->size = 0;       // ����Ʈ�� ũ�⸦ 0���� �ʱ�ȭ
}
void addTail(List *list, char data) {
    Node *newNode = (Node*)malloc(sizeof(Node));    // ���ο� ��� ���� �Ҵ�
    newNode->data = data;                           // ���ο� ��忡 ������ ����
    newNode->next = NULL;                           // ���ο� ����� ���� ��� �����͸� NULL�� �ʱ�ȭ
    
    if (list->head == NULL) {                       // ����Ʈ�� ������� ���
        list->head = newNode;                       // ���ο� ��带 ����Ʈ�� ���� ���� ����
    } else {
        Node *curr = list->head;
        while (curr->next != NULL) {                // ������ ������ �̵�
            curr = curr->next;
        }
        curr->next = newNode;                       // ������ ����� ���� ��带 ���ο� ���� ����
    }
    list->size++;                                   // ����Ʈ�� ũ�� ����
    cnt++;
    lct=cnt-1;
}
void add(List *list, int index, char data) {
    if (index < 0 || index > list->size) { // �߰��Ϸ��� �ε����� ��ȿ���� ���� ���
        printf("�߰��Ͻ÷��� ��ġ�� ����Ʈ�� ������ ����ϴ�!\n");
        return;
    }
    Node *newNode = (Node*) malloc(sizeof(Node)); // ���ο� ��� ����
    newNode->data = data;
    newNode->next = NULL;
    if(index!=0){ // �߰��Ϸ��� ��尡 head�� �ƴ� ���
        Node *current = list->head;
        Node *previous = NULL;
        for (int i = 0; i < index; i++) { // �߰��Ϸ��� ��ġ�� ���� ��带 ã�� ���� Ž��
            previous = current;
            current = current->next;
        }
        previous->next = newNode; // ���� ����� next �����͸� ���ο� ���� ����
        newNode->next = current; // ���ο� ����� next �����͸� ���� ���� ����
    } 

    else { // �߰��Ϸ��� ��尡 head�� ���
        newNode->next = list->head;
        list->head = newNode;
    } 
    list->size++; // ����Ʈ ũ�� ����
    cnt++;
    lct++;
}

void traverse_front() {
	lct = 0;//���� ��ġ�� ����Ʈ�� ���� ó������ �̵�
}
void traverse_rear() {
	lct = cnt-1;//���� ��ġ�� ����Ʈ�� ���� ���������� �̵�
};
void traverse_next() {
	lct++;//���� ��ġ�� ���� ���� �̵�
};
void traverse_prev() {
	lct--;//���� ��ġ�� ���� ���� �̵�
};
void delete(List *list, int index) {
    if (index < 0 || index >= list->size) { // �����Ϸ��� �ε����� ��ȿ���� ���� ���
        printf("����÷��� ��ġ�� ����Ʈ�� ������ ����ϴ�!\n");
        return;
    }
    Node *current = list->head;
    Node *previous = NULL;
    for (int i = 0; i < index; i++) { // �����Ϸ��� ����� ���� ��带 ã�� ���� Ž��
        previous = current;
        current = current->next;
    }
    if (previous == NULL) { // �����Ϸ��� ��尡 head�� ���
        list->head = current->next;
    } else { // �����Ϸ��� ��尡 head�� �ƴ� ���
        previous->next = current->next;
    }
    free(current); // ��� ����
    list->size--; // ����Ʈ ũ�� ����
    cnt--;
    if (lct==cnt) lct=0;
}
void print(List *list) {
    Node *curr = list->head;
    printf("����Ʈ�� ����� ����");
    while (curr != NULL) {                          // ������ ������ �̵�
        printf(" %c ", curr->data);                  // ���� ����� ������ ���
        curr = curr->next;
    }
    if (lct==-1) printf(" �����ϴ�.");
    else
        printf("�� ������, ���� ��ġ�� %d��° �Դϴ�.", lct+1);
        printf("\n");
}
Node *check_get_data(List *list, int index) {// �ε����� �ش��ϴ� ��� ��ȯ �Լ�
    if (index < 0 || index >= list->size) {   // �ε����� ����Ʈ ������ ��� ���
        return NULL;
    }
    Node *curr = list->head;
    int i = 0;
    while (curr != NULL && i < index) {       // ����Ʈ�� ��ȸ�ϸ鼭 �ε����� �ش��ϴ� ��� ã��
        curr = curr->next;
        i++;
    }
    return curr;
}
void get_data(List *list, int index) {// �ε����� �ش��ϴ� ��� ��� �Լ�
    Node *node = check_get_data(list, index);
    if (node == NULL) {                       // �ش� �ε����� ��尡 ���� ���
        printf("�ش� ��ġ�� ����Ʈ�� ������ ����ϴ�.\n");
    } else {                                  // �ش� �ε����� ��尡 �ִ� ���
        printf("%c\n", node->data);
    }
}
void is_Empty(List *list)
{
    if (list->head == NULL)
        printf("True\n"); // head�� NULL�̸� ����Ʈ�� ��������� ���
    else
        printf("Flase\n"); // head�� NULL�� �ƴϸ� ����Ʈ�� ���� ������ ���
}
void data_count(List *list)
{
    printf("%d\n", list->size); // ����Ʈ�� ũ�⸦ ���
}
int findtheindex(List *list, char value)
{
    int index = 0;              
    Node *current = list->head; // ���� ��带 head�� �ʱ�ȭ
    while (current != NULL){
        if (current->data == value) return index;
        
        current = current->next; 
        index++;                 
    }
    return -1; // �Է¹��� ���� ���� ����Ʈ�� ���� ��� -1 ��ȯ
}
void is_member(List* list, char value) {
    int nodeIndex = findtheindex(list, value);
    if (nodeIndex == -1) {
        printf("�Է¹��� ���� ���� ����Ʈ�� �����ϴ�.\n");
    } else {
        int index = nodeIndex + 1; 
        printf("%d: ", index);
        lct=index-1;
    }
}
void clear(List *list) {
    list->head = NULL;  // head�� NULL�� �ʱ�ȭ
    list->size = 0;     // size�� 0���� �ʱ�ȭ
    lct=-1;
}
void replace(List *list, int index, char data) {
    if (index < 0 || index >= list->size) { // ��ü�Ϸ��� �ε����� ��ȿ���� ���� ���
        printf("�ش� ��ġ�� ����Ʈ�� ������ ����ϴ�.\n");
        return;
    }
    Node *newNode = (Node*) malloc(sizeof(Node)); // ���ο� ��� ����
    newNode->data = data;
    newNode->next = NULL;
    if (index == 0) { // ��ü�Ϸ��� ��尡 head�� ���
        newNode->next = list->head->next;
        free(list->head); // ���� head ��� ����
        list->head = newNode;
    } else { // ��ü�Ϸ��� ��尡 head�� �ƴ� ���
        Node *current = list->head;
        Node *previous = NULL;
        for (int i = 0; i < index; i++) { // ��ü�Ϸ��� ��ġ�� ���� ��带 ã�� ���� Ž��
            previous = current;
            current = current->next;
        }
        previous->next = newNode; // ���� ����� next �����͸� ���ο� ���� ����
        newNode->next = current->next; // ���ο� ����� next �����͸� ���� ���� ����
        free(current); // ���� ��� ����
    }
}
void addFirst(List* list, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // �� ��� ����
    newNode->data = data;  // ��忡 ������ ����
    newNode->next = list->head;  // �� ����� ���� ��带 ���� head�� ����
    list->head = newNode;  // ����Ʈ�� head�� �� ���� ����
    list->size++;  // ����Ʈ�� ũ�� ����
}
void up(List *list){
    Node *curr = list->head; // ����Ʈ�� head�� curr�� ����
    while (curr != NULL){
        if (curr->data >= 97) curr->data = curr->data - 32;
        curr = curr->next;         // ���� ���� �̵�
    }
}
void down(List *list) {
    Node *curr = list->head; // ����Ʈ�� head�� curr�� ����
    while (curr != NULL){
        if (curr->data <= 90) curr->data = curr->data + 32;
        curr = curr->next;         // ���� ���� �̵�
    }

}
void tog(List *list){
    Node *curr = list->head; // ����Ʈ�� head�� curr�� ����
    while (curr != NULL){
        if (curr->data >= 97) curr->data = curr->data - 32;
        else if (curr->data <= 90) curr->data = curr->data + 32; 
        curr = curr->next;         // ���� ���� �̵�
    }
}
int count(List *list, char data){
    int count = 0;              
    Node *current = list->head; // ����Ʈ�� head�� ����Ű�� ������ ���� current �ʱ�ȭ
    while (current != NULL){
        if (current->data == data) count++;
        current = current->next; // current�� ���� ���� �̵�
    }
    return count; // ī��Ʈ ���� ��ȯ
}

void get_index(List *list, char data){
    int index = 0;              
    int numa = 0;               
    Node *current = list->head; // ����Ʈ�� head�� ����Ű�� ������ ���� current �ʱ�ȭ
    while (current != NULL){
        if (current->data == data){
            printf("%d��° ", index + 1);
            numa++;                      
        }
        current = current->next; // current�� ���� ���� �̵�
        index++;
    }
    if (numa!=0) printf("��ġ���� %c�� �����մϴ�.\n",data);
    else if (numa==0) printf("�ش� �����ʹ� ����Ʈ�� �������� �ʽ��ϴ�.\n");
}