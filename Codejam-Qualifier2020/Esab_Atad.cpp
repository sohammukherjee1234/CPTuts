#include<bits/stdc++.h>

using namespace std;

int findop(int x, int y){
    /*
        NC -> 0
        R -> 1
        C -> 2
        C + R -> 3
        same parity: 0 -> NC, Rev
                     1 -> C, C+R
        diff parity: 0 -> NC , C+R
                     1 -> C, R
    */
    
    if(x == 0){
        if( y == 0) return 0;
        else return 1;
    }
    else{
        if(y == 0) return 3;
        else return 2;
    }
}

pair<int,int> perform(pair<int,int>x, int op){
    if(op == 1){
        swap(x.first, x.second);
    }
    else if(op == 2){
        x.first = !x.first;
        x.second = !x.second;
    }
    else if(op == 3){
        x.first = !x.first;
        x.second = !x.second;
        swap(x.first, x.second);
    }
    
    return x;
}


/*
10 -> (5,5)
2 -> op
8 -> val (4,4)
*/
int main(){
    int t,n;
    cin>>t>>n;
    while(t--){
        int arr[n];
        fill(arr, arr+n, -1);
        
        int id1 = 0, id2 = 0;
        bool f1 = false, f2 = false;

        /*
            Logic: 
                Lets say we found 2 pairs of form (i, n-1-i) having same and different 
                values respectively. That is pair1 can be (1,1) and pair2 can be (0,1).
                Lets observe how they change in all 4 cases:
                case        same_parity                 different_parity
                No change      (1, 1) [no change]               (0, 1) [no change]
                Reverse        (1, 1) [no change]               (1, 0) [change]
                Complement     (0, 0) [change]                  (1, 0) [change]
                Rev + Comp     (0, 0) [change]                  (0, 1) [no change]

                Now lets make a truth table on whether the pairs changed or not 
                where 0 means no change and 1 means change

                case                same_parity        different parity
                0 (No change)          0                    0
                1 (Reverse)            0                    1
                2(Complement)          1                    1
                3(Rev + comp)          1                    0

                We can see that everytime an operation is performed on the array
                using any one of the 4 operations, if we have 2 such pairs we can
                uniquely determine the type of the operation.

                So what we do is, everytime the array gets changed, i.e on 11th,
                21st, 31st... queries, we update all the elements that we found
                till now using the operation that we determine using the above
                process. 
                But what if we haven't found both the pairs yet? 
                It means, all the pairs that we found till now are of same type
                (either same parity or different parity). In both the cases, to 
                update the array we found till now, we just need to consider if
                the existing one changed or not. If they changed we consider it 
                complementation otherwise no change.

                So in every sets of 10 queries, except the first one, we use 2
                queries to determine the type of operation and remaining 8 to
                find the values of 4 more pairs.



        */
        
        //Determining first 5 pairs. 
        for(int i = 0; i<5; i++){
            cout<<i+1<<endl;
            int x;
            cin>>x;
            arr[i] = x;
            
            cout<<(n-i)<<endl;
            cin>>x;
            arr[n-1-i] = x;
            
            if(arr[i] != arr[n-1-i]){
                f2 = true;
                id2 = i;
            }
            else{
                f1 = true;
                id1 = i;
            }
        }
        
        int queries = 10; //we already have done 10 queries
        int done = 10;
        int i = 5;
        
        while(done<n){
            queries ++;
            if(queries % 10 == 1){
                //the array has been changed. Determine the type of operation
                int op = 0;
                if(f1 and f2){
                    //when we have found both pair types
                    cout<<id1+1<<endl;
                    int x;
                    cin>>x;
                    cout<<id2+1<<endl;
                    int y;
                    cin>>y;
                    
                    op = findop(x^arr[id1], y^arr[id2]);
                    
                }
                else {
                    //when we have found all pairs of one type only
                    cout<<1<<endl;
                    int x;
                    cin>>x;
                    cout<<1<<endl;
                    cin>>x;
                    if(x^arr[0]) op = 2;
                }
                //updating the already found values
                for(int j = i-1;j>=0;j--){
                    pair<int, int> data = {arr[j], arr[n-1-j]};
                    data = perform(data, op);
                    arr[j] = data.first;
                    arr[n-1-j] = data.second;
                }
                queries += 2;
            }
            
            //obtaining values of remaining indices
            cout<<i+1<<endl;
            int x;
            cin>>x;
            arr[i] = x;
            
            queries ++;
            cout<<(n-i)<<endl;
            cin>>x;
            arr[n-1-i] = x;
            
            if(arr[i] == arr[n-1-i]){
                f1 = true;
                id1 = i;
            }
            else{
                f2 = true;
                id2 = i;
            }
            
            i ++;
            done += 2;
            
        }
        
        for(int i=0;i<n;i++) cout<<arr[i];
        
        cout<<endl;
        
        char ok;
        cin>>ok;
        if(ok == 'N') break;
        
    }
}