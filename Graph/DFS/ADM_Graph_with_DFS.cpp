#include <iostream>
#include <vector>
#include <stack>    // DFS, non-recursion version

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
    /* DFS related */
    void init_dfs() ;
    // process = 0 means do nothing, =1 process_vertex_early, =2 process_edge, =3 do 1 and 2
    void dfs_non_recursive(int start, int process) ;    // exactly the same as bfs, but use stack to hold the "will" visited vertex
    void dfs(int start, int process) ;                  // The ADM version recursive version dfs
    void process_vertex_late(int v) ;
    void process_vertex_early(int v) ;
    void process_edge(int x, int y) ;
    int get_dfs_edge_counter() ;
    void find_dfs_path(int start, int end) ;            // print the path after dfs
    void print_status() ;                               // print each vertex's parent, entry/exit time, after perfor the dfs()
    /* DFS related */
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

    /* DFS related */
    bool finished;              // used for terminate the dfs in advance
    int time;                   // "clock", it will tick each time enter or exit a vertex
    bool processed[MAXV+1];     // 0 if vertex[i] have not been processed, otherwise 1
    bool discovered[MAXV+1];    // 0 if vertex[i] have not been discovered, otherwise 1
    int parent[MAXV+1];         // parent[i] store the previously visited node of node i
    int entry_time[MAXV+1];     // the entry time of the ith vertex
    int exit_time[MAXV+1];      // the exit time of the ith vertex
    int dfs_edge_counter;       // count the number of edges during the bfs
    /* DFS related */
} ;

/* --------------------------- main --------------------- */
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

    cout << "start DFS" << endl;
    // do a dfs on graph G, start from vertex 1
    G->init_dfs();
    G->dfs(1, 1);
    // G->dfs_non_recursive(1, 1) ;              // process vertices
    cout << endl;
    cout << "-----\tThe 'Status' after perform the recursive DFS\t-----" << endl;
    G->print_status() ;

    // G->init_dfs();
    // G->dfs(1, 2) ;  // process edges
    // G->dfs_non_recursive(1, 2) ;

    // G->init_dfs();
    // G->dfs(1, 3) ;  // process both vertices and edges
    // G->dfs_non_recursive(1, 3) ;

    // cout << endl << "the path from 1 to 3 is : ";
    // G->find_dfs_path(1, 3) ;
    // cout << endl;

    return 0;
}
/* --------------------------- main --------------------- */

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


/* DFS related */
void graph::init_dfs() {
    for (int i = 0; i<=this->n_vertices; i++) {
        this->processed[i] = this->discovered[i] = false ;
        this->parent[i] = -1;
        this->entry_time[i] = this->exit_time[i] = 0;
    }
    this->dfs_edge_counter = 0;
    this->finished = false ;
    this->time = 0;
    return ;
}
// process = 0 means do nothing, =1 process_vertex_early, =2 process_edge, =3 do 1 and 2
void graph::dfs_non_recursive(int start, int process) {
    if (process == 0) return ;
    stack<int> stk;             // store the vertices to visit
    int cur;                    // current vertex
    int successor;              // next visited vertex of current vertex
    edgenode *dummy;            // will be used for traversaling the adjacent list

    // put the first node to the stack, and mark it as discovered
    stk.push(start) ;
    this->discovered[start] = true;

    // futher dfs discover
    while (!stk.empty()) {
        // get the top element of the stack
        cur = stk.top() ;
        stk.pop() ;
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
                stk.push(successor) ;
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
// process = 0 means do nothing, =1 process_vertex_early, =2 process_edge, =3 do 1 and 2
void graph::dfs(int start, int process) {
    if (process == 0) return ;
    
    int successor;              // next visited vertex of current vertex
    edgenode *dummy;            // will be used for traversaling the adjacent list

    // terminate dfs in advance
    if (this->finished) return ;

    // mark current vertex as discovered
    discovered[start] = true;
    // clock ticks
    this->time ++ ;
    // set the entry time for current discovered vertex
    this->entry_time[start] = this->time ;

    // (**optional) process this discovered vertex
    if (process == 1 || process == 3)
        this->process_vertex_early(start) ;

    // futher dfs discover
    dummy = this->edges[start] ;
    while (dummy != nullptr) {
        successor = dummy->y;
        if (!this->discovered[successor]) {
            parent[successor] = start;
            // (**optional) process the edge current->successor
            if (process == 2 || process == 3) {
                this->process_edge(start, successor) ;
            }
            this->dfs(successor, process) ;
        }
        else if ( (!this->processed[successor] && this->parent[start] != successor) || this->directed ) {
            // (**optional) process the edge current->successor
            if (process == 2 || process == 3) {
                this->process_edge(start, successor) ;
            }
        }

        // terminate dfs in advance
        if (finished) return ;

        dummy = dummy->next;
    }

    // (**optional)
    this->process_vertex_late(start) ;

    // clock ticks
    this->time ++ ;
    // set the exit time for current processed vertex
    exit_time[start] = time;
    // mark current processed vertex
    processed[start] = true;
}

void graph::print_status() {
    cout << "Vertex:\t";
    for (int i=1; i<=this->n_vertices; i++) {
        cout << i << "\t" ;
    }
    cout << endl;

    cout << "Parent:\t";
    for (int i=1; i<=this->n_vertices; i++) {
        cout << this->parent[i] << "\t" ;
    }
    cout << endl;

    cout << "Entry:\t";
    for (int i=1; i<=this->n_vertices; i++) {
        cout << this->entry_time[i] << "\t" ;
    }
    cout << endl;

    cout << "Exit:\t";
    for (int i=1; i<=this->n_vertices; i++) {
        cout << this->exit_time[i] << "\t" ;
    }
    cout << endl;
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
    this->dfs_edge_counter ++;
}

int graph::get_dfs_edge_counter() {
    return this->dfs_edge_counter ;
}
// ADM 7.6.2 Finding Paths
void graph::find_dfs_path(int start, int end) {
    if (start == end || end == -1) {
        cout << endl << start;
    }
    else {
        this->find_dfs_path(start, this->parent[end]);
        cout << " " << end;
    }
    return ;
}
/* DFS related */