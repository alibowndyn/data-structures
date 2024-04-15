#ifndef _ADJ_MATRIX
#define _ADJ_MATRIX

#include <inttypes.h>



/////////////////////////////////////////////////////////////////////////////////////////
//-----  TYPEDEFS  --------------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////

/// @brief An object representing a simple undirected graph
typedef struct Graph UGraph;

/// @brief An object representing a simple directed graph
typedef struct Graph Digraph;



/////////////////////////////////////////////////////////////////////////////////////////
//------  DECLARATIONS FOR COMMON FUNCTIONS  ------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Creates a Graph object with num_nodes nodes
 *
 * @param num_nodes The number of nodes in the graph
 * @param is_directed Whether the graph is directed or undirected
 * @return A pointer to a Graph object or NULL if there was an error
 */
struct Graph *create_graph(uint32_t num_nodes, uint8_t is_directed);

/**
 * @brief Frees the resources associated with g
 *
 * @param g A pointer to a Graph object
 */
void destroy_graph(struct Graph *g);

/**
 * @brief Returns the number of nodes in g
 *
 * @param g A pointer to a Graph object
 * @return The number of nodes in g or -1 if g is NULL
 */
int get_num_nodes(struct Graph *g);

/**
 * @brief Checks if u is in the vertex set of g
 *
 * @param g A pointer to a Graph object
 * @param u The node to check
 */
int has_node(struct Graph *g, uint32_t u);




/////////////////////////////////////////////////////////////////////////////////////////
//-----  DECLARATIONS FOR UNDIRECTED GRAPH  -------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Prints the adjacency matrix representation of the undirected graph g
 *
 * @param g A pointer to a UGraph object
 */
void u_print_adj_matrix(UGraph *g);

/**
 * @brief Prints the DOT language representation of the undirected graph g,
 *        which can be used by various Graphviz tools
 *
 * @param g A pointer to a UGraph object
 */
void u_print_dot(UGraph *g);

/**
 * @brief Returns the number of edges in the undirected graph g
 *
 * @param g A pointer to a UGraph object
 * @return The number of edges in g or -1 if g is NULL
 */
int u_get_num_edges(UGraph *g);

/**
 * @brief Checks if the undirected graph g contains the edge {u, v}
 *
 * @param g A pointer to a UGraph object
 * @param u One of the nodes of the edge
 * @param v The other node in the edge
 */
int u_has_edge(UGraph *g, uint32_t u, uint32_t v);

/**
 * @brief Adds an edge to the graph connecting u and v
 *
 * @param g A pointer to a UGraph object
 * @param u One of the nodes of the edge
 * @param v The other node in the edge
 */
void u_add_edge(UGraph *g, uint32_t u, uint32_t v);

/**
 * @brief Removes the edge connecting u and v from the undirected graph g
 *
 * @param g A pointer to a UGraph object
 * @param u One of the nodes of the edge
 * @param v The other node in the edge
 */
void u_remove_edge(UGraph *g, uint32_t u, uint32_t v);



/////////////////////////////////////////////////////////////////////////////////////////
//-----  DECLARATIONS FOR DIGRAPH  ----------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Prints the adjacency matrix representation of the digraph g
 *
 * @param g A pointer to a Digraph object
 */
void d_print_adj_matrix(Digraph *g);

/**
 * @brief Prints the DOT language representation of the directed graph g,
 *        which can be used by various Graphviz tools
 *
 * @param g A pointer to a Digraph object
 */
void d_print_dot(Digraph *g);

/**
 * @brief Returns the number of edges in the directed graph g
 *
 * @param g A pointer to a Digraph object
 * @return The number of edges in g or -1 if g is NULL
 */
int d_get_num_edges(Digraph *g);

/**
 * @brief Checks if the digraph g contains the edge (u, v)
 *
 * @param g A pointer to a Digraph object
 * @param u The initial vertex
 * @param v The terminal vertex
 */
int d_has_edge(Digraph *g, uint32_t u, uint32_t v);

/**
 * @brief Adds a directed edge to g from u to v
 *
 * @param g A pointer to a Digraph object
 * @param u The initial vertex
 * @param v The terminal vertex
 */
void d_add_edge(Digraph *g, uint32_t u, uint32_t v);

/**
 * @brief Removes the directed edge (u, v) from g
 *
 * @param g A pointer to a Digraph object
 * @param u The initial vertex
 * @param v The terminal vertex
 */
void d_remove_edge(Digraph *g, uint32_t u, uint32_t v);



#endif
