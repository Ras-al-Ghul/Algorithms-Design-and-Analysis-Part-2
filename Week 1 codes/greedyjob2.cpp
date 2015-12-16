#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

typedef vector <double> vi;
typedef vector <vi> vvi;
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i=(c).begin();i!=(c).end();i++)

const int sizes=10005;
const double epsilon=1e-1;
class schapp{
    vvi combined;
    int numofjobs;
public:
    void readfromfile();
    void sorts();
    void completiontime();
};

bool myfunc(vi first,vi second){

    if(first[2]!=second[2])
        return first[2]>second[2];
    else
        return first[0]>second[0];
}

void schapp::readfromfile(){
    ifstream infile("jobs.txt",ios::in);
    infile>>numofjobs;
    double a,b;
    while(infile>>a>>b){
        vi temp;
        temp.push_back(a);
        temp.push_back(b);
        temp.push_back(a/b);
    }
    infile.close();
    return;
}



void schapp::sorts(){
    std::sort(all(combined),myfunc);
    cout<<endl;
    return;
}

void  schapp::completiontime(){
    long long comptime=0;
    long long times=0;
    tr(combined,it){
        times=times+(*it)[1];
        comptime=comptime+(times*((*it)[0]));
    }
    cout<<comptime;

    return;
}

int main(){
    schapp obj;
    obj.readfromfile();
    obj.sorts();
    obj.completiontime();
    return 0;
}
