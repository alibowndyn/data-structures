#include <stdio.h>
#include <stdlib.h>

#include "adj_matrix.h"


int main()
{
    Digraph *g = (Digraph *)create_graph(5, 1);
    UGraph *ug = (UGraph *)create_graph(5, 0);

    d_add_edge(g, 0, 1);
    d_add_edge(g, 0, 2);
    d_add_edge(g, 0, 3);
    d_add_edge(g, 1, 2);
    d_add_edge(g, 1, 3);
    d_add_edge(g, 2, 4);
    d_add_edge(g, 4, 2);
    d_add_edge(g, 4, 4); // no self loops
    d_add_edge(g, 0, 1); // no multiple edges
    d_add_edge(g, 0, 7); // vertex not in vertex set
    d_add_edge(g, 7, 0); // vertex not in vertex set

    u_add_edge(ug, 0, 1);
    u_add_edge(ug, 0, 2);
    u_add_edge(ug, 0, 3);
    u_add_edge(ug, 1, 2);
    u_add_edge(ug, 1, 3);
    u_add_edge(ug, 2, 4);
    u_add_edge(ug, 2, 2); // no self loops
    u_add_edge(ug, 4, 2); // no multiple edges
    u_add_edge(ug, 0, 1); // redundant
    u_add_edge(ug, 0, 7); // vertex not in vertex set
    u_add_edge(ug, 7, 0); // vertex not in vertex set

    printf("digraph edges: %d\nundirected graph edges: %d\n\n",
        d_get_num_edges(g), u_get_num_edges(ug));


    u_print_adj_matrix(ug);
    u_print_dot(ug);

    puts("\n\n");
    d_print_adj_matrix(g);
    d_print_dot(g);


    u_remove_edge(ug, 3, 1);
    u_remove_edge(ug, 1, 0);
    u_remove_edge(ug, 1, 3); // already removed
    u_remove_edge(ug, 5, 3); // invalid
    u_remove_edge(ug, 5, 3); // invalid

    puts("\n\nundirected removed:");
    u_print_adj_matrix(ug);
    u_print_dot(ug);


    d_remove_edge(g, 1, 0);
    d_remove_edge(g, 2, 4);
    d_remove_edge(g, 1, 3); // already removed
    d_remove_edge(g, 5, 3); // invalid
    d_remove_edge(g, 5, 3); // invalid

    puts("\n\ndirected removed:");
    d_print_adj_matrix(g);
    d_print_dot(g);


    printf("\nAfter removal:\n  digraph edges: %d\n  undirected graph edges: %d\n\n",
        d_get_num_edges(g), u_get_num_edges(ug));



    destroy_graph(g);
    destroy_graph(ug);
    return EXIT_SUCCESS;
}