//자료구조 한옥영 교수님 3주차 수업활동
//c 기본 자료형 발표 프로그램 구현
//최종 작성일: 2023.03.17(금)
//2019313550 박병현

#include <stdio.h>
int harmonic(); //노래의 기본조를 입력받는 함수 선언
char morw(); //가수의 성별을 입력받는 함수 선언
double date(); //노래의 발매월을 입력받는 함수 선언
int songtype(char gender, int key); //열거형 변수의 멤버에 접근하기 위한 정수를 반환하는 함수
enum SONG{G1=1, G2, G3, G4, G5, G6, G7, G8, G9, G10, G11, G12, G13, G14, G15,
M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12, M13, M14, M15,
W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, W11, W12, W13, W14, W15}; //열거형 선언

int main(){
    enum SONG ss; //열거형 변수 선언
    char gender; //가수의 성별 반환 받는 문자형 변수 선언
    int key,num; //노래의 기본조를 반환 받는 정수형 변수 key, 열거형 변수 멤버에 해당하는 정수를 반환받는 정수형 변수 num 선언
    void *p; //문자열을 출력하기 위한 무치형 포인터 변수 선언
    double month; //발매월을 반환받기 위한 실수형 변수 선언
    printf("2023년 3월 17일 기준 YOUTUBE MUSIC 상위 30위 노래 중 원하시는 노래를 추천해 주는 프로그램입니다.\n");
    gender=morw(); //가수의 성별을 변수에 저장
    key=harmonic(); //노래의 기본조를 변수에 저장
    month=date(); //노래의 발매일을 변수에 저장
    num=songtype(gender, key); //가수의 성별을 변수에 저장
    ss=num; //열거형 멤버에 접근
    switch(ss){//switch문을 통해 추천하는 노래를 출력하여 보여줌. 만약 조건에 부합하는 노래가 없을 시, "추천해드릴 노래가 없네요."를 출력하고 프로그램 종료.
        case G4:
            if (month==22.12)
                p="뉴진스의 Ditto를 추천합니다.\n";
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;
        case G5:
            if (month==22.04)
                p="아이브의 LOVE DIVE를 추천합니다.\n";
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;
        case G12:
            if (month==22.10)
                p="르세라핌의 ANTIFRAGILE을 추천합니다.\n";
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;
        case G13:
            if (month==22.09)
                p="블랙핑크의 Shut Down을 추천합니다.\n";
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;  
        case M1:
            if (month==22.11)
                p="임영웅의 Polaroid를 추천합니다.\n";
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;    
        case M5:
            if (month==22.09)
                p="샘 스미스의 Unholy를 추천합니다.\n";
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;
        case M10:
            if (month==22.08)
                p="이마세의 Night Dancer를 추천합니다.\n";
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;   
        case M14:
            if (month==22.09)
                p="앨런 워커의 The drum을 추천합니다.\n";
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;    
        case W2:
            if (month==21.11)
                p="윤하의 오르트 구름을 추천합니다.\n";
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;   
        case G1:
            if (month==13.10)
                p="자우림의 스물다섯, 스물하나를 추천합니다.\n";
            else if (month==22.05)
                p="르세라핌의 FEARLESS를 추천합니다.\n";    
            else if (month==22.10)
                p="(여자)아이들의 Nxde를 추천합니다.\n";            
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;           
        case G9:
            if (month==23.01)
                p="뉴진스의 OMG, 하이키의 건물 사이에 피어난 장미를 추천합니다.\n";
            else if (month==22.08)
                p="아이브의 After LIKE를 추천합니다.\n";            
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;
        case G2:
            if (month==23.02)
                p="스테이씨의 Teddy Bear, 부석순의 파이팅 해야지를 추천합니다.\n";
            else if (month==22.08)
                  p="뉴진스의 Hype Boy를 추천합니다.\n";
            else if (month==22.11)
                p="스테이씨의 POPPY를 추천합니다.\n";                
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;                               
        case M6:
            if (month==23.02)
                p="지올팍의 CHRISTIAN를 추천합니다.\n";
            else if (month==18.02)
                p="요네즈 켄시의 Lemon를 추천합니다.\n";    
            else if (month==22.09)
                p="찰리 푸스의 I Don't Think That I LIke Her를 추천합니다.\n";            
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;             
        case G6:
            if (month==22.06)
                p="뉴진스의 Attention을 추천합니다.\n";
            else if (month==22.12)
                p="엔시티 드림의 Candy를 추천합니다.\n";            
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;              
        case M9:
            if (month==21.11)
                p="유리의 BETELGEUSE을 추천합니다.\n";
            else if (month==16.01)
                p="찰리 푸스의 Dangerously를 추천합니다.\n";            
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;                
        case M13:
            if (month==23.02)
                p="이찬원의 풍등을 추천합니다.\n";
            else if (month==22.10)
                p="요네즈 켄시의 KICK BACK을 추천합니다.\n";            
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;        
        case W4:
            if (month==17.05)
                p="아이묭의 Ai Wo Tsutaetaidatoka을 추천합니다.\n";
            else if (month==22.03)
                p="윤하의 사건의 지평선을 추천합니다.\n";            
            else
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;
        default:
                p="추천해드릴 노래가 없네요. 죄송합니다.\n"; break;           
  
    }
    printf("%s",(char*)p);//추천하는 노래, 혹은 추천하는 노래가 없음을 의미하는 문장을 출력
    return 0; //프로그램 종료
}






int songtype(char gender, int key){//열거형 변수의 멤버에 접근하기 위한 정수를 반환하는 함수 정의
    int num;
    if (gender==71)
        num=key;
    if (gender==77)
        num=key+15;
    if (gender==87)
        num=key+30;
    return num;
}




char morw(){//가수의 성별을 입력받는 함수 정의
    char gender;
    printf("가수의 성별을 입력하세요(여자:W , 남자: M, 그룹: G):");
    scanf("%c",&gender);
    fflush(stdin); //버퍼 초기화
    return gender;
}

int harmonic(){//노래의 기본조를 입력받는 함수 정의
    int key;
    printf("장조를 숫자로 입력하세요. 장조에 대한 정보는 다음과 같습니다.\n");
    printf("다장조: 1\n");
    printf("사장조: 2\n");
    printf("라장조: 3\n");
    printf("가장조: 4\n");
    printf("마장조: 5\n");
    printf("나장조: 6\n");
    printf("올림바장조: 7\n");
    printf("올림다장조: 8\n");
    printf("바장조: 9\n");
    printf("내림나장조: 10\n");
    printf("내림마장조: 11\n");
    printf("내림가장조: 12\n");
    printf("내림라장조: 13\n");
    printf("내림사장조: 14\n");
    printf("내림다장조: 15\n");
    scanf("%d",&key);
    fflush(stdin);     //버퍼 초기화
    return key;
}

double date(){//노래의 발매월을 입력받는 함수 정의
    double month;
    printf("몇월에 출시된 음악을 찾으시는지 입력하세요(ex 2022년 8월->22.08):");
    scanf("%lf",&month);
    fflush(stdin); //버퍼 초기화
    return month;
}