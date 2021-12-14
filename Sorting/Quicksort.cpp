#include <iostream>
#include <vector>
#include <algorithm>	// sort(), swap()

using namespace std;

void buildinSort(vector<int> &arr) ;
int partition(vector<int> &arr, int low, int high) ;
void Quicksort(vector<int> &arr, int low, int high) ;
void printarr(vector<int> arr) {for (auto i : arr) cout << i << " "; cout << endl;}

int main()
{
	vector<int> arr = {5, 3, 4, 1, 2};
	printarr(arr);
	buildinSort(arr) ;
	printarr(arr);

	vector<int> arr1 = {5, 3, 4, 1, 2};
	printarr(arr1);
	Quicksort(arr1, 0, arr1.size()-1) ;
	printarr(arr1);

	return 0;
}

void buildinSort(vector<int> &arr) {
	sort(arr.begin(), arr.end());
	return ;
}

int partition(vector<int> &arr, int low, int high) {
	int pivot = high ;	// choose the last element inside this portion to be the pivot

	// the first element that are greater than pivot element
	int firsthigh = low;

	// from 0 to n-2, swap all element that are <= pivot with the first high element
	// after entire loop, all the element after firsthigh and firsthigh will > pivot(the last element)
	for (int i=low; i<high; i++) {
		if (arr[i] <= arr[pivot]) {
			swap(arr[i], arr[firsthigh]);
			firsthigh++;
		}
	}

	// swap pivot element with the firsthigh element
	swap(arr[pivot], arr[firsthigh]) ;

	// now before firsthigh, all element <= firsthigh
	//     after  firsthigh, all element > firsthigh
	return firsthigh;
}
void Quicksort(vector<int> &arr, int low, int high) {
	if (low >= high) return ;
	int p = partition(arr, low, high) ;
	Quicksort(arr, low, p-1) ;
	Quicksort(arr, p+1, high) ;
}
