#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <set>
#include <cmath>
#include <map>
#include <queue>
using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i=(c).begin();i!=(c).end();i++)


int finds(map <vi,int> &m,vi tempo,int weight[],int value[]){
    if(tempo[0]==0)
        return 0;
    int i=tempo[0],x=tempo[1];
    vi temp1;temp1.pb(i);temp1.pb(x);
    vi temp2;temp2.pb(i-1);temp2.pb(x);
    vi temp3;temp3.pb(i-1);temp3.pb(x-weight[i]);
    int tempval2,tempval3;
    if(m.find(temp2)==m.end()){
        tempval2=finds(m,temp2,weight,value);
    }
    else
        tempval2=m[temp2];

    if(weight[i]>x){

        m[temp1]=tempval2;
        return m[temp1];
    }
    if(m.find(temp3)==m.end()){
        tempval3=finds(m,temp3,weight,value);
    }
    else
        tempval3=m[temp3];
    m[temp1]=max(tempval2,(tempval3+value[i]));
    return m[temp1];
}


int main(){
    ifstream ipfile("knapsack_big.txt",ios::in);
    int W,n;
    ipfile>>W>>n;
    int weight[n+1],value[n+1];
    for(int i=1;i<=n;i++)
        ipfile>>value[i]>>weight[i];

    map <vi,int> m;

    for(int i=1;i<=n;i++)
        for(int x=W;x<=W;x++){

            vi temp1;temp1.pb(i);temp1.pb(x);
            vi temp2;temp2.pb(i-1);temp2.pb(x);
            vi temp3;temp3.pb(i-1);temp3.pb(x-weight[i]);
            int tempval2,tempval3;
            if(m.find(temp2)==m.end()){
                tempval2=finds(m,temp2,weight,value);
            }
            else
                tempval2=m[temp2];

            if(weight[i]>x){

                m[temp1]=tempval2;
                continue;
            }
            if(m.find(temp3)==m.end()){
                tempval3=finds(m,temp3,weight,value);
            }
            else
                tempval3=m[temp3];
            m[temp1]=max(tempval2,(tempval3+value[i]));
        }
    ipfile.close();
    vi temps;temps.pb(n);temps.pb(W);
    cout<<endl<<"Ans is "<<m[temps]<<endl;

    return 0;
}

