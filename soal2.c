#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int dest;
    struct Edge* next;
} Edge;

typedef struct Graph {
    int node_count;
    Edge** nodes;
} Graph;

void create_graph(Graph* g, int node_count) {
    g->node_count = node_count;
    g->nodes = calloc(node_count, sizeof(*g->nodes));
}

void add_edge(Graph* g, int src, int dest) {
    Edge* edge = malloc(sizeof(*edge));
    edge->dest = dest;
    edge->next = g->nodes[src];
    g->nodes[src] = edge;
}

int detect_cycle_dfs(Edge* node_edges, int vert, int* visited, int* rec_stack) {
    if(rec_stack[vert])
        return 1;

    if(visited[vert])
        return 0;

    visited[vert] = 1;
    rec_stack[vert] = 1;
    
    for(Edge* edge = node_edges; edge != NULL; edge = edge->next) {
        if(detect_cycle_dfs(node_edges, edge->dest, visited, rec_stack)) {
            return 1;
        }
    }

    rec_stack[vert] = 0;
    return 0;
}

int detect_cycle(Graph* g) {
    int* visited = calloc(g->node_count, sizeof(*visited));
    int* rec_stack = calloc(g->node_count, sizeof(*visited));

    for(int vert = 0; vert < g->node_count; ++vert) {
        if(!visited[vert] && detect_cycle_dfs(g->nodes[vert], vert, visited, rec_stack)) {
            free(visited);
            free(rec_stack);
            return 1;
        }
    }

    free(visited);
    free(rec_stack);
    return 0;
}

int main(void) {
    Graph g;
    int tmp;
    scanf("%d", &tmp);
    create_graph(&g, tmp);
    scanf("%d", &tmp);

    for(int i = 0; i < tmp; ++i) {
        int src, dest;
        scanf("%d", &src);
        scanf("%d", &dest);
        add_edge(&g, src, dest);
    }

    if(detect_cycle(&g)) {
        printf("TIDAK BISA\n");
    }
    else {
        printf("BISA\n");
    }

    return 0;
}
