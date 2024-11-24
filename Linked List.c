//자료구조 한옥영 교수님 6주차 LAB02 Linked List ADT 구현
//최종 작성일: 2023.04.04(화)
//2019313550 박병현
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>            
 
typedef struct Node {// 연결리스트 노드 구조체
    char data;            // 문자 데이터
    struct Node *next;    // 다음 노드를 가리키는 포인터
} Node;
typedef struct List {// 연결리스트 구조체
    Node *head;    // 리스트의 시작 노드를 가리키는 포인터
    int size;      // 리스트의 크기
} List;
void show(); //명령어를 출력하는 함수
void initList(List *list);// 리스트 초기화 함수
void addTail(List *list, char data);// 리스트 마지막에 노드 추가 함수
void add(List *list, int index, char data);//리스트의 원하는 위치에 노드 추가 함수
void addFirst(List* list, char data);//리스트의 제일 처음에 노드 추가 함수
void traverse_front();//현재 위치를 리스트의 제일 처음으로 이동시키는 함수
void traverse_rear();//현재 위치를 리스트의 제일 마지막으로 이동시키는 함수
void traverse_next();//현재 위치의 다음으로 이동시키는 함수
void traverse_prev();//현재 위치의 이전으로 이동시키는 함수
void delete(List *list, int index);//특정 위치의 노드를 삭제시키는 함수
void print(List *list);//리스트 전체와 현재 위치를 출력시키는 함수
Node *check_get_data(List *list, int index);// 인덱스에 해당하는 노드 반환 함수
void get_data(List *list, int index);// 인덱스에 해당하는 노드 출력 함수
void is_Empty(List *list);//리스트가 비어있는지 확인해주는 함수
void data_count(List *list);//리스트의 노드의 수를 확인해주는 함수
int findtheindex(List *list, char value);//특정 노드의 위치를 확인해주는 함수
void is_member(List *list, char value);//특정 노드의 값이 리스트에 존재하는지 확인해주는 함수
void clear(List *list); // 리스트를 초기화하는 함수
void replace(List *list, int index, char data);//특정 인덱스의 값을 변환해주는 함수
void up(List *list);//자신만의 기능, 리스트의 입력된 노드의 값을 대문자로 변환해주는 함수
void down(List *list);//자신만의 기능, 리스트의 입력된 노드의 값을 소문자로 변환해주는 함수
void tog(List *list);//자신만의 기능, 리스트의 입력된 노드의 값을 대문자는 소문자로, 소문자는 대문자로 변환해주는 함수
int count(List* list, char data);//자신만의 기능, 입력한 데이터가 리스트에 몇개가 존재하는지 알려주는 함수
void get_index(List* list, char data);//자신만의 기능, 입력한 데이터가 리스트의 몇번째에 존재하는지 알려주는 함수
int lct=-1;//현재 위치를 확인하기 위한 전역변수
int cnt=0;//리스트의 크기를 확인하기 위한 전역변수



int main() {
    List list;//리스트 생성
    initList(&list); //리스트 초기화
    show();
    C:
    while(1){
        char enter[30]={0};//명령어를 입력받는 배열
        printf("명령어를 입력하세요:  ");
        scanf("%s",&enter);
        int i=0;
        while (enter[i] != '\0'){// 입력받은 배열의 끝이 나올 때까지 반복
            if (enter[i] == '+'){
                if (lct + 1 == cnt){              
                    addTail(&list, enter[i + 1]); // 리스트의 끝에 노드 추가
                    i++;                          
                }
                else{                                  
                    add(&list, lct + 1, enter[i + 1]); // lct+1 위치에 노드 추가
                    i++;                               
                }
            }
            else if (enter[i] == '<'){
                traverse_front(); // 리스트의 첫번째 노드부터 출력
                if (enter[i + 1] == '+'){     
                    addFirst(&list, enter[i + 2]); // 리스트의 첫번째 위치에 노드 추가
                    traverse_front();              
                    i = i + 2;                     
                }
            }
            else if (enter[i] == '>') traverse_rear(); 
            else if (enter[i] == 'N') traverse_next(); 
            else if (enter[i] == 'P') traverse_prev(); 
            else if (isdigit(enter[i]) & enter[i + 1] == '='){
                lct = (int)enter[i] - 49;          // lct에 입력된 숫자를 저장
                replace(&list, lct, enter[i + 2]); // lct 위치의 노드를 입력된 값으로 교체
                i++;                              
                goto A;                            
            }
            else if (isdigit(enter[i])){
                lct = (int)enter[i] - 49; // lct에 해당 숫자를 저장
                get_data(&list, lct);     // 해당 숫자에 해당하는 데이터 출력
                i++;                    
                goto C;                  
            }
            else if (enter[i] == '-')delete (&list, lct); 
            if (enter[i] == '='){                  
                replace(&list, lct, enter[i + 1]); // 해당 숫자에 해당하는 데이터를 입력된 문자열 다음 문자열로 대체
                i++;                              
            }
            else if (enter[i] == 'E'){
                is_Empty(&list); // 리스트가 비어있는지 확인
                goto C;          
            }
            else if (enter[i] == '#'){
                data_count(&list); // 리스트에 저장된 데이터의 개수 출력
                goto C;            
            }
            else if (enter[i] == '?') is_member(&list, enter[i + 1]); 
            else if (enter[i] == 'C'){
                clear(&list); // 리스트 초기화
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
    printf("프로그램을 종료합니다.\n");
    return 0;
}

void show(){
    printf("명령문을 안내해드리겠습니다.\n");
    printf("+(값): 리스트에 값 추가합니다.\n");
    printf("<: 현재 위치를 연결 리스트의 제일 처음으로 이동합니다.\n");
    printf(">: 현재 위치를 연결 리스트의 제일 마지막으로 이동합니다.\n");
    printf("(숫자): 현재 위치를 입력하신 위치로 이동합니다.\n");
    printf("-: 현재 위치의 노드를 제거합니다.\n");
    printf("G: 현재 위치의 데이터를 보여줍니다.\n");
    printf("L: 연결리스트에 저장된 모든 데이터와 현재 위치를 출력합니다..\n");
    printf("=(값): 현재 위치의 노드를 입력한 값으로 변환합니다.\n");
    printf("E: 연결리스트가 비어 있는지 확인합니다.\n");
    printf("#: 연결리스트에 저장된 데이터의 개수를 출력합니다.\n");
    printf("?(값): 입력한 값이 연결리스트의 몇번째에 존재하는지 출력합니다.\n");
    printf("C: 연결리스트 초기화 합니다.\n");
    printf("W(값): 입력한 값이 연결리스트에 저장된 위치를 출력합니다.\n");
    printf("U: 연결리스트 내부 데이터를 대문자로 변환합니다.\n");
    printf("D: 연결리스트 내부 데이터를 소문자로 변환합니다.\n");
    printf("T: 연결리스트 내부 데이터를 대문자는 소문자로, 소문자는 대문자로 변환합니다.\n");    
    printf("H(값): 입력한 값이 리스트에 몇개 존재하는지 알려줍니다..\n");
    printf("*: 프로그램을 종료합니다.\n"); //각 기능별 설명
}
void initList(List *list) {
    list->head = NULL;    // 리스트의 시작 노드를 NULL로 초기화
    list->size = 0;       // 리스트의 크기를 0으로 초기화
}
void addTail(List *list, char data) {
    Node *newNode = (Node*)malloc(sizeof(Node));    // 새로운 노드 동적 할당
    newNode->data = data;                           // 새로운 노드에 데이터 저장
    newNode->next = NULL;                           // 새로운 노드의 다음 노드 포인터를 NULL로 초기화
    
    if (list->head == NULL) {                       // 리스트가 비어있을 경우
        list->head = newNode;                       // 새로운 노드를 리스트의 시작 노드로 지정
    } else {
        Node *curr = list->head;
        while (curr->next != NULL) {                // 마지막 노드까지 이동
            curr = curr->next;
        }
        curr->next = newNode;                       // 마지막 노드의 다음 노드를 새로운 노드로 지정
    }
    list->size++;                                   // 리스트의 크기 증가
    cnt++;
    lct=cnt-1;
}
void add(List *list, int index, char data) {
    if (index < 0 || index > list->size) { // 추가하려는 인덱스가 유효하지 않은 경우
        printf("추가하시려는 위치가 리스트의 범위를 벗어납니다!\n");
        return;
    }
    Node *newNode = (Node*) malloc(sizeof(Node)); // 새로운 노드 생성
    newNode->data = data;
    newNode->next = NULL;
    if(index!=0){ // 추가하려는 노드가 head가 아닌 경우
        Node *current = list->head;
        Node *previous = NULL;
        for (int i = 0; i < index; i++) { // 추가하려는 위치의 이전 노드를 찾기 위해 탐색
            previous = current;
            current = current->next;
        }
        previous->next = newNode; // 이전 노드의 next 포인터를 새로운 노드로 변경
        newNode->next = current; // 새로운 노드의 next 포인터를 다음 노드로 변경
    } 

    else { // 추가하려는 노드가 head인 경우
        newNode->next = list->head;
        list->head = newNode;
    } 
    list->size++; // 리스트 크기 증가
    cnt++;
    lct++;
}

void traverse_front() {
	lct = 0;//현재 위치를 리스트의 제일 처음으로 이동
}
void traverse_rear() {
	lct = cnt-1;//현재 위치를 리스트의 제일 마지막으로 이동
};
void traverse_next() {
	lct++;//현재 위치를 다음 노드로 이동
};
void traverse_prev() {
	lct--;//현재 위치를 이전 노드로 이동
};
void delete(List *list, int index) {
    if (index < 0 || index >= list->size) { // 삭제하려는 인덱스가 유효하지 않은 경우
        printf("지우시려는 위치가 리스트의 범위를 벗어납니다!\n");
        return;
    }
    Node *current = list->head;
    Node *previous = NULL;
    for (int i = 0; i < index; i++) { // 삭제하려는 노드의 이전 노드를 찾기 위해 탐색
        previous = current;
        current = current->next;
    }
    if (previous == NULL) { // 삭제하려는 노드가 head인 경우
        list->head = current->next;
    } else { // 삭제하려는 노드가 head가 아닌 경우
        previous->next = current->next;
    }
    free(current); // 노드 삭제
    list->size--; // 리스트 크기 감소
    cnt--;
    if (lct==cnt) lct=0;
}
void print(List *list) {
    Node *curr = list->head;
    printf("리스트에 저장된 값은");
    while (curr != NULL) {                          // 마지막 노드까지 이동
        printf(" %c ", curr->data);                  // 현재 노드의 데이터 출력
        curr = curr->next;
    }
    if (lct==-1) printf(" 없습니다.");
    else
        printf("가 있으며, 현재 위치는 %d번째 입니다.", lct+1);
        printf("\n");
}
Node *check_get_data(List *list, int index) {// 인덱스에 해당하는 노드 반환 함수
    if (index < 0 || index >= list->size) {   // 인덱스가 리스트 범위를 벗어난 경우
        return NULL;
    }
    Node *curr = list->head;
    int i = 0;
    while (curr != NULL && i < index) {       // 리스트를 순회하면서 인덱스에 해당하는 노드 찾기
        curr = curr->next;
        i++;
    }
    return curr;
}
void get_data(List *list, int index) {// 인덱스에 해당하는 노드 출력 함수
    Node *node = check_get_data(list, index);
    if (node == NULL) {                       // 해당 인덱스의 노드가 없는 경우
        printf("해당 위치는 리스트의 범위를 벗어납니다.\n");
    } else {                                  // 해당 인덱스의 노드가 있는 경우
        printf("%c\n", node->data);
    }
}
void is_Empty(List *list)
{
    if (list->head == NULL)
        printf("True\n"); // head가 NULL이면 리스트가 비어있음을 출력
    else
        printf("Flase\n"); // head가 NULL이 아니면 리스트에 값이 있음을 출력
}
void data_count(List *list)
{
    printf("%d\n", list->size); // 리스트의 크기를 출력
}
int findtheindex(List *list, char value)
{
    int index = 0;              
    Node *current = list->head; // 현재 노드를 head로 초기화
    while (current != NULL){
        if (current->data == value) return index;
        
        current = current->next; 
        index++;                 
    }
    return -1; // 입력받은 값이 연결 리스트에 없는 경우 -1 반환
}
void is_member(List* list, char value) {
    int nodeIndex = findtheindex(list, value);
    if (nodeIndex == -1) {
        printf("입력받은 값이 연결 리스트에 없습니다.\n");
    } else {
        int index = nodeIndex + 1; 
        printf("%d: ", index);
        lct=index-1;
    }
}
void clear(List *list) {
    list->head = NULL;  // head를 NULL로 초기화
    list->size = 0;     // size를 0으로 초기화
    lct=-1;
}
void replace(List *list, int index, char data) {
    if (index < 0 || index >= list->size) { // 교체하려는 인덱스가 유효하지 않은 경우
        printf("해당 위치는 리스트의 범위를 벗어납니다.\n");
        return;
    }
    Node *newNode = (Node*) malloc(sizeof(Node)); // 새로운 노드 생성
    newNode->data = data;
    newNode->next = NULL;
    if (index == 0) { // 교체하려는 노드가 head인 경우
        newNode->next = list->head->next;
        free(list->head); // 기존 head 노드 삭제
        list->head = newNode;
    } else { // 교체하려는 노드가 head가 아닌 경우
        Node *current = list->head;
        Node *previous = NULL;
        for (int i = 0; i < index; i++) { // 교체하려는 위치의 이전 노드를 찾기 위해 탐색
            previous = current;
            current = current->next;
        }
        previous->next = newNode; // 이전 노드의 next 포인터를 새로운 노드로 변경
        newNode->next = current->next; // 새로운 노드의 next 포인터를 다음 노드로 변경
        free(current); // 기존 노드 삭제
    }
}
void addFirst(List* list, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // 새 노드 생성
    newNode->data = data;  // 노드에 데이터 저장
    newNode->next = list->head;  // 새 노드의 다음 노드를 현재 head로 지정
    list->head = newNode;  // 리스트의 head를 새 노드로 변경
    list->size++;  // 리스트의 크기 증가
}
void up(List *list){
    Node *curr = list->head; // 리스트의 head를 curr에 저장
    while (curr != NULL){
        if (curr->data >= 97) curr->data = curr->data - 32;
        curr = curr->next;         // 다음 노드로 이동
    }
}
void down(List *list) {
    Node *curr = list->head; // 리스트의 head를 curr에 저장
    while (curr != NULL){
        if (curr->data <= 90) curr->data = curr->data + 32;
        curr = curr->next;         // 다음 노드로 이동
    }

}
void tog(List *list){
    Node *curr = list->head; // 리스트의 head를 curr에 저장
    while (curr != NULL){
        if (curr->data >= 97) curr->data = curr->data - 32;
        else if (curr->data <= 90) curr->data = curr->data + 32; 
        curr = curr->next;         // 다음 노드로 이동
    }
}
int count(List *list, char data){
    int count = 0;              
    Node *current = list->head; // 리스트의 head를 가리키는 포인터 변수 current 초기화
    while (current != NULL){
        if (current->data == data) count++;
        current = current->next; // current를 다음 노드로 이동
    }
    return count; // 카운트 변수 반환
}

void get_index(List *list, char data){
    int index = 0;              
    int numa = 0;               
    Node *current = list->head; // 리스트의 head를 가리키는 포인터 변수 current 초기화
    while (current != NULL){
        if (current->data == data){
            printf("%d번째 ", index + 1);
            numa++;                      
        }
        current = current->next; // current를 다음 노드로 이동
        index++;
    }
    if (numa!=0) printf("위치에서 %c가 존재합니다.\n",data);
    else if (numa==0) printf("해당 데이터는 리스트에 존재하지 않습니다.\n");
}