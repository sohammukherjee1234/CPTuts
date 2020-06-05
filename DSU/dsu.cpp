
const int MAXN = 100*1000 + 5;
 
struct DSU{
	int parent[MAXN];
	vv<ii> extraEdge[MAXN];
	DSU(){
		FOR(i,MAXN)parent[i] = i;
	}
	int find(int a){
		if(parent[a] != a)parent[a] = find(parent[a]);
		return parent[a];
	}
	bool isSame(int a,int b){
		return find(a) == find(b);
	}
	void merge(int a,int b){
		if(isSame(a,b)){
			int pa = find(a);
			extraEdge[pa].pb({a,b});
		}else{
			int pa = find(a);
			int pb = find(b);
			if(extraEdge[pa].size() > extraEdge[pb].size()){
				parent[pb] = pa;
				for(auto e: extraEdge[pb])extraEdge[pa].pb(e);	
			}else{
				parent[pa] = pb;
				for(auto e: extraEdge[pa])extraEdge[pb].pb(e);
			}
		}
	}
};	