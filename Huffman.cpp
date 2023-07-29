#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MULTIPLE_TEST int t;cin>>t;while(t--)
#define PI (2*acos(0.0))
#define MAX_TREE_HT 100

//local array size = 1e5, global = 1e8
//int = 1e9, long long = 1e18
// 1 sec = 1e7 ~ 1e8

const int N = 1e7+10, mod = 1e9+7;

class HeapNode{
public:
    char data;
    int freq;
    HeapNode* left;
    HeapNode* right;

    HeapNode(char data, int freq){
        this->data = data;
        this->freq = freq;
        this->left = this->right = NULL;
    }

    bool isLeaf();
};

bool HeapNode::isLeaf(){
    return !left && !right;
}

class MinHeap{
public:
    int size, capacity;
    HeapNode** arr;

    MinHeap(int capacity){
        this->capacity = capacity;
        this->size = 0;

        arr = new HeapNode*[capacity];
    }

    MinHeap(char data[], int freq[], int size){
        this->capacity = size;
        arr = new HeapNode*[capacity];
        for (int i = 0; i < size; i++){
            arr[i] = new HeapNode(data[i],freq[i]);
        }

        this->size = size;
        buildHeap();
    }

    void minHeapify(int indx);
    bool isSizeOne();
    HeapNode* extractMin();
    void insertNode(HeapNode* node);
    void buildHeap();
};

void swapNode(HeapNode** other, HeapNode** another){
    HeapNode* temp = *other;
    *other = *another;
    *another = temp;
}

void MinHeap::minHeapify(int indx){
    int smallest = indx;
    int left = 2*indx+1;
    int right = 2*indx+2;

    if(left<this->size and this->arr[left]->freq < this->arr[smallest]->freq){
        smallest = left;
    }
    if(right<this->size and this->arr[right]->freq < this->arr[smallest]->freq){
        smallest = right;
    }

    if(smallest!=indx){
        swapNode(&arr[smallest],&arr[indx]);
        minHeapify(smallest);
    }
}

bool MinHeap::isSizeOne(){
    return size==1;
}

HeapNode* MinHeap::extractMin(){
    HeapNode* temp = arr[0];
    arr[0] = arr[size-1];
    size--;
    minHeapify(0);
    return temp;
}

void MinHeap::insertNode(HeapNode* node){
    size++;
    int i = size-1;

    while(i and node->freq < arr[(i-1)/2]->freq){
        arr[i] = arr[(i-1)/2];
        i=  (i-1)/2;
    } 
    arr[i] = node;
}

void MinHeap::buildHeap(){
    int n = size-1;
    for (int i = (n-1)/2 ; i >= 0; i--)
    {
        minHeapify(i);
    }
}



HeapNode* buildHuffmanTree(char data[], int freq[], int size){
    HeapNode* left;
    HeapNode* right;
    HeapNode* top;

    MinHeap* minHeap = new MinHeap(data,freq,size);

    while(!minHeap->isSizeOne()){
        left = minHeap->extractMin();
        right = minHeap->extractMin();

        top = new HeapNode('$',left->freq+right->freq);
        top->left = left;
        top->right = right;

        minHeap->insertNode(top);
    }
    return minHeap->extractMin();
}

void printArr(int arr[], int n){
    for (int i = 0; i < n; i++)
    {
        cout<<arr[i];
    }
    cout<<'\n';
}

void printCodes(HeapNode* root, int arr[], int top){
    if(root->left){
        arr[top]=0;
        printCodes(root->left,arr,top+1);
    }
    if(root->right){
        arr[top]=1;
        printCodes(root->right,arr,top+1);
    }

    if(root->isLeaf()){
        cout<<root->data<<": ";
        printArr(arr,top);
    }

}

void printHuffmanCodes(char data[], int freq[], int size){
    HeapNode* root = buildHuffmanTree(data,freq,size);
    int arr[MAX_TREE_HT],top = 0;
    printCodes(root,arr,top);

}



int main(){

    fastio

    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
 
    int size = sizeof(arr) / sizeof(arr[0]);
 
    printHuffmanCodes(arr, freq, size);
   

    return 0;
}