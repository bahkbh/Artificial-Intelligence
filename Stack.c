//자료구조 한옥영 교수님 7주차 LAB03 Stack ADT 구현
//최종 작성일: 2023.04.10(월)
//2019313550 박병현
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{   // 스택 노드 구조체 정의
    char data;         // 노드에 저장될 데이터
    struct node *next; // 다음 노드를 가리키는 포인터
} Node;

typedef struct stack {// 스택 구조체 정의 
    Node* top;  // 스택의 가장 상단 노드
    int size;   // 스택에 저장된 요소 개수
    int max;    // 스택의 최대 크기
} Stack;

void initStack(Stack* s, int max);// 스택 초기화 함수

int is_full(Stack* s);// 스택이 꽉 찼는지 확인하는 함수
void push(Stack* s, char data);// 스택에 데이터를 추가하는 함수
char pop(Stack* s);// 스택에서 데이터를 제거하고 반환하는 함수
char peek(Stack* s);// 스택에서 가장 상단에 있는 데이터를 반환하는 함수
int element_count(Stack* s);// 스택의 크기를 반환하는 함수
void clear(Stack* s);// 스택을 비우는 함수
void print(Stack* s);// 스택에 저장된 데이터를 출력하는 함수
void top(Stack *s);//top에 있는 값과 위치를 반환하는 함수
void replace(Stack* s, char data);// 스택의 top에 있는 데이터를 대체하는 함수
void show();//명령어의 모음을 출력하는 함수
int is_member(Stack* s, char data);//스택에 들어있는 값인지 확인하는 함수

//나만의 기능
int is_empty(Stack* s);// 나만의 기능1: 스택이 비어있는지 확인하는 함수
int count_data(Stack* s, char data);// 나만의 기능2: 스택에 중복되는 데이터가 몇개 있는지 확인하는 함수
void reverse_stack(Stack* s);// 나만의 기능3: 스택에 저장된 순서를 뒤집습니다.
int find_element(Stack* s, char data);// 나만의 기능4: 입력한 값이 스택에 몇번째에 존재하는지 알려줍니다.

int main() {
    int max;         // 스택의 최대 크기를 저장할 변수
    Stack s;         
    show();         
    int parsed;    
    char input[100]; // 스택의 크기를 저장받는 배열

    while (1){                                           
        printf("스택의 최대 크기를 입력하세요: "); 
        fgets(input, sizeof(input), stdin);        // 문자열 입력
        parsed = sscanf(input, "%d", &max);        // 정수로 형변환하여 max 변수에 저장
        if (parsed == 1){         
            break;
        }
        else{                
            printf("스택의 크기는 정수로 입력하셔야 합니다.\n");
        }
    }

    initStack(&s, max);   //Stack 생성
    char enter[100];      //명령어를 저장받는 배열
    while(1){
        B:
        printf("명령어를 입력하세요: ");
        scanf("%s",enter);
        for (int i=0;enter[i]!='\0';i++){
            if (enter[i]=='+'){
                push(&s, enter[i+1]); //스택에 데이터 추가
                i++;
            }
            else if (isdigit(enter[i])){ //숫자가 입력될 경우 해당 숫자만큼 pop 실행
                int num=(int) enter[i]-'0';
                for (int i=1; i<num;i++){
                    printf("%c ",pop(&s));
                }
            }
            else if (enter[i]=='P'){
                printf("\n");
                printf("%c \n",peek(&s));//제일 마지막 데이터 출력
                printf("\n");
                goto B;
            }
            else if (enter[i]=='-'){
                printf("%c ",pop(&s));//제일 마지막 데이터 출력 후 삭제
            }
                        
            else if (enter[i]=='F'){//스택이 가득 차 있는지 확인
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
            else if (enter[i]=='?'){//해당 데이터가 스택에 존재하는지 확인
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
            else if (enter[i]=='E'){//스택이 비어있는지 확인
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
            else if (enter[i]=='=') replace(&s,enter[i+1]);//제일 마지막 데이터 교체
            else if (enter[i]=='C') {//스택 초기화
                clear(&s);
            }
            else if (enter[i]=='#') {//스텍 갯수 출력
                printf("\n");
                printf("%d\n",element_count(&s));
                printf("\n");
                goto B;
                }
            else if (enter[i]=='T') {//제일 마지막 데이터 값, 위치 출력
                top(&s);
                goto B;
            }
            else if (enter[i] == '@') {//입력받은 데이터 개수 출력
            char data;
            sscanf(&enter[i + 1], "%c", &data);
            printf("\n");
            printf("%c는 스택에 %d개 있습니다.\n", data, count_data(&s, data));
            printf("\n");
            goto B;
        }
            else if (enter[i] == 'R') {//스택 뒤집기
                reverse_stack(&s);
        }
            else if (enter[i] == 'W') {//입력받은 데이터가 스택에 몇번째에 있는지 출력
            int position = find_element(&s, enter[i+1]);
            if (position != -1) {
                printf("\n");
                printf("Top을 스택의 1번이라고 하였을 때 \n");
                printf("%c는 스택의 %d번째 위치에 존재합니다.\n",enter[i+1], position+1);
                printf("\n");
            } else {
                printf("\n");
                printf("해당 데이터는 스택에 존재하지 않습니다.\n");
                printf("\n");
            }
            i++;
            goto B;
        }        
            else if (enter[i]=='*') goto A;//프로그램 종료
            else if (enter[i]=='L') continue;//스택 출력
        }
        
        printf("\n");
        print(&s);//스택 출력
        printf("\n");

    }
    A:
    printf("프로그램을 종료합니다.\n");
    return 0;
}
void show(){//명령어 안내
    printf("명령문을 안내해드리겠습니다.\n");
    printf("+(값): 스택에 값을 추가합니다.\n");
    printf("-: 제일 마지막에 추가한 값 제거합니다.\n");
    printf("P: 제일 마지막에 추가한 값을 보여줍니다.\n");
    printf("T: 제일 마지막에 추가한 값과 스택의 크기를 보여줍니다.\n");
    printf("=(값): 제일 마지막 원소를 입력하신 값으로 교체합니다.\n");
    printf("#: 스텍에 존재하는 값들의 개수를 출력합니다.\n");
    printf("C: 스택을 초기화합니다.\n");
    printf("E: 스택이 비어있는지 확인합니다.\n");
    printf("F: 스택이 꽉 차 있는지 확인합니다.\n");
    printf("?(값): 스택에 해당 값을 가지는 원소가 존재하는지 확인합니다.\n");
    printf("@(값): 스택에 해당 값을 가지는 원소가 몇개 존재하는지 알려줍니다.\n");
    printf("R: 스택에 저장된 순서를 뒤집습니다.\n");
    printf("W(값): 스택에 값이 몇번째에 위치하는지 출력합니다.\n");
    printf("L: 스택에 저장된 값과 현재 위치를 출력합니다.\n");
    printf("*: 프로그램을 종료합니다.\n\n");
}
void initStack(Stack* s, int max) {//스택 초기화
    s->top = NULL;
    s->size = 0;
    s->max = max;
}
int is_empty(Stack* s) {//스택이 비어있는지 확인
    return s->top == NULL;
}
int is_full(Stack* s) {//스택이 가득 차 있는지 확인
    return s->size == s->max;
}
void push(Stack* s, char data) {//스택에 데이터 추가
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
    if (is_empty(s)) {//스택이 비어있을 경우
        printf("\n");
        printf("Error: Nothing to pop.\n");
        return 0;
    }
    Node* temp = s->top;//스택의 데이터 출력
    char data = temp->data;
    s->top = temp->next;
    s->size--;
    free(temp);
    return data;
}
char peek(Stack* s) {
    if (is_empty(s)) {//스택이 비어있을 경우
        printf("\n");
        printf("Error: Nothing to peek.\n");
        return 0;
    }
    return s->top->data; //제일 마지막 데이터 출력
}
int element_count(Stack* s) {
    return s->size; //스택 갯수 출력
}
void clear(Stack* s) {
    while (!is_empty(s)) {//스택이 모두 다 빌 때 까지 스택에 저장된 데이터 pop
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

    while (!is_empty(s)) {    // 원래 스택에서 원소를 임시 스택에 옮기면서 문자열에 저장
        char top_element = pop(s);
        push(&temp, top_element);
        temp_str[i++] = top_element;
    }

    temp_str[i] = '\0';

    for (int j = strlen(temp_str) - 1; j >= 0; j--){    // 문자열을 역순으로 출력
        printf("%c ", temp_str[j]);
    }
    
    while (!is_empty(&temp)) {    // 임시 스택의 원소를 다시 원래 스택으로 옮김
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

    while (!is_empty(s)) {    // 원래 스택에서 원소를 찾으면서 임시 스택에 옮김
        char top_element = pop(s);
        push(&temp, top_element);

        if (top_element == data) {
            found = 1;
            break;
        }
    }

    while (!is_empty(&temp)) {    // 임시 스택의 원소를 다시 원래 스택으로 옮김
        push(s, pop(&temp));
    }

    return found;
}

int count_data(Stack* s, char data) {
    Stack temp;
    initStack(&temp, s->max);
    int count = 0;

    while (!is_empty(s)) {    // 원래 스택에서 원소를 찾으면서 임시 스택에 옮김
        char top_element = pop(s);
        push(&temp, top_element);

        if (top_element == data) {
            count++;
        }
    }

   
    while (!is_empty(&temp)) { // 임시 스택의 원소를 다시 원래 스택으로 옮김
        push(s, pop(&temp));
    }

    return count;
}
void reverse_stack(Stack* s) {
    Stack temp1;
    Stack temp2;
    initStack(&temp1, s->max);
    initStack(&temp2, s->max);


    while (!is_empty(s)) {    // 원래 스택의 원소를 temp1 스택에 옮김
        push(&temp1, pop(s));
    }


    while (!is_empty(&temp1)) {    // temp1 스택의 원소를 temp2 스택에 옮김
        push(&temp2, pop(&temp1));
    }


    while (!is_empty(&temp2)) {    // temp2 스택의 원소를 원래 스택으로 옮김
        push(s, pop(&temp2));
    }
}
int find_element(Stack* s, char data) {
    Stack temp;
    initStack(&temp, s->max);
    int position = -1;
    int index = 0;

    while (!is_empty(s)) {    // 원래 스택에서 원소를 찾으면서 임시 스택에 옮김
        char top_element = pop(s);
        push(&temp, top_element);

        if (top_element == data) {
            position = index;
            break;
        }

        index++;
    }

    while (!is_empty(&temp)) {    // 임시 스택의 원소를 다시 원래 스택으로 옮김
        push(s, pop(&temp));
    }

    return position;
}