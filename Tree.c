//�ڷᱸ�� �ѿ��� ������ 9���� LAB05 tree ADT ����
//���� �ۼ���: 2023.04.30(��)
//2019313550 �ں���
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binary_tree = -1; // ���� Ʈ�� ��� Ȱ��ȭ�ϸ� 1, �ƴϸ� 0
int join=-1;
typedef struct node{
    char data;
    struct node* left_child;
    struct node* right_child;
    int degree;
} Node;

typedef struct tree{
    Node* root;
} Tree;

void create(Tree* my_tree, char data);
Node* find_val(Tree* my_tree, char data);
int is_node(Tree* my_tree, char data);
void insert_node(Tree* my_tree, Node* parent_node, char data[]);
void show();
Node* find_parent(Tree* my_tree, char target, Node* parent);
void get_sibling(Tree* my_tree, Node* node);
void get_parent(Tree* my_tree, Node* node);
void get_child(Tree* my_tree, Node* node);
void get_ancestors(Tree* my_tree, Node* node);
void print_descendants(Tree* my_tree);
void get_descendants(Tree* my_tree, Node* node);
int count_node(Tree *my_tree);
void clear_helper(Node *node);
void clear(Tree *my_tree);
void degree_of_node(Tree *my_tree, Node *node);
int degree_of_tree_helper(Node* node);
void degree_of_tree(Tree *my_tree);
void insert_sibling(Tree* my_tree, Node* node, char data[]);
void level_of_node(Tree* my_tree, Node* node);
void level_of_tree(Tree* my_tree);
void delete_node(Tree* my_tree, Node* node);
Tree* join_trees(char data, Tree* tree1, Tree* tree2);
void print(Tree* my_tree);
void check_binary();
int main() {

    Tree my_tree;
    Tree my_tree_original;
    Tree my_tree_join;
    my_tree_original.root=NULL;
    my_tree_join.root=NULL;
    my_tree.root = NULL;
    check_binary();
    show();
    char enter[50];

    while (1) {
        A:
        printf("����� �Է��ϼ���: ");
        scanf("%s", enter);
        for (int i = 0; enter[i]!='\0'; i++) {
            if (enter[i] == '+') {
            if (enter[i + 1] == '^') {
                create(&my_tree, enter[i + 2]);
                i += 2;
                continue;
            }

            char parent_node = enter[i + 1];
            char input[50] = "";
            if (enter[i + 2] != '(') continue;

            int j = i + 3, count = 0;
            while (enter[j] != ')') {
                if ('A' <= enter[j] && 'z' >= enter[j]) {
                    input[count++] = enter[j];
                }
                j++;
            }
            insert_node(&my_tree, find_val(&my_tree, parent_node), input);
            i = j;
            }
        else if (enter[i] == 'T') goto C;
        else if(enter[i]=='S'){
            char node = enter[i+2];
            get_sibling(&my_tree, find_val(&my_tree,node));
            i+=3;
            goto A;
        }
        else if(enter[i]=='P'){
            char node = enter[i+2];
            get_parent(&my_tree, find_val(&my_tree,node));
            i+=3;
            goto A;
        }
        else if(enter[i]=='C'){
            char node = enter[i+2];
            get_child(&my_tree, find_val(&my_tree,node));
            i+=3;
            goto A;
        }
        else if(enter[i]=='A'){
        char node = enter[i+2];
        get_ancestors(&my_tree, find_val(&my_tree, node));
        printf("\n");
        i+=3;
        goto A;
        }
        else if(enter[i]=='D'){
            char node = enter[i+2];
            get_descendants(&my_tree, find_val(&my_tree,node));
            i+=3;
            goto A;
        }
        else if (enter[i] == '#') {
            printf("%d\n", count_node(&my_tree));
            goto A;
        }
        else if (enter[i] == 'K') {
            clear(&my_tree);
            goto A;
        }
        else if (enter[i] == 'G') {
            if (enter[i+1] == '(' && enter[i+3] == ')') {
                char node = enter[i+2];
                degree_of_node(&my_tree, find_val(&my_tree, node));
                i+=3;
            }
            else if (enter[i+1] != '(') {
                degree_of_tree(&my_tree);
                i++;
            }
            else goto A;
            goto A;
        }
        else if (enter[i]=='L'){
            if (enter[i+1]=='('&& enter[i+3]==')'){
                Node *l_node = find_val(&my_tree, enter[i+2]);
                level_of_node(&my_tree, l_node);
                i+=3;
                goto A;
            }
            else if (enter[i+1]!='('){
                level_of_tree(&my_tree);
                i++;
                goto A;
            }
        }
        else if (enter[i]=='-'){
            Node* del_node = find_val(&my_tree,enter[i+1]);
            delete_node(&my_tree, del_node);
            i+=2;
        }
        else if(enter[i]=='J'){
            if(join==-1){
                printf("���ο� Tree�� �Է��ϼ���.\n");
                printf("���ο� Tree �Է��� ������ J�� ��������.\n");
                join=1;
                my_tree_original=my_tree;
                my_tree=my_tree_join;
                goto A;
            }
            else if(join=1){
                char new_root[1];
                printf("���ο� ��Ʈ�� �Է��ϼ���: ");
                scanf("%s",new_root);
                printf("%s�� ���ο� Root�� �ϰ� ������ Tree ",new_root);
                print(&my_tree_original);
                printf("�� ���ο� Tree ");
                print(&my_tree);
                printf("�� ��ģ ���ο� Tree�� �����Ͽ����ϴ�.\n");
                Tree* joined=join_trees(new_root[0],&my_tree,&my_tree_original);
                my_tree=*joined;
                free(joined);
                join=-1;

            }

        }
        else if (enter[i] == '*') goto B;
            else if(enter[i] == '='){
                if(enter[i+1] == '+'){
                    char s_node = enter[i+2];
                    char data[50] = "";
                    if(enter[i+3] == '('){
                        int j = i+4;
                        int count = 0;
                        while(enter[j] != ')'){
                            if('A'<=enter[j] && 'z'>=enter[j]){
                                data[count] = enter[j];
                                count++;
                            }
                            j++;
                        }
                        insert_sibling(&my_tree, find_val(&my_tree, s_node), data);
                        i = j;
                    }
                }
            }
        }

        C:
        printf("(");
        print(&my_tree);
        printf(")\n");
    }
    B:
    printf("���α׷��� �����մϴ�.\n");
    return 0;
}

void create(Tree* my_tree, char data) {
    if (my_tree->root != NULL) {
        fprintf(stderr, "Error: ��Ʈ ��尡 �̹� �����մϴ�.\n");
        return;
    }

    Node* root = (Node*) malloc(sizeof(Node));
    if (root == NULL) {
        fprintf(stderr, "Error: ��Ʈ�� ���� �޸� �Ҵ翡 �����Ͽ����ϴ�.\n");
        return;
    }

    root->data = data;
    root->left_child = NULL;
    root->right_child = NULL;
    root->degree = 0;

    my_tree->root = root;
    return;
}

Node* find_val(Tree* my_tree, char data){
    Node* position = my_tree->root;
    while(position != NULL){
        if(position->data == data){
            return position;
        }
        else if(position->left_child != NULL && position->right_child != NULL){
            Node* left_tree_position = find_val(&(Tree){position->left_child}, data);
            Node* right_tree_position = find_val(&(Tree){position->right_child}, data);
            if(left_tree_position != NULL){
                return left_tree_position;
            }
            else if(right_tree_position != NULL){
                return right_tree_position;
            }
            else{
                return NULL;
            }
        }
        else if(position->left_child != NULL){
            position = position->left_child;
        }
        else if(position->right_child != NULL){
            position = position->right_child;
        }
        else{
            return NULL;
        }
    }
    return NULL;
}

int is_node(Tree* my_tree, char data){
    Node* tmp;
    tmp = find_val(my_tree, data);
    if(tmp == NULL){
        return 0;
    }
    else{
        return 1;
    }
}
void insert_node(Tree* my_tree, Node* parent_node, char data[]) {
    if (parent_node == NULL) {
        printf("Error: �θ� ��尡 �������� �ʽ��ϴ�.\n");
        return;
    }

    int n = strlen(data);
    if (binary_tree == 1 && n > 2) {
        printf("Error: ���� Ʈ���� �ڽ��� 2������ ���� �� �����ϴ�.\n");
        return;
    }
    else if (binary_tree == 1 && (parent_node->degree) + n > 2) {
        printf("Error: ���� Ʈ���� �ڽ��� 2������ ���� �� �����ϴ�.\n");
        return;
    }

    Node* current = parent_node->left_child;
    if (current == NULL) {
        current = parent_node;
    }
    else { // �̹� �ڽ��� ������
        for (int i = 0; i < parent_node->degree - 1; i++) {
            current = current->right_child;
        }
    }

    for (int i = 0; i < n; i++) {
        Node* node_fresh = (Node*)malloc(sizeof(Node));
        node_fresh->data = data[i];
        node_fresh->left_child = NULL;
        node_fresh->right_child = NULL;
        node_fresh->degree = 0;

        if (parent_node->degree == 0) {
            current->left_child = node_fresh;
        }
        else {
            current->right_child = node_fresh;
        }

        parent_node->degree += 1;
        current = node_fresh;
    }
}
void print(Tree* my_tree){
    if(my_tree->root == NULL){
        printf("Ʈ���� ����ֽ��ϴ�.");
        return;
    }
    Tree left_tree, right_child_tree;
    left_tree.root = my_tree->root->left_child;
    right_child_tree.root = my_tree->root->right_child;
    printf("%c", my_tree->root->data);
    if(left_tree.root != NULL){
        printf("(");
        print(&left_tree);
        printf(")");
    }
    if(right_child_tree.root != NULL){
        printf(",");
        print(&right_child_tree);
    }
    return;
}


void show(){  //��ɾ� �ȳ�
    printf("��ɹ��� �ȳ��ص帮�ڽ��ϴ�.\n");
    printf("+^���: ��Ʈ ��带 �߰��մϴ�.\n");
    printf("+�θ���(���1,���2,���3...): �ڽ� ��带 �߰��մϴ�.\n");
    printf("L: Ʈ���� ������ ����մϴ�.\n");
    printf("L(���): ����� ������ ����մϴ�.\n");
    printf("G: Ʈ���� ������ ����մϴ�.\n");
    printf("G(��): ����� ������ ����մϴ�.\n");
    printf("P(���): �θ� ��带 ����մϴ�.\n");
    printf("C(���): �ڽ� ��带 ����մϴ�.\n");
    printf("S(���): ����� ���� ��带 ����մϴ�.\n");
    printf("A(���): ����� ���� ��带 ��� ����մϴ�.\n");
    printf("D(���): ����� �ڼ� ��带 ��� ����մϴ�.\n");
    printf("T: Ʈ���� ����մϴ�.\n");
    printf("K: Ʈ���� �ʱ�ȭ�մϴ�.\n");
    printf("J:���ο� Ʈ���� ��Ʈ�� �Է��� ������ Ʈ���� ��Ĩ�ϴ�.\n");
    printf("=+���(���1,���2,���3,...): ����� ���� ��带 �߰��մϴ�.\n");
    printf("-���: ��带 �����մϴ�.\n");
    printf("#: ����� ������ ����մϴ�.\n");
    printf("*: ���α׷��� �����մϴ�.\n\n");
}
Node* find_parent(Tree* my_tree, char target, Node* parent){
    if((my_tree->root->data) == target){
        return NULL;
    }
    Tree left_tree, right_tree;
    Node* position;
    Node* tmp;
    left_tree.root = my_tree->root->left_child;
    right_tree.root = my_tree->root->right_child;
    position = my_tree->root;
    if((position->left_child == NULL) && (position->right_child == NULL)){
        return NULL;
    }
    if((position->left_child != NULL) && (position->left_child->data) == target){
        return position;
    }
    else if((position->right_child != NULL) && (position->right_child->data) == target){
        return parent;
    }
    else{
        if(position->right_child == NULL){
            tmp = find_parent(&left_tree, target, position);
            return tmp;
        }
        else if(position->left_child == NULL){
            tmp = find_parent(&right_tree, target, parent);
            return tmp;
        }
        else{
            tmp = find_parent(&left_tree, target, position);
            if(tmp==NULL){
                tmp = find_parent(&right_tree, target, parent);
            }
            return tmp;
        }
    }
}

void get_sibling(Tree* my_tree, Node* node){
    if(node==NULL){
        printf("ERROR: ��尡 Ʈ���� �������� �ʽ��ϴ�.\n");
        return;
    }
    char value = node->data;
    int count;
    if(node == my_tree->root){
        printf("���� ��尡 �������� �ʽ��ϴ�.\n");
        return;
    }
    Node* parent;
    Node* position;
    parent = find_parent(my_tree, value, my_tree->root);
    position = parent->left_child;
    count = (parent->degree)-1;
    if(count == 0){
        printf("���� ��尡 �������� �ʽ��ϴ�.\n");
        return;
    }
    printf("{");
    for(int i=0;i<(parent->degree);i++){
        if(position->data != value && count != 0){
            printf("%c,", position->data);
        }
        else if(position->data != value){
            printf("%c", position->data);
        }
        position = position->right_child;
        count--;
    }
    printf("}\n");
    return;
}
void get_parent(Tree* my_tree, Node* node) {
    if (node == NULL) {
        printf("Error: �Է��Ͻ� ��尡 Ʈ���� �������� �ʽ��ϴ�.\n");
        return;
    }
    if (node == my_tree->root) {
        printf("�θ� ��尡 �������� �ʽ��ϴ�.\n");
        return;
    }
    Node* parent_node = find_parent(my_tree, node->data, my_tree->root);
    if (parent_node == NULL) {
        printf("�θ� ��尡 �������� �ʽ��ϴ�.\n");
        return;
    }
    printf("%c\n", parent_node->data);
}
void get_child(Tree* my_tree, Node* node) {
    if (node == NULL) {
        printf("Error: �Է��Ͻ� ��尡 Ʈ���� �������� �ʽ��ϴ�.\n");
        return;
    }
    if (node->degree == 0) {
        printf("�ڽ� ��尡 �������� �ʽ��ϴ�.\n");
        return;
    }

    printf("{");
    Node* current = node->left_child;
    int count = node->degree;
    while (current != NULL && count > 0) {
        if (count != 1) {
            printf("%c, ", current->data);
        } else {
            printf("%c", current->data);
        }
        current = current->right_child;
        count--;
    }
    printf("}\n");
}
void get_ancestors(Tree* my_tree, Node* node) {
    if (node == NULL) {
        printf("Error: �Է��Ͻ� ��尡 Ʈ���� �������� �ʽ��ϴ�.\n");
        return;
    }

    if (node == my_tree->root) {
        printf("���� ��尡 �������� �ʽ��ϴ�.\n");
        return;
    }

    Node* current = node;
    while (current != my_tree->root) {
        current = find_parent(my_tree, current->data, my_tree->root);
        if (current == NULL) {
            printf("���� ��尡 �������� �ʽ��ϴ�.\n");
            return;
        }
        printf("%c ", current->data);
    }
}
void print_descendants(Tree* my_tree){
    Tree left_tree, right_tree;
    left_tree.root = my_tree->root->left_child;
    right_tree.root = my_tree->root->right_child;
    printf("%c", my_tree->root->data);
    if(left_tree.root != NULL){
        printf("(");
        print_descendants(&left_tree);
        printf(")");
    }
    if(right_tree.root != NULL){
        printf(" ");
        print_descendants(&right_tree);
    }
    return;
}
void get_descendants(Tree* my_tree, Node* node){
    Tree left_tree;
    left_tree.root = node->left_child;
    if(left_tree.root != NULL){
        print_descendants(&left_tree);
    }
    printf("\n");
    return;
}
int count_node_helper(Node *node) {
    if (node == NULL) {
        return 0;
    }

    int count = 1; // ���� ��带 ����
    count += count_node_helper(node->left_child);
    count += count_node_helper(node->right_child);

    return count;
}

int count_node(Tree *my_tree) {
    if (my_tree == NULL || my_tree->root == NULL) {
        return 0;
    }

    return count_node_helper(my_tree->root);
}
void clear_helper(Node *node) {
    if (node == NULL) {
        return;
    }

    clear_helper(node->left_child);
    clear_helper(node->right_child);

    free(node);
}

void clear(Tree *my_tree) {
    if (my_tree == NULL || my_tree->root == NULL) {
        return;
    }

    clear_helper(my_tree->root);
    my_tree->root = NULL;
}
void degree_of_node(Tree *my_tree, Node *node) {
    if (my_tree == NULL || node == NULL) {
        printf("Error: �Է��Ͻ� ��尡 Ʈ���� �������� �ʽ��ϴ�.\n");
        return;
    }

    printf("%d\n", node->degree);
}
int degree_of_tree_helper(Node* node) {
    if (node == NULL) {
        return 0;
    }

    int max_degree = node->degree;
    int left_degree = degree_of_tree_helper(node->left_child);
    int right_degree = degree_of_tree_helper(node->right_child);

    if (left_degree > max_degree) {
        max_degree = left_degree;
    }
    if (right_degree > max_degree) {
        max_degree = right_degree;
    }

    return max_degree;
}
void degree_of_tree(Tree *my_tree) {
    if (my_tree == NULL || my_tree->root == NULL) {
        printf("Error: Ʈ���� ��� �ֽ��ϴ�.\n");
        return;
    }

    int max_degree = degree_of_tree_helper(my_tree->root);
    printf("%d\n", max_degree);
}
void insert_sibling(Tree* my_tree, Node* node, char data[]){
    if(node==NULL || node == my_tree->root){
        printf("ERROR: ��尡 Ʈ���� �������� �ʽ��ϴ�.\n");
    }
    insert_node(my_tree, find_parent(my_tree, node->data, my_tree->root), data);
    return;
}
void level_of_node(Tree* my_tree, Node* node) {
    if (node == NULL) {
        printf("Error: �Է��Ͻ� ��尡 Ʈ���� �������� �ʽ��ϴ�.\n");
    }
    else {
        int level = 0;
        Node* current_node = node;
        while (current_node != my_tree->root) {
            current_node = find_parent(my_tree, current_node->data, my_tree->root);
            level++;
        }
        printf("%d\n", level);
    }
}
void level_of_tree(Tree* my_tree) {
    if (my_tree->root == NULL) {
        printf("Error: Ʈ���� ����ֽ��ϴ�.\n");
        return;
    }
    int level = -1;
    Node* current_node = my_tree->root;
    while (current_node != NULL) {
        level++;
        current_node = current_node->left_child;
    }
    printf("%d\n", level);
}
void delete_node(Tree* my_tree, Node* node){
    if(node==NULL){
        printf("ERROR: ��尡 Ʈ���� �������� �ʽ��ϴ�..\n");
        return;
    }
    if(node->left_child != NULL){//�θ� ���
        printf("ERROR: �θ� ���� ������ �� �����ϴ�.\n");
        return;
    }
    else if(node == my_tree->root){
        free(node);
        my_tree->root = NULL;
        return;
    }
    Node* parent;
    Node* before;
    Node* after;
    parent = find_parent(my_tree, node->data, my_tree->root);
    after = node->right_child;
    if(parent->left_child == node){//ù �ڽ� (���� ������ ���)
        before = parent;
        if(after==NULL){ //������ �ڽ�
            parent->left_child = NULL;
            (parent->degree) = (parent->degree)-1;
            free(node);
        }
        else{
            parent->left_child = after;
            (parent->degree) = (parent->degree)-1;
            free(node);
        }
    }
    else{
        before = parent->left_child;
        while(before->right_child != node){
            before = before->right_child;
        }
        (parent->degree) = (parent->degree)-1;
        before->right_child = node->right_child;
        free(node);
    }
    return;
}
Tree* join_trees(char data, Tree* tree1, Tree* tree2){
    Tree* join = (Tree*)malloc(sizeof(Tree));
    join->root = NULL;
    create(join, data);
    join->root->left_child = tree1->root;
    join->root->left_child->right_child = tree2->root;
    join->root->degree = 2;
    return join;
}
void check_binary(){
    while(1){
        printf("���� Ʈ�� ���� �����Ͻ� ��� 1, �Ϲ� Ʈ�� ���� �����Ͻ� ��� 0�� �Է��ϼ���: ");
        scanf("%d", &binary_tree);
        if (binary_tree!=1&&binary_tree!=0){
            printf("�߸��� ���� �Է��ϼ̽��ϴ�.\n");
        }
        else if(binary_tree==1){
            printf("���� Ʈ�� ����Դϴ�.\n");
            return;
        } 
        else {
            printf("�Ϲ� Ʈ�� ����Դϴ�.\n");
            return ;
            }
    }
}
