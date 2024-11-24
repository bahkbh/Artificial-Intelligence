//자료구조 한옥영 교수님 8주차 LAB04 Queue ADT 구현
//최종 작성일: 2023.06.09(금)
//2019313550 박병현
#include <stdio.h>
#include <ctype.h>
#define MAX_SIZE 1000

typedef struct { // 큐 구조체 정의
    int head;
    int tail;
    int data[MAX_SIZE];
} Queue;

void initQueue(Queue* queue); // 큐 초기화 함수
int is_empty(Queue* queue); // 큐가 비어있는지 확인하는 함수
int is_full(Queue* queue); // 큐가 가득 차 있는지 확인하는 함수
void enqueue(Queue* queue, int data); // 큐에 데이터를 삽입하는 함수
int dequeue(Queue* queue); // 큐에서 데이터를 삭제하고 출력하는 함수
void print(Queue* queue); // 큐에 저장된 데이터를 출력하는 함수
void data_count(Queue* queue); //큐에 저장된 데이터의 갯수를 출력하는 함수
void head(Queue* queue); //큐의 제일 첫번째로 저장된 데이터의 배열 인덱스 번호를 알려주는 함수
void tail(Queue* queue); //큐의 마지막에 저장된 데이터의 배열 인덱스 번호를 알려주는 함수
void clear(Queue* queue); // 큐를 초기화하는 함수
void is_member(Queue* queue, char data); // 큐에 데이터가 있는지 확인하는 함수
void replace(Queue* queue, char data); //큐의 제일 마지막 데이터를 바꿔주는 함수
void show(); //명령어를 보여주는 함수
int peek(Queue* queue); //큐의 제일 첫 데이터를 보여주는 함수
////나만의 기능
int how_many(Queue* queue, char target); //큐에 해당 데이터가 몇개 존재하는지 알려주는 함수
void update(Queue *queue); //큐의 제일 처음 저장되어 있는 데이터를 제일 마지막으로 옮기는 함수.
void remove_duplicates(Queue* queue); // 중복 요소를 제거하는 함수


int main() {         
    show();  
    Queue queue;
    initQueue(&queue);        
    char enter[100];      //명령어를 저장받는 배열
    while(1){
        B:
        printf("명령어를 입력하세요: ");
        scanf("%s",enter);
        for (int i=0;enter[i]!='\0';i++){
            if (enter[i]=='+'){
                enqueue(&queue, enter[i+1]); //스택에 데이터 추가
                i++;
            }
            else if (isdigit(enter[i])){ //숫자가 입력될 경우 해당 숫자만큼 dequeue 실행
                int num=(int) enter[i]-'0';
                for (int i=1; i<num;i++){
                    printf("%c ",dequeue(&queue));
                }
            }
            else if (enter[i]=='P'){
                printf("\n");
                printf("%c \n",peek(&queue));//제일 마지막 데이터 출력
                printf("\n");
                goto B;
            }

            else if (enter[i] == '-') {
                int dequeued = dequeue(&queue); // 제일 처음에 추가한 데이터를 꺼내고
                if (dequeued != -1) { // 큐가 비어있지 않으면 출력
                    printf("%c ", dequeued);
                }
            }
                        
            else if (enter[i]=='F'){//큐가 가득 차 있는지 확인
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

            else if (enter[i]=='?'){//해당 데이터가 큐에에 존재하는지 확인
            is_member(&queue, enter[i+1]);
            goto B;
            }
            
            else if (enter[i]=='E'){//큐가 비어있는지 확인
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
                replace(&queue, enter[i + 1]); // 제일 마지막 데이터 교체
                i++;
            }
            else if (enter[i]=='C') {//큐 초기화
                clear(&queue);
                goto B;
            }
            else if (enter[i]=='#') {//큐에 저장된 데이터 갯수 출력
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
            else if (enter[i] == 'R') { // 중복 요소 제거
                remove_duplicates(&queue);
            }             
            else if (enter[i]=='*') goto A;//프로그램 종료
            else if (enter[i]=='L') continue;//큐 출력
        }
        
        printf("\n");
        print(&queue);//큐 출력
        printf("\n");

    }
    A:
    printf("프로그램을 종료합니다.\n");
    return 0;
}
void show(){  //명령어 안내
    printf("명령문을 안내해드리겠습니다.\n");
    printf("+(값): 큐에 값을 추가합니다.\n");
    printf("-: 제일 처음에 추가한 값 제거합니다.\n");
    printf("L: 큐에 저장된 값을 출력합니다.\n");
    printf("P: 제일 처음에 추가한 값을 보여줍니다.\n");
    printf("E: 큐가 비어있는지 확인합니다.\n");
    printf("F: 큐가 꽉 차 있는지 확인합니다.\n");
    printf("H: 큐의 제일 앞에 저장되어 있는 데이터의 위치를 확인합니다.\n");
    printf("T: 큐의 제일 앞에 마지막에 되어 있는 데이터의 위치를 확인합니다.\n");
    printf("R: 큐에 저장된 값들 중 중복된 값을 제거합니다..\n");
    printf("=(값): 제일 마지막 원소를 입력하신 값으로 교체합니다.\n");
    printf("#: 큐에 존재하는 값들의 개수를 출력합니다.\n");
    printf("C: 큐를 초기화합니다.\n");
    printf("U: 큐의 제일 앞에 저장되어 있는 데이터를 큐의 제일 마지막에 저장시킵니다.\n");
    printf("@(값): 큐에 해당 값이 몇개 존재하는지 알려줍니다.\n");
    printf("?(값): 큐에 해당 값을 가지는 원소가 존재하는지 확인합니다.\n"); 
    printf("*: 프로그램을 종료합니다.\n\n");
}

void initQueue(Queue* queue) {// 큐 초기화 함수
    queue->head = -1;
    queue->tail = -1;
}

int is_empty(Queue* queue) { // 큐가 비어있는지 확인하는 함수
    return queue->head == -1;
}

int is_full(Queue* queue) { // 큐가 가득 차 있는지 확인하는 함수
    return queue->tail == MAX_SIZE - 1;
}

void enqueue(Queue* queue, int data) { // 큐에 데이터를 삽입하는 함수
    if (is_full(queue)) {
        if (is_empty(queue)) {
            printf("큐가 가득 차 있습니다.\n");
            return;
        }
        else { // 앞쪽에 남는 자리가 있다면, 요소들을 앞으로 이동
            for (int i = queue->head; i <= queue->tail; i++) {
                queue->data[i-queue->head] = queue->data[i];
            }
            queue->tail -= queue->head;
            queue->head = 0;
        }
    }
    if (queue->tail == MAX_SIZE - 1) { // 큐의 뒤쪽이 꽉 찼다면
        printf("큐가 가득 차 있습니다.\n");
        return;
    }
    queue->tail++;
    queue->data[queue->tail] = data;
    if (is_empty(queue)) {
        queue->head = 0;
    }
}

int dequeue(Queue* queue) {// 큐에서 데이터를 삭제하고 출력하는 함수
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

void print(Queue* queue) { // 큐에 저장된 데이터를 출력하는 함수
    if (is_empty(queue)) {
        printf("큐가 비어있습니다.\n");
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

void data_count(Queue *queue){ //큐에 저장된 데이터의 갯수를 출력하는 함수
    printf("%d\n", queue->tail - queue->head +1 );
}

void head(Queue *queue){ //큐의 제일 첫번째로 저장된 데이터의 배열 인덱스 번호를 알려주는 함수
    if (queue->head==-1){
        return ;
    }
    else{
        printf("%d\n", queue->head+1);
    }
}

void tail(Queue *queue){ //큐의 마지막에 저장된 데이터의 배열 인덱스 번호를 알려주는 함수
    if (queue->tail==-1){
        return ;
    }
    else{
        printf("%d\n", queue->tail+1);
    }
}

void clear(Queue* queue) { // 큐를 초기화하는 함수
    while (!is_empty(queue)) {
        dequeue(queue); // 큐가 비어있을 때까지 dequeue()를 호출하여 모든 요소를 삭제
    }
}
void is_member(Queue* queue, char data) { // 큐에 데이터가 있는지 확인하는 함수
    Queue tempQueue; // 복사용 큐
    initQueue(&tempQueue);
    int count = 0; // 몇 번째 데이터인지 세는 변수
    int found = 0; // 일치하는 데이터를 찾았는지 여부를 저장하는 변수

    // 입력받은 데이터를 찾기 위해 큐에서 데이터를 하나씩 꺼내며 비교
    while (!is_empty(queue)) {
        char dequeued = dequeue(queue);
        enqueue(&tempQueue, dequeued); // 큐에서 꺼낸 데이터를 임시 큐에 삽입
        if (dequeued == data) { // 일치하는 데이터를 찾으면
            printf("%d\n", count + 1); // 몇 번째 데이터인지 출력하고
            found = 1; // 찾았음을 표시
        }
        count++; // 카운트 증가
    }

    // 원래 큐에 임시 큐의 내용을 다시 삽입
    while (!is_empty(&tempQueue)) {
        char dequeued = dequeue(&tempQueue);
        enqueue(queue, dequeued);
    }

    // 입력받은 데이터가 큐에 없을 경우 -1 출력 후 메시지 출력
    if (!found) {
        printf("-1\n찾으시는 데이터가 큐에 없습니다.\n");
    }
}
void replace(Queue* queue, char data) { //큐의 제일 마지막 데이터를 바꿔주는 함수
    if (is_empty(queue)) {
        printf("큐가 비어있습니다.\n");
        return;
    }
    
    Queue tempQueue;
    initQueue(&tempQueue);
    
    // 큐의 모든 요소를 임시 큐로 이동하면서 마지막 요소를 찾습니다.
    while (!is_empty(queue)) {
        char dequeued = dequeue(queue);
        if (queue->head == -1) { // 마지막 요소가 꺼내졌을 때
            dequeued = data; // 데이터를 교체합니다.
        }
        enqueue(&tempQueue, dequeued); // 임시 큐에 데이터를 넣습니다.
    }

    // 임시 큐의 내용을 원래 큐로 다시 옮김.
    while (!is_empty(&tempQueue)) {
        char dequeued = dequeue(&tempQueue);
        enqueue(queue, dequeued);
    }
}
int peek(Queue* queue) { //큐의 제일 첫 데이터를 보여주는 함수
    if (is_empty(queue)) {
        printf("큐가 비어있습니다.\n");
        return -1;
    }
    return queue->data[queue->head];
}
int how_many(Queue* queue, char target) { //큐에 해당 데이터가 몇개 존재하는지 알려주는 함수
    int count = 0;
    for (int i = queue->head; i <= queue->tail; i++) {
        if (queue->data[i] == target) {
            count++;
        }
    }
    return count;
}
void update(Queue* queue) {  //큐의 제일 처음 저장되어 있는 데이터를 제일 마지막으로 옮기는 함수.
    if (is_empty(queue)) {
        printf("큐가 비어있습니다.\n");
        return;
    }

    int first_data = dequeue(queue);
    enqueue(queue, first_data);
}
void remove_duplicates(Queue* queue) { // 중복 요소를 제거하는 함수
    Queue tempQueue; //임시 큐 선언
    initQueue(&tempQueue);

    while (!is_empty(queue)) {//큐의 요소를 하나씩 꺼내어 중복되었는지 검사
        char dequeued = dequeue(queue);
        int is_duplicate = 0;
        
        Queue checkQueue; //중복 검사를 위한 큐 선언
        initQueue(&checkQueue);
        
        while (!is_empty(&tempQueue)) { // checkQueue에 있는 요소들을 다시 tempQueue에 옮김
            char temp_dequeued = dequeue(&tempQueue);
            if (dequeued == temp_dequeued) {
                is_duplicate = 1;
            }
            enqueue(&checkQueue, temp_dequeued);
        }
        
        while (!is_empty(&checkQueue)) { // 중복되지 않는다면(tempQueue에도 없는 값이라면) tempQueue에 해당 요소를 삽입
            enqueue(&tempQueue, dequeue(&checkQueue));
        }
        
        if (!is_duplicate) {
            enqueue(&tempQueue, dequeued);
        }
    }

    while (!is_empty(&tempQueue)) {  // tempQueue에 있는 요소들을 큐(queue)에 다시 삽입하여, 중복된 요소가 제거된 큐를 반환
        enqueue(queue, dequeue(&tempQueue));
    }
}