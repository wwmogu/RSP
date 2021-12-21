#include <iostream>
#include <vector>

using namespace std;

// maximum number of vetices
#define MAXV 100

// edge node struct
struct edgenode {
    int y;                  // adjacency info
    int weight;             // edge weight
    struct edgenode *next;  // next edge 
} ;

// Graph class
class graph {
public:
    graph() ;
    graph(bool directed) ;
    void read_graph(bool directed) ;
    void insert_edge(int x, int y, bool directed) ;
    void print_graph() ;
private:
    // edgenode* edges[MAXV+1]; // ADM c version, which is the same as the below cpp version
    // vector<edgenode*> edges = vector<edgenode*>(MAXV+1, nullptr);   
    vector<edgenode*> edges;    // e.g. edges[0]: ->edgenode->edgenode->edgenode
                                //      edges[1]: ->edgenode
                                //      edges[2]: ->edgenode->edgenode

    int out_degree[MAXV+1];     // outdegree of each vertex
    int n_vertices;             // # of vertices in the graph
    int n_edges;                // # of edges in the graph
    bool directed;              // is the graph directed
} ;

/* ---------------- main ------------------- */
int main()
{
    bool directed = false ;
    // initialize the graph with the "directed" status
    graph *G = new graph(directed);

    // read the graph in
    G->read_graph(directed) ;
    cout << endl;

    // print the graph
    G->print_graph() ;

    return 0;
}
/* ---------------- main ------------------- */

graph::graph() {
    // initialize the number of edges and vertices to zero
    this->n_edges = this->n_vertices = 0;
    // initialize the directed false
    this->directed = false;

    // initialize all of the vectices out degree to zero
    for (int i=1; i<=MAXV; i++) {
        this->out_degree[i] = 0;
    }
    // initialize all of the "edge" to "empty"
    for (int i=0; i<=MAXV; i++) {
        this->edges.push_back(nullptr) ; 
    }
} 

graph::graph(bool directed) {
    // initialize the number of edges and vertices to zero
    this->n_edges = this->n_vertices = 0;
    // initialize the directed info as we want
    this->directed = directed;

    // initialize all of the vectices out degree to zero
    for (int i=1; i<=MAXV; i++) {
        this->out_degree[i] = 0;
    }
    // initialize all of the "edge" to "empty"
    for (int i=0; i<=MAXV; i++) {
        this->edges.push_back(nullptr) ; 
    }
}

void graph::read_graph(bool directed) {
    this->directed = directed;
    
    // read the graph from stdin
    cout << "Enter the number of vertices and the number of edges(vertices edges): " << endl;
    int n_vertices, n_edges;
    cin >> n_vertices >> n_edges;   // # vertices and # edges

    // set the number of vertices
    this->n_vertices = n_vertices ;

    int x, y;
    for (int i=1; i<=n_edges; i++) {
        cout << "Enter the edge(x-y):" << endl;
        cin >> x >> y;              // readin edges' two endpoint
        this->insert_edge(x, y, directed) ;
    }
}

void graph::insert_edge(int x, int y, bool directed) {
    cout << "insert: " << x << "->" << y << endl;
    edgenode* tmpnode = new edgenode;
    tmpnode->y = y;
    tmpnode->weight = 0;
    tmpnode->next = this->edges[x];

    this->edges[x] = tmpnode;          // edges[x]: tmp->original_node (the same as linked list inseart head)

    this->out_degree[x] ++ ;           // increment the number of vetex x's outdegree

    if (directed) {
        // directed, which means we only add x->y, so just increment the number of edges
        this->n_edges ++ ;
    }
    else {
        // undirected, x->y implies y->x, so recursivly add y->x
        insert_edge(y, x, true) ;
    }
}

void graph::print_graph() {
    edgenode* dummy ;
    for (int i=1; i<=this->n_vertices; i++) {
        cout <<"vertex " << i << " connected with: ";
        dummy = this->edges[i];

        // traversal all vertex connected to vertex i
        // exactly the same as traversal in a linked list
        while (dummy != nullptr) {
            cout << dummy->y << "->";
            dummy = dummy->next ;
        }
        cout << "NULL" ;
        cout << endl ;
    }
}
