#include <iostream>

using namespace std;

// A binomial tree node.
struct BinomialTree {
  int key;
  int degree;
  BinomialTree *child, *sibling, *parent;
};

// A binomial heap.
struct BinomialHeap {
  BinomialTree *head;
  int size;

  BinomialHeap() {
    head = nullptr;
    size = 0;
  }

  // Inserts a new node into the heap.
  void insert(int key) {
    BinomialTree *new_node = new BinomialTree();
    new_node->key = key;
    new_node->degree = 0;
    new_node->child = nullptr;
    new_node->sibling = nullptr;
    new_node->parent = nullptr;

    // Link the new node to the head of the heap.
    new_node->sibling = head;
    head = new_node;
    size++;
  }

  // Finds the minimum key in the heap.
  int findMin() {
    int min = INT_MAX;
    for (BinomialTree *tree = head; tree != nullptr; tree = tree->sibling) {
      if (tree->key < min) {
        min = tree->key;
      }
    }
    return min;
  }

  // Deletes the minimum key from the heap.
  void extractMin() {
    // Find the minimum key.
    int min = findMin();
    BinomialTree *min_tree = nullptr;
    for (BinomialTree *tree = head; tree != nullptr; tree = tree->sibling) {
      if (tree->key == min) {
        min_tree = tree;
        break;
      }
    }

    // If the minimum key is the only node in the heap, then simply set the head to nullptr.
    if (min_tree == head && min_tree->sibling == nullptr) {
      head = nullptr;
    } else {
      // Otherwise, we need to unlink the minimum key from the list.
      if (min_tree->sibling == nullptr) {
        // If the minimum key is the last node in the list, then we need to set the sibling of the previous node to nullptr.
        min_tree->sibling->parent = nullptr;
      } else {
        // Otherwise, we need to set the sibling of the minimum key to the sibling of the previous node.
        min_tree->sibling->parent = min_tree->parent;
      }

      // If the minimum key is the root of the heap, then we need to set the new root to the sibling of the minimum key.
      if (min_tree->parent == nullptr) {
        head = min_tree->sibling;
      } else {
        // Otherwise, we need to link the sibling of the minimum key to the parent of the minimum key.
        min_tree->parent->child = min_tree->sibling;
      }
    }

    // Free the memory associated with the minimum key.
    delete min_tree;
    size--;
  }

  // Decreases the key of a node in the heap.
  void decreaseKey(int key, int new_key) {
    for (BinomialTree *tree = head; tree != nullptr; tree = tree->sibling) {
      if (tree->key == key) {
        tree->key = new_key;
        break;
      }
    }
  }

  // Unions two binomial heaps.
  void mergeHeaps(BinomialHeap *other) {
    for (BinomialTree *tree = other->head; tree != nullptr; tree = tree->sibling) {
      insert(tree->key);
    }
  }

  // Gets the size of the heap.
  int getSize() {
    return size;
  }

  // Checks if the heap is empty.
  bool isEmpty() {
    return size == 0;
  }
};
int main() {
  BinomialHeap *heap = new BinomialHeap();

  // Insert some nodes into the heap.
  heap->insert(10);
  heap->insert(5);
  heap->insert(7);
  heap->insert(2);
  heap->insert(3);

  // Print the minimum key in the heap.
  std::cout << "The minimum key in the heap is " << heap->findMin() << std::endl;

  // Extract the minimum key from the heap.
  heap->extractMin();

  // Print the new minimum key in the heap.
  std::cout << "The new minimum key in the heap is " << heap->findMin() << std::endl;

  // Delete the heap.
  delete heap;

  return 0;
}

