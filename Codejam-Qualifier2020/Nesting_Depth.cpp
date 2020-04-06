#include<bits/stdc++.h>

using namespace std;

int main(){
    int t;
    cin>>t;
    for(int query=1;query<=t;query++){
        cout<<"Case #"<<query<<": ";
        string s;
        cin>>s;
        /*
            Logic:
                We only open a bracket when needed and close when needed. 
                We keep track of current nesting depth. Now three cases
                arise:
                  1. current nesting depth = current digit: In this case we already have
                                        the given depth, so we dont open or close any bracket
                                        just add our digit.
                  2. current nesting depth > current digit: In this case we have a greater depth
                                        than needed, so we close some brackets
                  3. current nesting depth < current digit: In this case we have a lesser depth
                                        than needed, so we open some brackets
        */
        
        int depth_till_now = 0; //maintains current nesting depth
        string res = ""; //result string
        
        
        for(int i=0;i<s.size();i++){
            int d = (int)(s[i] - '0');
            if(d == depth_till_now){
                res += s[i];
            }
            else if(d < depth_till_now){
                while(d<depth_till_now){
                    res += ")";
                    depth_till_now --;
                }
                res += s[i];
            }
            else{
                while(d>depth_till_now){
                    res += "(";
                    depth_till_now ++;
                }
                res += s[i];
            }
        }
        
        while(depth_till_now>0){
            res += ")";
            depth_till_now --;
        }
        
        /* (((3))1(2))
        */
        
        cout<<res<<'\n';
    }
}