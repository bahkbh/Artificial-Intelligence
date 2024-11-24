//자료구조 한옥영 교수님 8주차 LAB04 Deueue ADT 구현
//최종 작성일: 2023.04.23(일)
//2019313550 박병현
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {// 덱에서 사용되는 노드 정보를 담은 구조체
    char data;
    struct Node* prev;
    struct Node* next;
} Node;


Node* create_node(char data) {// 새로운 노드를 생성하여 초기화하는 함수
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

typedef struct Deque {// 덱 구조체
    Node* head;
    Node* tail;
    int count;
    int max_size;
} Deque;

void add_front(Deque* deque, char data);//덱의 front에 데이터를 삽입하는 함수
void add_rear(Deque* deque, char data);//덱의 rear에 데이터를 삽입하는 함수
char delete_front(Deque* deque);//덱의 front에 저장된 데이터를 반환하고 삭제하는 함수
char delete_rear(Deque* deque);//덱의 rear에 저장된 데이터를 반환하고 삭제하는 함수
void init(Deque* deque);//덱을 초기화 하는 함수

int is_empty(Deque* deque);//덱이 비어있는지 확인하는 함수
int is_full(Deque* deque);//덱이 가득 차 있는지 확인하는 함수
void print(Deque* deque);//덱을 출력하는 함수
char get_front(Deque* deque);//덱의 front에 저장된 데이터를 보여주는 함수
char get_rear(Deque* deque);//덱의 rear에 저장된 데이터를 보여주는 함수
int data_count(Deque* deque);//덱에 저장된 데이터의 갯수를 보여주는 함수
void is_member(Deque* deque, char data);//덱에 입력한 데이터가 몇번째에 존재하는지 알려주는 함수
void replace_front(Deque* deque, char data);//덱의 front의 값을 입력받은 값으로 교체하는 함수
void replace_rear(Deque* deque, char data);//덱의 rear의 값을 입력받은 값으로 교체하는 함수
void clear(Deque* deque);//덱을 초기화 하는 함수
int how_many(Deque* deque, char data);//입력 받은 값이 덱에 몇개 존재하는 지 알려주는 함수
void remove_duplicate(Deque* deque);//덱에 존재하는 중복되는 값을 지워주는 함수
void update(Deque* deque, char direction);//방향을 입력받고 rear의 값을 front로 옮겨주거나, front의 값을 rear로 옮겨주는 함수
void show();//명령어를 출력하는 함수

int main() {
    Deque deque;
    init(&deque);
    char enter[100];      //명령어를 저장받는 배열
    show();
    while(1){
        B:
        printf("명령어를 입력하세요: ");
        scanf("%s",enter);
        for (int i=0;enter[i]!='\0';i++){
            if (enter[i]=='>'){
                i++;
                for (int i=1;enter[i]!='\0';i++){
                if (enter[i]=='+'){
                    add_rear(&deque, enter[i+1]); //덱에 데이터 추가
                    i++;
                }
            
                else if (isdigit(enter[i])){ //숫자가 입력될 경우 해당 숫자만큼 delete_rear 실행
                    int num=(int) enter[i]-'0';
                    for (int i=1; i<num;i++){
                        printf("%c ",delete_rear(&deque));
                    }
                }
                else if (enter[i] == '-') {
                    int dequeued = delete_rear(&deque); // 제일 처음에 추가한 데이터를 꺼내고
                    if (dequeued != -1) { // 덱이 비어있지 않으면 출력
                        printf("%c ", dequeued);
                    }
                }
                else if (enter[i]=='U'){
                    update(&deque,'>');
                }
                else if (enter[i]=='P'){
                    printf("%c \n",get_rear(&deque));//제일 마지막 데이터 출력
                    goto B;
                }
                else if (enter[i] == '=') {
                    replace_rear(&deque, enter[i + 1]); // 제일 마지막 데이터 교체
                    i++;
                }  
                }  }
            else if (enter[i]=='<'){
                i++;
                for (int i=1;enter[i]!='\0';i++){
                if (enter[i]=='+'){
                    add_front(&deque, enter[i+1]); //덱에 데이터 추가
                    i++;
                }
            
                else if (isdigit(enter[i])){ //숫자가 입력될 경우 해당 숫자만큼 delete_front 실행
                    int num=(int) enter[i]-'0';
                    for (int i=1; i<num;i++){
                        printf("%c ",delete_front(&deque));
                    }
                }
                else if (enter[i] == '-') {
                    int dequeued = delete_front(&deque); // 제일 처음에 추가한 데이터를 꺼내고
                    if (dequeued != -1) { // 덱이 비어있지 않으면 출력
                        printf("%c ", dequeued);
                    }
                }
                else if (enter[i]=='U'){
                    update(&deque,'<');
                }
                else if (enter[i]=='P'){
                    printf("%c \n",get_front(&deque));//제일 마지막 데이터 출력
                    goto B;
                }
                else if (enter[i] == '=') {
                    replace_front(&deque, enter[i + 1]); // 제일 마지막 데이터 교체
                }
            }
            }
            else if (enter[i]=='F'){//덱이 가득 차 있는지 확인
                if(is_full(&deque)){
                    printf("True\n");
                }
                else
                    printf("False\n");
                goto B;
            }
 

            else if (enter[i]=='?'){//해당 데이터가 덱에 존재하는지 확인
            is_member(&deque, enter[i+1]);
            goto B;
            }
                
            else if (enter[i]=='E'){//덱이 비어있는지 확인
                if (is_empty(&deque)) {
                    printf("True\n");
                    }
                else {
                    printf("False\n");
                }
                goto B;
            }

            else if (enter[i]=='C') {//덱 초기화
                clear(&deque);
                goto B;
            }
            else if (enter[i]=='#') {//덱에 저장된 데이터 갯수 출력
                printf("%d\n",data_count(&deque));
                goto B;
                }

            else if (enter[i]=='@'){
                printf("%d\n",how_many(&deque, enter[i+1]));
                goto B;
            }

            else if (enter[i] == 'R') { // 중복 요소 제거
                remove_duplicate(&deque);
            }             
            else if (enter[i]=='*') goto A;//프로그램 종료
            else if (enter[i]=='L') continue;//덱 출력
        }
            
            printf("\n");
            print(&deque);//덱 출력
            printf("\n");

    }
    A:
    printf("프로그램을 종료합니다.\n");
    return 0;
}

void show(){//명령어 출력
    printf("명령문을 안내해드리겠습니다.\n");
    printf("<+(값): front에 값을 추가합니다.\n");
    printf(">+(값): rear에 값을 추가합니다.\n");
    printf("<-: front의 값을 제거합니다.\n");
    printf(">-: rear의 값을 제거합니다.\n");
    printf("<P: front의 값을 보여줍니다.\n");
    printf(">P: rear의 값을 보여줍니다.\n");
    printf("L: 덱에 저장된 값을 출력합니다.\n");
    printf("E: 덱이 비어있는지 확인합니다.\n");
    printf("F: 덱이 꽉 차 있는지 확인합니다.\n");
    printf("?(값): 덱에 해당 값을 가지는 원소가 존재하는지 확인합니다.\n");
    printf("#: 덱에 존재하는 값들의 개수를 출력합니다.\n");
    printf("C: 덱을 초기화합니다.\n");
    printf(">U: front에 있는 데이터를 rear로 옮깁니다.\n");
    printf("<U: rear에 있는 데이터를 front로 옮깁니다.\n");
    printf("@(값): 덱에 해당 값이 몇개 존재하는지 알려줍니다.\n");
    printf("R: 덱에 저장된 값들 중 중복된 값을 제거합니다..\n");
    printf("*: 프로그램을 종료합니다.\n\n");

}
void init(Deque* deque) {//덱을 초기화 하는 함수
    deque->head = NULL;
    deque->tail = NULL;
    deque->count = 0;
    deque->max_size = 100;
}
void add_front(Deque* deque, char data) {//덱의 front에 데이터를 삽입하는 함수
    if (deque->count == deque->max_size) {
        printf("덱이 가득 차 있습니다.\n");
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

void add_rear(Deque* deque, char data) {//덱의 rear에 데이터를 삽입하는 함수
    if (deque->count == deque->max_size) {
        printf("덱이 가득 차 있습니다.\n");
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
char delete_front(Deque* deque) {//덱의 front에 저장된 데이터를 반환하고 삭제하는 함수
    if (deque->head == NULL) {
        printf("덱이 비어있습니다.\n");
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
char delete_rear(Deque* deque) {//덱의 rear에 저장된 데이터를 반환하고 삭제하는 함수
    if (deque->tail == NULL) {
        printf("덱이 비어있습니다.\n");
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
int is_empty(Deque* deque) {//덱이 비어있는지 확인하는 함수
    return deque->count == 0;
}
int is_full(Deque* deque) {//덱이 가득 차 있는지 확인하는 함수
    return deque->count == deque->max_size;
}
void print(Deque* deque) {//덱을 출력하는 함수
    if (deque->count == 0) {
        printf("덱이 비어있습니다.\n");
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
char get_front(Deque* deque) {//덱의 front에 저장된 데이터를 보여주는 함수
    if (deque->head == NULL) {
        printf("덱이 비어있습니다.\n");
        return '\0';
    }
    return deque->head->data;
}
char get_rear(Deque* deque) {//덱의 rear에 저장된 데이터를 보여주는 함수
    if (deque->tail == NULL) {
        printf("덱이 비어있습니다.\n");
        return '\0';
    }
    return deque->tail->data;
}
int data_count(Deque* deque) {//덱에 저장된 데이터의 갯수를 보여주는 함수
    return deque->count;
}
void is_member(Deque* deque, char data) {//덱에 입력한 데이터가 몇번째에 존재하는지 알려주는 함수
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
    printf("-1\n찾으시는 값이 덱에 존재하지 않습니다.\n");
}
void replace_front(Deque* deque, char data) {//덱의 front의 값을 입력받은 값으로 교체하는 함수
    if (deque->head == NULL) {
        printf("덱이 비어있습니다.\n");
    return;
}
deque->head->data = data;
}
void replace_rear(Deque* deque, char data) {//덱의 rear의 값을 입력받은 값으로 교체하는 함수
    if (deque->tail == NULL) {
        printf("덱이 비어있습니다.\n");    
    return;
}
    deque->tail->data = data;
}
void clear(Deque* deque) {//덱을 초기화 하는 함수
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
int how_many(Deque* deque, char data) {//입력 받은 값이 덱에 몇개 존재하는 지 알려주는 함수
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
void remove_duplicate(Deque* deque) {//덱에 존재하는 중복되는 값을 지워주는 함수
    Node* current = deque->head;
    while (current != NULL) {// 현재 노드를 기준으로 다음 노드부터 중복값 탐색
        Node* runner = current->next;
        while (runner != NULL) {
            if (current->data == runner->data) { // 중복된 값이 있을 경우
                Node* temp_node = runner;
                runner = runner->next;
                if (temp_node == deque->tail) {// 중복된 노드를 제거
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

void update(Deque* deque, char direction) {//방향을 입력받고 rear의 값을 front로 옮겨주거나, front의 값을 rear로 옮겨주는 함수
    if (deque->count < 2) { // 노드가 1개 이하일 때는 동작하지 않음
        return;
    }
    if (direction == '<') { // rear의 값을 front로 이동시키는 경우
        Node* temp_node = deque->tail;
        deque->tail = deque->tail->prev;
        deque->tail->next = NULL;
        temp_node->prev = NULL;
        temp_node->next = deque->head;
        deque->head->prev = temp_node;
        deque->head = temp_node;
    } else if (direction == '>') {{ // front의 값을 rear로 이동시키는 경우
        Node* temp_node = deque->head;
        deque->head = deque->head->next;
        deque->head->prev = NULL;
        temp_node->next = NULL;
        temp_node->prev = deque->tail;
        deque->tail->next = temp_node;
        deque->tail = temp_node;
    } 
    }
    else {// 유효하지 않은 방향이 입력된 경우
        printf("유효한 방향이 아닙니다.\n");
    }
    }
