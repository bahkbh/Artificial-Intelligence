//�ڷᱸ�� �ѿ��� ������ 12���� �ǽ����� LAB08 Graph ADT ����
//���� �ۼ���: 2023.05.20(��)
//2019313550 �ں���
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

typedef struct vertex {
	struct vertex* next;
	char data;
	int visited;
	struct edge* connect;
	int count_edge;
}VERTEX;

typedef struct edge {
	VERTEX* vertex;
	struct edge* more;
}EDGE;

typedef struct my_graph {
	int count_vertex;
	VERTEX* head;
}GRAPH;
void create(GRAPH* my_graph);
void print(GRAPH* my_graph);
int vertex_exist(GRAPH* my_graph, char data);//������ ���1
VERTEX* search_vertex(GRAPH* my_graph, char data);
int edge_exist(GRAPH* my_graph, char data1, char data2);
int degree_of_vertex(GRAPH* my_graph, char data);
void is_connected(GRAPH* my_graph);
void is_empty(GRAPH* my_graph);
void insert_vertex(GRAPH* my_graph, char data);
void add_edge(GRAPH* my_graph, char data1, char data2);
void adjacent(GRAPH* my_graph, char data);
void delete_vertex(GRAPH* my_graph, char data);
void delete_edge(GRAPH* my_graph, char datum1, char datum2);
int path_exist(GRAPH* my_graph, VERTEX* data1, VERTEX* data2);
void reset_visited(GRAPH* my_graph);
int find_path(GRAPH* my_graph, VERTEX* data1, VERTEX* data2, char backtrack[]);
int num_of_vertex(GRAPH* my_graph);
int num_of_edge(GRAPH* my_graph);
void rename_vertex(GRAPH* my_graph, char data1, char data2);
void clear(GRAPH* my_graph);
void show();
void findMaxDegree(GRAPH* my_graph);//������ ���2
void find_path_way(GRAPH* my_graph, VERTEX* data1, VERTEX* data2);//������ ���3


int main() {
    show();
	char enter[30];
	GRAPH* my_graph = (GRAPH*)malloc(sizeof(GRAPH));
	A:
	while (1) {
        printf("����� �Է��ϼ���: ");
        scanf("%s", enter);

		for (int i = 0; enter[i] != '\0'; i++) {
			if (enter[i] == 'G') {
				create(my_graph);
			}
			else if (enter[i] == '+') {
				i++; 
				insert_vertex(my_graph,enter[i]);
			}
			else if (enter[i] == 'E') {
				add_edge(my_graph, enter[i + 2], enter[i + 4]);
				i += 5;
			}
			else if (enter[i] == 'L') {
                continue;
            }
			else if (enter[i] == 'V') {
                printf("%d\n",degree_of_vertex(my_graph,enter[i+2]));
                i=i+3;
                goto A;
			}
			else if (enter[i] == 'C') {
				is_connected(my_graph);
				goto A;
			}
			else if (enter[i] == 'N') {
                is_empty(my_graph);
				goto A;
			}
			else if (enter[i] == 'A') {
                adjacent(my_graph,enter[i+2]);
                i=i+3;
				goto A;
			}
			else if (enter[i] == '-') {
				i++;
				delete_vertex(my_graph,enter[i]);
			}
			else if (enter[i] == 'P') {
				VERTEX* data1 = search_vertex(my_graph, enter[i + 2]);
				VERTEX* data2 = search_vertex(my_graph, enter[i + 4]);
				if (data1 == NULL || data2 == NULL) {
					i += 5;
					continue;
				}
				if (path_exist(my_graph, data1, data2)) {
					printf("True\n");
					reset_visited(my_graph);
				}
				else {
					printf("Flase\n");
				}
				i += 5;
				reset_visited(my_graph);
				goto A;
			}
			else if (enter[i] == 'X') {
                printf("%d\n",num_of_vertex(my_graph));
				goto A;
			}
			else if (enter[i] == 'H') {
                printf("%d\n",num_of_edge(my_graph));
				goto A;
			}
			else if (enter[i] == 'D') {
                delete_edge(my_graph,enter[i+2],enter[i+4]);
                i+=5;
			}
			else if (enter[i] == 'K') {
                clear(my_graph);
			}
			else if (enter[i] == 'R') {
				rename_vertex(my_graph, enter[i + 2], enter[i + 4]);
				i += 5;
			}
            else if(enter[i]=='M'){
                findMaxDegree(my_graph);
                goto A;
            }
            else if (enter[i]=='?'){
				int exist = vertex_exist(my_graph, enter[i + 2]);
				if (exist) {
					printf("True\n");
				}
				else
					printf("Flase\n");
				i+=3;
                goto A;
            }
			else if (enter[i] == '~') {
				VERTEX* data1 = search_vertex(my_graph, enter[i + 2]);
				VERTEX* data2 = search_vertex(my_graph, enter[i + 4]);
				if (data1 == NULL || data2 == NULL) {
					i += 5;
					continue;
				}
				if (path_exist(my_graph, data1, data2)) {
					reset_visited(my_graph);
					find_path_way(my_graph, data1, data2);
				}
				else {
					printf("False\n");
				}
				i += 5;
				reset_visited(my_graph);
                goto A;

			}
			else if (enter[i] == '*') {
				clear(my_graph);
				printf("���α׷��� �����մϴ�.\n");
				goto B;

			}
		}

			print(my_graph);
	}
	B:
	return 0;
}
void create(GRAPH* my_graph) {
	my_graph->head = NULL;
	my_graph->count_vertex = 0;
}
void print(GRAPH* my_graph) {
    VERTEX* currentVertex = my_graph->head;
    printf("(");

    while (currentVertex) {
        printf("%c", currentVertex->data);

        EDGE* currentEdge = currentVertex->connect;
        while (currentEdge) {
            if (currentEdge == currentVertex->connect) {
                printf("(");
            }
            printf("%c", currentEdge->vertex->data);

            if (currentEdge->more != NULL) {
                printf(",");
            }
            currentEdge = currentEdge->more;
            if (currentEdge == NULL) {
                printf(")");
            }
        }

        if (currentVertex->next != NULL) {
            printf(", ");
        }
        currentVertex = currentVertex->next;
    }
    printf(")\n");
}
int vertex_exist(GRAPH* my_graph, char data) {
    if (my_graph == NULL) {
        printf("�׷����� �������� �ʽ��ϴ�.\n");
        return -1;
    }

    VERTEX* current_vertex = my_graph->head;
    
    while (current_vertex != NULL) {
        if (current_vertex->data == data) {
            return 1;
        }
        current_vertex = current_vertex->next;
    }

    return 0;
}
VERTEX* search_vertex(GRAPH* my_graph, char data) {
    if (!vertex_exist(my_graph, data)) {
        printf("������ �������� �ʽ��ϴ�.\n");
        return NULL;
    }

    VERTEX* current_vertex = my_graph->head;

    while (current_vertex != NULL) {
        if (current_vertex->data == data) {
            return current_vertex;
        }
        current_vertex = current_vertex->next;
    }

    return NULL;
}
int edge_exist(GRAPH* my_graph, char data1, char data2) {
    if (my_graph == NULL) {
        printf("�׷����� �������� �ʽ��ϴ�.\n");
        return -1;
    }

    VERTEX* searched_vertex = search_vertex(my_graph, data1);
    if (searched_vertex == NULL) {
        printf("�ش� ������ �������� �ʽ��ϴ�.\n");
        return -1;
    }

    EDGE* current_edge = searched_vertex->connect;
    
    while (current_edge != NULL) {
        if (current_edge->vertex->data == data2) {
            return 1;
        }
        current_edge = current_edge->more;
    }

    return 0;
}
int degree_of_vertex(GRAPH* my_graph, char data) {
	VERTEX* searched_vertex = search_vertex(my_graph, data);

	return (searched_vertex == NULL) ? -1 : searched_vertex->count_edge;
}
void is_connected(GRAPH* my_graph) {
	VERTEX* iter_vertex = my_graph->head;

	while (iter_vertex) {
		if (iter_vertex->count_edge == 0) {
            printf("False\n");
			return;
		}
		iter_vertex = iter_vertex->next;
	}
    printf("True\n");
    return;
}
void insert_vertex(GRAPH* my_graph, char data) {
    if (my_graph == NULL) {
        printf("�׷����� �������� �ʽ��ϴ�.\n");
        return;
    }

    if (vertex_exist(my_graph, data)) {
        printf("�����Ͱ� �̹� �����մϴ�.\n");
        return;
    }

    VERTEX* new_vertex = (VERTEX*) malloc(sizeof(VERTEX));
    if (new_vertex == NULL) {
        printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.\n");
        return;
    }

    new_vertex->connect = NULL;
    new_vertex->visited = 0;
    new_vertex->next = NULL;
    new_vertex->data = data;
    new_vertex->count_edge = 0;

    if (my_graph->head == NULL) {
        my_graph->head = new_vertex;
    } else {
        VERTEX* current_vertex = my_graph->head;

        while (current_vertex->next != NULL) {
            current_vertex = current_vertex->next;
        }

        current_vertex->next = new_vertex;
    }

    my_graph->count_vertex++;
}
void add_edge(GRAPH* my_graph, char data1, char data2) {
    if (!vertex_exist(my_graph, data1) || !vertex_exist(my_graph, data2)) {
        printf("�ش� ������ �������� �ʽ��ϴ�.\n");
        return;
    }

    if (edge_exist(my_graph, data1, data2)) {
        printf("������ �̹� �����մϴ�.\n");
        return;
    }
    if (my_graph == NULL) {
        printf("�׷����� �������� �ʽ��ϴ�.\n");
        return;
    }
    VERTEX* vertex1 = search_vertex(my_graph, data1);
    VERTEX* vertex2 = search_vertex(my_graph, data2);
    EDGE* edge1 = (EDGE*) malloc(sizeof(EDGE));
    edge1->more = NULL;
    edge1->vertex = vertex2;
    if (vertex1->connect == NULL) {
        vertex1->connect = edge1;
    } else {
        EDGE* last_edge = vertex1->connect;
        while (last_edge->more != NULL) {
            last_edge = last_edge->more;
        }
        last_edge->more = edge1;
    }
    vertex1->count_edge++;
    EDGE* edge2 = (EDGE*) malloc(sizeof(EDGE));
    edge2->more = NULL;
    edge2->vertex = vertex1;
    if (vertex2->connect == NULL) {
        vertex2->connect = edge2;
    } else {
        EDGE* last_edge = vertex2->connect;
        while (last_edge->more != NULL) {
            last_edge = last_edge->more;
        }
        last_edge->more = edge2;
    }
    vertex2->count_edge++;
}
void is_empty(GRAPH* my_graph) {
    if(my_graph->head==NULL){
        printf("True\n");
        return;
    }
    else{
        printf("False\n");
        return ;
    }
}
void adjacent(GRAPH* my_graph, char data) {
	VERTEX* target_vertex = search_vertex(my_graph, data);
	if (target_vertex == NULL) {
		return;
	}

	EDGE* edge_iter = target_vertex->connect;

	printf("{");
	while (edge_iter) {
		printf("%c", edge_iter->vertex->data);

		if (edge_iter->more != NULL) {
			printf(", ");
		}
		edge_iter = edge_iter->more;
	}
	printf("}\n");
}
void delete_vertex(GRAPH* my_graph, char data) {
	VERTEX* del_vertex = search_vertex(my_graph, data);
	if (del_vertex == NULL) {
		return;
	}

	if (del_vertex->connect == NULL) {
		if (my_graph->head == del_vertex) {
			my_graph->head = my_graph->head->next;
		} else {
			VERTEX* vertex_iter = my_graph->head;
			while (vertex_iter->next != del_vertex) {
				vertex_iter = vertex_iter->next;
			}
			vertex_iter->next = vertex_iter->next->next;
		}
		free(del_vertex);
	} 
    else {
		int user_choice;
		printf("������� ������ ������ �����մϴ�. �����Ͻðڽ��ϱ�? (0�� ������ ������ ����մϴ�. �����Ͻ÷��� 0�� �ƴ� �ٸ� ���ڸ� �Է��ϼ���.):");
        
		scanf("%d", &user_choice);


		if (user_choice == 0) {
			return;
		} 
        else {
			EDGE* edge_iter = del_vertex->connect;
			printf("(");
			printf("%c", edge_iter->vertex->data);

			for (int i = 1; i < del_vertex->count_edge; i++) {
				edge_iter = edge_iter->more;
				printf(",%c", edge_iter->vertex->data);
			}
			printf(")\n");

			EDGE* current_edge, *prev_edge;
			VERTEX* linked_vertex;
			EDGE* linked_edge;

			while (del_vertex->connect) {
				linked_vertex = search_vertex(my_graph, del_vertex->connect->vertex->data);
				current_edge = linked_vertex->connect;

				if (current_edge->vertex->data == del_vertex->data) {
					linked_vertex->connect = linked_vertex->connect->more;
				} 
                else {
					while (current_edge->more->vertex->data != del_vertex->data) {
						current_edge = current_edge->more;
					}
					prev_edge = current_edge;
					current_edge = current_edge->more;
					prev_edge->more = current_edge->more;
				}

				linked_vertex->count_edge--;
				free(current_edge);

				prev_edge = del_vertex->connect;
				del_vertex->connect = del_vertex->connect->more;
				free(prev_edge);
				del_vertex->count_edge--;
			}

			if (my_graph->head == del_vertex) {
				my_graph->head = my_graph->head->next;
			} 
            else {
				VERTEX* vertex_iter = my_graph->head;
				while (vertex_iter->next != del_vertex) {
					vertex_iter = vertex_iter->next;
				}
				vertex_iter->next = vertex_iter->next->next;
			}

			free(del_vertex);
		}
	}
	my_graph->count_vertex--;
}
void delete_edge(GRAPH* my_graph, char datum1, char datum2) {
    VERTEX* vertex1 = search_vertex(my_graph, datum1);
    VERTEX* vertex2 = search_vertex(my_graph, datum2);

    if (!vertex1 || !vertex2) {
        return;
    }

    if (!edge_exist(my_graph, datum1, datum2)) {
        printf("������ �������� �ʽ��ϴ�.\n");
        return;
    }

    EDGE* edge_iter1 = vertex1->connect;
    EDGE* edge_to_delete1 = NULL;

    if (edge_iter1->vertex->data == datum2) {
        edge_to_delete1 = edge_iter1;
        vertex1->connect = edge_iter1->more;
    } else {
        while (edge_iter1->more->vertex->data != datum2) {
            edge_iter1 = edge_iter1->more;
        }
        edge_to_delete1 = edge_iter1->more;
        edge_iter1->more = edge_iter1->more->more;
    }

    vertex1->count_edge--;
    free(edge_to_delete1);

    EDGE* edge_iter2 = vertex2->connect;
    EDGE* edge_to_delete2 = NULL;

    if (edge_iter2->vertex->data == datum1) {
        edge_to_delete2 = edge_iter2;
        vertex2->connect = edge_iter2->more;
    } else {
        while (edge_iter2->more->vertex->data != datum1) {
            edge_iter2 = edge_iter2->more;
        }
        edge_to_delete2 = edge_iter2->more;
        edge_iter2->more = edge_iter2->more->more;
    }

    vertex2->count_edge--;
    free(edge_to_delete2);
}
int path_exist(GRAPH* my_graph, VERTEX* data1, VERTEX* data2) {
	if (data1 == data2) return 1;
	
	EDGE* adjacentEdge = data1->connect;
	data1->visited = 1;

	while (adjacentEdge != NULL) {
		if (!adjacentEdge->vertex->visited) {
			if (path_exist(my_graph, adjacentEdge->vertex, data2)) return 1;
		}
		adjacentEdge = adjacentEdge->more;
	}

	return 0;
}
void reset_visited(GRAPH* my_graph) {
	VERTEX* currentNode = my_graph->head;

	for (int index = 0; index < my_graph->count_vertex; index++) {
		currentNode->visited = 0;
		currentNode = currentNode->next;
	}
}
int find_path(GRAPH* my_graph, VERTEX* data1, VERTEX* data2, char backtrack[]) {
	if (data1 == data2) return 1;
	
	EDGE* adjacentEdge = data1->connect;
	data1->visited = 1;

	while (adjacentEdge) {
		if (!adjacentEdge->vertex->visited) {
			backtrack[(adjacentEdge->vertex->data - 'A')] = data1->data;
			if (find_path(my_graph, adjacentEdge->vertex, data2, backtrack)) return 1;
		}
		adjacentEdge = adjacentEdge->more;
	}

	return 0;
}
int num_of_vertex(GRAPH* my_graph) {
	return my_graph->count_vertex;
}
int num_of_edge(GRAPH* my_graph) {
	int edgeCount = 0;
	VERTEX* currentNode = my_graph->head;

	for (int index = 0; index < num_of_vertex(my_graph); index++) {
		edgeCount += currentNode->count_edge;
		currentNode = currentNode->next;
	}

	return edgeCount / 2;
}
void rename_vertex(GRAPH* my_graph, char data1, char data2) {
	VERTEX* targetVertex = search_vertex(my_graph, data1);
	if (targetVertex == NULL) return;
	
	if (vertex_exist(my_graph, data2)) {
		printf("�����Ͻ÷��� ���� �̹� �׷����� �����մϴ�.\n");
		return;
	}

	targetVertex->data = data2;
	EDGE* targetEdge = targetVertex->connect;
	EDGE* searchEdge = NULL;

	while (targetEdge) {
		searchEdge = targetEdge->vertex->connect;
		while (searchEdge) {
			if (searchEdge->vertex->data == data1) searchEdge->vertex->data = data2;
			searchEdge = searchEdge->more;
		}
		targetEdge = targetEdge->more;
	}
}
void clear(GRAPH* my_graph) {
    if (my_graph == NULL) {
        printf("�׷����� �������� �ʽ��ϴ�.\n");
        return;
    }

    VERTEX* current_vertex = my_graph->head;
    while (current_vertex != NULL) {
        VERTEX* temp = current_vertex;
        current_vertex = current_vertex->next;
        EDGE* current_edge = temp->connect;
        while (current_edge != NULL) {
            EDGE* temp_edge = current_edge;
            current_edge = current_edge->more;
            free(temp_edge);
        }
        
        free(temp);
    }

    my_graph->head = NULL;
    my_graph->count_vertex = 0;
}
void show(){
    printf("��ɹ��� �ȳ��ص帮�ڽ��ϴ�.\n");
    printf("G: �׷��� �����մϴ�.\n");
    printf("+��: �׷����� ���� �������� �߰��մϴ�.\n");
    printf("-��: �׷����� ���� �������� �����մϴ�.\n");
    printf("E(��1,��2): �� ���� ���� �������� �����մϴ�.\n");
    printf("V(��): ���� �׷����� ������ ������ ����մϴ�.\n");
    printf("C: �׷����� ����׷����̸� True, ����׷����� �ƴ϶�� False�� ����մϴ�.\n");
    printf("N: �׷����� ��������� True, ������� ������ False�� ����մϴ�.\n");
    printf("A(��): �ش� ���� ����� ������ ����մϴ�.\n");
    printf("P(��1,��2): ��1�� ��2�� ����Ǿ������� True, ����Ǿ����� ������ False�� ����մϴ�.\n");
    printf("X: �׷����� ������ ���� ����մϴ�.\n");
    printf("H: �׷����� ������ ���� ����մϴ�.\n");
    printf("D(��1,��2): �� ������ ������ ������ �����մϴ�.\n");
    printf("R(��1,��2): ��1�� ��2�� �����մϴ�.\n");
    printf("L: �׷����� ����մϴ�.\n");
    printf("K: �׷����� �ʱ�ȭ�մϴ�.\n");

    printf("~(��1,��2): ��1���� ��2�� ���� ��θ� ����մϴ�.\n"); //������ ���1
    printf("M: ������ ���� ū ������ ���� �� ������ ����մϴ�.\n");//������ ���2
    printf("?(��1): �ش� ���� �׷����� �����ϸ� True, �������� ������ False�� ����մϴ�.\n");//������ ���3
    printf("*: ���α׷��� �����մϴ�.\n");
}
void find_path_way(GRAPH* my_graph, VERTEX* data1, VERTEX* data2) {
    char previousVertex[100];
    char path[100];

    find_path(my_graph, data1, data2, previousVertex);

    char endVertexData = data2->data;
    char startVertexData = data1->data;
    int pathIndex = 0;

    while (endVertexData != startVertexData) {
        path[pathIndex] = previousVertex[endVertexData - 'A'];
        endVertexData = previousVertex[endVertexData - 'A'];
        pathIndex++;
    }

    for (int i = pathIndex - 1; i >= 0; i--) {
        printf("%c -> ", path[i]);
    }
	printf("%c\n", data2->data);
}
void findMaxDegree(GRAPH* my_graph) {
    if (my_graph == NULL || my_graph->head == NULL) {
        printf("�׷����� �������� �ʰų� ������ �����ϴ�.\n");
        return;
    }

    int maxDegree = 0;
    VERTEX* maxDegreeVertex = NULL;

    VERTEX* current_vertex = my_graph->head;
    while (current_vertex != NULL) {
        if (current_vertex->count_edge > maxDegree) {
            maxDegree = current_vertex->count_edge;
            maxDegreeVertex = current_vertex;
        }
        current_vertex = current_vertex->next;
    }

    if (maxDegreeVertex == NULL) {
        printf("������ degree ���� �����ϴ�.\n");
        return;
    }

    printf("���� ū degree�� ���� ����: %c\n", maxDegreeVertex->data);
    printf("Degree ��: %d\n", maxDegree);
}