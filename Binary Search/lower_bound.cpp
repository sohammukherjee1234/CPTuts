#include <bits/stdc++.h>
using namespace std;


bool P(int x, int e){
    /*
        Predicate function
        Returns true or false depending upon array value
        For lower_bound we make our predicate fn to be
        true when x>=e and false otherwise
    */
    
    return (x>=e);
}

/*
    Our logic is to always make hi point to a True and
    lo always point to a false
    So we end in a state where lo points to last false
    and hi points to first true.
    
    i.e
    [F, T]
*/


int lowerBound(int *arr, int n, int e){
    /*
        Function that computes lower_bound for e
        lower_bound basically is first index where
        arr[i]>=e. If no such index returns -1
        
        Constraint: Array is sorted
        
        Complexity: O(LogN)
    */
    
    int lo = 0, hi = n-1;
    if(!P(arr[hi], e)) return -1; //No element >=e
    if(P(arr[lo], e)) return 0; //all elements >=e
    
    while(lo<hi-1){
        int mid = (lo+hi)/2;
        if(P(arr[mid], e)){
            /*
                If P(arr[mid), e) is true, it means
                this can be candidate solution or solution
                is towards left. So we set hi to mid
            */
            hi = mid;
        }
        else lo = mid;
    }
    
    return hi;
}

int main() {
	// your code goes here
	
	int arr[] = {1, 2, 2, 2, 3, 3, 4};
	cout<<lowerBound(arr, 7, 3);
	return 0;
}
