//�ڷᱸ�� �ѿ��� ������ 3���� ����Ȱ��
//c �⺻ �ڷ��� ��ǥ ���α׷� ����
//���� �ۼ���: 2023.03.17(��)
//2019313550 �ں���

#include <stdio.h>
int harmonic(); //�뷡�� �⺻���� �Է¹޴� �Լ� ����
char morw(); //������ ������ �Է¹޴� �Լ� ����
double date(); //�뷡�� �߸ſ��� �Է¹޴� �Լ� ����
int songtype(char gender, int key); //������ ������ ����� �����ϱ� ���� ������ ��ȯ�ϴ� �Լ�
enum SONG{G1=1, G2, G3, G4, G5, G6, G7, G8, G9, G10, G11, G12, G13, G14, G15,
M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12, M13, M14, M15,
W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, W11, W12, W13, W14, W15}; //������ ����

int main(){
    enum SONG ss; //������ ���� ����
    char gender; //������ ���� ��ȯ �޴� ������ ���� ����
    int key,num; //�뷡�� �⺻���� ��ȯ �޴� ������ ���� key, ������ ���� ����� �ش��ϴ� ������ ��ȯ�޴� ������ ���� num ����
    void *p; //���ڿ��� ����ϱ� ���� ��ġ�� ������ ���� ����
    double month; //�߸ſ��� ��ȯ�ޱ� ���� �Ǽ��� ���� ����
    printf("2023�� 3�� 17�� ���� YOUTUBE MUSIC ���� 30�� �뷡 �� ���Ͻô� �뷡�� ��õ�� �ִ� ���α׷��Դϴ�.\n");
    gender=morw(); //������ ������ ������ ����
    key=harmonic(); //�뷡�� �⺻���� ������ ����
    month=date(); //�뷡�� �߸����� ������ ����
    num=songtype(gender, key); //������ ������ ������ ����
    ss=num; //������ ����� ����
    switch(ss){//switch���� ���� ��õ�ϴ� �뷡�� ����Ͽ� ������. ���� ���ǿ� �����ϴ� �뷡�� ���� ��, "��õ�ص帱 �뷡�� ���׿�."�� ����ϰ� ���α׷� ����.
        case G4:
            if (month==22.12)
                p="�������� Ditto�� ��õ�մϴ�.\n";
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;
        case G5:
            if (month==22.04)
                p="���̺��� LOVE DIVE�� ��õ�մϴ�.\n";
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;
        case G12:
            if (month==22.10)
                p="���������� ANTIFRAGILE�� ��õ�մϴ�.\n";
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;
        case G13:
            if (month==22.09)
                p="����ũ�� Shut Down�� ��õ�մϴ�.\n";
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;  
        case M1:
            if (month==22.11)
                p="�ӿ����� Polaroid�� ��õ�մϴ�.\n";
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;    
        case M5:
            if (month==22.09)
                p="�� ���̽��� Unholy�� ��õ�մϴ�.\n";
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;
        case M10:
            if (month==22.08)
                p="�̸����� Night Dancer�� ��õ�մϴ�.\n";
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;   
        case M14:
            if (month==22.09)
                p="�ٷ� ��Ŀ�� The drum�� ��õ�մϴ�.\n";
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;    
        case W2:
            if (month==21.11)
                p="������ ����Ʈ ������ ��õ�մϴ�.\n";
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;   
        case G1:
            if (month==13.10)
                p="�ڿ츲�� �����ټ�, �����ϳ��� ��õ�մϴ�.\n";
            else if (month==22.05)
                p="���������� FEARLESS�� ��õ�մϴ�.\n";    
            else if (month==22.10)
                p="(����)���̵��� Nxde�� ��õ�մϴ�.\n";            
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;           
        case G9:
            if (month==23.01)
                p="�������� OMG, ����Ű�� �ǹ� ���̿� �Ǿ ��̸� ��õ�մϴ�.\n";
            else if (month==22.08)
                p="���̺��� After LIKE�� ��õ�մϴ�.\n";            
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;
        case G2:
            if (month==23.02)
                p="�����̾��� Teddy Bear, �μ����� ������ �ؾ����� ��õ�մϴ�.\n";
            else if (month==22.08)
                  p="�������� Hype Boy�� ��õ�մϴ�.\n";
            else if (month==22.11)
                p="�����̾��� POPPY�� ��õ�մϴ�.\n";                
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;                               
        case M6:
            if (month==23.02)
                p="�������� CHRISTIAN�� ��õ�մϴ�.\n";
            else if (month==18.02)
                p="����� �˽��� Lemon�� ��õ�մϴ�.\n";    
            else if (month==22.09)
                p="���� Ǫ���� I Don't Think That I LIke Her�� ��õ�մϴ�.\n";            
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;             
        case G6:
            if (month==22.06)
                p="�������� Attention�� ��õ�մϴ�.\n";
            else if (month==22.12)
                p="����Ƽ �帲�� Candy�� ��õ�մϴ�.\n";            
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;              
        case M9:
            if (month==21.11)
                p="������ BETELGEUSE�� ��õ�մϴ�.\n";
            else if (month==16.01)
                p="���� Ǫ���� Dangerously�� ��õ�մϴ�.\n";            
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;                
        case M13:
            if (month==23.02)
                p="�������� ǳ���� ��õ�մϴ�.\n";
            else if (month==22.10)
                p="����� �˽��� KICK BACK�� ��õ�մϴ�.\n";            
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;        
        case W4:
            if (month==17.05)
                p="���̒D�� Ai Wo Tsutaetaidatoka�� ��õ�մϴ�.\n";
            else if (month==22.03)
                p="������ ����� ������ ��õ�մϴ�.\n";            
            else
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;
        default:
                p="��õ�ص帱 �뷡�� ���׿�. �˼��մϴ�.\n"; break;           
  
    }
    printf("%s",(char*)p);//��õ�ϴ� �뷡, Ȥ�� ��õ�ϴ� �뷡�� ������ �ǹ��ϴ� ������ ���
    return 0; //���α׷� ����
}






int songtype(char gender, int key){//������ ������ ����� �����ϱ� ���� ������ ��ȯ�ϴ� �Լ� ����
    int num;
    if (gender==71)
        num=key;
    if (gender==77)
        num=key+15;
    if (gender==87)
        num=key+30;
    return num;
}




char morw(){//������ ������ �Է¹޴� �Լ� ����
    char gender;
    printf("������ ������ �Է��ϼ���(����:W , ����: M, �׷�: G):");
    scanf("%c",&gender);
    fflush(stdin); //���� �ʱ�ȭ
    return gender;
}

int harmonic(){//�뷡�� �⺻���� �Է¹޴� �Լ� ����
    int key;
    printf("������ ���ڷ� �Է��ϼ���. ������ ���� ������ ������ �����ϴ�.\n");
    printf("������: 1\n");
    printf("������: 2\n");
    printf("������: 3\n");
    printf("������: 4\n");
    printf("������: 5\n");
    printf("������: 6\n");
    printf("�ø�������: 7\n");
    printf("�ø�������: 8\n");
    printf("������: 9\n");
    printf("����������: 10\n");
    printf("����������: 11\n");
    printf("����������: 12\n");
    printf("����������: 13\n");
    printf("����������: 14\n");
    printf("����������: 15\n");
    scanf("%d",&key);
    fflush(stdin);     //���� �ʱ�ȭ
    return key;
}

double date(){//�뷡�� �߸ſ��� �Է¹޴� �Լ� ����
    double month;
    printf("����� ��õ� ������ ã���ô��� �Է��ϼ���(ex 2022�� 8��->22.08):");
    scanf("%lf",&month);
    fflush(stdin); //���� �ʱ�ȭ
    return month;
}