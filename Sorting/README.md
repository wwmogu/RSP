## Test Instruction
1. copy code into `main.cpp`
2. goto terminal, type `./test.sh`

## Sorting
1. `Heapsort.cpp`
	* There are two version of my heap sort
	* One using `priority_queue` which is a max heap another is using the build-in `make_hepe`
	* Do not implement heap itself

2. `Mergesort.cpp`
	* There are two `merge`, one is using `vector` and another is using `queue`. both of them need extra space for the half array.

3. `Quicksort.cpp`
	* It is the ADM version quicksort, when do the partition, finding the first element that greater than pivot. Then swap the pivot with it.
	* ADM's version choose the last element as pivot which when the array is originally in ascending order will take O(N^2).
