#include<bits/stdc++.h>

using namespace std;



int main(){
    int t;
    cin>>t;
    for(int query=1;query<=t;query++){
        cout<<"Case #"<<query<<": ";
        int n;
        cin>>n;
        pair<int, pair<int, int> > arr[n];
        
        for(int i=0;i<n;i++){
            cin>>arr[i].first>>arr[i].second.first;
            arr[i].second.second = i;
        }
        
        /*
            sort(arr,arr+n) -> sorts the array in increasing order
            when type of each element is pair<int, pair<int,int> >
            sorts the array  w.r.t the first value. If 2 elements
            have same first value, sorts them wrt second.first and
            then second.second

            Ex: Consider {2, {3,4}}, {3,{4,5}}, {2,{1,3}}, {2,{3,6}}

            sorting them will give:
                {2, {1,3}}, {2, {3,4}}, {2,{3,6}}, {3,{4,5}}
        */
        sort(arr, arr+n);
        
        
        bool ok = true;
        int person_id[n]; //tracks which person is assigned ith task
        fill(person_id, person_id+n, -1);
        
        /*
            Logic:
                For each person we maintain ending times i.e when they will
                be next free. We use max_end1 and max_end2 for person 1 and 2
                respectively. Now the jobs are sorted in increasing order of
                time. So for current job we check when both the persons will
                be free next. If one of them gets free before the job starts,
                we assign it to him and update his max_end. Else we report 
                its IMPOSSIBLE to make an assignment
        */
        int max_end1 = 0, max_end2 = 0;
        
        for(int i=0;i<n;i++){
            if(arr[i].first>=max_end1){
                person_id[arr[i].second.second] = 0;
                max_end1 = arr[i].second.first;
            }
            else if(arr[i].first >= max_end2){
                person_id[arr[i].second.second] = 1;
                max_end2 = arr[i].second.first;
            }
            else{
                ok = false;
            }
        }
        
        if(!ok) cout<<"IMPOSSIBLE\n";
        else{
            for(int i=0;i<n;i++){
                if(person_id[i] == 0) cout<<"C";
                else cout<<"J";
            
                
            }
            cout<<"\n";
        }
    }
}