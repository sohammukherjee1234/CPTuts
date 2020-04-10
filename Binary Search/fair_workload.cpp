#include <bits/stdc++.h>
using namespace std;

/*
    Problem link: https://community.topcoder.com/stat?c=problem_statement&pm=1901&rd=4650
*/

bool P(int req_workers, int num_workers){
    /*
        Predicate function
        Returns true or false depending upon array value
        For Fair Workload it returns true when 
        req_workers <= num_workers 
    */
    
    return (req_workers <= num_workers);
}

/*
    Our logic is to always make hi point to a True and
    lo always point to a false
    So we end in a state where lo points to last false
    and hi points to first true.
    
    i.e
    [F, T]
*/


int getNumWorkers(int *cabinets, int n, int max_papers){
    /*
        Function that returns number of workers needed For
        assignment of n cabinets to the workers such that each
        worker gets a maximum of max_papers.
    */
    
    int num_workers  = 1, papers_taken = 0;
    for(int i=0;i<n;i++){
        if((papers_taken + cabinets[i]) <= max_papers){
            /*
                We can assign this cabinet to current worker 
                without violating the constraint of max_papers
            */
            papers_taken += cabinets[i];
        }
        else{
            /*
                We need a new worker as if we assign this cabinet to the existing worker
                he will have papers > max_papers
            */
            num_workers ++;
            papers_taken = cabinets[i];
        }
    }
    
    return num_workers;
}

int getMinimumMaxPapers(int *arr, int n, int m){
    /*
        Function that returns the minimum value of the maximum papers
        a person gets such that each cabinet is assigned to an worker and
        there are m total workers.
        We will binary search on our ans as we can see ans array will be
        of the form [F,F,F,F,T,T,T,T]
        Refer to the lecture for details
    */
    
    int lo = *max_element(arr, arr+n);
    int hi = accumulate(arr, arr+n, 0); //sum of elements

    while(lo<hi-1){
        int mid = (lo + hi)/2;
        int workers = getNumWorkers(arr, n, mid);
        if(P(workers, m)) hi = mid;
        else lo = mid;
    }
    
    return hi;
    
}

int main() {
	// your code goes here
	
    int cabinets[] = {3, 4, 4, 5, 3};
    cout<<getMinimumMaxPapers(cabinets, 5, 3);
	return 0;
}
