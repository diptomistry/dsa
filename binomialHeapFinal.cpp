#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    int degree; // number of child
    Node *child; // left most child
    Node *sibling; // node at right side
    Node *parent;

    Node(int key) {
        data = key;
        degree = 0;
        child = NULL;
        sibling = NULL;
        parent = NULL;
    }
};

Node* track[1003];

// combines two binomial trees with the same degree****
// root1 is combined into root2(root2 to be the new root)
Node* combineBinomialTrees(Node *root1, Node *root2) {//The function takes two pointers to the root nodes of the trees (root1 and root2) as input and returns a pointer to the new root node of the combined tree.
    if(root1->data < root2->data) swap(root1, root2);//The function starts by comparing the data values of the two root nodes (root1->data and root2->data) and swapping them if necessary so that root1 has the larger data value. This ensures that the combined tree will preserve the min-heap property of the binomial heap data structure.

    root1->parent = root2;//root2 on root1 parent
    root1->sibling = root2->child;//sib(right),left
    root2->child = root1;
    root2->degree++;

    return root2;
    //The function  updates the pointers of the nodes to combine them into a single tree. root1 becomes a child of root2, so root1->parent is set to root2, root1->sibling is set to root2->child, and root2->child is set to root1. The degree of root2 is also incremented to reflect the addition of root1 as a child.

//Finally, the function returns a pointer to the new root node of the combined tree, which is root2.
}


Node* mergeBinomialHeaps(Node *head1, Node *head2) {
    Node *head = NULL;

    //If both heaps are non-empty, the function selects the head node of the merged heap based on the degrees of the head nodes of the input heaps. Specifically, if the degree of head1 is less than or equal to the degree of head2, then head1 becomes the head of the merged heap, and vice versa.
    if(head1 == NULL && head2 == NULL) return NULL;
    else if(head2 == NULL) return head1;
    else if(head1 == NULL) return head2;
    else if(head1->degree <= head2->degree) {//head1 should become the new root of the merged heap
        head = head1;//the line head = head1; updates the reference to the new root of the merged heap, and the line head1 = head1->sibling; moves to the next tree in the sibling list, preparing for the next iteration of merging.
        head1 = head1->sibling;
    }
    else {
        head = head2;
        head2 = head2->sibling;
    }

    Node *temp = head;
    //to merge the remaining nodes of the two heaps
    while(head1 != NULL && head2 != NULL) {
        if(head1->degree <= head2->degree) {// It compares the degrees of the current nodes (head1->degree and head2->degree) and appends the node with the smaller degree to the end of the merged heap. The function also updates the sibling pointers of the nodes to maintain the linked list structure of the heap.
            temp->sibling = head1;
            temp = temp->sibling;
            head1 = head1->sibling;
        }
        else {
            temp->sibling = head2;
            temp = temp->sibling;
            head2 = head2->sibling;
        }
    }

    while(head1 != NULL) {
        temp->sibling = head1;
        temp = temp->sibling;
        head1 = head1->sibling;
    }

    while(head2 != NULL) {
        temp->sibling = head2;
        temp = temp->sibling;
        head2 = head2->sibling;
    }

    return head;
    //After merging all nodes of the input heaps, the function returns a pointer to the head node of the merged heap.
}
//This code defines a function unionBinomialHeaps that merges two binomial heaps into a single binomial heap and removes any duplicate trees (i.e., trees with the same degree) from the merged heap.
Node* unionBinomialHeaps(Node *head1, Node *head2) {
    Node *head = mergeBinomialHeaps(head1, head2);//The union operation is used to combine two binomial heaps, but unlike merge, it also allows for merging two heaps with the same degree.

    if(head == NULL || head->sibling == NULL) {//The function starts by calling the mergeBinomialHeaps function to merge the two input heaps into a single heap. If the merged heap is empty or has only one tree, it returns the merged heap as is.
        return head;
    }

    Node *px = NULL, *x = head, *nx = head->sibling, *snx = head->sibling->sibling;
    //If the merged heap has multiple trees, the function sets up a loop to remove any duplicate trees. The loop uses four pointers to keep track of the current tree (x), the previous tree (px), the next tree (nx), and the tree after the next tree (snx). The function starts with x and nx set to the first and second trees in the merged heap, respectively, and px and snx set to NULL.

    while(nx != NULL) {//In each iteration of the loop, the function compares the degrees of x and nx to determine if they are duplicates. If they are not duplicates (i.e., they have different degrees or snx has a different degree than nx), the function updates the pointers to move to the next pair of trees (px = x, x = nx, nx = snx, snx = (snx != NULL) ? snx->sibling : NULL).
        if(x->degree != nx->degree || (snx != NULL && nx->degree == snx->degree)) {
            px = x;
            x = nx;
            nx = snx;
            if(snx != NULL) snx = snx->sibling;
        }
        else {//f x and nx are duplicates, the function uses the combineBinomialTrees function to merge the two trees into a single tree with a higher degree. The function then updates the sibling pointer of x to skip nx, updates the sibling pointer of px (or the head pointer if px is NULL) to point to the merged tree, and updates the pointers to move to the next pair of trees as before.
            x = combineBinomialTrees(x, nx);
            if(px == NULL) {
                head = x;
            }
            else {
                px->sibling = x;
            }
            x->sibling = snx;
            nx = snx;
            if(snx != NULL) snx = snx->sibling;
        }
   }

    return head;//After removing all duplicate trees, the function returns a pointer to the head node of the final merged heap.
}

void insertion(Node *&head, int key) {
    Node *newnode = new Node(key);
    track[key] = newnode;
    head = unionBinomialHeaps(head, newnode);
}
//reverses the order of a linked list of binomial trees
void reverseLinkedList(Node *&head) {
    Node* prev = NULL;
    Node* curr = head;

 while(curr != NULL) {
    curr->parent = NULL; // set parent pointer to null
    Node *temp = curr->sibling; // temporary pointer to sibling node
    curr->sibling = prev; // set sibling pointer to previous node
    prev = curr; // set previous pointer to current node
    curr = temp; // set current pointer to temporary node
}

head = prev; // update head pointer to the new head of the reversed list

}
// function to delete a node from a binomial heap
Node* deleteNode(Node *head, Node *node) {
    Node *px = NULL, *x = head;
    while(1) {
        if(x == node) {
            break;
        }
        px = x;
        x = x->sibling;
    }

    if(px != NULL) {
    px->sibling = x->sibling; // remove the node from the sibling list of its parent
}
else {
    head = x->sibling; // the deleted node was the root node
}

Node *newHead = x->child; // reverse the order of the children of the deleted node
reverseLinkedList(newHead);

track[x->data] = NULL; // remove the deleted node from the track array
delete(x); // delete the node

return unionBinomialHeaps(head, newHead); // union the resulting heap with the main heap and return it

}
// function to extract the minimum value from a binomial heap
int extractMin(Node *&head) {
    Node *Min = head;
    Node *temp = head->sibling;

    while(temp != NULL) {
        if(temp->data < Min->data) {
            Min = temp;
        }
        temp = temp->sibling;
    }
    int min = Min->data;

    head = deleteNode(head, Min);// delete the node with minimum value from the heap

    return min;
}
// function to get the minimum value from a binomial heap
int getMin(Node *head) {
    Node *Min = head;
    Node *temp = head->sibling;

    while(temp != NULL) {
        if(temp->data < Min->data) {
            Min = temp;
        }
        temp = temp->sibling;
    }

    return Min->data;
}

// function to decrease the key of a node in a binomial heap
void decreaseKey(Node *&head, int key, int decreaseTo) {
Node *node = track[key]; // get the node with the given key
node->data = decreaseTo; // update the value of the node to the new value
track[decreaseTo] = node; // update the track array with the new key-node mapping
track[key] = NULL; // remove the previous key-node mapping
// swap the node with its parent until the parent has smaller value
    while(node->parent != NULL && node->parent->data > node->data) {
        swap(node->data, node->parent->data);
        swap(track[node->data], track[node->parent->data]);
        node = node->parent;
    }
}

// function to delete a node with given key from a binomial heap
void deletion(Node *&head, int key) {
decreaseKey(head, key, 0); // decrease the key of the node to 0
head = deleteNode(head, track[0]); // delete the node with key
}

void print(Node *head) {
    if(head == NULL) return;
    print(head->child);
    cout << head->data << ' ';
    print(head->sibling);
}

int main() {
    Node *head = NULL;
    int arr[] = {4, 6, 3, 11, 9, 5, 14, 10, 21, 7, 13, 20, 2};
    for(int i = 0; i < 13; i++) {
        insertion(head, arr[i]);
    }
    print(head); cout << '\n';

    cout << extractMin(head) << '\n';
    cout << extractMin(head) << '\n';
    print(head); cout << '\n';

    //cout << extractMin(head) << '\n';

    decreaseKey(head, 14, 3);
    print(head); cout << '\n';

    deletion(head, 20);
    print(head); cout << '\n';
    Node *head1 = NULL, *head2 = NULL;
    int arr1[] = {4, 6, 3, 11, 9};
    int arr2[] = {5, 14, 10, 21, 7, 13, 20, 2};

    for(int i = 0; i < 5; i++) {
        insertion(head1, arr1[i]);
    }
    for(int i = 0; i < 8; i++) {
        insertion(head2, arr2[i]);
    }

    cout << "Heap 1: ";
    print(head1);
    cout << endl;

    cout << "Heap 2: ";
    print(head2);
    cout << endl;

    Node *head3 = mergeBinomialHeaps(head1, head2);

    cout << "Merged Heap: ";
    print(head3);
    cout << endl;

    return 0;
}