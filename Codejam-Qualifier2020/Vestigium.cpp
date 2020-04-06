#include<bits/stdc++.h>

using namespace std;

int main(){
    int t;
    cin>>t;
    for(int query=1;query<=t;query++){
        cout<<"Case #"<<query<<": ";
        
        int n;
        cin>>n;
        
        int mat[n][n];
        
        for(int i=0;i<n;i++)
         for(int j=0;j<n;j++) cin>>mat[i][j];
         
        /*
            Computing the trace
            Trace is basically summation of mat[i][i]
        */
        int trace = 0;
        
        for(int i=0;i<n;i++) trace += mat[i][i];
        
        int row = 0, col = 0;
        
        bool present[n+1];
        
        /*
            Logic:
            We declare an array present of size n+1.
            Now for each row, we try seeing if there 
            is any repeated element. We do this by 
            looping over all the elements in that row
            one by one and keep track of the elements
            seen by making the corresponding entry true
            in present. For example if 0th column has 2
            then we set present[2] = true. When we come 
            to an entry that has corresponding entry in
            present array as true, we can conclude row
            has a repeated element. For example, if column
            1 also has 2, we find that present[2] is true
            (set by 2 in 0th column). So we can conclude
            this row has a repeated element and thus increment
            our row counter.
            Do the same for column
        */
        
        for(int i=0;i<n;i++){
            /*
                fill(arr, arr+n, x) means
                for(int i=0;i<n;i++) arr[i] = x
            */
            fill(present, present+n+1, false);
            
            for(int j=0;j<n;j++){
                if(present[mat[i][j]]){
                    row ++;
                    break;
                }
                present[mat[i][j]] = true;
            }
            
            fill(present, present+n+1, false);
            
            for(int j=0;j<n;j++){
                if(present[mat[j][i]]){
                    col ++;
                    break;
                }
                present[mat[j][i]] = true;
            }
            
        }
        
        cout<<trace<<" "<<row<<" "<<col<<'\n';
        
    }
}