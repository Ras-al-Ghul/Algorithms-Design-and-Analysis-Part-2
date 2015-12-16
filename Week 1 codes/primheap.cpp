#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <climits>
#include <utility>
using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;

int minele;

#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i=(c).begin();i!=(c).end();i++)

int readfromfile(multimap<int,vector<int> > &graph){
    ifstream dupipfile("edges.txt",ios::in);
    int numofvertices,numofedges;
    dupipfile>>numofvertices>>numofedges;
    int temp1,temp2,temp3;
    minele=INT_MAX;
    multimap<int,vector<int > > dupgraph;
    while(dupipfile>>temp1>>temp2>>temp3){
        if(temp3<minele)
            minele=temp3;
        vi temp;
        temp.push_back(temp2);temp.push_back(temp3);temp.push_back(0);
        dupgraph.insert(std::pair<int,vector<int> >(temp1,temp));
    }

    dupipfile.close();

    ofstream dupsopfile("edges.txt",ios::app);
    tr(dupgraph,it){
        dupsopfile<<(*it).second[0]<<"\t"<<(*it).first<<"\t"<<(*it).second[1]<<endl;
    }
    dupsopfile.close();

    ifstream ipfile("edges.txt",ios::in);
    ipfile>>numofvertices>>numofedges;
    while(ipfile>>temp1>>temp2>>temp3){
        vi temp;
        temp.push_back(temp2);temp.push_back(temp3-minele);temp.push_back(0);
        graph.insert(std::pair<int,vector<int> >(temp1,temp));
    }
    ipfile.close();
    return numofvertices;
}

class MinHeap
{
    vvi harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    // Constructor
    MinHeap(int capacity);

    // to heapify a subtree with root at given index
    void MinHeapify(int );

    int parent(int i) { return (i-1)/2; }

    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // to extract the root which is the minimum element
    vi extractMin();

    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val);

    // Returns the minimum key (key at root) from min heap
    vi getMin() { return harr[0]; }

    // Deletes a key stored at index i
    void deleteKey(int i);

    // Inserts a new key 'k'
    void insertKey(vi k);
    void swaps(vi & temp1, vi &temp2);
    void display(){
        return;
    }
    int mapvertices(vi &mapofvertices){
        for(int i=0;i<heap_size;i++){
            mapofvertices[harr[i][0]]=i;
        }
        return heap_size;
    }
    int returnsize(){return heap_size;}
};

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
}

// Inserts a new key 'k'
void MinHeap::insertKey(vi k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr.pb(k);

    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)][1] > harr[i][1])
    {
       swaps(harr[i], harr[parent(i)]);
       i = parent(i);
    }
}

// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
    if(new_val>=harr[i][1])
        return;
    harr[i][1] = new_val;
    while (i != 0 && harr[parent(i)][1] > harr[i][1])
    {
       swaps(harr[i], harr[parent(i)]);
       i = parent(i);
    }
}

// Method to remove minimum element (or root) from min heap
vi MinHeap::extractMin()
{
    vi temp;temp.pb(INT_MAX);
    if (heap_size <= 0)
        return temp;
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // Store the minimum vakue, and remove it from heap
    vi root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
}


// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();
}

// A recursive method to heapify a subtree with root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l][1] < harr[i][1])
        smallest = l;
    if (r < heap_size && harr[r][1] < harr[smallest][1])
        smallest = r;
    if (smallest != i)
    {
        swaps(harr[i], harr[smallest]);
        MinHeapify(smallest);
    }
}
void MinHeap::swaps(vi & temp1, vi &temp2)
{
    vi temp = temp1;
    temp1 = temp2;
    temp2 = temp;
}


int main(){
    vi mapofvertices;

    multimap<int,vector<int> > graph;
    const int numofvertices=readfromfile(graph);
    vvi vertices;
    for(int i=0;i<numofvertices;i++){
        vi temp;temp.pb(i+1),temp.pb(INT_MAX),temp.pb(0);
        vertices.pb(temp);
    }
    vertices[0][1]=0;

    MinHeap verticesheap(numofvertices);
    tr(vertices,it){
        verticesheap.insertKey(*it);
    }

    int oldheapsize=verticesheap.returnsize();
    for(int i=0;i<oldheapsize+1;i++)
        mapofvertices.push_back(INT_MAX);

    int currentheapsize=verticesheap.mapvertices(mapofvertices);

    int arr[numofvertices+1];for(int i=0;i<numofvertices+1;i++)arr[i]=INT_MAX;
    int sum=0;
    while(verticesheap.returnsize()!=0){
        vi tempvertex=verticesheap.extractMin();
        sum=sum+tempvertex[1];
        verticesheap.mapvertices(mapofvertices);
        arr[tempvertex[0]]=1;
        pair<multimap<int,vector<int> >::iterator,multimap<int,vector<int> >::iterator> temppair=graph.equal_range(tempvertex[0]);
        for(multimap<int,vector<int> >::iterator it=temppair.first;it!=temppair.second;it++){
            if(arr[((*it).second[0])]!=1){
                verticesheap.decreaseKey(mapofvertices[(*it).second[0]],((*it).second[1]));
                verticesheap.mapvertices(mapofvertices);
            }
        }
    }
    cout<<"The final answer is "<<sum-((numofvertices-1)*(-minele))<<endl;

    return 0;
}

