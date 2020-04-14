/* Problem Link: https://www.codechef.com/JULY17/problems/IPCTRAIN */


#include<bits/stdc++.h>



using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n, d;
        cin>>n>>d;
        pair<int, pair<int,int> > trainer[n];
        
        for(int i=0;i<n;i++){
            int si, ti,di;
            cin>>di>>ti>>si;
            trainer[i] = {si, {di, ti}};
            
        }
        
        sort(trainer, trainer+n);
        
        set<int> freeDates;
        
        for(int i=1;i<=d;i++) freeDates.insert(i);
        
        
        for(int i=n-1;i>=0;i--){
            int si = trainer[i].first;
            int di = trainer[i].second.first;
            int ti = trainer[i].second.second;
            
            //getting first free date >= di
            auto itr = freeDates.lower_bound(di);
            
            while(itr != freeDates.end()){
                itr = freeDates.erase(itr);
                ti --;
            }   
            
            sadness += ti * si;
        }
        
      
  
        cout<<sadness<<"\n";
    }
    return 0;
}
