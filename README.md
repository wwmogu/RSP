# Ravi's Study Program

Duration: 2021-2022 Summer Holiday.
Aim: Getting offer from FAAMG.

----



# A summary of Beginner Tasks

## Vector amortized time

When the vast majority of the operation is taking $\mathcal{O}(1)$ time, and other operation take much longer than vast majority, we could use amortized analysis.

Since we need to double the size and copy current element into new double sized array , when vector is full. 

The total time we need for doubling the size is $1 + 2 + 4 + 8 + 16 +\  ...\ +x \approx 2x$.

The amortized time said that we need $\frac{2x}{x}$ time for each adding, which is $\mathcal{O}(1)$.



## Linked List

```cpp
struct Node {
    int var;
    Node *next;
};
```

* Singly Linked List:

   `Node1 -> Node2 -> Node3 -> nullptr`

  `search(var)`: $\mathcal{O}(n)$

  `insert_front(var)`: $\mathcal{O}(1)$, if linked list is unsorted.

  `delete(var)`: $\mathcal{O}(n)$, because we need to search the predecessor of the var first.

* [Linked-List_Implementation](https://github.com/a1779748/RSP/tree/main/LinkedList)



## Stacks and Queues

* Stacks
  * LIFO (last in first out)
* Queues
  * FIFO (first in first out)



## Binary Tree

```cpp
struct Node {
    int var;
    Node *left;
    Node *right;
};
```

* BST:

  `traversal()`: O(number of node)

  `search(var)`: O(the height of the BST)

  `insert(var)`: O(search) + O(1)insert = O(the height of the BST)

  `delete(var)`: O(search) + O(1)delete = O(the height of the BST)

* [BST-Implementation](https://github.com/a1779748/RSP/tree/main/BinarySearchTree)



## Balanced Binary Search Tree
* AVL 

  AVL balance: the $|balance\  factor| < 2$, which means the height of the tree is $\approx log(n)$

  > balance factor = $|(height\ \ of\ \ left\ \ child) - (height\ \ of\ \ right\ \ child)|$

  `search(var)`: $\mathcal{O}(log(n))$

  `insert(var)`: O(search) + O(balance/swap nodes) = O(log(n) + 1) = $\mathcal{O}(log(n))$

  `delete(var)`: O(search) + O(balance/swap nodes) = O(log(n) + 1) = $\mathcal{O}(log(n))$

* Red-Black 





## Heap (priority queue in cpp)

* `get_min()` or `get_max()` -> $\mathcal{O}(1)$
* `remove_top()` -> $\mathcal{O}(log(n))$
  1. replace top element with the last element in the heap: $\mathcal{O}(1)$, array heap
  2. bubble-down: $\mathcal{O}(log(n))$
* `insert()` -> $\mathcal{O}(log(n))$
  1. insert to the bottom (the last empty slot in the "heap array"): $\mathcal{O}(1)$
  2. bubble-up: $\mathcal{O}(log(n))$, since binary heap is a complete binary tree which tree height is log(n)



## Tries(prefix tree, n-ary tree)

* Extra Learning Material

  [YouTube Introduction to Tries](https://www.youtube.com/watch?v=AXjmTQ8LEoI)

  [UCSanDiego Intro to Tries](https://www.coursera.org/lecture/data-structures-optimizing-performance/core-introduction-to-tries-08Xyf)

* checking if prefix if valid in O(length of the string)




## Graph
* Data Structure
	* Adjacency List 
		* [Implementation](https://github.com/a1779748/RSP/blob/main/Graph/RepresentGraph/ADM-AdjacencyList.cpp) 
	* Adjacency Matrix
	  * [implementation](https://github.com/a1779748/RSP/blob/main/Graph/RepresentGraph/easyGraph.cpp) 
* BFS (using queue)
  * O(vertices + edges) on adjacency list
  * O($vertices^2$) on adjacency matrix
  * [Implementation](https://github.com/a1779748/RSP/blob/main/Graph/BFS) 
  * application
    * shortest path **on equal weighted or unweighted graph**
    * finding path
    * Find **connected components**, all edges that are discovered are in the same components
    * Make the **bipartite graph**, check if the graph is **a bipartite graph** 
* DFS (using stack)
  * O(vertices + edges) on adjacency list
  * O($vertices^2$) on adjacency matrix
  * [Implementation](https://github.com/a1779748/RSP/tree/main/Graph/DFS) 
  * application
    * finding path
    * finding cycles
    * Topological sorting on **directed graph**
    * Strongly connected components on **directed graph**





## MST (on weighted graph)

* Prim's (greedy)
  * O(vertices * edges) <- normal
  * O(E + VlogV) <- optimal using priority queue to handle Minimum Unselected Distance part (V vertices * each insertion into heap logV)
* Kruskal (greedy)
  * **normal ????????????????????????????????????????????????????????????**
  * O(ElogE) <- optimal using Union-Find(find/merge component) and priority queue(sorting edges, in O(ElogE))
* Union-Find (used in Kruskal)
  * find(x), O(log(n))
  * union(s1, s2), O(log(n))



## Shortest Path (on weighted graph)

* Dijkstra (greedy)
  * O(vertices * edges) <- normal,same as prim's
  * O(E + VlogV) <- optimal using priority queue to handle Minimum Unselected Distance part (V vertices * each insertion into heap logV) same as prim's
* All-Pairs Shortest Path (Floyd-Warshall)
  * O($V^3$)
* Bellman-Ford





## Quick Sort and Quick Select algorithm
* Quick Sort
  * O(nlogn) if we choose the pivot properly
  * O($n^2$) if the pivot do not split the array in each round
  * [Implementation](https://github.com/a1779748/RSP/blob/main/Sorting/Quicksort.cpp) 

* Quick Selection
  * it is the same as quick sort, but we do not need to go to both partial part, we only go to one direction which may include our target.





## Merge Sort

[implementation](https://github.com/a1779748/RSP/blob/main/Sorting/Mergesort.cpp)



## Bit Manipulation

`bitwise XOR ^`: 1 if two bits are different

`bitwise And &`: 1 iff both bits are 1

`bitwise Or |`: 1 if any of two bits is 1

Arithmetic: right shift by filling in the sign bit(left most bit)

Logical: right shift by filling in the 0s



## Singleton Design Pattern

> The Singleton pattern ensures that a class has only one instance and ensures access to the instance through the application. (CTCI)



## Factory Design Pattern

> The Factory Method offers an inter face for creating an instance of a class, with its subclasses deciding which class to instantiate. (CTCI)





## Some other useful website

[Algorithm visualization](https://visualgo.net/en)

