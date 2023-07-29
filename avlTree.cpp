#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;
struct avl {
   int d;           // data stored in node
   struct avl *l;   // left child pointer
   struct avl *r;   // right child pointer
}*r;

class avl_tree {
   public:
      int height(avl *);       // function to get the height of a node
      int difference(avl *);   // function to get the difference in heights of left and right subtrees of a node
      avl *rr_rotat(avl *);    // function to perform right-right rotation on a node
      avl *ll_rotat(avl *);    // function to perform left-left rotation on a node
      avl *lr_rotat(avl*);     // function to perform left-right rotation on a node
      avl *rl_rotat(avl *);    // function to perform right-left rotation on a node
      avl * balance(avl *);    // function to balance the AVL tree starting from a node
      avl * insert(avl*, int); // function to insert a new node with given data into AVL tree
      void show(avl*, int);    // function to print AVL tree in ASCII format
      void inorder(avl *);     // function to do in-order traversal of AVL tree
      void preorder(avl *);    // function to do pre-order traversal of AVL tree
      void postorder(avl*);    // function to do post-order traversal of AVL tree
      
      avl_tree() {
         r = NULL;             // constructor to initialize the AVL tree
      }
};

int avl_tree::height(avl *t) {
   int h = 0;
   if (t != NULL) {
      int l_height = height(t->l);    // recursively get height of left subtree
      int r_height = height(t->r);    // recursively get height of right subtree
      int max_height = max(l_height, r_height);  // get maximum height among left and right subtree
      h = max_height + 1;              // add 1 to get height of the current node
   }
   return h;
}

int avl_tree::difference(avl *t) {
   int l_height = height(t->l);   // get height of left subtree
   int r_height = height(t->r);   // get height of right subtree
   int b_factor = l_height - r_height; // get balance factor of node
   return b_factor;
}

avl *avl_tree::rr_rotat(avl *parent) {
   avl *t;
   t = parent->r;            // get right child of parent
   parent->r = t->l;         // set left child of right child of parent as right child of parent
   t->l = parent;            // set parent as left child of right child of parent
   cout<<"Right-Right Rotation";  // print message for rotation
   return t;                 // return new parent
}

avl *avl_tree::ll_rotat(avl *parent) {
   avl *t;
   t = parent->l;            // get left child of parent
   parent->l = t->r;         // set right child of left child of parent as left child of parent
   t->r = parent;            // set parent as right child of left child of parent
   cout<<"Left-Left Rotation";    // print message for rotation
   return t;                 // return new parent
}

avl *avl_tree::lr_rotat(avl *parent) {
   avl *t;
   t = parent->l;            // Store the left child of the parent in t
   parent->l = rr_rotat(t);  // Perform a right-right rotation on the left child of parent
   cout<<"Left-Right Rotation";
   return ll_rotat(parent);  // Perform a left-left rotation on the parent
}


// Right-Left Rotation of AVL tree
avl *avl_tree::rl_rotat(avl *parent) {
avl *t;
t = parent->r;
parent->r = ll_rotat(t); // apply Left-Left Rotation on right child of parent
cout<<"Right-Left Rotation";
return rr_rotat(parent); // apply Right-Right Rotation on parent
}

// Balancing function for AVL tree
avl *avl_tree::balance(avl *t) {
int bal_factor = difference(t);
if (bal_factor > 1) {
if (difference(t->l) > 0)
t = ll_rotat(t); // Left-Left case
else
t = lr_rotat(t); // Left-Right case
} else if (bal_factor < -1) {
if (difference(t->r) > 0)
t = rl_rotat(t); // Right-Left case
else
t = rr_rotat(t); // Right-Right case
}
return t;
}

// Insertion function for AVL tree
avl *avl_tree::insert(avl *r, int v) {
if (r == NULL) {
r = new avl;
r->d = v;
r->l = NULL;
r->r = NULL;
return r;
} else if (v< r->d) {
r->l = insert(r->l, v);
r = balance(r); // balance the tree
} else if (v >= r->d) {
r->r = insert(r->r, v);
r = balance(r); // balance the tree
} return r;
}

// Function to show the AVL tree
void avl_tree::show(avl *p, int l) {
int i;
if (p != NULL) {
show(p->r, l+ 1);
cout<<" ";
if (p == r)
cout << "Root -> ";
for (i = 0; i < l&& p != r; i++)
cout << " ";
cout << p->d;
show(p->l, l + 1);
}
}

// Inorder Traversal of AVL tree
void avl_tree::inorder(avl *t) {
if (t == NULL)
return;
inorder(t->l);
cout << t->d << " ";
inorder(t->r);
}

// Preorder Traversal of AVL tree
void avl_tree::preorder(avl *t) {
if (t == NULL)
return;
cout << t->d << " ";
preorder(t->l);
preorder(t->r);
}

// Postorder Traversal of AVL tree
void avl_tree::postorder(avl *t) {
if (t == NULL)
return;
postorder(t ->l);
postorder(t ->r);
cout << t->d << " ";
}
int main() {
   int c, i;
   avl_tree avl;
   while (1) {
      cout << "1.Insert Element into the tree" << endl;
      cout << "2.show Balanced AVL Tree" << endl;
      cout << "3.InOrder traversal" << endl;
      cout << "4.PreOrder traversal" << endl;
      cout << "5.PostOrder traversal" << endl;
      cout << "6.Exit" << endl;
      cout << "Enter your Choice: ";
      cin >> c;
      switch (c) {
         case 1:
            cout << "Enter value to be inserted: ";
            cin >> i;
            r = avl.insert(r, i);
         break;
         case 2:
            if (r == NULL) {
               cout << "Tree is Empty" << endl;
               continue;
            }
            cout << "Balanced AVL Tree:" << endl;
            avl.show(r, 1);
            cout<<endl;
         break;
         case 3:
            cout << "Inorder Traversal:" << endl;
            avl.inorder(r);
            cout << endl;
         break;
         case 4:
            cout << "Preorder Traversal:" << endl;
            avl.preorder(r);
            cout << endl;
         break;
         case 5:
            cout << "Postorder Traversal:" << endl;
            avl.postorder(r);
            cout << endl;
         break;
         case 6:
            exit(1);
         break;
         default:
            cout << "Wrong Choice" << endl;
      }
   }
   return 0;
}