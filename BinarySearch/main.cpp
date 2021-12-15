#include <iostream>
#include <vector>
#include <algorithm>    // lower_bound(), upper_bound();

using namespace std ;

typedef pair<int, int> PII;
PII buildin_binary_search(vector<int> arr, int target) ;
int simple_binary_search(vector<int> arr, int target, int low, int high) ;
int my_exact_upperbound(vector<int> arr, int target, int low, int high) ;

int main()
{
    vector<int> arrDistinct  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> arrDuplicate = {0, 1, 2, 3, 3, 3, 3, 3, 4, 5};

    PII buildin_bound_Distinct = buildin_binary_search(arrDistinct, 3) ;
    PII buildin_bound_Duplicate = buildin_binary_search(arrDuplicate, 3) ;
    cout << "Distinct bound for 3: "<< "lower-> " << buildin_bound_Distinct.first << ", upper-> " << buildin_bound_Distinct.second << endl;
    cout << "Duplicate bound for 3: "<< "lower-> " << buildin_bound_Duplicate.first << ", upper-> " << buildin_bound_Duplicate.second << endl;

    puts("");
    int pos_Distinct = simple_binary_search(arrDistinct, 3, 0, arrDistinct.size()-1) ;
    int pos_Duplicate = simple_binary_search(arrDuplicate, 3, 0, arrDuplicate.size()-1) ;
    cout << "Distict 3 at: " << pos_Distinct << endl;
    cout << "Duplicte 3 at: " << pos_Duplicate << endl ;

    puts("");

    int bound_Distinct = my_exact_upperbound(arrDistinct, 3, 0, arrDistinct.size()-1) ;
    int bound_Duplicate = my_exact_upperbound(arrDuplicate, 3, 0, arrDuplicate.size()-1) ;
    cout << "bound Distict 3 at: " << bound_Distinct << endl;
    cout << "bound Duplicte 3 at: " << bound_Duplicate << endl ;

    return 0; 
}

int my_exact_upperbound(vector<int> arr, int target, int low, int high) {
    if (low > high) return high ;

    int mid = (low + high) / 2;

    if (target < arr[mid]) {
        return my_exact_upperbound(arr, target, low, mid-1) ;
    }
    else {
        return my_exact_upperbound(arr, target, mid+1, high) ;
    }
}

int simple_binary_search(vector<int> arr, int target, int low, int high) {
    if (low > high) {
        return -1;
    }

    int mid = (high + low) >> 1;

    if (arr[mid] == target) {
        return mid ;
    }
    if (target < arr[mid]) {
        return simple_binary_search(arr, target, low, mid-1) ;
    }
    else {
        return simple_binary_search(arr, target, mid+1, high) ;
    }
}

PII buildin_binary_search(vector<int> arr, int target) {
    sort(arr.begin(), arr.end()) ;

    vector<int>::iterator low = lower_bound(arr.begin(), arr.end(), target) ;
    auto high = upper_bound(arr.begin(), arr.end(), target) ;

    return {low-arr.begin(), high-arr.begin()};
}