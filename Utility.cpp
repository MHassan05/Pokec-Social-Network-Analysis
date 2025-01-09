#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// an m-array tree that will help in building tree with different number of childs
class Tree
{
    class Node
    {
    public:
        int data;
        vector<Node *> children;
        Node(int data = 0)
        {
            this->data = data;
        }
    };

    Node *root;

public:
    Tree()
    {
        root = nullptr;
    }

    // function to insert data in tree
    void insert(int val)
    {
        if (root == nullptr)
        {
            root = new Node(val);
            return;
        }

        if (root->data == val)
        {
            return;
        }

        for (auto &child : root->children)
        {
            if (child->data == val)
            {
                return;
            }
        }
        this->root->children.push_back(new Node(val));
    }

    // function to display the performing all traversal algorithms 
    void Display()
    {
        if (root == nullptr)
        {
            return;
        }
        cout << "Pre-order Traversal: ";
        preOrderTraversal(root);
        cout << endl;

        cout << "BFS Traversal: ";
        BreadthFirstSearch(root);
        cout << endl;

        cout << "Post-order Traversal: ";
        postOrderTraversal(root);
        cout << endl;
    }

private:

    // Performs breadth-first search (BFS) starting from the given node 
    void BreadthFirstSearch(Node *nodeptr)
    {
        if(nodeptr == nullptr)
        {
            return;
        }
        
        queue<Node *> q;
        q.push(nodeptr);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();
            cout << current->data << " ";

            // Push all children of the current node into the queue for further exploration
            for (auto &child : current->children)
            {
                q.push(child);
            }
        }
    }

    // Performs pre-order traversal (visit root, then children)
    void preOrderTraversal(Node *nodeptr)
    {
        if (nodeptr == nullptr)
        {
            return;
        }

        cout << nodeptr->data << " ";
        for (auto &child : nodeptr->children)
        {
            preOrderTraversal(child);
        }
    }

    // Performs post-order traversal (visit children, then root)
    void postOrderTraversal(Node *nodeptr)
    {
        if (nodeptr == nullptr)
        {
            return;
        }

        for (auto &child : nodeptr->children)
        {
            postOrderTraversal(child);
        }
        cout << nodeptr->data << " ";
    }
};

class Graph
{
    int V; // contains maximum number of vertices
    vector<int> *adj;
    int newV;

public:
    Graph(int V)
    {
        this->V = this->newV = V;
        adj = new vector<int>[V];
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void display()
    {
        for (int i = 0; i < V; i++)
        {
            cout << i + 1 << " -> ";
            for (auto &v : adj[i])
            {
                cout << v + 1 << " ";
            }
            cout << "\n"
                 << endl;
        }
    }

// Try to color the graph using two colors (0 and 1)
    bool isBipartite()
    {
        vector<int> color(this->newV, -1);
        queue<int> q;

        for (int i = 0; i < this->newV; i++)
        {
            if (color[i] == -1)
            {
                color[i] = 0;
                q.push(i);

                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();

                    // Traverse all neighbors of the current vertex
                    for (auto &v : adj[u])
                    {
                        if (color[v] == -1)
                        {
                            color[v] = 1 - color[u];
                            q.push(v);
                        }
                        else if (color[v] == color[u])
                        {
                            return false;     // If a neighbor has the same color, the graph is not bipartite
                        }
                    }
                }
            }
        }
        return true;  // If all vertices can be colored without conflicts, the graph is bipartite
    }

    // function to resize the graph if it limits exceeds 
    void resizeGraph(int n)
    {
        if (n > this->newV)
        {
            vector<int> *newAdj = new vector<int>[n];
            for (int i = 0; i < this->newV; i++)
            {
                newAdj[i] = adj[i];
            }

            this->newV = n;
            delete[] adj;
            adj = newAdj;
        }
    }

    void kruskalMST()
    {
        vector<pair<int, int>> edges;

        // Add edges to the edge list
        for (int u = 0; u < this->newV; u++)
        {
            for (auto &v : adj[u])
            {
                if (u < v)
                {
                    edges.push_back({u, v});
                }
            }
        }

        vector<int> parent(this->newV, -1); // Keep track of connected components
        cout << "Spanning tree edges:" << endl;

        for (auto &edge : edges)
        {
            int u = edge.first;
            int v = edge.second;

            // Check if u and v are in the same component (using DFS/BFS or manual checking)
            if (findParent(u, parent) != findParent(v, parent))
            {
                cout << u + 1 << " - " << v + 1 << endl; // Add the edge to MST
                unionComponents(u, v, parent);           // Union the components
            }
        }
    }

private:
    // Helper function to find the parent (without DSU)
    int findParent(int u, vector<int> &parent)
    {
        while (parent[u] != -1)
        {
            u = parent[u];
        }
        return u;
    }

    // Helper function to union two components (without DSU)
    void unionComponents(int u, int v, vector<int> &parent)
    {
        int parentU = findParent(u, parent);
        int parentV = findParent(v, parent);

        if (parentU != parentV)
        {
            parent[parentU] = parentV; // Merge the components
        }
    }
};

//////////////////////////////////////   End of Utility File //////////////////////////////////////////////////////////
