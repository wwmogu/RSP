#include <queue>
#include <vector>
#include <iostream>
#include <functional>	// greater<>
#include <algorithm>	// make_heap(v.begin(), v.end()), sort_heap(v.begin(), v.end());

using namespace std;

void Heapsort(vector<int> &arr) {
	vector<int> sorted;

	// by default it is Max heap, using greater set it to min heap
	priority_queue<int, vector<int>, greater<int>> pq;
	for (auto i : arr) {
		pq.push(i);
	}
	
	while(!pq.empty()) {
		sorted.push_back(pq.top());
		pq.pop() ;
	}
	arr = sorted ;
	
	return ;
}

void buildin_heapsort(vector<int> &arr) {
	make_heap(arr.begin(), arr.end()) ;
	sort_heap(arr.begin(), arr.end()) ;
	return ;
}

void  printarr(vector<int> arr) {
	for (auto i : arr) cout << i << ' ';
	cout << endl ;
}

int main()
{
	vector<int> arr = {-1, 0, 1, 5, 4, 2, 3};
	printarr(arr) ;
	Heapsort(arr) ;
	printarr(arr) ;

	vector<int> arr1 = {-1, 0, 1, 5, 4, 2, 3};
	printarr(arr1) ;
	buildin_heapsort(arr1) ;
	printarr(arr1) ;

	return 0;
}
