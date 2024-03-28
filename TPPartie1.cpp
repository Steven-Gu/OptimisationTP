#include <iostream>
#include <vector>
using namespace std;
struct Node {
    int id;
    int color;
};

struct Graph {
    int V;
    vector<Node> nodes;
    vector<vector<int> > adj;

    Graph(int V) {
        this->V = V;
        nodes.resize(V);
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int countEdges() {
        int count = 0;
        for (int i = 0; i < V; i++) {
            count += adj[i].size();
        }
        return count / 2;
    }

    int countEdges(int id) {
        return adj[id].size();
    }

    void sortNodeByEdges() {
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (countEdges(i) < countEdges(j)) {
                    swap(nodes[i], nodes[j]);
                }
            }
        }
    }

    void addNode(int id, int color=0) {
        nodes[id].id = id;
        nodes[id].color = color;
    }

    void addNNodes(int n) {
        for (int i = 0; i < n; i++) {
            addNode(i);
        }
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
        cout << "Node " << nodes[i].id << " color " << nodes[i].color << " : ";
        for (int j = 0; j < adj[nodes[i].id].size(); j++) {
            cout << adj[nodes[i].id][j] << " ";
        }
        cout << endl;
    }
    }

    Node getNodeById(int id) {
        for(int i = 0; i < V; i++) {
            if (nodes[i].id == id) {
                return nodes[i];
            }
        }
        throw ("Node not found");
    } 

    void coloriage() {
        sortNodeByEdges();
        int color = 1;
        for (int i = 0; i < V; i++) {
            if (nodes[i].color == 0) {
                nodes[i].color = color;
                for (int j = 0; j < V; j++) {
                    if (nodes[j].color == 0) {
                        bool canColor = true;
                        for (int k = 0; k < adj[nodes[j].id].size(); k++) {
                            if (color == getNodeById(adj[nodes[j].id][k]).color) {
                                canColor = false;
                                break;
                            }
                        }
                        if (canColor) {
                            nodes[j].color = color;
                        }
                    }
                }
                color++;
            }
        }
        
    }

    void Testcoloriage() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < adj[nodes[i].id].size(); j++) {
                if (nodes[i].color == getNodeById(adj[nodes[i].id][j]).color) {
                    throw ("Coloriage incorrect");
                }
            }
        }
    }
};

int main(){
    Graph g(9);
    g.addNNodes(9);
    g.addEdge(0, 7);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(0, 5);
    g.addEdge(2, 5);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 6);
    g.addEdge(2, 1);
    g.addEdge(3, 6);
    g.addEdge(4, 5);
    g.addEdge(1, 6);
    g.addEdge(1, 4);
    g.addEdge(1, 8);
    g.coloriage();
    g.printGraph();
    g.Testcoloriage();
    return 0;
}

