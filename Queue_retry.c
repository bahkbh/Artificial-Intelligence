//�ڷᱸ�� �ѿ��� ������ 8���� LAB04 Queue ADT ����
//���� �ۼ���: 2023.06.09(��)
//2019313550 �ں���
#include <stdio.h>
#include <ctype.h>
#define MAX_SIZE 1000

typedef struct { // ť ����ü ����
    int head;
    int tail;
    int data[MAX_SIZE];
} Queue;

void initQueue(Queue* queue); // ť �ʱ�ȭ �Լ�
int is_empty(Queue* queue); // ť�� ����ִ��� Ȯ���ϴ� �Լ�
int is_full(Queue* queue); // ť�� ���� �� �ִ��� Ȯ���ϴ� �Լ�
void enqueue(Queue* queue, int data); // ť�� �����͸� �����ϴ� �Լ�
int dequeue(Queue* queue); // ť���� �����͸� �����ϰ� ����ϴ� �Լ�
void print(Queue* queue); // ť�� ����� �����͸� ����ϴ� �Լ�
void data_count(Queue* queue); //ť�� ����� �������� ������ ����ϴ� �Լ�
void head(Queue* queue); //ť�� ���� ù��°�� ����� �������� �迭 �ε��� ��ȣ�� �˷��ִ� �Լ�
void tail(Queue* queue); //ť�� �������� ����� �������� �迭 �ε��� ��ȣ�� �˷��ִ� �Լ�
void clear(Queue* queue); // ť�� �ʱ�ȭ�ϴ� �Լ�
void is_member(Queue* queue, char data); // ť�� �����Ͱ� �ִ��� Ȯ���ϴ� �Լ�
void replace(Queue* queue, char data); //ť�� ���� ������ �����͸� �ٲ��ִ� �Լ�
void show(); //��ɾ �����ִ� �Լ�
int peek(Queue* queue); //ť�� ���� ù �����͸� �����ִ� �Լ�
////������ ���
int how_many(Queue* queue, char target); //ť�� �ش� �����Ͱ� � �����ϴ��� �˷��ִ� �Լ�
void update(Queue *queue); //ť�� ���� ó�� ����Ǿ� �ִ� �����͸� ���� ���������� �ű�� �Լ�.
void remove_duplicates(Queue* queue); // �ߺ� ��Ҹ� �����ϴ� �Լ�


int main() {         
    show();  
    Queue queue;
    initQueue(&queue);        
    char enter[100];      //��ɾ ����޴� �迭
    while(1){
        B:
        printf("��ɾ �Է��ϼ���: ");
        scanf("%s",enter);
        for (int i=0;enter[i]!='\0';i++){
            if (enter[i]=='+'){
                enqueue(&queue, enter[i+1]); //���ÿ� ������ �߰�
                i++;
            }
            else if (isdigit(enter[i])){ //���ڰ� �Էµ� ��� �ش� ���ڸ�ŭ dequeue ����
                int num=(int) enter[i]-'0';
                for (int i=1; i<num;i++){
                    printf("%c ",dequeue(&queue));
                }
            }
            else if (enter[i]=='P'){
                printf("\n");
                printf("%c \n",peek(&queue));//���� ������ ������ ���
                printf("\n");
                goto B;
            }

            else if (enter[i] == '-') {
                int dequeued = dequeue(&queue); // ���� ó���� �߰��� �����͸� ������
                if (dequeued != -1) { // ť�� ������� ������ ���
                    printf("%c ", dequeued);
                }
            }
                        
            else if (enter[i]=='F'){//ť�� ���� �� �ִ��� Ȯ��
                if(is_full(&queue)){
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

            else if (enter[i]=='?'){//�ش� �����Ͱ� ť���� �����ϴ��� Ȯ��
            is_member(&queue, enter[i+1]);
            goto B;
            }
            
            else if (enter[i]=='E'){//ť�� ����ִ��� Ȯ��
                if (is_empty(&queue)) {
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
            else if (enter[i] == '=') {
                replace(&queue, enter[i + 1]); // ���� ������ ������ ��ü
                i++;
            }
            else if (enter[i]=='C') {//ť �ʱ�ȭ
                clear(&queue);
                goto B;
            }
            else if (enter[i]=='#') {//ť�� ����� ������ ���� ���
                printf("\n");
                data_count(&queue);
                printf("\n");
                goto B;
                }
            else if (enter[i]=='H'){
                head(&queue);
                goto B;
            }
            else if (enter[i]=='T'){
                tail(&queue);
                goto B;
            }

            else if (enter[i]=='@'){
                printf("%d\n",how_many(&queue, enter[i+1]));
                goto B;
            }
            else if (enter[i]=='U'){
                update(&queue);
            }
            else if (enter[i] == 'R') { // �ߺ� ��� ����
                remove_duplicates(&queue);
            }             
            else if (enter[i]=='*') goto A;//���α׷� ����
            else if (enter[i]=='L') continue;//ť ���
        }
        
        printf("\n");
        print(&queue);//ť ���
        printf("\n");

    }
    A:
    printf("���α׷��� �����մϴ�.\n");
    return 0;
}
void show(){  //��ɾ� �ȳ�
    printf("��ɹ��� �ȳ��ص帮�ڽ��ϴ�.\n");
    printf("+(��): ť�� ���� �߰��մϴ�.\n");
    printf("-: ���� ó���� �߰��� �� �����մϴ�.\n");
    printf("L: ť�� ����� ���� ����մϴ�.\n");
    printf("P: ���� ó���� �߰��� ���� �����ݴϴ�.\n");
    printf("E: ť�� ����ִ��� Ȯ���մϴ�.\n");
    printf("F: ť�� �� �� �ִ��� Ȯ���մϴ�.\n");
    printf("H: ť�� ���� �տ� ����Ǿ� �ִ� �������� ��ġ�� Ȯ���մϴ�.\n");
    printf("T: ť�� ���� �տ� �������� �Ǿ� �ִ� �������� ��ġ�� Ȯ���մϴ�.\n");
    printf("R: ť�� ����� ���� �� �ߺ��� ���� �����մϴ�..\n");
    printf("=(��): ���� ������ ���Ҹ� �Է��Ͻ� ������ ��ü�մϴ�.\n");
    printf("#: ť�� �����ϴ� ������ ������ ����մϴ�.\n");
    printf("C: ť�� �ʱ�ȭ�մϴ�.\n");
    printf("U: ť�� ���� �տ� ����Ǿ� �ִ� �����͸� ť�� ���� �������� �����ŵ�ϴ�.\n");
    printf("@(��): ť�� �ش� ���� � �����ϴ��� �˷��ݴϴ�.\n");
    printf("?(��): ť�� �ش� ���� ������ ���Ұ� �����ϴ��� Ȯ���մϴ�.\n"); 
    printf("*: ���α׷��� �����մϴ�.\n\n");
}

void initQueue(Queue* queue) {// ť �ʱ�ȭ �Լ�
    queue->head = -1;
    queue->tail = -1;
}

int is_empty(Queue* queue) { // ť�� ����ִ��� Ȯ���ϴ� �Լ�
    return queue->head == -1;
}

int is_full(Queue* queue) { // ť�� ���� �� �ִ��� Ȯ���ϴ� �Լ�
    return queue->tail == MAX_SIZE - 1;
}

void enqueue(Queue* queue, int data) { // ť�� �����͸� �����ϴ� �Լ�
    if (is_full(queue)) {
        if (is_empty(queue)) {
            printf("ť�� ���� �� �ֽ��ϴ�.\n");
            return;
        }
        else { // ���ʿ� ���� �ڸ��� �ִٸ�, ��ҵ��� ������ �̵�
            for (int i = queue->head; i <= queue->tail; i++) {
                queue->data[i-queue->head] = queue->data[i];
            }
            queue->tail -= queue->head;
            queue->head = 0;
        }
    }
    if (queue->tail == MAX_SIZE - 1) { // ť�� ������ �� á�ٸ�
        printf("ť�� ���� �� �ֽ��ϴ�.\n");
        return;
    }
    queue->tail++;
    queue->data[queue->tail] = data;
    if (is_empty(queue)) {
        queue->head = 0;
    }
}

int dequeue(Queue* queue) {// ť���� �����͸� �����ϰ� ����ϴ� �Լ�
    if (is_empty(queue)) {
        printf("Error (nothing to dequeue).\n");
        return -1;
    }
    int data = queue->data[queue->head];
    if (queue->head == queue->tail) {
        queue->head = queue->tail = -1;
    }
    else {
        queue->head++;
    }
    return data;
}

void print(Queue* queue) { // ť�� ����� �����͸� ����ϴ� �Լ�
    if (is_empty(queue)) {
        printf("ť�� ����ֽ��ϴ�.\n");
        return;
    }
    Queue temp;
    initQueue(&temp);
    printf("Queue: ");
    while (!is_empty(queue)){
        printf("%c ", peek(queue));
        enqueue(&temp, dequeue(queue));
    }
    printf("\n");
    while (!is_empty(&temp))
        enqueue(queue, dequeue(&temp));
}

void data_count(Queue *queue){ //ť�� ����� �������� ������ ����ϴ� �Լ�
    printf("%d\n", queue->tail - queue->head +1 );
}

void head(Queue *queue){ //ť�� ���� ù��°�� ����� �������� �迭 �ε��� ��ȣ�� �˷��ִ� �Լ�
    if (queue->head==-1){
        return ;
    }
    else{
        printf("%d\n", queue->head+1);
    }
}

void tail(Queue *queue){ //ť�� �������� ����� �������� �迭 �ε��� ��ȣ�� �˷��ִ� �Լ�
    if (queue->tail==-1){
        return ;
    }
    else{
        printf("%d\n", queue->tail+1);
    }
}

void clear(Queue* queue) { // ť�� �ʱ�ȭ�ϴ� �Լ�
    while (!is_empty(queue)) {
        dequeue(queue); // ť�� ������� ������ dequeue()�� ȣ���Ͽ� ��� ��Ҹ� ����
    }
}
void is_member(Queue* queue, char data) { // ť�� �����Ͱ� �ִ��� Ȯ���ϴ� �Լ�
    Queue tempQueue; // ����� ť
    initQueue(&tempQueue);
    int count = 0; // �� ��° ���������� ���� ����
    int found = 0; // ��ġ�ϴ� �����͸� ã�Ҵ��� ���θ� �����ϴ� ����

    // �Է¹��� �����͸� ã�� ���� ť���� �����͸� �ϳ��� ������ ��
    while (!is_empty(queue)) {
        char dequeued = dequeue(queue);
        enqueue(&tempQueue, dequeued); // ť���� ���� �����͸� �ӽ� ť�� ����
        if (dequeued == data) { // ��ġ�ϴ� �����͸� ã����
            printf("%d\n", count + 1); // �� ��° ���������� ����ϰ�
            found = 1; // ã������ ǥ��
        }
        count++; // ī��Ʈ ����
    }

    // ���� ť�� �ӽ� ť�� ������ �ٽ� ����
    while (!is_empty(&tempQueue)) {
        char dequeued = dequeue(&tempQueue);
        enqueue(queue, dequeued);
    }

    // �Է¹��� �����Ͱ� ť�� ���� ��� -1 ��� �� �޽��� ���
    if (!found) {
        printf("-1\nã���ô� �����Ͱ� ť�� �����ϴ�.\n");
    }
}
void replace(Queue* queue, char data) { //ť�� ���� ������ �����͸� �ٲ��ִ� �Լ�
    if (is_empty(queue)) {
        printf("ť�� ����ֽ��ϴ�.\n");
        return;
    }
    
    Queue tempQueue;
    initQueue(&tempQueue);
    
    // ť�� ��� ��Ҹ� �ӽ� ť�� �̵��ϸ鼭 ������ ��Ҹ� ã���ϴ�.
    while (!is_empty(queue)) {
        char dequeued = dequeue(queue);
        if (queue->head == -1) { // ������ ��Ұ� �������� ��
            dequeued = data; // �����͸� ��ü�մϴ�.
        }
        enqueue(&tempQueue, dequeued); // �ӽ� ť�� �����͸� �ֽ��ϴ�.
    }

    // �ӽ� ť�� ������ ���� ť�� �ٽ� �ű�.
    while (!is_empty(&tempQueue)) {
        char dequeued = dequeue(&tempQueue);
        enqueue(queue, dequeued);
    }
}
int peek(Queue* queue) { //ť�� ���� ù �����͸� �����ִ� �Լ�
    if (is_empty(queue)) {
        printf("ť�� ����ֽ��ϴ�.\n");
        return -1;
    }
    return queue->data[queue->head];
}
int how_many(Queue* queue, char target) { //ť�� �ش� �����Ͱ� � �����ϴ��� �˷��ִ� �Լ�
    int count = 0;
    for (int i = queue->head; i <= queue->tail; i++) {
        if (queue->data[i] == target) {
            count++;
        }
    }
    return count;
}
void update(Queue* queue) {  //ť�� ���� ó�� ����Ǿ� �ִ� �����͸� ���� ���������� �ű�� �Լ�.
    if (is_empty(queue)) {
        printf("ť�� ����ֽ��ϴ�.\n");
        return;
    }

    int first_data = dequeue(queue);
    enqueue(queue, first_data);
}
void remove_duplicates(Queue* queue) { // �ߺ� ��Ҹ� �����ϴ� �Լ�
    Queue tempQueue; //�ӽ� ť ����
    initQueue(&tempQueue);

    while (!is_empty(queue)) {//ť�� ��Ҹ� �ϳ��� ������ �ߺ��Ǿ����� �˻�
        char dequeued = dequeue(queue);
        int is_duplicate = 0;
        
        Queue checkQueue; //�ߺ� �˻縦 ���� ť ����
        initQueue(&checkQueue);
        
        while (!is_empty(&tempQueue)) { // checkQueue�� �ִ� ��ҵ��� �ٽ� tempQueue�� �ű�
            char temp_dequeued = dequeue(&tempQueue);
            if (dequeued == temp_dequeued) {
                is_duplicate = 1;
            }
            enqueue(&checkQueue, temp_dequeued);
        }
        
        while (!is_empty(&checkQueue)) { // �ߺ����� �ʴ´ٸ�(tempQueue���� ���� ���̶��) tempQueue�� �ش� ��Ҹ� ����
            enqueue(&tempQueue, dequeue(&checkQueue));
        }
        
        if (!is_duplicate) {
            enqueue(&tempQueue, dequeued);
        }
    }

    while (!is_empty(&tempQueue)) {  // tempQueue�� �ִ� ��ҵ��� ť(queue)�� �ٽ� �����Ͽ�, �ߺ��� ��Ұ� ���ŵ� ť�� ��ȯ
        enqueue(queue, dequeue(&tempQueue));
    }
}