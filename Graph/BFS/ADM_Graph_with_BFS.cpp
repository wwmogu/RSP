#include <iostream>
#include <vector>
#include <queue>    // Used in bfs

using namespace std;

// maximum number of vetices
#define MAXV 100

struct edgenode {
    int y;                  // adjacency info
    int weight;             // edge weight
    struct edgenode *next;  // next edge 
} ;

class graph {
public:
    graph() ;
    graph(bool directed) ;
    void read_graph(bool directed) ;
    void insert_edge(int x, int y, bool directed) ;
    void print_graph() ;
    /* BFS related */
    void init_bfs() ;
    void bfs(int start, int process) ;  // process = 0 means do nothing, =1 process_vertex_early, =2 process_edge, =3 do 1 and 2
    void process_vertex_late(int v) ;
    void process_vertex_early(int v) ;
    void process_edge(int x, int y) ;
    int get_bfs_edge_counter() ;
    void find_bfs_path(int start, int end) ;  // print the path after bfs
    /* BFS related */
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

    /* BFS related */
    bool processed[MAXV+1];     // 0 if vertex[i] have not been processed, otherwise 1
    bool discovered[MAXV+1];    // 0 if vertex[i] have not been discovered, otherwise 1
    int parent[MAXV+1];         // parent[i] store the previously visited node of node i
    int bfs_edge_counter;       // count the number of edges during the bfs
    /* BFS related */
} ;


int main()
{
    bool directed = false ;
    // initialize the graph with the "directed" status
    graph *G = new graph(directed);

    // read the graph in
    /* 
        1----2 
        |  / | \
        | /  |   3
        |/   | /
        5----4
    */
    G->read_graph(directed) ;
    cout << endl;

    // print the graph
    G->print_graph() ;
    cout << endl;

    cout << "start BFS" << endl;
    // do a bfs on graph G, start from vertex 1
    G->init_bfs();
    G->bfs(1, 1) ;              // process vertices
    cout << endl << "the path from 1 to 3 is : ";
    G->find_bfs_path(1, 3) ;    // print path from start to end
    cout << endl;
    cout << endl << "the path from 5 to 3 is : ";
    G->find_bfs_path(5, 3) ;    // print path from start to end
    cout << endl;

    // G->init_bfs();
    // G->bfs(1, 2) ;  // process edges

    // G->init_bfs();
    // G->bfs(1, 3) ;  // process both vertices and edges

    // G->find_bfs_path(start, end) ;

    return 0;
}

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
        this->insert_edge(y, x, true) ;
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


/* BFS related */
void graph::init_bfs() {
    for (int i = 0; i<=this->n_vertices; i++) {
        this->processed[i] = this->discovered[i] = false ;
        this->parent[i] = -1;
    }
    this->bfs_edge_counter = 0;
    return ;
}
// process = 0 means do nothing, =1 process_vertex_early, =2 process_edge, =3 do 1 and 2
void graph::bfs(int start, int process) {
    if (process == 0) return ;
    queue<int> q;               // store the vertices to visit
    int cur;                    // current vertex
    int successor;              // next visited vertex of current vertex
    edgenode *dummy;            // will be used for traversaling the adjacent list

    // put the first node to the queue, and mark it as discovered
    q.push(start) ;
    this->discovered[start] = true;

    // futher bfs discover
    while (!q.empty()) {
        // dequeue the front element of the queue
        cur = q.front() ;
        q.pop() ;
        // (**optional) process this discovered vertex and mark it as processed
        if (process == 1 || process == 3)
            this->process_vertex_early(cur) ;
        this->processed[cur] = true ;
        // discovered connected vertex
        dummy = this->edges[cur] ;
        while (dummy != nullptr) {
            // current vetex will become the previously visited node
            successor = dummy->y;
            // (**optional) process the edge cur->successor
            if (process == 2 || process == 3) {
                if (!this->processed[successor] || this->directed) {
                    this->process_edge(cur, successor) ;
                }
            }
            // if the successor has not been discovered, push it into queue and mark it as discovered
            if (this->discovered[successor] != true) {
                q.push(successor) ;
                this->discovered[successor] = true;
                // also set the parent for successor vertex (it will be helpful when we want the path of the dfs)
                this->parent[successor] = cur;
            }
            // move to next connected vertex
            dummy=dummy->next;
        }
        // (**optional)
        this->process_vertex_late(cur) ;
    }
}
void graph::process_vertex_late(int v) {
    // as ADM suggest, since processing vertex on entry, so do nothing after process
    return ;
}
void graph::process_vertex_early(int v) {
    // do something on current visiting vertex;
    // e.g. print the current visiting vertex
    cout << "vertex " << v << " has been processed\n";

    return ;
}

void graph::process_edge(int x, int y) {
    // do something on current visiting edge
    // e.g. print the edge
    cout << "edge " << x << " -> " << y << " has been processed\n";
    // e.g. count the number of edges has been processed
    this->bfs_edge_counter ++;
}

int graph::get_bfs_edge_counter() {
    return this->bfs_edge_counter ;
}
// ADM 7.6.2 Finding Paths
void graph::find_bfs_path(int start, int end) {
    if (start == end || end == -1) {
        cout << endl << start;
    }
    else {
        this->find_bfs_path(start, this->parent[end]);
        cout << " " << end;
    }
    return ;
}
/* BFS related */