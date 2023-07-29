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

class BinarySearchTree{
public:
    int* arr;
    int root = 0;
    
    BinarySearchTree(int capacity){
        arr = new int[4*capacity];
        memset(arr,-1,sizeof(arr));
    }

    int parent(int index){
        return (index-1)/2;
    }

    int left(int index){
        return (index*2)+1;
    }

    int right(int index){
        return (index*2)+2;
    }

    void insert(int root,int value){
        if(arr[root] == -1){
            arr[root]=value;
        }
        else if(value<=arr[root]){
            insert(left(root),value);
        }
        else{
            insert(right(root),value);
        }
    }

    void insertIter(int value){
        int root = arr[0];
        if(root==-1){
            root = value;
            return;
        }
        int curr = root;
        while(arr[curr]!=-1){
            if(value<=arr[curr]) curr = left(curr);
            else if(value>arr[curr]) curr = right(curr);
        }
        arr[curr]=value;
    }

    int findMin(int root){
        while(arr[left(root)]!=-1){
            root = left(root);
        }return root;
    }

    void remove(int root, int value){
        if(arr[root]==-1) return;
        else if(value<arr[root]) remove(left(root),value);
        else if(value> arr[root]) remove(right(root),value);

        else{
            if(arr[left(root)]==-1){
                arr[root]=arr[right(root)];
            }
            if(arr[right(root)]==-1){
                arr[root]=arr[left(root)];
            }
            else{
                int min = findMin(right(root));
                arr[root]=arr[min];
                arr[min]=-1;
            }

        }
    }

    int find(int root, int value){
        if(arr[root]==-1)
            return -1;
        
        if(value==arr[root]) return root;
        else if(value<arr[root]) root = left(root);
        else root = right(root);
    }

    int height(int root){
        if(root==-1) return 0;

        return 1+ max(height(left(root)),height(right(root)));
    }

    bool isBalanced(int root){
        if(arr[root]==-1) return true;

        int lh = height(left(root));
        int rh = height(right(root));

        if(isBalanced(left(root)) and isBalanced(right(root)) and abs(lh-rh)<=1) return true;

        return false;
    }
    //either 0 or 2 children
    bool isFull(int root){
        if(arr[root]==-1) return true;

        if(arr[left(root)]==-1 and arr[right(root)]==-1) return true;

        if(arr[left(root)]!=-1 and arr[right(root)]!=-1){
            return isFull(left(root)) and isFull(right(root));
        }
        return false;
    }

    bool isComplete(int root){
        if(arr[root]==NULL) return true;

        queue<int> q;
        // Create a flag variable which will be set true
        // when a non-full node is seen
        bool flag = false;
        // Do level order traversal using queue.
        q.push(root);

        while(!q.empty()){
            int temp = q.front();
            q.pop();

            /* Check if left child is present*/
            if(arr[left(root)]!=-1){
                // If we have seen a non-full node, and we see a node
                // with non-empty left child, then the given tree is not
                // a complete Binary Tree
                if(flag) return false;
                // Enqueue Left Child
                q.push(left(root));
            }
            else flag = true;
            /* Check if right child is present*/
            if(arr[right(root)]!=-1){
                // If we have seen a non full node, and we see a node
                // with non-empty right child, then the given tree is not
                // a complete Binary Tree
                if(flag) return false;
                // Enqueue Right Child
                q.push(right(root));
            }
            // If this a non-full node, set the flag as true
            else flag = true;
        }
        /* If we reach here, then the tree is complete Binary Tree*/
        return true;
    }

    //all nodes except leaf have two children, all leaf at same level
    bool checkPerfect(int root,int level, int depth){
        if(arr[root]==-1) return true;

        if(arr[left(root)]==-1 && arr[right(root)]==-1)
            return depth==level+1;
        if(arr[left(root)]==-1 || arr[right(root)]==-1)
            return false;
        
        return checkPerfect(left(root),level+1,depth) && checkPerfect(right(root),level+1,depth);
    }

    bool isPerfect(int root){
        int lh = height(root);
        return checkPerfect(root,0,lh);
    }

    bool isDegenerate(int root){
        if(arr[root]==-1) return true;

        if(arr[left(root)]!=-1 and arr[right(root)]!=-1) 
            return false;

        if(arr[left(root)]==-1) return isDegenerate(right(root));
        else return isDegenerate(left(root));
    }

    bool isLeftSkewed(int root){
        int rh = height(right(root));
        return rh==0;
    }
    bool isRightSkewed(int root){
        int lh = height(left(root));
        return lh==0;
    }

    
};

int main(){

    fastio

    

    return 0;
}