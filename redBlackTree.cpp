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
enum Color {RED, BLACK};

struct Node {
    int value;
    Color color;
    Node *left, *right, *parent;

    Node(int k) {
        value = k;
        color = RED;
        left = right = parent = nullptr;
    }
};

class RedBlackTree {
private:


    Node *root;

    void leftRotate(Node *x);
    void rightRotate(Node *x);
    void fixInsert(Node *x);
    void fixDelete(Node *x);
    void transplant(Node* u, Node* v);
    Node* findNode(int k);

public:
    RedBlackTree() {
        root = nullptr;
    }

    void insert(int k);
    void remove(int k);
    void printInorder();
    void printLevelOrder();
    int getMin();
    int getMax();
    bool contains(int k);
};

void RedBlackTree::leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left != nullptr) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}


void RedBlackTree::rightRotate(Node *y) {
    Node *x = y->left;
    y->left = x->right;

    if (x->right != nullptr) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

void RedBlackTree::fixInsert(Node *x) {
    while (x != root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            Node *y = x->parent->parent->right;
            if (y != nullptr && y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    leftRotate(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rightRotate(x->parent->parent);
            }
        } else {
            Node *y = x->parent->parent->left;
            if (y != nullptr && y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    rightRotate(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                leftRotate(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::fixDelete(Node *x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

Node* RedBlackTree::findNode(int value) {
    Node* curr = root;
    while (curr != nullptr) {
        if (value == curr->value) {
            return curr;
        } else if (value < curr->value) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return nullptr;
}

void RedBlackTree::insert(int value) {
    Node* newNode = new Node(value);
    if (root == nullptr) {
        root = newNode;
        root->color = Color::BLACK;
        return;
    }

    Node* parent = nullptr;
    Node* curr = root;
    while (curr != nullptr) {
        parent = curr;
        if (value < curr->value) {
            curr = curr->left;
        } else if (value > curr->value) {
            curr = curr->right;
        } else {
            // Value already exists in tree, do not insert
            delete newNode;
            return;
        }
    }

    newNode->parent = parent;
    if (value < parent->value) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    fixInsert(newNode);
}

void RedBlackTree::remove(int value) {
    Node* node = findNode(value);
    if (node == nullptr) {
        // Node not found, do not remove
        return;
    }

    Node* y = node;
    Color y_original_color = y->color;
    Node* x = nullptr;

    if (node->left == nullptr) {
        x = node->right;
        transplant(node, node->right);
    } else if (node->right == nullptr) {
        x = node->left;
        transplant(node, node->left);
    } else {
        y = minimum(node->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == node) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        transplant(node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }

    delete node;

    if (y_original_color == Color::BLACK) {
        fixDelete(x);
    }
}

Node* minimum(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}


void RedBlackTree::printInorder() {
    if (root == nullptr) {
        std::cout << "Tree is empty.\n";
        return;
    }

    printInorderHelper(root);
}



void printInorderHelper(const Node* node) {
    if (node != nullptr) {
        printInorderHelper(node->left);
        std::cout << node->value << " ";
        printInorderHelper(node->right);
    }
}

void RedBlackTree::printLevelOrder() {
    if (root == nullptr) {
        std::cout << "Tree is empty.\n";
        return;
    }

    std::queue<const Node*> nodesQueue;
    nodesQueue.push(root);

    while (!nodesQueue.empty()) {
        const Node* node = nodesQueue.front();
        nodesQueue.pop();
        std::cout << node->value << " ";

        if (node->left != nullptr) {
            nodesQueue.push(node->left);
        }

        if (node->right != nullptr) {
            nodesQueue.push(node->right);
        }
    }
}

bool RedBlackTree::contains(int value) {
    const Node* node = root;
    while (node != nullptr) {
        if (value < node->value) {
            node = node->left;
        }
        else if (value > node->value) {
            node = node->right;
        }
        else { // value == node->value
            return true;
        }
    }
    return false;
}

void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}




int main(){

    fastio

    

    return 0;
}