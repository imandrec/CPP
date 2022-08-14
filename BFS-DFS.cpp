#include <queue>
#include <stack>
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;


class Graph {   
    //I'm using the adjacency list method for the graph structure
    
    int Vertices;
    list<int>* adj;
public:
    Graph(int Vertices) {
        this->Vertices = Vertices;
        adj = new list<int>[Vertices];
    }
    void addEdge(int source, int destination) {
        adj[source].push_back(destination);
        adj[destination].push_back(source);

    }
    
//Breadth-First Search 
    void BFS(int startingNode) {
        cout << "BFS traversal\n";
        vector <bool> visited(this->Vertices, false);

        queue<int> Q;
        visited[startingNode] = true;
        Q.push(startingNode);


        list<int>::iterator it;

        while (!Q.empty()) {
            int current = Q.front();
            cout << current << "-> ";
            Q.pop();
            for (it = adj[current].begin(); it != adj[current].end(); ++it) {
                int v = *it;
                if (!visited[v]) {
                    visited[v] = true;
                    Q.push(v);
                }
            }
        }
    }

// Depth-First Search
    void DFS(int startingNode) {
        cout << "\n\nDFS traversal\n";
        vector <bool> visited(this->Vertices, false);

        stack<int> Stack;
        visited[startingNode] = true;
        Stack.push(startingNode);


        list<int>::iterator it;

        while (!Stack.empty()) {
            int current = Stack.top();
            cout << current << "-> ";
            Stack.pop();
            for (it = adj[current].begin(); it != adj[current].end(); ++it) {
                int v = *it;
                if (!visited[v]) {
                    visited[v] = true;
                    Stack.push(v);
                }
            }
        }
    }
    ~Graph() {
        delete[] adj;
    }
};


int main() {
    Graph graph(9);
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(0, 8);
    graph.addEdge(1, 7);
    graph.addEdge(3, 2);
    graph.addEdge(3, 4);
    graph.addEdge(8, 4);
    graph.addEdge(2, 5);
    graph.addEdge(5, 6);
    
    
    graph.BFS(0); //Question 1 solution-Breadth-First Search 
    graph.DFS(0); //Question 2 solution-Depth-First Search
    cout << "\n\n\n\n";
    
    return 0;
}
