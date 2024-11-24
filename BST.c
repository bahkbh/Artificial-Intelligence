//�ڷᱸ�� �ѿ��� ������ 10���� LAB06 BST ADT ����
//���� �ۼ���: 2023.05.07(��)
//2019313550 �ں���
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
int CreateOfInsert=0;

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
void inorder_traversal(NODE* root);
void right_root_left_traversal(NODE* root);
int get_min(NODE* root);
int get_max(NODE* root);
void find_path(NODE* root, NODE* target);
void delete_node(BST* my_bst, int data);
int height(NODE* root);
int get_right_child(BST* my_bst, int data);
int get_left_child(BST* my_bst, int data);
int count_node(NODE* root);
void clear(BST* my_bst);
NODE* find_node(NODE* root, int data);//������ ���1: �θ��带 ã���ִ� �Լ�
NODE* get_parent(BST* my_bst, NODE* current_node, NODE* target);//������ ���2: ��尡 Ʈ���� �����ϴ��� Ȯ���ϴ� �Լ�
void what_father(BST* my_bst, int data); //������ ��� 3: Ʈ���� ���Եǰ� �Ǹ� �θ��尡 ���� ���� �������ִ� �Լ�

int main() {
    show();
	char enter[30];
	BST* my_bst = (BST*)malloc(sizeof(BST));
	my_bst->root = NULL;
	A:
	while (1) {
        printf("����� �Է��ϼ���: ");
        scanf("%s", enter);

		for (int i = 0; enter[i] != '\0'; i++) {
			if (enter[i] == '+' && CreateOfInsert == 0) {
				i++;
				create(my_bst, CharToNum(enter, &i));
				i--;
			}
			else if (enter[i] == '+' && CreateOfInsert == 1) {
				i++;
				insert_node(my_bst, CharToNum(enter, &i));
				i--;
			}
			else if (enter[i] == 'P') {
				continue;
			}
			else if (enter[i] == 'I') {
				inorder_traversal(my_bst->root);
				printf("\n");
				goto A;
			}
			else if (enter[i] == 'R') {
				right_root_left_traversal(my_bst->root);
				printf("\n");
				goto A;
			}
			else if (enter[i] == 'N') {
				printf("%d\n", get_min(my_bst->root));
				goto A;
			}
			else if (enter[i] == 'X') {
				printf("%d\n", get_max(my_bst->root));
				goto A;
			}
			else if (enter[i] == 'F') {
				i++;

				NODE* finding = find_node(my_bst->root, CharToNum(enter, &i));
				i--;

				if (finding == NULL) {
					printf("�ش� ���� Ʈ���� �������� �ʽ��ϴ�.\n");
				}
				else {
			    	printf("Root");					
					find_path(my_bst->root, finding);
				}
				goto A;
			}
			else if (enter[i] == '-') {
				i++;
				delete_node(my_bst, CharToNum(enter, &i));
				i--;
			}
			else if (enter[i] == 'H') {

					if (CreateOfInsert == 0) {
						printf("Ʈ���� ����ֽ��ϴ�.\n");
						continue;
					}
					
					printf("%d\n", height(my_bst->root));
					goto A;
			}
			else if (enter[i] == 'G') {
				i += 2;
				int right_child = get_right_child(my_bst, CharToNum(enter, &i));

				if (right_child == -1) {
					continue;
				}
				else if (right_child == -2) {
					printf("NULL\n");
				}
				else
					printf("%d\n", right_child);
				goto A;
			}
			else if (enter[i] == 'L') {
				i += 2;

				int left_child = get_left_child(my_bst, CharToNum(enter, &i));

				if (left_child == -1) {
					continue;
				}
				else if (left_child == -2) {
					printf("NULL\n");
				}
				else
					printf("%d\n", CharToNum(enter, &i), left_child);
				goto A;
			}
			else if (enter[i] == '#') {
				printf("%d\n", count_node(my_bst->root));
				goto A;
			}
			else if (enter[i] == 'C') {
				clear(my_bst);
				printf("Ʈ���� �ʱ�ȭ �Ͽ����ϴ�.\n");
				goto A;
			}

			else if (enter[i] == '^') {
				i += 2;

				NODE* kid = find_node(my_bst->root, CharToNum(enter, &i));

				if (kid == my_bst->root) {
					printf("�θ� �������� �ʽ��ϴ�.\n");
				}
				else if (kid == NULL) {
					printf("�Է��Ͻ� ���� Ʈ���� �������� �ʽ��ϴ�.\n");
				}
				else {
					NODE* parent = get_parent(my_bst, my_bst->root, kid);
					printf("%d\n",parent->data);
					goto A;
				}
			}
            else if (enter[i]=='?'){
                i+=2;
                NODE* finding=find_node(my_bst->root,CharToNum(enter,&i));
                if (finding==NULL){
                    printf("Flase\n");
                    goto A;
                }
                else{
                    printf("True\n");
                    goto A;
                }
            }
            else if(enter[i]=='W'){
                i+=2;
                what_father(my_bst,CharToNum(enter,&i));
            }
			else if (enter[i] == '*') {
				clear(my_bst);
				printf("���α׷��� �����մϴ�.\n");
				goto B;

			}
		}
			print(my_bst);
			printf("\n");
	}
	B:
	return 0;
}
void show(){
    printf("��ɹ��� �ȳ��ص帮�ڽ��ϴ�.\n");
    printf("+��: ��带 �߰��մϴ�.\n");
    printf("-��: ��带 �����մϴ�.\n");
    printf("I: Left-Root-Right ����� ��ȸ ���\n");
    printf("R: Right-Root-Left ����� ��ȸ ���\n");
    printf("N: Ʈ������ ���� ���� ���� ����մϴ�.\n");
    printf("X: Ʈ������ ���� ū ���� ����մϴ�.\n");
    printf("F��: ��Ʈ���� �ش� ������ ���� ��θ� ����մϴ�.\n");
    printf("G(��): �ش� ����� ������ �ڽ��� ����մϴ�.\n");
    printf("L(��): �ش� ����� ���� �ڽ��� ����մϴ�.\n");
    printf("H: Ʈ���� ���̸� ����մϴ�.\n");
    printf("#: ����� ������ ����մϴ�.\n");
	printf("^(��): �θ� ��带 ����մϴ�.");
    printf("?(��): �ش� ���� Ʈ���� �����ϸ� True, �������� ������ False�� ����մϴ�.\n");
    printf("W(��): �Է��Ͻ� ���� �θ� ��尡 �� ���� �����Ͽ� �����ݴϴ�.\n");
    printf("C: Ʈ���� �ʱ�ȭ �մϴ�.\n");
    printf("*: ���α׷��� �����մϴ�.\n\n");
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
            printf("�Է��Ͻ� �����ʹ� �̹� Ʈ���� �����մϴ�.\n");
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
        printf("Ʈ���� ����ֽ��ϴ�.");
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

void delete_node(BST *my_bst, int data) {
    if (CreateOfInsert == 0) {
        printf("Ʈ���� ����ֽ��ϴ�.\n");
        return ;
    }

    NODE *node_to_delete = find_node(my_bst->root, data);
    if (node_to_delete == NULL) {
        printf("�Է��Ͻ� ���� Ʈ���� �������� �ʽ��ϴ�.\n");
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

int height(NODE* root) {
	int left_height, right_height;

	if (!root) return 0;
	else {
		left_height = height(root->left);
		right_height = height(root->right);
		return 1 + (left_height > right_height ? left_height : right_height);
	}
}

int get_right_child(BST *my_bst, int data) {
    NODE *target_node = find_node(my_bst->root, data);
    
    if (target_node == NULL) {
        printf("�Է��Ͻ� ���� Ʈ���� �������� �ʽ��ϴ�.\n");
        return -1;
    }
    
    if (target_node->right == NULL) {
        return -2;
    }
    
    return target_node->right->data;
}

int get_left_child(BST *my_bst, int data) {
    NODE *target_node = find_node(my_bst->root, data);
    
    if (target_node == NULL) {
        printf("�Է��Ͻ� ���� Ʈ���� �������� �ʽ��ϴ�.\n");
        return -1;
    }
    
    if (target_node->left == NULL) {
        return -2;
    }
    
    return target_node->left->data;
}

int count_node(NODE* root) {
	if (root == NULL) {
		return 0;
	}

	return count_node(root->left) + count_node(root->right) + 1;
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
NODE* get_parent(BST* my_bst, NODE* current_node, NODE* target) {//������ ���1
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

NODE* find_node(NODE* root, int data) {//������ ���2
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
void what_father(BST* my_bst,int data){ //������ ��� 3
    if(my_bst->root == NULL){
        printf("Ʈ���� ����ֽ��ϴ�.\n");
        return;
    }
    insert_node(my_bst,data);
    NODE* kid = find_node(my_bst->root, data);
    NODE* parent = get_parent(my_bst, my_bst->root, kid);
    printf("%d�� �Է��Ͻø�, �θ� ���� %d�� �� �� �Դϴ�.\n",data, parent->data);
    delete_node(my_bst,data);
}
