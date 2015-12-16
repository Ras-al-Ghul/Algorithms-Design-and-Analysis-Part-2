#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i=(c).begin();i!=(c).end();i++)

const int clusternumber=4;

bool compares(vi first,vi second){

    if(first[2]<second[2])
        return true;
    else if(first[2]==second[2]){
        if(first[0]<second[0])
            return true;
        else if(first[0]==second[0]){
            if(first[1]<second[1])
                return true;
            else if(first[1]==second[1])
                return true;
            else
                return false;
        }
        else
            return false;

    }
    else
        return false;
}

int readfromfile(vvi &datum){
    ifstream ipfile("clustering1.txt",ios::in);
    int numofnodes;
    ipfile>>numofnodes;
    int a,b,c;
    while(ipfile>>a>>b>>c){
        vi temp;
        temp.pb(a);
        temp.pb(b);
        temp.pb(c);
        datum.pb(temp);
    }
    ipfile.close();
    std::sort(all(datum),compares);
    return numofnodes;
}

void initializecluster(vvi &unionfind,int numofvertices){
    for(int i=0;i<=numofvertices;i++){
        vi temp;temp.pb(i);
        unionfind.pb(temp);
    }
    return;
}

bool finds(vvi &unionfind,int i,int j){
    int temp1=i,temp2=j;
    while(unionfind[temp1][0]!=temp1)
        temp1=unionfind[temp1][0];
    while(unionfind[temp2][0]!=temp2)
        temp2=unionfind[temp2][0];
    if(temp1==temp2)
        return true;
    else
        return false;
}

void unions(vvi &unionfind,int i,int j){
    int temp1=i,temp2=j;
    while(unionfind[temp1][0]!=temp1)
        temp1=unionfind[temp1][0];
    while(unionfind[temp2][0]!=temp2)
        temp2=unionfind[temp2][0];

    unionfind[temp1][0]=unionfind[temp2][0];
    return;
}

int findans(vvi &unionfind,vvi &datum,int numofnodes){
    int finalans;int currentclusternum=numofnodes,temp=0;
    tr(datum,it){
        int node1=(*it)[0],node2=(*it)[1],distances=(*it)[2];
        if(finds(unionfind,node1,node2)){
            temp=distances;
            continue;
        }
        else{
            unions(unionfind,node1,node2);
            currentclusternum--;
        }
        if(currentclusternum==clusternumber-1){
            it--;
            temp=(*it)[2];
            return temp;
        }
    }
    return 0;
}

int main(){
    vvi datum;
    vvi unionfind;
    int numofnodes=readfromfile(datum);
    initializecluster(unionfind,numofnodes);
    int finalans=findans(unionfind,datum,numofnodes);
    cout<<finalans<<endl;
    return 0;
}

