//자료구조 한옥영 교수님 12주차 실습과제 LAB08 Graph ADT 구현
//최종 작성일: 2023.05.20(토)
//2019313550 박병현
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
int vertex_exist(GRAPH* my_graph, char data);//나만의 기능1
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
void findMaxDegree(GRAPH* my_graph);//나만의 기능2
void find_path_way(GRAPH* my_graph, VERTEX* data1, VERTEX* data2);//나만의 기능3


int main() {
    show();
	char enter[30];
	GRAPH* my_graph = (GRAPH*)malloc(sizeof(GRAPH));
	A:
	while (1) {
        printf("명령을 입력하세요: ");
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
				printf("프로그램을 종료합니다.\n");
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
        printf("그래프가 존재하지 않습니다.\n");
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
        printf("정점이 존재하지 않습니다.\n");
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
        printf("그래프가 존재하지 않습니다.\n");
        return -1;
    }

    VERTEX* searched_vertex = search_vertex(my_graph, data1);
    if (searched_vertex == NULL) {
        printf("해당 정점이 존재하지 않습니다.\n");
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
        printf("그래프가 존재하지 않습니다.\n");
        return;
    }

    if (vertex_exist(my_graph, data)) {
        printf("데이터가 이미 존재합니다.\n");
        return;
    }

    VERTEX* new_vertex = (VERTEX*) malloc(sizeof(VERTEX));
    if (new_vertex == NULL) {
        printf("메모리 할당에 실패하였습니다.\n");
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
        printf("해당 정점이 존재하지 않습니다.\n");
        return;
    }

    if (edge_exist(my_graph, data1, data2)) {
        printf("간선이 이미 존재합니다.\n");
        return;
    }
    if (my_graph == NULL) {
        printf("그래프가 존재하지 않습니다.\n");
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
		printf("지우려는 정점에 간선이 존재합니다. 삭제하시겠습니까? (0을 누르면 삭제를 취소합니다. 삭제하시려면 0이 아닌 다른 숫자를 입력하세요.):");
        
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
        printf("간선이 존재하지 않습니다.\n");
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
		printf("변경하시려는 값은 이미 그래프에 존재합니다.\n");
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
        printf("그래프가 존재하지 않습니다.\n");
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
    printf("명령문을 안내해드리겠습니다.\n");
    printf("G: 그래프 생성합니다.\n");
    printf("+값: 그래프에 값을 정점으로 추가합니다.\n");
    printf("-값: 그래프에 값을 정점에서 제거합니다.\n");
    printf("E(값1,값2): 두 개의 값을 간선으로 연결합니다.\n");
    printf("V(값): 현재 그래프의 간선의 갯수를 출력합니다.\n");
    printf("C: 그래프가 연결그래프이면 True, 연결그래프가 아니라면 False를 출력합니다.\n");
    printf("N: 그래프가 비어있으면 True, 비어있지 않으면 False를 출력합니다.\n");
    printf("A(값): 해당 값과 연결된 정점을 출력합니다.\n");
    printf("P(값1,값2): 값1과 값2가 연결되어있으면 True, 연결되어있지 않으면 False를 출력합니다.\n");
    printf("X: 그래프의 정점의 수를 출력합니다.\n");
    printf("H: 그래프의 간선의 수를 출력합니다.\n");
    printf("D(값1,값2): 두 정점을 연결한 간선을 삭제합니다.\n");
    printf("R(값1,값2): 값1을 값2로 변경합니다.\n");
    printf("L: 그래프를 출력합니다.\n");
    printf("K: 그래프를 초기화합니다.\n");

    printf("~(값1,값2): 값1에서 값2로 가는 경로를 출력합니다.\n"); //나만의 기능1
    printf("M: 차수가 가장 큰 정점의 값과 그 차수를 출력합니다.\n");//나만의 기능2
    printf("?(값1): 해당 값이 그래프에 존재하면 True, 존재하지 않으면 False를 출력합니다.\n");//나만의 기능3
    printf("*: 프로그램을 종료합니다.\n");
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
        printf("그래프가 존재하지 않거나 정점이 없습니다.\n");
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
        printf("정점의 degree 값이 없습니다.\n");
        return;
    }

    printf("가장 큰 degree를 가진 정점: %c\n", maxDegreeVertex->data);
    printf("Degree 값: %d\n", maxDegree);
}