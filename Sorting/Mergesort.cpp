#include <iostream>
#include <vector>
#include <queue>

using namespace std ;

void Mergesort(vector<int> &arr, int low, int high) ;
void Merge(vector<int> &arr, int low, int mid, int high) ;
void printarr(vector<int> arr){ for(auto i : arr) cout << i << ' '; cout << endl; }
void ADMmerge(vector<int> &arr, int low, int mid, int high) ;

int main()
{
	vector<int> arr = {5, -1, 3, 4, 2, 1, 0} ;
	printarr(arr) ;
	Mergesort(arr, 0, arr.size()-1) ;
	printarr(arr) ;
	return 0;
}


void Mergesort(vector<int> &arr, int low, int high) {
	if (low >= high) return ;
	int mid = (low + high) >> 1;

	Mergesort(arr, low, mid) ;
	Mergesort(arr, mid+1, high) ;

	//	Merge(arr, low, mid, high) ;
	ADMmerge(arr, low, mid, high) ;
}

void ADMmerge(vector<int> &arr, int low, int mid, int high) {
	queue<int> buflow, bufhigh ;
	for (int i=low; i<=mid; i++) buflow.push(arr[i]);
	for (int i=mid+1; i<=high; i++) bufhigh.push(arr[i]);

	int i = low ;
	while (!buflow.empty() && !bufhigh.empty()) {
		if (buflow.front() <= bufhigh.front()) {
			arr[i++] = buflow.front();
			buflow.pop() ;
		}
		else {
			arr[i++] = bufhigh.front();
			bufhigh.pop() ;
		}
	}

	while (!buflow.empty()) {
		arr[i++] = buflow.front();
		buflow.pop();
	}
	while (!bufhigh.empty()) {
		arr[i++] = bufhigh.front();
		bufhigh.pop();
	}
}

void Merge(vector<int> &arr, int low, int mid, int high) {
	vector<int> buflow, bufhigh;
	for (int i=low; i<=mid; i++) buflow.push_back(arr[i]);
	for (int i=mid+1; i<=high; i++) bufhigh.push_back(arr[i]);

	int i = low, l = 0, h = 0;;
	while ( l<(int)buflow.size() && h<(int)bufhigh.size()) {
		if (buflow[l] <= bufhigh[h]) {
			arr[i] = buflow[l] ;
			l ++;
		}
		else {
			arr[i] = bufhigh[h] ;
			h ++;
		}
		i ++ ;
	}

	while (l < (int)buflow.size()) {
		arr[i] = buflow[l];
		i++, l++;
	}
	while (h < (int)bufhigh.size()) {
		arr[i] = bufhigh[h];
		i++, h++;
	}
}
