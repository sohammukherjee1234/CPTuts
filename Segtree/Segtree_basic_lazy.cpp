#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long 
#define ld long double
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define il pair<ll,ll>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 10*100*1000+5;//0*1000+5;
const ll MOD = 1e9 + 7;

// n = 1e6;
//  2.1 *1e6
/*
1) build
2) update
3) get()


*/


struct SegmentTree{
	// range max/ point update
	int st[4*MAXN];
	// for input you are given n. smallest i such that 2^i > n : m = 2^i;; actual size needed = 2*m
	SegmentTree(int n){
		FOR(i,4*MAXN)st[i] = 0;
	}
	int combine(int a,int b){
		return a+b;
	}

	void pushdown(int node,int ss,int se){ // O(1)
		st[node] += lz[node]*(se-ss+1); // I update my segmenttree value
		if(ss != se){
			lz[node*2+1] += lz[node];// I push my lazy value to my children.
			lz[node*2+2] += lz[node];
		}
		lz[node] = 0; // I set my own lazy value to 0.
	}

	void update(int node,int ss,int se,int l,int r,int val){
		// break condition
		pushdown(node,ss,se);
		if(l > se or r < ss)return;
		
		// tag condition
		if(l <= ss and se <= r){
			// inside
			lz[node] += val;
			pushdown(node,ss,se);
			return;
		}

		int mid = (ss+se)/2;
		update(node*2+1,ss,mid,pos,val);
		update(node*2+2,mid+1,se,pos,val);
		st[node] = combine(st[node*2+1],st[node*2+2]);
	}
	// [L .... ... [ss...se] .. R]
	int get(int node,int ss,int se,int l,int r){
		if(l > se or r < ss)return 0;
		if(l <= ss and se <= r)return st[node];
		int mid = (ss+se)/2;
		return combine(get(node*2+1,ss,mid,l,r),get(node*2+2,mid+1,se,l,r));
	}
};





int main(){
	//precalc();
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	

	return 0;
}



