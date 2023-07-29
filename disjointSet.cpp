#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MULTIPLE_TEST int t;cin>>t;while(t--)
#define PI (2*acos(0.0))

//local array size = 1e5, global = 1e8
//int = 1e9, long long = 1e18
// 1 sec = 1e7 ~ 1e8

const int N = 1e7+10, mod = 1e9+7;

class DisjointSet
{
private: //private variables and functions
    int n; //number of elements in the set
    int* parent; //an array to store the parent of each element
    int* rank; //an array to store the rank of each element (the height of its subtree)

public: //public variables and functions
    DisjointSet(int n); //constructor function to initialize the set
    void make(int i); //helper function to initialize a single element
    void makeSet(); //function to initialize the entire set
    int find(int i); //function to find the root of an element
    void Union(int a, int b); //function to merge two elements into a single set
};

//Constructor function for the DisjointSet class
DisjointSet::DisjointSet(int n)
{
    parent = new int[n]; //allocate memory for the parent array
    memset(parent,-1, sizeof parent); //initialize all elements of parent array to -1 (signifies that they are root nodes)
    rank = new int[n]; //allocate memory for the rank array
    memset(rank,-1, sizeof rank); //initialize all elements of rank array to -1 (signifies that they are the root of a tree with height 1)
    this->n = n; //store the number of elements in the set

    makeSet(); //initialize the entire set
}

//Helper function to initialize a single element
void DisjointSet::make(int a){
    parent[a] = a; //the parent of a is itself (initially)
    rank[a]=1; //the rank of a is 1 (initially)
}

//Function to initialize the entire set
void DisjointSet::makeSet(){
    for (int i = 0; i < n; i++)
    {
        parent[i]=i; //the parent of each element is itself (initially)
    }
    
}

//Function to find the root of an element (with path compression optimization)
int DisjointSet::find(int i){
    if(parent[i]==i) return i; //if i is the root of its tree, return i

    return parent[i] = find(parent[i]); //otherwise, set the parent of i to be the root of its tree, and return that root
}
void DisjointSet::Union(int a, int b){ //Function to merge two elements into a single set (with union by rank optimization)
    a = find(a); //find the root of a
    b = find(b); //find the root of b

    if(a==b) return; //if a and b are already in the same set, there's no need to merge them

    if(rank[a]<rank[b]){ //if the rank of a's tree is less than that of b's tree, make b the parent of a
        parent[a] = b;
    }
    else if(rank[b]<rank[a]){ //if the rank of b's tree is less than that of a's tree, make a the parent of b
        parent[b]=a;
    }
    else{ //if the ranks are equal, make one the parent of the other and increment the rank of the new parent
        parent[b]=a;
        rank[a]++;
    }
}

bool hasCycle(vector<int> adj[], int n){ //Function to check if a graph represented by an adjacency list has a cycle
    DisjointSet* d = new DisjointSet(n); //initialize a disjoint set with n elements

    for (int i = 0; i < n; i++) //loop through all nodes in the graph
    {
        for(int j: adj[i]){ //loop through all neighbors of the current node
            int rootI = d->find(i); //find the root of the current node's tree
            int rootJ = d->find(j); //find the root of the neighbor's tree

            if(rootI==rootJ) return true; //if they have the same root, there's a cycle in the graph
            else d->Union(i,j); //otherwise, merge the two nodes into the same set
        }
    }
    return false; //if we make it through all nodes and edges without finding a cycle, there isn't one
}






int main(){

    fastio
    DisjointSet* d = new DisjointSet(5);

    d->Union(0,2);
    d->Union(4,2);
    d->Union(3,1);

    if (d->find(4) == d->find(0))
        cout << "Yes\n";
    else
        cout << "No\n";
    if (d->find(1) == d->find(0))
        cout << "Yes\n";
    else
        cout << "No\n";
 
    

    return 0;
}