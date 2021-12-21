#include <iostream>
#include <vector>

using namespace std;

// the fake Adjacency List Graph
vector<int> fakeAdjacencyList[6] ;

// Adjacency Matrix
// c -> bool graph[5][5];
vector<vector<bool>> AdjacencyMatrix(6, vector<bool>(6, false)) ;

void init_list_graph() ;
void show_list_graph() ;
void init_matrix_graph() ;
void show_matrix_graph() ;

/* -------------- main ------------- */
int main()
{
    /* initialize the list graph*/
    init_list_graph();
    /* show the list graph */
    cout << "--Adjacency List graph--\n";
    show_list_graph();
    cout << endl;

    /* initialize the matrix graph*/
    init_matrix_graph() ;
    /* show the matirx graph */
    cout << "--Adjacency Matrix graph--\n";
    show_matrix_graph() ;

    return 0;
}
/* -------------- main ------------- */

void init_list_graph() {
    /* 
        1----2 
        |  / | \
        | /  |   3
        |/   | /
        5----4
    */

    // 1: 2->5
    fakeAdjacencyList[1].push_back(2) ;
    fakeAdjacencyList[1].push_back(5) ;
    // 2: 1->5->4->3
    fakeAdjacencyList[2].push_back(1) ;
    fakeAdjacencyList[2].push_back(5) ;
    fakeAdjacencyList[2].push_back(4) ;
    fakeAdjacencyList[2].push_back(3) ;
    // 3: 2->4
    fakeAdjacencyList[3].push_back(2) ;
    fakeAdjacencyList[3].push_back(4) ;
    // 4: 3->2->5
    fakeAdjacencyList[4].push_back(3) ;
    fakeAdjacencyList[4].push_back(2) ;
    fakeAdjacencyList[4].push_back(5) ;
    // 5: 1->2->4
    fakeAdjacencyList[5].push_back(1) ;
    fakeAdjacencyList[5].push_back(2) ;
    fakeAdjacencyList[5].push_back(4) ;
    return ;
}
void show_list_graph() {
    int vertices = 5;
    for (int i=1; i<=vertices; i++) {
        cout << "vertex " << i << " connected with: ";
        for (auto v : fakeAdjacencyList[i]) {
            cout << v << "->";
        }
        cout << "NULL" << endl;
    }
    return ;
}



void init_matrix_graph() {
    /* 
        1----2 
        |  / | \
        | /  |   3
        |/   | /
        5----4
    */
    AdjacencyMatrix[1][2] = AdjacencyMatrix[1][5] = true ;
    AdjacencyMatrix[2][1] = AdjacencyMatrix[2][5] = AdjacencyMatrix[2][4] = AdjacencyMatrix[2][3] = true;
    AdjacencyMatrix[3][2] = AdjacencyMatrix[3][4] = true ;
    AdjacencyMatrix[4][5] = AdjacencyMatrix[4][2] = AdjacencyMatrix[4][3] = true;
    AdjacencyMatrix[5][1] = AdjacencyMatrix[5][2] = AdjacencyMatrix[5][4] = true;
    return ;
}
void show_matrix_graph() {
    for (int i=1; i<=5; i++) {
        for (int j=1; j<=5; j++) {
            cout << AdjacencyMatrix[i][j] << " " ;
        }
        cout << endl;
    }
    cout << endl;

    return ;
}
