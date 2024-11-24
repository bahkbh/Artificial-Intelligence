//자료구조 한옥영 교수님 11주차 LAB07 AVL ADT 구현
//최종 작성일: 2023.05.11(목)
//2019313550 박병현
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
int CreateOrInsert=0;
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
    int height;
}NODE;
typedef struct avl {
	NODE* root;
}AVL;
void show();
int count_node(NODE* root);
int CharToNum(char enter[], int* i);
void create(AVL* my_avl, int data);
NODE* get_parent(AVL* my_avl, NODE* current_node, NODE* target);//나만의 기능1
NODE* find_node(NODE* root, int data);//나만의 기능2
int sum(NODE* root);//나만의 기능3
float avg(NODE* root);//나만의 기능4
void print(AVL* my_avl);
void inorder_traversal(NODE* root);
void right_root_left_traversal(NODE* root);
int get_min(NODE* root);
int get_max(NODE* root);
void find_path(NODE* root, NODE* target_node) ;
int get_right_child(AVL *my_avl, int data);
int get_left_child(AVL *my_avl, int data);
int height_node(AVL* my_avl, NODE* root, NODE* data);
NODE* findParent(AVL* my_avl, int target);
void adjust_height(AVL *my_avl, int mode);
void left_rotate(AVL *my_avl, NODE* node);
void right_rotate(AVL *my_avl, NODE* node);
void LR_rotate(AVL *my_avl, NODE* node);
void RL_rotate(AVL *my_avl, NODE* node);
int height_tree(AVL* my_avl, int current_height);
int balance_factor(AVL* my_avl, NODE* node);
void rebalance(AVL* my_avl, AVL* current_AVL);
NODE* check_node(AVL* my_avl, int target);
int node_exist(AVL* my_avl, int target);
void insert_node(AVL* my_avl, int data);
void delete_node(AVL* my_avl, NODE* node);
void clear(AVL* my_avl);


int main() {
    show();
	char enter[30];
	AVL* my_avl = (AVL*)malloc(sizeof(AVL));
	my_avl->root = NULL;
	A:
	while (1) {
        printf("명령을 입력하세요: ");
        scanf("%s", enter);

		for (int i = 0; enter[i] != '\0'; i++) {
			if (enter[i] == '+' && CreateOrInsert == 0) {
				i++;
				create(my_avl, CharToNum(enter, &i));
			}
			else if (enter[i] == '+' && CreateOrInsert == 1) {
				i++;
				insert_node(my_avl, CharToNum(enter, &i));
			}
			else if (enter[i] == 'P') {
				continue;
			}
			else if (enter[i] == 'I') {
				inorder_traversal(my_avl->root);
				printf("\n");
				goto A;
			}
			else if (enter[i] == 'R') {
				right_root_left_traversal(my_avl->root);
				printf("\n");
				goto A;
			}
			else if (enter[i] == 'N') {
				printf("%d\n", get_min(my_avl->root));
				goto A;
			}
			else if (enter[i] == 'X') {
				printf("%d\n", get_max(my_avl->root));
				goto A;
			}
			else if (enter[i] == 'F') {
				i++;
				NODE* finding = find_node(my_avl->root, CharToNum(enter, &i));
				if (finding == NULL) {
					printf("해당 값이 트리에 존재하지 않습니다.\n");
				}
				else {
			    	printf("Root");					
					find_path(my_avl->root, finding);
				}
				goto A;
			}
			else if (enter[i] == '-') {
				i++;
				delete_node(my_avl, check_node(my_avl, CharToNum(enter, &i)));
			}
			else if (enter[i] == 'T') {
					if (CreateOrInsert == 0) {
						printf("트리가 비어있습니다.\n");
						continue;
					}
					printf("%d\n", height_tree(my_avl,0));
					goto A;
			}
			else if (enter[i] == 'H') {
                    i++;
    				NODE* finding = find_node(my_avl->root, CharToNum(enter, &i));
			    	if (finding == NULL) {
				    	printf("해당 값이 트리에 존재하지 않습니다.\n");
				    }
					else{
                        printf("%d\n",height_node(my_avl, my_avl->root,finding));
                    }
					goto A;
			}
			else if (enter[i] == 'B') {
                    i++;
    				NODE* finding = find_node(my_avl->root, CharToNum(enter, &i));
			    	if (finding == NULL) {
				    	printf("해당 값이 트리에 존재하지 않습니다.\n");
				    }
					else{
                        printf("%d\n",balance_factor(my_avl, check_node(my_avl, CharToNum(enter, &i))));
                    }
					goto A;
			}
			else if (enter[i] == 'G') {
				i ++;
				int right_child = get_right_child(my_avl, CharToNum(enter, &i));
				if (right_child == 0) {
					continue;
				}
				else if (right_child == 1) {
					printf("NULL\n");
				}
				else
					printf("%d\n", right_child);
				goto A;
			}
			else if (enter[i] == 'L') {
				i++;
				int left_child = get_left_child(my_avl, CharToNum(enter, &i));
				if (left_child == 0) {
					continue;
				}
				else if (left_child == 1) {
					printf("NULL\n");
				}
				else
					printf("%d\n", left_child);
				goto A;
			}

			else if (enter[i] == '#') {
				printf("%d\n", count_node(my_avl->root));
				goto A;
			}
			else if (enter[i] == 'C') {
				clear(my_avl);
				printf("트리를 초기화 하였습니다.\n");
				goto A;
			}
			else if (enter[i] == '^') {
				i ++;

				NODE* kid = find_node(my_avl->root, CharToNum(enter, &i));

				if (kid == my_avl->root) {
					printf("부모가 존재하지 않습니다.\n");
				}
				else if (kid == NULL) {
					printf("입력하신 노드는 트리에 존재하지 않습니다.\n");
				}
				else {
					NODE* parent = get_parent(my_avl, my_avl->root, kid);
					printf("%d\n",parent->data);
					goto A;
				}
			}
            else if (enter[i]=='?'){
                i++;
                NODE* finding=find_node(my_avl->root,CharToNum(enter,&i));
                if (finding==NULL){
                    printf("Flase\n");
                    goto A;
                }
                else{
                    printf("True\n");
                    goto A;
                }
            }
            else if(enter[i]=='S'){
                printf("%d\n",sum(my_avl->root));
                goto A;
            }
            else if(enter[i]=='A'){
                printf("%.2lf\n",avg(my_avl->root));
                goto A;
            }
			else if (enter[i] == '*') {
				clear(my_avl);
				printf("프로그램을 종료합니다.\n");
				goto B;

			}
		}
            printf("(");
			print(my_avl);
            printf(")");
			printf("\n");
	}
	B:
	return 0;
}

void show(){
    printf("명령문을 안내해드리겠습니다.\n");
    printf("+값: 노드를 추가합니다.\n");
    printf("-값: 노드를 삭제합니다.\n");
    printf("I: Left-Root-Right 방식으로 순회 출력합니다.\n");
    printf("R: Right-Root-Left 방식으로 순회 출력합니다.\n");
    printf("N: 트리에서 가장 작은 값을 출력합니다.\n");
    printf("X: 트리에서 가장 큰 값을 출력합니다.\n");
    printf("T: 트리의 높이를 출력합니다.\n");
    printf("F값: 루트에서 해당 노드까지 가는 경로를 출력합니다.\n");
    printf("G값: 해당 노드의 오른쪽 자식을 출력합니다.\n");
    printf("L값: 해당 노드의 왼쪽 자식을 출력합니다.\n");
    printf("B값: 해당 노드의 Balancing Factor를 출력합니다.\n");
    printf("H값: 해당 노드의 높이를 출력합니다.\n");
	printf("^값: 부모 노드를 출력합니다.\n");
    printf("?값: 해당 값이 트리에 존재하면 True, 존재하지 않으면 False를 출력합니다.\n");
    printf("A: 트리의 모든 노드에 저장된 값의 평균을 보여줍니다.\n");
    printf("S: 트리의 모든 노드에 저장된 값의 합을 보여줍니다.\n");
    printf("#: 노드의 갯수를 출력합니다.\n");
    printf("C: 트리를 초기화 합니다.\n");
    printf("*: 프로그램을 종료합니다.\n\n");
}
int count_node(NODE* root) {
	if (root == NULL) {
		return 0;
	}
	return count_node(root->left) + count_node(root->right) + 1;
}
int CharToNum(char enter[], int* i) {
	int number = 0;
    while (isdigit(enter[*i])) {
        number = number * 10 + (enter[*i] - '0');
        (*i)++;
    }
    return number;
}
void create(AVL* my_avl, int data) {
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height=0;
    my_avl->root = new_node;
	CreateOrInsert = 1;
}
NODE* get_parent(AVL* my_avl, NODE* current_node, NODE* target) {//나만의 기능1
    if (!current_node) {
        return NULL;
    }

    if (current_node->left == target || current_node->right == target) {
        return current_node;
    }

    NODE* parent_node = NULL;

    parent_node = get_parent(my_avl, current_node->left, target);
    if (parent_node != NULL) {
        return parent_node;
    }

    parent_node = get_parent(my_avl, current_node->right, target);
    if (parent_node != NULL) {
        return parent_node;
    }

    return NULL;
}
NODE* find_node(NODE* root, int data) {//나만의 기능2
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
int sum(NODE* root){//나만의 기능3
    NODE* new_node=root;
	int count = 0, left, right;
	if (root == NULL) return 0;
	while (new_node != NULL) {
		count = new_node->data;
		left = sum(new_node->left);
		right = sum(new_node->right);

		return count + left + right;
	}
}
float avg(NODE* root){//나만의 기능4
    return 1.0*sum(root)/count_node(root);
}
void print(AVL* my_avl) {
    if (my_avl->root == NULL) {
        printf("트리가 비어있습니다.");
        return;
    }
    
    AVL left_subtree, right_subtree;
    left_subtree.root = my_avl->root->left;
    right_subtree.root = my_avl->root->right;
    
    printf("%d", my_avl->root->data);
    
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
void inorder_traversal(NODE* root) {
	if (root != NULL) {
		inorder_traversal(root->left);
		printf("%d ", root->data);
		inorder_traversal(root->right);
	}
}
void right_root_left_traversal(NODE* root)  {
	if (root != NULL) {
		right_root_left_traversal(root->right);
		printf("%d ", root->data);
		right_root_left_traversal(root->left);
	}
}
int get_min(NODE* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}
int get_max(NODE* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}
void find_path(NODE* root, NODE* target_node) {
    while (root->data != target_node->data) {
        if (target_node->data > root->data) {
            printf(">Right");
            root = root->right;
        }
        else {
            printf(">Left");
            root = root->left;
        }
    }
    printf("\n");
}
int get_right_child(AVL *my_avl, int data) {
    NODE *target_node = find_node(my_avl->root, data);
    if (target_node == NULL) {
        printf("입력하신 값이 트리에 존재하지 않습니다.\n");
        return 0;
    }
    if (target_node->right == NULL) {
        return 1;
    }
    return target_node->right->data;
}
int get_left_child(AVL *my_avl, int data) {
    NODE *target_node = find_node(my_avl->root, data); 
    if (target_node == NULL) {
        printf("입력하신 값이 트리에 존재하지 않습니다.\n");
        return 0;
    }
    if (target_node->left == NULL) {
        return 1;
    }
    return target_node->left->data;
}
int height_node(AVL* my_avl, NODE* root, NODE* data){ 
	int height = 0;
	while (data != root) {
		data = get_parent(my_avl,my_avl->root, data);
		height++;
	}
	return height;
}
NODE* findParent(AVL* my_avl, int target) {
    if (my_avl->root->data == target) {
        return NULL;
    }
    NODE* current = my_avl->root;
    if ((current->left && current->left->data == target) || 
        (current->right && current->right->data == target)) {
        return current;
    }
    AVL subtree;
    NODE* parent;
    if (current->left) {
        subtree.root = current->left;
        parent = findParent(&subtree, target);
        if (parent) {
            return parent;
        }
    }
    if (current->right) {
        subtree.root = current->right;
        parent = findParent(&subtree, target);
        if (parent) {
            return parent;
        }
    }
    return NULL;
}
void adjust_height(AVL *my_avl, int mode){
    AVL leftTree, rightTree;
    
    if(my_avl->root == NULL){
        return;
    }

    if(my_avl->root->left != NULL){
        leftTree.root = my_avl->root->left;
        adjust_height(&leftTree, mode);
    }

    if(my_avl->root->right != NULL){
        rightTree.root = my_avl->root->right;
        adjust_height(&rightTree, mode);
    }

    my_avl->root->height += mode;
    return;
}
void left_rotate(AVL *my_avl, NODE* node){
    NODE* tmp = node->right;
    NODE* parent = findParent(my_avl, node->data);
    AVL RR_tree = {node->right->right}, RL_tree = {node->right->left}, L_tree = {node->left};
    char LR_flag = 'N';

    if(parent != NULL){
        LR_flag = (parent->left == node) ? 'L' : (parent->right == node) ? 'R' : 'N';
    }
    NODE** parent_link = (LR_flag == 'L') ? &(parent->left) : (LR_flag == 'R') ? &(parent->right) : &(my_avl->root);

    *parent_link = tmp;
    node->right = RL_tree.root;
    tmp->left = node;
    node->height++;
    tmp->height--;

    adjust_height(&RR_tree, -1);
    adjust_height(&L_tree, 1);
}
void right_rotate(AVL *my_avl, NODE* node){
    NODE* tmp = node->left;
    NODE* parent = findParent(my_avl, node->data);
    AVL LL_tree = {node->left->left}, LR_tree = {node->left->right}, R_tree = {node->right};
    char LR_flag = 'N';

    if(parent != NULL){
        LR_flag = (parent->left == node) ? 'L' : (parent->right == node) ? 'R' : 'N';
    }
    NODE** parent_link = (LR_flag == 'L') ? &(parent->left) : (LR_flag == 'R') ? &(parent->right) : &(my_avl->root);

    *parent_link = tmp;
    node->left = LR_tree.root;
    tmp->right = node;
    node->height++;
    tmp->height--;

    adjust_height(&LL_tree, -1);
    adjust_height(&R_tree, 1);
}
void LR_rotate(AVL *my_avl, NODE* node){
    left_rotate(my_avl, node->left);
    right_rotate(my_avl, node);
    return;
}
void RL_rotate(AVL *my_avl, NODE* node){
    right_rotate(my_avl, node->right);
    left_rotate(my_avl, node);
    return;
}
int height_tree(AVL* my_avl, int current_height) {
    if (my_avl->root == NULL) {
        printf("입력하신 값이 트리에 존재하지 않습니다.\n");
        return current_height;
    }

    int left_height = 0;
    int right_height = 0;
    AVL left_subtree;
    AVL right_subtree;

    left_subtree.root = my_avl->root->left;
    right_subtree.root = my_avl->root->right;

    if (my_avl->root->left == NULL && my_avl->root->right == NULL) {
        return current_height + 1;
    }

    if (left_subtree.root != NULL) {
        left_height = height_tree(&left_subtree, current_height + 1);
    }

    if (right_subtree.root != NULL) {
        right_height = height_tree(&right_subtree, current_height + 1);
    }

    return (left_height > right_height) ? left_height : right_height;
}
int balance_factor(AVL* my_avl, NODE* node) {
    if (node == NULL) {
        return 0;
    }
    AVL left_subtree = { .root = node->left };
    AVL right_subtree = { .root = node->right };
    int left_height = node->left ? height_tree(&left_subtree, 0) : 0;
    int right_height = node->right ? height_tree(&right_subtree, 0) : 0;
    return left_height - right_height;
}
void rebalance(AVL* my_avl, AVL* current_AVL) {
    if (!my_avl->root) {
        return;
    }
    if (current_AVL->root->left) {
        AVL left_subtree = { .root = current_AVL->root->left };
        rebalance(my_avl, &left_subtree);
    }
    if (current_AVL->root->right) {
        AVL right_subtree = { .root = current_AVL->root->right };
        rebalance(my_avl, &right_subtree);
    }
    int bf = balance_factor(my_avl, current_AVL->root);
    int left_bf = current_AVL->root->left ? balance_factor(my_avl, current_AVL->root->left) : 0;
    int right_bf = current_AVL->root->right ? balance_factor(my_avl, current_AVL->root->right) : 0;
    if (bf == 2 && left_bf == 1) {
        right_rotate(my_avl, current_AVL->root);
    } else if (bf == 2 && left_bf == -1) {
        LR_rotate(my_avl, current_AVL->root);
    } else if (bf == -2 && right_bf == -1) {
        left_rotate(my_avl, current_AVL->root);
    } else if (bf == -2 && right_bf == 1) {
        RL_rotate(my_avl, current_AVL->root);
    }
}
NODE* check_node(AVL* my_avl, int target) {
    NODE* index = my_avl->root;
    AVL sub_tree;
    if (index->data == target) {
        return index;
    }
    if (index->data > target) {
        if (my_avl->root->left == NULL) {
            return NULL;
        }
        sub_tree.root = my_avl->root->left;
        return check_node(&sub_tree, target);
    }
    if (index->data < target) {
        if (my_avl->root->right == NULL) {
            return NULL;
        }
        sub_tree.root = my_avl->root->right;
        return check_node(&sub_tree, target);
    }
    return index;
}
int node_exist(AVL* my_avl, int target) {
    NODE* tmp = check_node(my_avl, target);
    return tmp == NULL ? 0 : 1;
}
void insert_node(AVL* my_avl, int data) {
    if(node_exist(my_avl, data)) { 
        printf("입력하신 값은 이미 트리에 존재합니다.\n");
        return;
    }
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    if (my_avl->root == NULL) {
        my_avl->root = new_node;
    } else {
        NODE* current = my_avl->root;
        while (1) {
            if (current->data > data) {
                if (current->left == NULL) {
                    current->left = new_node;
                    break;
                } else {
                    current = current->left;
                }
            } else {
                if (current->right == NULL) {
                    current->right = new_node;
                    break;
                } else {
                    current = current->right;
                }
            }
        }
    }
    rebalance(my_avl, my_avl);
}
void delete_node(AVL* my_avl, NODE* node) {
    if (node == NULL) {
        printf("입력하신 값이 트리에 존재하지 않습니다.\n");
        return;
    }

    int is_root = (node->data == my_avl->root->data) ? 1 : 0;
    NODE* parent = NULL;

    if (!is_root) {
        parent = findParent(my_avl, node->data);
    }

    if (node->left == NULL && node->right == NULL) { 
        if (is_root) {
            free(node);
            my_avl->root = NULL;
            return;
        } else {
            NODE **parentNode = (parent->left == node) ? &parent->left : &parent->right;
            *parentNode = NULL;
            free(node);
            rebalance(my_avl, my_avl);
            return;
        }
    } 
    else if (node->left == NULL || node->right == NULL) { 
        NODE *childNode = (node->left == NULL) ? node->right : node->left;

        if (is_root) {
            my_avl->root = childNode;
        } else {
            NODE **parentNode = (parent->left == node) ? &parent->left : &parent->right;
            *parentNode = childNode;
        }

        free(node);
        rebalance(my_avl, my_avl);
        return;
    } 
    else {
        NODE* kid = node->left;
        while (kid->right != NULL) { 
            kid = kid->right;
        }

        int temp = node->data;
        node->data = kid->data;
        kid->data = temp;

        delete_node(my_avl, kid);
    }
}
void clear(AVL* my_avl) {
    NODE* currentNode = my_avl->root;
    while (my_avl->root != NULL) {
        currentNode = my_avl->root;
        while (currentNode->left != NULL) {
            currentNode = currentNode->left;
        }
        delete_node(my_avl, currentNode);
    }
}
