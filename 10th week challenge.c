//자료구조 한옥영 교수님 10주차 도전과제
//최종 작성일: 2023.05.07(일)
//2019313550 박병현
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

int CreateOfInsert=0;

typedef struct Heap{
    int heap[100];
    int size;
} HEAP;

typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}NODE;

typedef struct bst {
	NODE* root;
}BST;
void show();
int CharToNum(char enter[], int* i);
void create(BST* my_bst, int data);
void insert_node(BST* my_bst, int data);
void print(BST* my_bst);
NODE* get_parent(BST* my_bst, NODE* current_node, NODE* target);
void delete_node(BST *my_bst, int data);
void clear(BST* my_bst);
void insert_max_heap(HEAP* my_heap, int data);
int delete_max_heap(HEAP* my_heap);
void insert_min_heap(HEAP* my_heap, int data);
int delete_min_heap(HEAP* my_heap);
void print_heap(HEAP* my_heap, int i);
NODE* find_node(NODE* root, int data);
void BSTToMaxHeap(BST* my_bst, HEAP* my_heap);
void BSTToMinHeap(BST* my_bst, HEAP* my_heap);
void HeapToBST(HEAP* my_heap, BST* my_BST);
int main(void){ 
    show();
	char enter[30];
    char mode[2];
    char change[5];
    char st;
	BST* my_bst = (BST*)malloc(sizeof(BST));
	my_bst->root = NULL;
    HEAP max_heap = {'\0'};
    HEAP min_heap = {'\0'};
    max_heap.size = min_heap.size = 0;
    
    
    printf("입력 모드를 선택하세요.\n");
    printf("MAX HEAP: M\n");
    printf("MIN_HEAP: N\n");
    printf("BST: B\n");
    C:
    printf("입력하세요:");
    scanf("%s", &mode);
    
    if(mode[0] == 'M'){
        st = 'M';
    }
    else if(mode[0] == 'B'){
        st = 'B';
    }
    else if(mode[0] == 'N'){
        st = 'N';
    }
    else{
        printf("올바른 값을 입력하세요.\n");
        goto C;
    }
    show();

	while (1) {
        printf("명령을 입력하세요: ");
        scanf("%s", enter);

		for (int i = 0; enter[i] != '\0'; i++) {
            if(st=='B'){
                if (enter[i] == '+' && CreateOfInsert == 0) {
                    i++;
                    create(my_bst, CharToNum(enter, &i));
                    i--;
                    goto X;
                }
                else if (enter[i] == '+' && CreateOfInsert == 1) {
                    i++;
                    insert_node(my_bst, CharToNum(enter, &i));
                    i--;
                    goto X;
                }
                else if (enter[i] == '-') {
                    i++;
                    delete_node(my_bst, CharToNum(enter, &i));
                    i--;
                    goto X;
                }
                else if (enter[i] == 'P') {
                    X:
                    print(my_bst);
                    printf("\n");
                    }
                else if(enter[i]=='H'){
                    printf("Max Heap으로 변경할 경우 M, Min Heap으로 변경할 경우 N을 입력하세요.:");
                    scanf("%s",change);
                    if (change[0]=='M') {
                        BSTToMaxHeap(my_bst,&max_heap);
                        clear(my_bst);
                        st='M';
                        goto Y;
                    }
                    else {
                        BSTToMinHeap(my_bst,&min_heap);
                        clear(my_bst);
                        st='N';
                        goto Z;
                    }
                    
                }
                else if(enter[i]=='C'){
                    clear(my_bst);
                    
                }
                else if(enter[i]=='B'){
                    printf("이미 BST 입니다.\n");
                    
                }                
                else if (enter[i] == '*') {
                    clear(my_bst);
                    printf("프로그램을 종료합니다.\n");
                    goto B;

                }
		    }
            else if(st=='M'){
                    if (enter[i] == '+') {
                        i++;
                        insert_max_heap(&max_heap, CharToNum(enter, &i));
                        i--;
                        goto Y;
                    }
                    else if (enter[i] == '-') {
                        i++;
                        delete_max_heap(&max_heap);
                        i--;
                        goto Y;
                    }
                    else if (enter[i] == 'P') {
                        Y:
                        print_heap(&max_heap,1);
                        printf("\n");
                        }
                    else if(enter[i]=='B'){
                        HeapToBST(&max_heap,my_bst);
                        st='B';
                        goto X;
                    }
                    else if(enter[i]=='H'){
                        printf("이미 Heap 입니다.\n");
                    }
                    else if(enter[i]=='C'){
                        printf("잘못된 입력입니다.\n");
                        
                    }
                    else if (enter[i] == '*') {
                        printf("프로그램을 종료합니다.\n");
                        goto B;

                    }
                }
            else if(st=='N'){
                    if (enter[i] == '+') {
                        i++;
                        insert_min_heap(&min_heap,CharToNum(enter,&i));
                        i--;
                        goto Z;
                    }
                    else if (enter[i] == '-') {
                        i++;
                        delete_min_heap(&min_heap);
                        i--;
                        goto Z;
                    }
                    else if (enter[i] == 'P') {
                        Z:
                        print_heap(&min_heap,1);
                        printf("\n");
                        }
                    else if(enter[i]=='B'){
                        HeapToBST(&min_heap,my_bst);
                        st='B';
                        goto X;
                    }
                    else if(enter[i]=='C'){
                        printf("잘못된 입력입니다.\n");
                        
                    }
                    else if(enter[i]=='H'){
                        printf("이미 Heap 입니다.\n");
                    }
                    else if (enter[i] == '*') {
                        printf("프로그램을 종료합니다.\n");
                        goto B;

                    }
                }
        }

	}
	B:
	return 0;
}


void show(){
    printf("명령문을 안내해드리겠습니다.\n");
    printf("+값: 노드를 추가합니다.\n");
    printf("-값: Heap일 경우 루트를 삭제하고, BST일 경우 입력하신 노드를 삭제합니다.\n");
    printf("C: 초기화 합니다.\n");
    printf("B: Heap 일 경우 BST로 변환 합니다.\n");
    printf("H: BST 일 경우 Heap으로 변환 합니다.\n");
    printf("*: 프로그램을 종료합니다.\n\n");
}
int CharToNum(char enter[], int* i) {

	int number = 0;

    while (isdigit(enter[*i])) {
        number = number * 10 + (enter[*i] - '0');
        (*i)++;
    }

    return number;
}

void create(BST* my_bst, int data) {
    NODE* new_node = (NODE*)malloc(sizeof(NODE));

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    my_bst->root = new_node;
	CreateOfInsert = 1;
}
void insert_node(BST* my_bst, int data) {
    NODE* current_node = my_bst->root;
    NODE* parent_node = NULL;

    while (current_node != NULL) {
        if (current_node->data == data) {
            printf("입력하신 데이터는 이미 트리에 존재합니다.\n");
            return;
        }
        parent_node = current_node;

        if (data > current_node->data) {
            current_node = current_node->right;
        } else {
            current_node = current_node->left;
        }
    }

    NODE* new_node = (NODE*)malloc(sizeof(NODE));

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    if (data > parent_node->data) {
        parent_node->right = new_node;
    } else {
        parent_node->left = new_node;
    }
}
void print(BST* my_bst) {
    if (my_bst->root == NULL) {
        printf("트리가 비어있습니다.");
        return;
    }
    
    BST left_subtree, right_subtree;
    left_subtree.root = my_bst->root->left;
    right_subtree.root = my_bst->root->right;
    
    printf("%d", my_bst->root->data);
    
    if (left_subtree.root == NULL && right_subtree.root == NULL) {
        return;
    }
    
    printf("(");
    
    if (left_subtree.root != NULL) {
        print(&left_subtree);
    }
    
    printf(",");
    
    if (right_subtree.root != NULL) {
        print(&right_subtree);
    }
    
    printf(")");
	
    return;
}


NODE* get_parent(BST* my_bst, NODE* current_node, NODE* target) {
    if (!current_node) {
        return NULL;
    }

    if (current_node->left == target || current_node->right == target) {
        return current_node;
    }

    NODE* parent_node = NULL;

    parent_node = get_parent(my_bst, current_node->left, target);
    if (parent_node != NULL) {
        return parent_node;
    }

    parent_node = get_parent(my_bst, current_node->right, target);
    if (parent_node != NULL) {
        return parent_node;
    }

    return NULL;
}

void delete_node(BST *my_bst, int data) {
    if (CreateOfInsert == 0) {
        printf("트리가 비어있습니다.\n");
        return ;
    }

    NODE *node_to_delete = find_node(my_bst->root, data);
    if (node_to_delete == NULL) {
        printf("입력하신 값이 트리에 존재하지 않습니다.\n");
        return ;
    }

    int removed_data;
    NODE *parent_node;

    if (node_to_delete->left == NULL && node_to_delete->right == NULL) {
        if (node_to_delete == my_bst->root) {
            removed_data = node_to_delete->data;
            free(node_to_delete);
            my_bst->root = NULL;
            CreateOfInsert = 0;
        } else {
            parent_node = get_parent(my_bst, my_bst->root, node_to_delete);

            if (parent_node->right == node_to_delete) {
                parent_node->right = node_to_delete->left;
            } else {
                parent_node->left = node_to_delete->left;
            }
            removed_data = node_to_delete->data;
            free(node_to_delete);
        }
    } else if (node_to_delete->left != NULL && node_to_delete->right == NULL) {
        if (node_to_delete == my_bst->root) {
            my_bst->root = node_to_delete->left;
        } else {
            parent_node = get_parent(my_bst, my_bst->root, node_to_delete);

            if (parent_node->right == node_to_delete) {
                parent_node->right = node_to_delete->left;
            } else {
                parent_node->left = node_to_delete->left;
            }
        }
        removed_data = node_to_delete->data;
        free(node_to_delete);
    } else if (node_to_delete->left == NULL && node_to_delete->right != NULL) {
        if (node_to_delete == my_bst->root) {
            my_bst->root = node_to_delete->right;
        } else {
            parent_node = get_parent(my_bst, my_bst->root, node_to_delete);

            if (parent_node->right == node_to_delete) {
                parent_node->right = node_to_delete->right;
            } else {
                parent_node->left = node_to_delete->right;
            }
        }
        removed_data = node_to_delete->data;
        free(node_to_delete);
    } else {
        NODE *successor = node_to_delete->left;

        while (successor->right != NULL) {
            successor = successor->right;
        }

        removed_data = node_to_delete->data;
        int successor_data = successor->data;

        delete_node(my_bst, successor->data);
        node_to_delete->data = successor_data;
    }
}


void clear(BST* my_bst) {

	while (1) {
		if (my_bst->root == NULL) {
			CreateOfInsert=0;
			break;
		}

		delete_node(my_bst, my_bst->root->data);
	}
}


void insert_max_heap(HEAP* my_heap, int data){
    int i;
    my_heap->size++;
    i = my_heap->size;
    while((i!=1) && (data > my_heap->heap[i/2])){
        my_heap->heap[i] = my_heap->heap[i/2];
        i /= 2;
    }
    my_heap->heap[i] = data;
    return;
}

int delete_max_heap(HEAP* my_heap){
    int data = my_heap->heap[1];
    int tmp = my_heap->heap[my_heap->size];
    my_heap->size--;
    int parent = 1;
    int child = 2;
    while(child <= my_heap->size){
        if((child < my_heap->size) && (my_heap->heap[child] < my_heap->heap[child+1])){
            child ++; 
        }
        if(tmp >= my_heap->heap[child]){ 
            break;
        }
        else{
            my_heap->heap[parent] = my_heap->heap[child]; 
            parent = child;
            child *=2;
        }
    }
    my_heap->heap[parent] = tmp;
    return data;
}

void insert_min_heap(HEAP* my_heap, int data){
    int i;
    i=my_heap->size++;
    i = my_heap->size;
    while((i!=1) && (data < my_heap->heap[i/2])){ 
        my_heap->heap[i] = my_heap->heap[i/2];
        i /= 2;
    }
    my_heap->heap[i] = data;
    return;
}
int delete_min_heap(HEAP* my_heap){
    int parent = 1;
    int child = 2;
    int data = my_heap->heap[1]; 
    int temp = my_heap->heap[my_heap->size]; 
    my_heap->size--;
    while(child <= my_heap->size){ 
        if((child < my_heap->size) && (my_heap->heap[child] > my_heap->heap[child+1])){
            child = child+1;
        }
        if(temp <= my_heap->heap[child]){ 
            break;
        }
        else{
            my_heap->heap[parent] = my_heap->heap[child];
            parent = child;
            child = child*2;
        }
    }
    my_heap->heap[parent] = temp;
    return data;
}

void print_heap(HEAP* my_heap, int i){
    if(my_heap->size == 0){
        printf("힙이 비었습니다.");
        return;
    }
    printf("%d", my_heap->heap[i]);
    if((i*2 > my_heap->size) && ((i*2)+1 > my_heap->size)){
        return;
    }
    printf("(");
    if(i*2 <= my_heap->size){
        print_heap(my_heap, (i*2));
    }
    printf(",");
    if((i*2)+1 <= my_heap->size){
        print_heap(my_heap, ((i*2)+1));
    }
    printf(")");
    return;
}



void HeapToBST(HEAP* my_heap, BST* my_BST){ 
    int i;
    int size;
    size = my_heap->size;
    clear(my_BST);
    for(i=1;i<=size;i++){
        if(i==1){
            create(my_BST, delete_max_heap(my_heap));
        }
        else{
            insert_node(my_BST, delete_max_heap(my_heap));
        }
    }
    return;
}

void BSTToMaxHeap(BST* my_bst, HEAP* my_heap){
    while(my_bst->root != NULL){
        NODE* new_node = my_bst->root;
        while(new_node->left!=NULL){
            new_node = new_node->left;
        }
        
        insert_max_heap(my_heap, new_node->data);
        delete_node(my_bst, new_node->data);
    }
    return;
}

void BSTToMinHeap(BST* my_bst, HEAP* my_heap){
    while(my_bst->root != NULL){
        NODE* new_node = my_bst->root;
        while(new_node->left!=NULL){
            new_node = new_node->left;
        }
        insert_min_heap(my_heap, new_node->data);
        delete_node(my_bst, new_node->data);
    }
    return;
}
NODE* find_node(NODE* root, int data) {
    while (root != NULL) {
        if (data == root->data) {
            return root;
        }
        else if (data >root->data) {
            root = root->right;
        }
        else {
            root = root->left;
        }
    }

    return root;
}
