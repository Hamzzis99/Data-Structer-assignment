#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;  // ������ ����
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ
void init(GraphType* g) {
    int v;
    g->n = 0;
    for (v = 0; v < MAX_VERTICES; v++)
        g->adj_list[v] = NULL;
}

// ���� ����
void set_vertex(GraphType* g, int n) {
    if ((n >= 0) && (n < MAX_VERTICES))
        g->n = n;
}

// ���� ����
void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����");
        return;
    }
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

// ���� ����Ʈ ���
void print_adj_list(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i];
        printf("%d : ", i);
        while (p != NULL) {
            printf("%d -> ", p->vertex);
            p = p->link;
            printf("");
        }
        printf("NULL");
        printf("\n");
    }
}

// DFS ����
void dfs_list(GraphType* g, int v, int visited[]) {
    GraphNode* w;
    visited[v] = 1;
    printf("[%d] -> ", v);
    for (w = g->adj_list[v]; w != NULL; w = w->link) {
        if (!visited[w->vertex])
            dfs_list(g, w->vertex, visited);
    }
}

// BFS ����
void bfs_list(GraphType* g, int v, int visited[]) {
    GraphNode* w;
    GraphNode* queue[MAX_VERTICES];
    int front = 0, rear = 0;
    printf("[%d] -> ", v);
    visited[v] = 1;
    queue[rear++] = g->adj_list[v];
    while (front < rear) {
        w = queue[front++];
        for (; w != NULL; w = w->link) {
            if (!visited[w->vertex]) {
                visited[w->vertex] = 1;
                printf("[%d] -> ", w->vertex);
                queue[rear++] = g->adj_list[w->vertex];
            }
        }
    }
}

int main(void) {
    GraphType* g;
    int i;
    int visited[MAX_VERTICES] = { 0 };

    g = (GraphType*)malloc(sizeof(GraphType));
    init(g);
    set_vertex(g, 11);  // ������ ���� ����
    // ���� �߰�
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 1, 3);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 4, 7);
    insert_edge(g, 4, 8);
    insert_edge(g, 5, 6);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 10);
    insert_edge(g, 7, 9);
    insert_edge(g, 7, 10);
    insert_edge(g, 8, 9);
    // �׷��� ���
    print_adj_list(g);


    // ���� �켱 Ž��
    printf("���� �켱 Ž��\n");
    dfs_list(g, 0, visited); // 0�� �������� ����
    printf("\n\n");

    // �ʺ� �켱 Ž��
    printf("�ʺ� �켱 Ž��\n");
    for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0; // �湮 ��� �ʱ�ȭ
    bfs_list(g, 0, visited); // 0�� �������� ����
    printf("\n");

    // �޸� ����
    for (i = 0; i < g->n; i++) {
        GraphNode* current = g->adj_list[i];
        GraphNode* next;
        while (current != NULL) {
            next = current->link;
            free(current);
            current = next;
        }
    }
    free(g);

    return 0;
}
