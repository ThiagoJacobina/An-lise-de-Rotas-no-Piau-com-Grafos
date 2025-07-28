
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_CIDADES 10

const char *cidades[] = {
    "Corrente", "Gilbués", "Bom Jesus", "Floriano", "Oeiras",
    "Teresina", "Campo Maior", "Piripiri", "Luís Correia", "Parnaíba"
};

typedef struct Node {
    int vertice;
    struct Node *next;
} Node;

typedef struct Graph {
    Node *adj[MAX_CIDADES];
    int numVertices;
} Graph;

Node *createNode(int v) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Erro ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }
    newNode->vertice = v;
    newNode->next = NULL;
    return newNode;
}

Graph *GRAPHinit(int V) {
    Graph *G = (Graph *)malloc(sizeof(Graph));
    if (G == NULL) {
        perror("Erro ao alocar memória para o grafo");
        exit(EXIT_FAILURE);
    }
    G->numVertices = V;
    for (int i = 0; i < V; i++) {
        G->adj[i] = NULL;
    }
    return G;
}

void GRAPHinsertArc(Graph *G, int origem, int destino) {
    Node *newNode = createNode(destino);
    newNode->next = G->adj[origem];
    G->adj[origem] = newNode;
}

void GRAPHprint(Graph *G) {
    printf("--- Representacao do Grafo ---\n");
    for (int i = 0; i < G->numVertices; i++) {
        Node *temp = G->adj[i];
        printf("  %s (%d):", cidades[i], i);
        while (temp) {
            printf(" -> %s (%d)", cidades[temp->vertice], temp->vertice);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("----------------------------\n\n");
}

void freeGraph(Graph *G) {
    for (int i = 0; i < G->numVertices; i++) {
        Node *current = G->adj[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(G);
}

int path[MAX_CIDADES];
int pathIndex = 0;
int visited[MAX_CIDADES];

int shortestPathLen = -1;
int shortestPath[MAX_CIDADES];

int longestPathLen = -1;
int longestPath[MAX_CIDADES];

void findAllPaths(Graph *G, int u, int destino) {
    visited[u] = 1;
    path[pathIndex++] = u;

    if (u == destino) {
        printf("  Caminho encontrado: ");
        for (int i = 0; i < pathIndex; i++) {
            printf("%s", cidades[path[i]]);
            if (i < pathIndex - 1) {
                printf(" -> ");
            }
        }
        printf(" (Tamanho: %d)\n", pathIndex - 1);

        if (shortestPathLen == -1 || (pathIndex - 1) < shortestPathLen) {
            shortestPathLen = pathIndex - 1;
            for (int i = 0; i < pathIndex; i++) {
                shortestPath[i] = path[i];
            }
            for (int i = pathIndex; i < MAX_CIDADES; i++) {
                shortestPath[i] = -1;
            }
        }

        if ((pathIndex - 1) > longestPathLen) {
            longestPathLen = pathIndex - 1;
            for (int i = 0; i < pathIndex; i++) {
                longestPath[i] = path[i];
            }
            for (int i = pathIndex; i < MAX_CIDADES; i++) {
                longestPath[i] = -1;
            }
        }
    } else {
        Node *temp = G->adj[u];
        while (temp) {
            if (!visited[temp->vertice]) {
                findAllPaths(G, temp->vertice, destino);
            }
            temp = temp->next;
        }
    }

    pathIndex--;
    visited[u] = 0;
}

void findPathsFromCorrenteToParnaiba(Graph *G) {
    int origem = 0;
    int destino = 9;

    printf("--- Buscando Caminhos de %s para %s ---\n", cidades[origem], cidades[destino]);

    for (int i = 0; i < G->numVertices; i++) {
        visited[i] = 0;
        path[i] = -1;
        shortestPath[i] = -1;
        longestPath[i] = -1;
    }
    pathIndex = 0;
    shortestPathLen = -1;
    longestPathLen = -1;

    findAllPaths(G, origem, destino);

    printf("\n--- Resultados Finais ---\n");

    if (shortestPathLen != -1) {
        printf("Caminho Mais Curto (Tamanho: %d): ", shortestPathLen);
        for (int i = 0; i < MAX_CIDADES && shortestPath[i] != -1; i++) {
            printf("%s", cidades[shortestPath[i]]);
            if (shortestPath[i+1] != -1 && i < MAX_CIDADES -1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("Nenhum caminho encontrado de %s para %s.\n", cidades[origem], cidades[destino]);
    }

    if (longestPathLen != -1) {
        printf("Caminho Mais Longo (Tamanho: %d): ", longestPathLen);
        for (int i = 0; i < MAX_CIDADES && longestPath[i] != -1; i++) {
            printf("%s", cidades[longestPath[i]]);
            if (longestPath[i+1] != -1 && i < MAX_CIDADES -1) {
                printf(" -> ");
            }
        }
        printf("\n");
    }
    printf("---------------------------\n");
}

int main() {
    Graph *G = GRAPHinit(MAX_CIDADES);

    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 2, 3);
    GRAPHinsertArc(G, 3, 4);
    GRAPHinsertArc(G, 4, 5);
    GRAPHinsertArc(G, 5, 6);
    GRAPHinsertArc(G, 6, 7);
    GRAPHinsertArc(G, 7, 8);
    GRAPHinsertArc(G, 8, 9);
    GRAPHinsertArc(G, 5, 9);
    GRAPHinsertArc(G, 2, 5);

    GRAPHprint(G);
    findPathsFromCorrenteToParnaiba(G);
    freeGraph(G);

    return 0;
}
