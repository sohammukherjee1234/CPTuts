#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <cmath>
#include <set>
#include <map>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define ld long double
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define vv vector

using namespace std;

const int MAXN = (1<<21);

#define endl '\n'

int k;
int* B;
int* arr;
int n;
int* psum;


// 1st func
bool isOk(int j){ // this will return true, if sum[Arr[i...j]] <= k, otherwise false
	if(j >= n)return true;
	return B[j];
}

// A[i] + A[i+1] + ... A[j-1] + A[j]
int calcSum(int i,int j){ // i is the left endpoint, j is the right endpoint
	// O(1)
	if(i == 0)psum[j];
	return psum[j] - psum[i-1];
}

// 2nd func
bool isOk(int i,int j){
	// O(1)
	if(j >= n)return true; // isOK(1,n) B[] = {0,0,0,0,0,0,0,1,1,1,1,1,1}
	return calcSum(i,j) <= k; // B[j]
}

int main(){
	cin >> n >> k ;
	arr = new int[n];
	int ans[n];
	B = new int[n];
	psum = new int[n];

/*
[|5,4,3,6,7],k =14
[5,9,12,18,25]
left = 1;
rightindex = 4; sum = 20
ans[leftindex] = 3;


query ( B[3] )
return B[3]; // O(1)
->0 / 1 // O(1)
left = 1
A[1] + A[2] + A[3] <= k 


*/

	FOR(i,n)cin >> arr[i];
	// O(n)
	FOR(i,n){
		if(i == 0){
			psum[i] = arr[i];
		}else {
			psum[i] = arr[i] + psum[i-1];
		}
	}


	// O(n) * [O(logn)] + O(n)
	FOR(left_index,n){
		int sum = 0;
		/*
		This code was basically if we had generated the whole 'B' array for every
		iteration of the loop, taking overall O(n) time. note that in the actual 'binary
		search on answer' we are only keeping this array in our head - ie, we just know that
		the array, if we had generated it, would have been monotonic. Since we only need to use
		this array to know during our binary search whether to go left or right, and since
		we only access O(logn) elements of the array during the binary search, that means
		a lot of our computation to find the array B had been wasted, if we would just generate
		the values in the array - ie B[i] for some i - on the fly. Which was the main concept 
		that we had talked about --  not actually finding the values of every element of B 
		in the precomputation stage, but rather finding only the values that we need during
		the binary search. 
		

		FOR(i,left_index)B[i] = 0; // otherwise B[0...left-1] will have garbage values. 

		for(int right_index = left_index;right_index <n; right_index++){
			sum += arr[right_index];
			if(sum <= k){
				B[right_index] = 0; // when sum<= k so by definition, B[i] = 0;
			}else{
				B[right_index] = 1; // by definition.
			}
		}

		*/
		int low = left_index;
		int high = n-1;
		while(high >= low){
			if(high - low <= 10){
				for(int possible_ans = low;possible_ans <= high;possible_ans++){
					bool is1 = isOk(left_index,possible_ans);
					bool is1_next = isOk(left_index,possible_ans + 1);
					if((is1 == false) and (is1_next == true)){
						// this effectively means that 'possible_ans' is my optimal answer
						ans[left_index] = possible_ans;
						break;
					}
				}
				break;
			}


			int mid = (low+high)/2;

			bool is1 = isOk(left_index mid);
			bool is1_next = isOk(left_index, mid + 1);
			if((is1 == false) and (is1_next == true)){
				// this effectively means that 'possible_ans' is my optimal answer
				ans[left_index] = mid;
				break;
			}else if(is1 == true){
				high = mid-1;
			}else{
				low = mid+1;
			}
		}
	}
	FOR(i,n)cout << ans[i] << " ";cout << endl;

	return 0;
}




// ============================== //
// ============================== //
// ============================== //
// ============================== //

bool check(int n,int ans){ // true, if yes, false if no.
	// you do the simulation. 
}

int binary_search(int n){
	int low = 1;
	int high = n;
	while(hight >= low){
		int mid = (high  + low)/2;
		if(check(n,mid) and (check(n,mid-1) == false)){
			// 1
			return mid;
		}else if(check(n,mid)){
			// case 2
			high = mid -1;
		}else{
			// case 3
			low = mid +1;
		}
	}
}

// ============================ // 
// ============================ // 