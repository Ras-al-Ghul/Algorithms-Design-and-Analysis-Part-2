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

int BITLENGTH;
int ones=0,twos=0;

typedef vector <int> vi;
typedef vector <vi> vvi;
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i=(c).begin();i!=(c).end();i++)

#define consts 24

int readfromfileandcountdups(set<string>& nodes){
    ifstream ipfile("clustering_big.txt",ios::in);
    int numofnodes,zeroes=0;
    ipfile>>numofnodes>>BITLENGTH;
    string actual,temp,readto;
    getline(ipfile,temp);
    while(getline(ipfile,readto)){
        actual="";
        istringstream strings(readto);
        while(strings>>temp)
            actual+=temp;
        if(nodes.set::find(actual)!=nodes.end()){
            zeroes++;
            continue;
        }
        nodes.insert(actual);
    }
    ipfile.close();
    return zeroes;
}
int newsetsize;
void countnumofonesandtwos(set<string>& nodes){
    set<string> tempnodes;

    string strings;

    tr(nodes,it){

        strings=(*it);int sets=0;

        unsigned long temps=0;
        for(int i=0;i<BITLENGTH;i++){
            temps=temps+((strings[BITLENGTH-1-i]-48)*(int(pow(2,i))));
        }
        bitset<consts> currentnum(temps);

        for(int i=0;i<BITLENGTH;i++){
            bitset <consts> combo(int(pow(2,i)));
            bitset <consts> result=currentnum^combo;
            if(nodes.find(result.to_string())!=nodes.end()){
                sets=1;
                ones++;
            }
        }
        for(int i=0;i<BITLENGTH;i++){
            for(int j=i+1;j<BITLENGTH;j++){
                bitset <consts> combo(0);combo[i]=1;combo[j]=1;
                bitset <consts> result=currentnum^combo;
                if(nodes.find(result.to_string())!=nodes.end()){
                    sets=1;
                    twos++;
                }
            }
        }
        if(sets==0)
            tempnodes.insert(strings);

    }
    cout<<"The number of edges of cost 1 is "<<ones/2<<endl;
    cout<<"The number of edges of cost 2 is "<<twos/2<<endl;

    cout<<"The size of set is "<<nodes.size()<<endl;

    tr(tempnodes,it){
        nodes.erase((*it));
    }
    tempnodes.clear();
    newsetsize=nodes.size();
    cout<<"The new size of set is "<<newsetsize<<endl;
    return;
}

void addtovector(set<string>& nodes,int arrays[][2]){
    string strings;
    for(int i=0;i<int(pow(2,24));i++){
        arrays[i][0]=0;arrays[i][1]=0;
    }
    tr(nodes,it){
        strings=(*it);

        unsigned long temps=0;
        for(int i=0;i<BITLENGTH;i++){
            temps=temps+((strings[BITLENGTH-1-i]-48)*(int(pow(2,i))));
        }

        arrays[temps][0]=temps;
        arrays[temps][1]=0;
    }
    return;
}

void unions(long val1,long val2,int arrays[][2]){
    long temp1=val1,temp2=val2;
    while(arrays[temp1][0]!=temp1)
        temp1=arrays[temp1][0];
    while(arrays[temp2][0]!=temp2)
        temp2=arrays[temp2][0];

    //union based on rank
    if(arrays[temp2][1]>arrays[temp1][1]){
        arrays[temp1][0]=temp2;
    }
    else if(arrays[temp2][1]<arrays[temp1][1]){
        arrays[temp2][0]=temp1;
    }
    else{
        arrays[temp1][0]=temp2;
        arrays[temp2][1]+=1;
    }
    return;
}

bool finds(long val1,long val2,int arrays[][2]){
    queue<long> tempq1,tempq2;
    long temp1=val1,temp2=val2;
    while(arrays[temp1][0]!=temp1){
        temp1=arrays[temp1][0];
        tempq1.push(temp1);
    }
    while(arrays[temp2][0]!=temp2){
        temp2=arrays[temp2][0];
        tempq2.push(temp2);
    }
    long tempo;
    while(!tempq1.empty()){
        tempo=tempq1.front();
        tempq1.pop();
        arrays[tempo][0]=temp1;
    }
    while(!tempq2.empty()){
        tempo=tempq2.front();
        tempq2.pop();
        arrays[tempo][0]=temp2;
    }
    if(temp1==temp2)
        return true;
    else
        return false;
}
int clustercount;
void findclusters(set<string>& nodes,int arrays[][2]){
    clustercount=nodes.size();
    tr(nodes,it){
        string strings=(*it);
        unsigned long temps=0;
        for(int i=0;i<BITLENGTH;i++){
            temps=temps+((strings[BITLENGTH-1-i]-48)*(int(pow(2,i))));
        }
        bitset<consts> currentnum(temps);
        for(int i=0;i<BITLENGTH;i++){
            bitset <consts> combo(int(pow(2,i)));
            bitset <consts> result=currentnum^combo;
            if(arrays[result.to_ulong()][0]!=0){
                if(finds(temps,result.to_ulong(),arrays)){
                    continue;
                }
                else{
                    unions(temps,result.to_ulong(),arrays);
                    clustercount--;
                }
            }
        }
        for(int i=0;i<BITLENGTH;i++){
            for(int j=i+1;j<BITLENGTH;j++){
                bitset <consts> combo(0);combo[i]=1;combo[j]=1;
                bitset <consts> result=currentnum^combo;
                if(arrays[result.to_ulong()][0]!=0){
                    if(finds(temps,result.to_ulong(),arrays)){
                        continue;
                    }
                    else{
                        unions(temps,result.to_ulong(),arrays);
                        clustercount--;
                    }
                }
            }
        }
    }
    cout<<"The number of clusters is "<<clustercount<<endl;
}

int main(){
    set<string> nodes;

    ifstream ipfile("clustering_big.txt",ios::in);
    int numofnodes;
    ipfile>>numofnodes;
    ipfile.close();
    cout<<"The total number of nodes is "<<numofnodes<<endl;

    int zeroes=readfromfileandcountdups(nodes);
    cout<<"The number of edges of cost 0 is "<<zeroes<<endl;

    countnumofonesandtwos(nodes);


    int arrays[int(pow(2,24))][2];

    addtovector(nodes,arrays);
    findclusters(nodes,arrays);

    cout<<"The final answer is "<<numofnodes-newsetsize+clustercount-zeroes<<endl;
    return 0;
}
