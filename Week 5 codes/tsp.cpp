#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
#include <list>
#include <bitset>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>
#include <limits>

#include <sys/resource.h>

using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(auto i=(c).begin();i!=(c).end();i++)
#define numofpoints 25	//Change this to the number of points in the file
#define infinte 100000

bool definitelyLessThan(float a, float b)
{
    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * std::numeric_limits<double>::epsilon());
}

int factorial(int n){
    if(n==1||n==0)
        return 1;
    int ans=1;
    for(int i=2;i<=n;i++)
        ans=ans*i;
    return ans;
}

int ncr(int n,int r){
    if(n<r)
        return 0;
    else if(r==0)
        return 1;
    else{
        int tempn=n;
        int ans=1;
        while(n>(tempn-r)){
            ans=ans*n;
            n--;
        }
        while(r>1){
            ans=ans/r;
            r--;
        }
        return ans;
    }
}

int npr(int n,int r){
    if(n<r)
        return 0;
    else{
        return (ncr(n,r)*factorial(r));
    }
}

float eucdist(int first,int second,vector< vector <float> > &coordinates){
    float ydiff=abs(coordinates[second][1]-coordinates[first][1]);
    ydiff=ydiff*ydiff;
    float xdiff=abs(coordinates[second][0]-coordinates[first][0]);
    xdiff=xdiff*xdiff;
    return (float(sqrt((xdiff+ydiff))));
}

void readandcalcdist(float *distances){
    vector< vector <float> > coordinates(numofpoints+1);
    ifstream ipfile("tsp.txt");		//Provide the input filename here
    int numberofpts;
    ipfile>>numberofpts;
    for(int i=1;i<=numberofpts;i++){
        vector <float> tempvec(2);
        double a,b;ipfile>>a;ipfile>>b;
        tempvec[0]=float(a);tempvec[1]=float(b);
        coordinates[i]=(tempvec);
    }
    ipfile.close();

    int distarrcount=1;
    for(int i=1;i<numofpoints;i++){
        for(int j=i+1;j<=numofpoints;j++){
            distances[distarrcount++]=eucdist(i,j,coordinates);
        }
    }
    coordinates.erase(all(coordinates));
    return;
}


float getdist(int first,int second,float *distances){
    if(first>second)
        swap(first,second);
    int baseindex=0;
    for(int i=1;i<first;i++)
        baseindex=baseindex+(numofpoints-i);
    return distances[(baseindex+(second-first))];
}



void basecase(float temparr[][numofpoints+1],float *distances){
    for(int i=0;i<=int(pow(2,numofpoints));i++){
        temparr[i][1]=infinte;
    }
    for(int i=1;i<=numofpoints;i++){
        temparr[1][i]=getdist(i,1,distances);
    }
}

int tsp(){
    float distances[ncr(numofpoints,2)+1];
    readandcalcdist(distances);

    float temparr[int(pow(2,numofpoints))+1][numofpoints+1];
    
    basecase(temparr,distances);

    for(int setsize=2;setsize<numofpoints;setsize++){
        //construct newset out of otherset without dest vert. and of course without 1
        for(int destvert=2;destvert<=numofpoints;destvert++){
            int newset[numofpoints-2],newsetindex=0;
            for(int i=2;i<=numofpoints;i++){
                if(i==destvert)
                    continue;
                newset[newsetindex++]=i;
            }

            int n=newsetindex;int r=setsize-1;

            std::string bitmask(r, 1); // K leading 1's
            bitmask.resize(n, 0); // N-K trailing 0's

            // print integers and permute bitmask
            do {

                int combinationsindex=0;
                int holder[r];

                for (int i = 0; i < n; ++i) // [0..N-1] integers
                {
                    if (bitmask[i])
                        holder[combinationsindex++]=newset[i];
                }
                
                float mindist=infinte;
                bitset<numofpoints> binnum;
                binnum.set(0,true);

                for(int k=2;k<=numofpoints;k++)
                    binnum.set(k-1,false);

                for(int j=0;j<r;j++){
                    binnum.set((holder[j]-1),true);
                }

                mindist=infinte;
                for(int k=1;k<=r;k++){

                        binnum.set(holder[k-1]-1,false);
                        int tempnum=binnum.to_ulong();
                        if(definitelyLessThan(temparr[tempnum][holder[k-1]]+getdist(holder[k-1],destvert,distances),mindist)){
                            mindist=temparr[tempnum][holder[k-1]]+getdist(holder[k-1],destvert,distances);
                        }
                        binnum.set(holder[k-1]-1,true);

                }
                temparr[binnum.to_ulong()][destvert]=mindist;

            } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

        }
    }


    bitset<numofpoints> finally;
    for(int i=0;i<numofpoints;i++)
        finally.set(i,true);

    int indice;
    int tempcount=1;

    float tspdist=infinte;
    for(int i=2;i<=numofpoints;i++){
        finally.set(tempcount,false);
        indice=finally.to_ulong();

        if(definitelyLessThan(temparr[indice][i]+getdist(i,1,distances),tspdist))
            tspdist=temparr[indice][i]+getdist(i,1,distances);
        finally.set(tempcount++,true);
    }
    cout<<tspdist;

    return 0;

}

int main(int argc, char **argv){

	const rlim_t kStackSize = 2048 * 1024 * 1024;   // min stack size = 2 GB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

	tsp();
	return 0;
}

