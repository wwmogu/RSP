## Instruction
1. `ADM_Graph_with_DFS.cpp`: type `make DFS` to see the running result.
2. type `make clean` to remove all cpp executable file

## new Graph
> add DFS functionality to the ADM version adjacency list Graph.

1. `ADM_Graph_with_DFS.cpp`
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
    * `init_dfs()` function clear all **status** array for dfs, as well as the `parent[], entry_time[], exit_time[]` array and `time` clock
    * `dfs(int start, int process)` ADM recursive version of DFS, which also maintain a "clock" which will help us to keep track all vertex entry and exit time.
    * `dfs_non_recursive(int start, int process)` 99% similar to bfs, use stack to hold the "will-visit" vertex

