//자료구조 한옥영 교수님 5주차 LAB01 Array ADT 구현
//최종 작성일: 2023.04.01(토)
//2019313550 박병현
#include <stdio.h>
#include <string.h> //문자열 함수를 사용하기 위한 헤더파일

int lct = -1; //현재 위치를 나타내기 위한 전역 변수
int size = 0; //배열에 존재하는 데이터의 수를 나타내기 위한 전역변수
void show(); //명령어를 보여주는 함수
void insert(char arr[], char data); //데이터를 추가하는 함수
void traverse_front(int num);//현재 위치를 맨 앞으로 이동시키는 함수
void traverse_rear(int num);//현재 위치를 맨 뒤로 이동시키는 함수
void delete(char arr[]);//값을 지우는 함수
void empty(char arr[]);//배열을 초기화 하는 함수
void get_data(char arr[]);//현재 위치의 데이터를 보여주는 함수
void replace(char arr[],char new_data);//현재 위치의 데이터를 입력값으로 변환시키는 함수
void move(char arr[], int index);//현재 위치의 데이터를 입력받은 index의 위치로 이동시키는 함수
void data_count(char arr[]);//데이터의 개수와 마지막 인덱스 번호를 출력하는 함수
void up(char arr[]); //데이터를 대문자로 만들어주는 함수
void down(char arr[]); //데이터를 소문자로 만들어주는 함수
void change(char arr[]); //대문자인 데이터를 소문자로 만들어주고 소문자인 데이터를 대문자로 만들어주는 함수
void print(char arr[]); //데이터를 모두 출력하고 현재 위치를 보여주는 함수

int main() {
	char my_array[30]; //데이터를 저장하는 배열
	char enter[30]; //명령어를 입력받는 배열
    show();
    while(1){
        B: printf("명령어를 입력하세요: ");
        scanf("%s",enter);

        if(enter[0]=='+'){//데이터를 입력받는 경우
            for(int i=0; i<strlen(enter);i++){
                if(enter[i]!='+') {
                    insert(my_array,enter[i]);
                    lct++;
                    size++;
                }
            }
        }
        if(enter[0]=='<'){//현재 위치를 맨 앞으로 이동하는 경우
            int num=0;
            lct=0;
            if(enter[1]=='\0') goto A;//<만 입력한 경우 현재 위치를 변경시키고 데이터와 위치를 출력
            if(enter[1]=='-') delete(my_array);//<뒤에 -가 있을 경우 delete 함수 호출
            if(enter[1]=='M'){//<뒤에 M이 있을 경우 move 함수 호출
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
            for(int i=0; i<size;i++){//<뒤에 N 또는 P가 있을 경우 해당하는 값 만큼 현재 위치 이동
                if(enter[i]=='N') num++;
                if(enter[i]=='P') num--;
            }
            traverse_front(num);
        }
        if(enter[0]=='>'){//현재 위치를 맨 뒤로 이동하는 경우
            int num=0;
            lct=size-1;
            if(enter[1]=='\0') goto A;//<만 입력한 경우 현재 위치를 변경시키고 데이터와 위치를 출력
            if(enter[1]=='-') delete(my_array);//<뒤에 -가 있을 경우 delete 함수 호출
            if(enter[1]=='M'){//<뒤에 M이 있을 경우 move 함수 호출
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
            for(int i=0; i<size;i++){//<뒤에 N 또는 P가 있을 경우 해당하는 값 만큼 현재 위치 이동
                if(enter[i]=='N') num++;
                if(enter[i]=='P') num--;
            }            
            traverse_rear(num);
        }
        if(enter[0]=='-') delete(my_array);//현재 위치의 데이터 삭재하는 경우
        if(enter[0]=='E') empty(my_array);//배열을 초기화하는 경우
        if(enter[0]=='=') replace(my_array,enter[1]);//현재 위치의 데이터를 입력값으로 바꾸는 경우
        if(enter[0]=='@'){ //현재 위치의 데이터를 보여주는 경우
            get_data(my_array);
            goto B;
        }
        if(enter[0]=='M') {//현재 위치의 데이터를 입력받은 index의 위치로 이동시키려는 경우
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
        if(enter[0]=='L') goto A;//데이터를 출력하고, 현재 위치를 보여주는 경우
        if(enter[0]=='N') data_count(my_array);//데이터의 갯수와 마지막 인덱스 번호를 보여주는 경우
        if(enter[0]=='U') up(my_array);//데이터를 대문자로 만드는 경우
        if(enter[0]=='D') down(my_array);//데이터를 소문자로 만드는 경우
        if(enter[0]=='C') change(my_array);//대문자인 데이터를 소문자로 만들어주고 소문자인 데이터를 대문자로 만들어주는 경우
        if(enter[0]=='F') {
            printf("프로그램을 종료합니다.\n");
            break;//프로그램 종료
        }
        A: print(my_array);//해당 기능 수행 후 배열에 저장된 데이터와 현재 위치 출력
       }

}

void show(){
    printf("명령어를 안내해 드리겠습니다.\n");
    printf("+(데이터): 데이터를 추가합니다.\n");
    printf("<(추가 명령어): 배열의 제일 처음으로 간 후 추가 명령을 실행합니다. 추가 명령이 없으시면 배열의 제일 처음으로 현재 위치를 이동시킵니다.\n");
    printf(">(추가명령어): 배열의 제일 마지막으로 간 후 추가 명령을 실행합니다. 추가 명령이 없으시면 배열의 제일 마지막으로 현재 위치를 이동시킵니다.\n");
    printf("M(추가 명령어): 현재 위치에 존재하는 데이터를 이동시킵니다.\n");
    printf("추가 명령어 종류: P: 현재 위치 직전 데이터, N: 현재 위치 다음 데이터, 숫자: 인덱스\n");
    printf("-: 현재 위치의 데이터를 제거합니다.\n");
    printf("@: 현재 위치의 데이터를 출력합니다.\n");
    printf("=(데이터): 현재 위치의 데이터를 입력하신 데이터로 변환합니다.\n");
    printf("E: 배열을 초기화합니다.\n");
    printf("N: 데이터 갯수와 인덱스 마지막 번호 값 출력합니다.\n");    
    printf("U: 대문자로 변환합니다.\n");
    printf("D: 소문자로 변환합니다.\n");
    printf("C: 대소문자 변환\n");
    printf("L: 배열에 저장된 모든 데이터를 출력하고 현재 위치를 출력합니다.\n");
    printf("F: 프로그램을 종료합니다.\n\n");
    }
void insert(char arr[], char data) {
	if (lct + 1 == size) arr[lct + 1] = data; //배열 끝에 데이터를 추가하는 경우
	else //중간에 추가하는 경우
		for (int i = size; i > lct+1; i--) arr[i] = arr[i - 1];
		arr[lct + 1] = data;
}
void print(char arr[]) {
	for (int i = 0; i < size; i++) printf("%c ", arr[i]); //데이터 출력
	if (size) printf("현재 위치는 %d번째에 있는 %c입니다.\n",lct+1 ,arr[lct]);
	else printf("empty array\n");//배열에 데이터가 존재하지 않을 경우 출력
}
void traverse_front(int num){
    lct=lct+num;//현재 위치 수정
}
void traverse_rear(int num){
    lct=lct+num;//현재 위치 수정
}
void delete(char arr[]){
    size--;
    for (int i = lct; i < size; i++) {
		arr[i] = arr[i + 1];
	}
    if (lct>=size) {//현재 위치가 배열의 크기보다 큰 경우 배열의 처음으로 돌아감
        lct=0;
    }
}
void empty(char arr[]){
    arr[0]='\0';//배열 및 현재 위치, 배열 크기 초기화
    lct=-1;
    size=0;
}
void get_data(char arr[]){
    printf("현재 위치에 있는 값은 %c 입니다.\n",arr[lct]);
}
void move(char arr[], int index){
    char tmp;//임시 저장 공간
    if(lct==index) printf("현재 위치입니다!\n");//옮기려고 하는 위치가 현재 위치일 경우
    else if (lct>index){//현재 위치보다 인덱스 번호가 작은곳으로 옮기려고 할때
        tmp=arr[lct];
        for(int i=lct;i>index;i--) arr[i]=arr[i-1];
        arr[index]=tmp;
        lct=index;
    }
    else{//현재 위치보다 인덱스 번호가 큰 곳으로 옮기려고 할때
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
    for(int i=0;i<size;i++){//아스키 코드를 이용해 대문자로 변환
        if(arr[i]>=97) arr[i]=arr[i]-32;
    }
}
void down(char arr[]){
    for(int i=0;i<size;i++){//아스키 코드를 이용해 소문자로 변환
        if(arr[i]<=90) arr[i]=arr[i]+32;
    }    
}
void change(char arr[]){
    for(int i=0;i<size;i++){//아스키 코드를 이용해 대문자는 소문자로, 소문자는 대문자로 변환
        if(arr[i]<=90) arr[i]=arr[i]+32;
        else if(arr[i]>=97) arr[i]=arr[i]-32;
    } 
}
void data_count(char arr[]){
    printf("데이터의 개수는 %d개이며, 인덱스 번호는 %d번까지 있습니다.\n",size,size-1);
}