## Vector amortized time

Usage:

    push_back() normally takes O(1) time. However, the “double” behavior happens not very often but takes O(n) time to copy over. How can we measure the time complexity for it?

    The Amortized analysis is the trick.

How it works and Big-Oh:

    Only consider the time needed for copy: 1 + 2 + 4 + 8 + ... + x ~= 2x

    Then the amortized time for each push_back() will be (2x/x), the time complicity is O(1).

## Linked List

```cpp
struct Node {
    int var;
    Node *next;
};
```

- Singly Linked List:

  `Node1 -> Node2 -> Node3 -> nullptr`

  `search(var)`: O(n)

  `insert_front(var)`: O(1), if linked list is unsorted.

  `delete(var)`: O(n), because we need to search the predecessor of the var first.

- [Linked-List_Implementation](https://github.com/a1779748/RSP/tree/main/LinkedList)

## Stacks and Queues

- Stacks
  - LIFO (last in first out)
- Queues
  - FIFO (first in first out)

## Binary Tree

```cpp
struct Node {
    int var;
    Node *left;
    Node *right;
};
```

- BST:

  `traversal()`: O(number of node)

  `search(var)`: O(the height of the BST)

  `insert(var)`: O(search) + O(1)insert = O(the height of the BST)

  `delete(var)`: O(search) + O(1)delete = O(the height of the BST)

- [BST-Implementation](https://github.com/a1779748/RSP/tree/main/BinarySearchTree)

## Balanced Binary Search Tree

* Usage:

  improve the performance for normal BST.(since when a BST is only have one side[unbalanced], make it no difference with search in a list→O(n))

* How it works:

  For both AVL and Red-Black Trees, we maintain some rules which will keep the BST balanced.

  **AVL:**

  1. maintain a balance factor{abs(#left - #right)} for each node, when “balance factor > 1” we rebalancing the BST by rotating three node.

  **Red-Black:**

  1. every node has a color(red or black)

  2. the root is always black

  3. no adjacent red nodes

  4. leaf nodes are black

  5. from each root to every leave, # of black nodes is the same.

     when the above rules are violated, we perform the rotate operation to balance the tree.

* Big-Oh: (log n is the height of tree, since the trees are balanced)

  **Search:**
  	
		AVL: avg→O(logn) worst→O(logn)
	
		Red-Black: avg→O(logn) worst→O(logn)
  
  **Insert:**
  	
		AVL: avg→O(logn) worst→O(logn)
	
		Red-Black: avg→amortizedO(1) worst→O(logn)
  
  **Delete:**
  	
		AVL: avg→O(logn) worst→O(logn)
	
		Red-Black: avg→amortized O(1) worst→O(logn)

Notes for cpp: map, multimap, multiset in cpp are implemented by Red-Black tree.

## Heap (priority queue in cpp)

- `get_min()` or `get_max()` -> O(1)
- `remove_top()` -> O(logn)
  1. replace top element with the last element in the heap: O(1), array heap
  2. bubble-down: O(logn)
- `insert()` -> O(logn)
  1. insert to the bottom (the last empty slot in the "heap array"): O(1)
  2. bubble-up: O(logn), since binary heap is a complete binary tree which tree height is log(n)

## Tries(prefix tree, n-ary tree)

- Usage: 

  improve string search time to O(length of the string)

* How it works:

  store each character of a string in a tree, and each node will have an additional flag to indicate if the current position is the end of a string.

  for example:

  	The word `apple` would be stored in a path like a(no)→p(no)→p(no)→l(no)→e(no)→_(yes)

  	when we search along this path, when we reach `_` we will know the characters before will form a “word”.

* Big-Oh:

  find(): O(length of the string)

  insert(): O(length of the string)

## Graph

- Data Structure
  - Adjacency List
    - [Implementation](https://github.com/a1779748/RSP/blob/main/Graph/RepresentGraph/ADM-AdjacencyList.cpp)
  - Adjacency Matrix
    - [implementation](https://github.com/a1779748/RSP/blob/main/Graph/RepresentGraph/easyGraph.cpp)
- BFS (using queue)
  - O(vertices + edges) on adjacency list
  - O(vertices^2) on adjacency matrix
  - [Implementation](https://github.com/a1779748/RSP/blob/main/Graph/BFS)
  - application
    - shortest path **on equal weighted or unweighted graph**
    - finding path
    - Find **connected components**, all edges that are discovered are in the same components
    - Make the **bipartite graph**, check if the graph is **a bipartite graph**
- DFS (using stack)
  - O(vertices + edges) on adjacency list
  - O(vertices^2) on adjacency matrix
  - [Implementation](https://github.com/a1779748/RSP/tree/main/Graph/DFS)
  - application
    - finding path
    - finding cycles
    - Topological sorting on **directed graph**
    - Strongly connected components on **directed graph**

## MST (on weighted graph)

- What is MST:

  The least-cost path touches every vertex. OR

  A tree which includes all of the Graph’s vertices, and this tree has the minimum weight

- ~~Prim’s algorithm:~~ (not finished)

  * How it works:
    1. Choose a start vertex and add it to the spanning tree.
    2. Find the shortest connection between the spanning tree and the non-spanning tree, then add it to the spanning tree.
    3. repeat step 2 until all of the vertices are in the spanning tree.

  * ~~Big-Oh:~~

    Normally: O(V^2)

    by keeping the non-spanning tree “vertex” into a binary heap, the time complexity will be O((E + V)logV).

- Kruskal’s algorithm:

  * How it works:
    1. sort all of the edges of graph G (Ascending order)
    2. find the smallest edge(not in the spanning tree) and add it to the spanning tree if the new edge will not form a circle, otherwise, skip this edge.
    3. repeat step 2 until all of the vertices are covered (or there are n-1 edges in the spanning tree).

  * Big-Oh:

    1. Sort will take O(ElogE)

    2. Loop each edge will take O(E), and we will use Union-Find to “check the circle” and add one edge into the spanning tree, it will take O(logV) for `find()` operation to check circle + O(logV) for `union()` to add the new edge to the spanning tree.

       In total step2 will take O(ElogV)

    3. Therefore, the entire time for Kruskal’s algorithm is O(ElogE) + O(ElogV)

       From [wikipedia]([]()), I know that O(ElogE) = O(ElogV)

       So The time complexity of this algorithm is either O(ElogE) or O(VlogV)

## Union Find

* Usage: 
  * Could be used in Kruskal’s algorithm

* How it works:

  ~~use a parent array to store each element’s parent, if the two elements have the same root they will be in the same set.~~

  Union: merge two disjoint sets together

  Find: find the element in which set(the root of the element).

* Big-Oh:

  Union(): O(logn)

  Find(): O(logn)

## Shortest Path (on weighted graph)

- ~~Dijkstra (greedy)~~ (not finished)
  - O(vertices * edges) <- normal,same as prim's
  - O(E + VlogV) <- optimal using priority queue to handle Minimum Unselected Distance part (V vertices * each insertion into heap logV) same as prim's
- All-Pairs Shortest Path (Floyd-Warshall)
  - O(V^3)
- Bellman-Ford

## Quick Sort and Quick Select algorithm

- Quick Sort

  - O(nlogn) if we choose the pivot properly
  - O(n^2) if the pivot do not split the array in each round
  - [Implementation](https://github.com/a1779748/RSP/blob/main/Sorting/Quicksort.cpp)

- Quick Selection

  - Usage: 

    find the kth smallest element in an unordered list.

  - How it works: 

    - Similar to quicksort, but in each recursion step, it only goes in one direction(the path might have the kth smallest element). So, on average it is quicker than quicksort(O(nlogn).

  - Big-Oh: n + n/2 + n/4 + n/8 + ... + 1 ~= 2n ⇒ O(n)

    - Notes for quicksort: 

      it’s big-O is O(nlogn), **n** means there are **n** element and **logn** means, it will split **logn** times.

      So write in mathematic: n + (n/2 + n/2) + ( (n/4+n/4) + (n/4+n/4) ) + ... + n*(n/n) = n * logn ⇒ O(nlogn)

## Merge Sort

[implementation](https://github.com/a1779748/RSP/blob/main/Sorting/Mergesort.cpp)

## Bit Manipulation

`bitwise XOR ^`: 1 if two bits are different

`bitwise And &`: 1 iff both bits are 1

`bitwise Or |`: 1 if any of two bits is 1

Arithmetic: right shift by filling in the sign bit(left most bit)

Logical: right shift by filling in the 0s

## Singleton Design Pattern

* Requirement:

  One class has only one ‘single’ instance.

* How in cpp:

  Hide the constructor and make a public get function to create the single instance of the class. e.g. `getInstance()`

* Example(CPP from Wikipedia):

```cpp
class Singleton {
 public:
	// make a public get function to create the single instance
  static Singleton& GetInstance() {
    // Allocate with `new` in case Singleton is not trivially destructible.
    static Singleton* singleton = new Singleton();
    return *singleton;
  }

 private:
	// hide constructor
  Singleton() = default;

  // Delete copy/move so extra instances can't be created/moved.
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;
};
```

* CTCI concept:

	The Singleton pattern ensures that a class has only one instance and ensures access to the instance through the application. (CTCI)

## Factory Design Pattern

* Requirement:

  Provide the interface of the class method and let instance or the child class determine what functionality the method should do.

* How in cpp:

  Let the base class be an abstract class(base class with pure virtual function).

  Then design the functionality of the pure virtual function in its child class.

* Example(CPP from tutorialspoint):

```cpp
class Base {
   public:
      virtual void s() = 0; // Pure Virtual Function
};

class child:public Base {
   public:
      void s() {
         cout << "Virtual Function in child class\\n";
      }
};
```

* CTCI concept:

	The Factory Method offers an interface for creating an instance of a class, with its subclasses deciding which class to instantiate. (CTCI)

## Some other useful website

[Algorithm visualization](https://visualgo.net/en)
