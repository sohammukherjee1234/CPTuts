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
//#define int long long
#define ld long double
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 5*10*1000+5;//0*1000+5;
const int MAXK = 100+4;
const ll MOD = 1e9 +7;

int vals[MAXN];
vi g[MAXN];

ll dp[MAXN][MAXK];
int k;
void dfs(int node,int p=-1){
	for(auto e : g[node])
		if(e != p)
			dfs(e,node);
	// all children are visited. now its time to update our dp
	/*
	we are only storing the prefixDp for current and prev node, since for our current node all our
	calculations only depend on the value of the previous row(or column, however you visualise your dp).
	This is a very common memory saving trick that is used - when we are doing a dp[i][j], and dp[i][j] depends
	on dp[i-1][x] for some x, its enough to just store the last row and the current row of the dp. 

	here prefixDp[i][j] would have meant i have processed the first i children, and have recieved j contribution. 
	This is effectively stored as prefixDp[0][j]. We then calculate for prefixDp[i+1][j] as prefixDp[1][j]. Then,
	before moving onto the next child, we paste prefixDp[1][.] to prefixDp[0][.].

	Further note that to do as prefixDp[i][j] would have been more painful to implement since when skipping
	the node which is not our child but our parent, we would have had to copy paste the previous row as ditto,
	or somehow maintained the fact that we had actually incremented i, without actually processing anything new,
	or kept a separate pointer. more code => more chances of bug. hence, this is better here. + it saves memory.
	*/
	ll prefixDp[2][k+1];
	FOR(i,k+1)prefixDp[0][i] = prefixDp[1][i]= 0;

	// this is because of the first time that we process a child, we have effectively received 0 contribution in 
	// exactly 1 way before this. Otherwise, you will have to do a different set of rules for the first chlid,
	// and then the below recurrance for the next child onwards. 
	prefixDp[0][0] = 1;
	for(auto e : g[node]){
		if(e == p)continue;

		FOR(j,k+1){
			FOR(x,j+1){
				// this step was as discussed in class. 
				prefixDp[1][j] += (dp[e][x] * prefixDp[0][j-x])%MOD;
				prefixDp[1][j] %= MOD;
			}
		}

		FOR(i,k+1){
			prefixDp[0][i] = prefixDp[1][i];
			prefixDp[1][i] = 0;
		}
	}
	FOR(i,k+1){
		if(i == 0 and vals[node] == 1){
			dp[node][0] = 0;
		}else{
			dp[node][i] = prefixDp[0][i-vals[node]];
		}
	}
	// we do this so that there is also the option of selecting nothing. 
	dp[node][0]++;
	dp[node][0] %= MOD;
}

void solve(){
	int n;
	cin >> n >> k;
	FOR(i,n)cin >> vals[i];
	FOR(i,n)g[i].clear();
	FOR(i,n-1){
		int a,b;
		cin >> a >> b;a--;b--;
		g[a].pb(b);
		g[b].pb(a);
	}
	// input taking done.
	dfs(0);
	ll sum = 0;
	FOR(i,n){
		sum += dp[i][k] - (k == 0) + MOD; // we subtract 1 when k == 0 since in all those places, we had counted
		// doing nothing too, but selecting an empty set is not valid obviously as the overall answer. However, it 
		// was important to be included in the dp, since other answers might have assumed that taking 0 contribution
		// from a child was also possible. 

		sum %= MOD;
	}
	cout << sum << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}