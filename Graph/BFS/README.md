## Instruction
1. `ADM_Graph_with_BFS.cpp`: type `make BFS` to see the running result.
2. type `make clean` to remove all cpp executable file

## new Graph
> add BFS functionality to the ADM version adjacency list Graph.

1. `ADM_Graph_with_BFS.cpp`
    * This one is like cpp version of ADM's adjacency-list Graph(The same functionality and the same logical)
    * `graph_ADM.in` is the input Graph of this program.
        this graph looks like:
        ```
        1----2 
        |  / | \
        | /  |   3
        |/   | /
        5----4
        ```
    * `init_bfs()` function clear all **status** array for bfs, as well as the `parent[]` array
    * `bfs(int start, int process)` function add `process` option to choose which kind of process the bfs will do.
    * `find_bfs_path(int start, int end)` function will only works correctly after doing a bfs. 

