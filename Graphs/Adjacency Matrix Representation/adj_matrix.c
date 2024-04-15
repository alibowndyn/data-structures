#include <stdio.h>
#include <stdlib.h>

#include "adj_matrix.h"



/////////////////////////////////////////////////////////////////////////////////////////
//------  GRAPH STRUCT  ---------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////

typedef struct Graph {
    uint32_t num_nodes;
    uint8_t **mat;
} UGraph, Digraph;



/////////////////////////////////////////////////////////////////////////////////////////
//------  COMMON FUNCTIONS  -----------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Internal function for determining if g or g.mat is NULL
 *
 * @param g A pointer to a Graph object
 */
int is_graph_invalid(struct Graph *g)
{
    return g == NULL || g->mat == NULL;
}

/**
 * @brief Internal function to check if g is valid and whether
 *        u and v are both in the vertex set of g
 */
int are_guv_params_invalid(struct Graph *g, uint32_t u, uint32_t v)
{
    return is_graph_invalid(g) || u >= g->num_nodes || v >= g->num_nodes;
}


struct Graph *create_graph(uint32_t num_nodes, uint8_t is_directed)
{
    if (num_nodes == 0)
    {
        fprintf(stderr, "Cannot create an empty graph. Graph must have at least one node.");
        return NULL;
    }

    struct Graph *new = (struct Graph *)malloc( sizeof(struct Graph) );
    if (new == NULL)
    {
        fprintf(stderr, "Could not allocate memory.\n");
        return NULL;
    }

    new->num_nodes = num_nodes;

    new->mat = (uint8_t **)malloc(new->num_nodes * sizeof(uint8_t*));
    if (new->mat == NULL)
    {
        fprintf(stderr, "Could not allocate memory.\n");

        free(new);
        return NULL;
    }

    for (int i = 0; i < new->num_nodes; i++)
    {
        // if undirected, only fill in the lower triangular matrix
        new->mat[i] = (uint8_t *)calloc(
            is_directed ? new->num_nodes : (i + 1), sizeof(uint8_t));

        if (new->mat[i] == NULL)
        {
            fprintf(stderr, "Could not allocate memory.\n");
            destroy_graph(new);

            return NULL;
        }
    }

    return new;
}

void destroy_graph(struct Graph *g)
{
    if (is_graph_invalid(g))
        return;

    for (int i = 0; i < g->num_nodes; i++)
    {
        if (g->mat[i] != NULL)
            free(g->mat[i]);
    }

    free(g->mat);
    free(g);
}

int get_num_nodes(struct Graph *g)
{
    if (is_graph_invalid(g))
        return -1;

    return g->num_nodes;
}

int has_node(struct Graph *g, uint32_t u)
{
    if (is_graph_invalid(g))
        return 0;

    return u < g->num_nodes;
}



/////////////////////////////////////////////////////////////////////////////////////////
//------  DEFINITIONS FOR UNDIRECTED GRAPH  -------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////

void u_print_adj_matrix(UGraph *g)
{
    if (is_graph_invalid(g))
        return;

    for (int i = 0; i < g->num_nodes; i++)
    {
        int j;
        for (j = 0; j < i; j++)
        {
            printf("%d ", g->mat[i][j]);
        }

        // make it symmetrical
        printf("0 ");
        for (int k = j+1; k < g->num_nodes; k++)
        {
            printf("%d ", g->mat[k][i]);
        }

        puts("");
    }
}

void u_print_dot(UGraph *g)
{
    if (is_graph_invalid(g))
        return;

    puts("graph {");

    for (int i = 1; i < g->num_nodes; i++)
    for (int j = 0; j < i; j++)
    {
        if (g->mat[i][j] == 1)
            printf("%d -- %d;\n", i, j);
    }

    puts("}");
}

int u_get_num_edges(UGraph *g)
{
    if (is_graph_invalid(g))
        return -1;

    int edges = 0;

    for (int i = 0; i < g->num_nodes; i++)
    for (int j = 0; j < i+1; j++)
    {
        if (g->mat[i][j] == 1)
            edges++;
    }

    return edges;
}

int u_has_edge(UGraph *g, uint32_t u, uint32_t v)
{
    if (are_guv_params_invalid(g, u, v))
        return 0;

    // always check in the lower triangular matrix
    if (u < v)
        return g->mat[v][u];
    else
        return g->mat[u][v];
}

void u_add_edge(UGraph *g, uint32_t u, uint32_t v)
{
    // only fill in the lower triangular matrix
    if (!are_guv_params_invalid(g, u, v) && u != v)
    {
        g->mat[v][u] = 1;
    }
}

void u_remove_edge(UGraph *g, uint32_t u, uint32_t v)
{
    if (!are_guv_params_invalid(g, u, v))
    {
        if (u < v)
            g->mat[v][u] = 0;
        else
            g->mat[u][v] = 0;
    }
}



/////////////////////////////////////////////////////////////////////////////////////////
//------  DEFINITIONS FOR DIGRAPH -----------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////

void d_print_adj_matrix(Digraph *g)
{
    for (int i = 0; i < g->num_nodes; i++)
    {
        for (int j = 0; j < g->num_nodes; j++)
        {
            printf("%d ", g->mat[i][j]);
        }

        puts("");
    }
}

void d_print_dot(Digraph *g)
{
    if (is_graph_invalid(g))
        return;

    puts("digraph {");

    for (int i = 0; i < g->num_nodes; i++)
    for (int j = 0; j < g->num_nodes; j++)
    {
        if (g->mat[i][j] == 1)
            printf("%d -> %d;\n", i, j);
    }

    puts("}");
}

int d_get_num_edges(Digraph *g)
{
    if (is_graph_invalid(g))
        return -1;

    int edges = 0;

    for (int i = 0; i < g->num_nodes; i++)
    for (int j = 0; j < g->num_nodes; j++)
    {
        if (g->mat[i][j] == 1)
            edges++;
    }

    return edges;
}

int d_has_edge(Digraph *g, uint32_t u, uint32_t v)
{
    if (are_guv_params_invalid(g, u, v))
        return 0;

    return g->mat[u][v];
}

void d_add_edge(Digraph *g, uint32_t u, uint32_t v)
{
    if (!are_guv_params_invalid(g, u, v) && u != v)
    {
        g->mat[u][v] = 1;
    }
}

void d_remove_edge(Digraph *g, uint32_t u, uint32_t v)
{
    if (!are_guv_params_invalid(g, u, v))
        g->mat[u][v] = 0;
}
