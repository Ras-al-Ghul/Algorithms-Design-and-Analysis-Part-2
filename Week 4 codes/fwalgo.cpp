#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i=(c).begin();i!=(c).end();i++)

#define valueofedge 47978

int numofvertices,numofedges;
const int numofv=1000;
int shortestpath=INT_MAX;

void enterinputs(vvi & edgevec){
    ifstream ipfile("graph1.txt");  //Change the file in this line to graph2.txt and later graph3.txt after executing for graph1.txt
    ipfile>>numofvertices>>numofedges;
    for(int i=0;i<numofedges;i++){
        vi tempvec;
        int a,b,c;ipfile>>a>>b>>c;
        tempvec.pb(a);tempvec.pb(b);tempvec.pb(c);
        edgevec[i]=tempvec;
    }
    ipfile.close();
    return;
}

void initialize(int mainarr[numofv+1][numofv+1][2] , vvi & edgevec){
    for(int i=1;i<numofvertices+1;i++){
        for(int j=1;j<numofvertices+1;j++){
            if(i==j){
                mainarr[i][j][0]=0;
                continue;
            }
            mainarr[i][j][0]=100000;
        }
    }

    for(int i=0;i<numofedges;i++){

        int src,dest,cost;src=edgevec[i][0];dest=edgevec[i][1];cost=edgevec[i][2];

        if(cost<mainarr[src][dest][0]){
            mainarr[src][dest][0]=cost;
        }
        if(cost<shortestpath)
            shortestpath=cost;
    }

    return;
}

int returnmin(int a,int b){
    return ((a<b)?a:b);
}

int main(){

    vvi edgevec(valueofedge);
    enterinputs(edgevec);
    int mainarr[numofv+1][numofv+1][2];

    initialize(mainarr,edgevec);

        for(int k=1;k<numofvertices+1;k++){
            for(int i=1;i<numofvertices+1;i++){
                for(int j=1;j<numofvertices+1;j++){
                    int temp1=mainarr[i][j][0],temp2=mainarr[i][k][0]+mainarr[k][j][0];
                    mainarr[i][j][1]=returnmin(temp1,temp2);
                    if(mainarr[i][j][1]<shortestpath)
                        shortestpath=mainarr[i][j][1];
                }
            }
            for(int i=1;i<numofvertices+1;i++){
                for(int j=1;j<numofvertices+1;j++){
                    mainarr[i][j][0]=mainarr[i][j][1];
                }
            }
        }

    for(int i=1;i<numofvertices+1;i++){
        if(mainarr[i][i][1]<0){
            cout<<"NULL";return 0;
        }
    }

    cout<<shortestpath<<endl;
    return 0;
}
