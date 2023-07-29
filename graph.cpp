#include <bits/stdc++.h>
using namespace std;

template <typename T>
class CircularQueue
{
private:
    T *arr;
    int front;
    int rear;
    int capacity;

public:
    CircularQueue(int size)
    {
        arr = new T[size];
        capacity = size;
        front = -1;
        rear = -1;
    }

    ~CircularQueue()
    {
        delete[] arr;
    }

    bool isEmpty() const
    {
        return (front == -1);
    }

    bool isFull() const
    {
        return ((rear + 1) % capacity == front);
    }

    void enqueue(T element)
    {
        if (isFull())
        {
            cout << "Queue is full\n";
            return;
        }
        if (isEmpty())
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % capacity;
        }
        arr[rear] = element;
    }

    T dequeue()
    {
        T element;
        if (isEmpty())
        {
            cout << "Queue is empty\n";
            return element;
        }
        else if (front == rear)
        {
            element = arr[front];
            front = -1;
            rear = -1;
        }
        else
        {
            element = arr[front];
            front = (front + 1) % capacity;
        }
        return element;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty\n";
            return;
        }
        int i;
        for (i = front; i != rear; i = (i + 1) % capacity)
        {
            cout << arr[i] << " ";
        }
        cout << arr[i] << std::endl;
    }
};

// Define the node structure for the linked list
struct Node
{
    int data;
    Node *next;
    Node(int d) : data(d), next(nullptr) {}
};

// Define the adjacency list class
class Graph
{
private:
    int V;          // Number of vertices
    Node **adjList; // Array of linked lists
    int adjmatrix[1000][1000];
    bool visit[1000];
    int parent[1000];
    int start[1000];
    int end[1000];
    int time;

public:
    Graph(int V)
    {
        this->V = V;
        adjList = new Node *[V + 1];
        time = 0;
        for (int i = 0; i <= V; i++)
        {
            adjList[i] = nullptr;
            visit[i] = false;
        }
        for (int i = 0; i <= V; i++)
        {
            for (int j = 0; j <= V; j++)
            {
                adjmatrix[i][j] = 0;
            }
        }
    }

    // Add an edge to the graph
    void addEdge(int src, int dest)
    {
        // Create a new node for the destination vertex
        Node *newNode = new Node(dest);
        // Add the node to the front of the source vertex's linked list
        newNode->next = adjList[src];
        adjList[src] = newNode;

        // If the graph is undirected, add the reverse edge as well
        // Comment this out if the graph is directed
        newNode = new Node(src);
        newNode->next = adjList[dest];
        adjList[dest] = newNode;
        adjmatrix[src][dest] = 1;
    }

    // Print the adjacency list representation of the graph
   void printlist()
 {
// Loop through each vertex
for (int i = 0; i < V; i++)
{
// Get the head node of the adjacency list of the current vertex
Node *node = adjList[i];
// Print the current vertex
cout << i << " -> ";
// Loop through each adjacent vertex of the current vertex
while (node != nullptr)
{
// Print the adjacent vertex
cout << node->data << " ";
// Move to the next adjacent vertex
node = node->next;
}
// Print a new line after all adjacent vertices have been printed
cout << endl;
}
// Print a new line after all vertices and their adjacent vertices have been printed
cout << endl;
 }







 // Print the adjacency matrix representation of the graph
void printmatrix()
{
// Loop through all rows
for (int i = 0; i < V; i++)
{
// Loop through all columns
for (int j = 0; j < V; j++)
{
// Print the value in the matrix at position (i,j)
cout << adjmatrix[i][j] << ' ';
}
// Move to next row and add new line
cout << endl;
}
// Add extra new line after printing matrix
cout << endl;
}
// This function performs Breadth First Search starting from the given 'start' vertex
// It initializes the distances of all vertices to infinity and uses a circular queue to keep track of visited vertices
// The distance of the start vertex is set to 0
// The function then dequeues vertices from the queue and traverses its neighbors to update their distances
// The function prints the visited vertices in BFS order
   int dist[1000]; // array to keep track of distances of vertices from the starting vertex
void bfs(int start)
{
// Initialize distances of all vertices to infinity
for (int i = 0; i < V; i++)
{
dist[i] = INT_MAX;
}// Create a circular queue and enqueue the starting vertex
CircularQueue<int> q(V);
q.enqueue(start);

// Set the distance of the start vertex to 0
dist[start] = 0;

// Traverse the graph using BFS
while (!q.isEmpty())
{
    // Dequeue a vertex and print it
    int vertex = q.dequeue();
    cout << vertex << " ";

    // Traverse the neighbors of the dequeued vertex
    for (Node *neighbor = adjList[vertex]; neighbor != nullptr; neighbor = neighbor->next)
    {
        int neighbor_vertex = neighbor->data;
        if (dist[neighbor_vertex] == INT_MAX)
        {
            // If the neighbor vertex is not visited, enqueue it and update its distance
            q.enqueue(neighbor_vertex);
            dist[neighbor_vertex] = 1 + dist[vertex];
        }
    }
}

// Print a new line after printing all the visited vertices
cout << endl;

    }

    // A function to perform DFS traversal of the graph starting from given vertex
void dfs(int vertex)
{
// Mark the current vertex as visited and record the starting time
visit[vertex] = true;
start[vertex] = time++;
cout << vertex << " ";

       // Traverse all the neighbors of the current vertex recursively
for (Node *neighbor = adjList[vertex]; neighbor != nullptr; neighbor = neighbor->next)
{
    int child = neighbor->data;
    if (visit[child])
        continue;
    parent[child] = vertex;
    dfs(child);
}

// Record the finishing time of the current vertex
end[vertex] = time++;

    }
};

// Driver code
int main()
{
    // Create a graph with 5 vertices
    Graph g(5);

    // Add some edges
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Print the graph
    g.printlist();
    g.printmatrix();
    g.bfs(0);
    g.dfs(0);

    return 0;
}