#include<iostream>
#include<vector>
using namespace std;

struct Node {
    int id;
};

struct Graph_with_weight {
    int V;
    vector<Node> nodes;
    vector<vector<pair<int, int> > > adj;
    Graph_with_weight(int V) {
        this->V = V;
        nodes.resize(V);
        adj.resize(V);
        addNNodes(V);
    }
    
    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    
    void addNode(int id) {
        nodes[id].id = id;
    }
    void addNNodes(int n) {
        for (int i = 0; i < n; i++) {
            addNode(i);
        }
    }
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Node " << nodes[i].id << " : ";
            for (auto x : adj[i]) {
                cout << x.first << " ";
            }
            cout << endl;
        }
    }

    vector<int> SLPP(int start) {
        vector<bool> visited(V, false);
        vector<int> path;
        int current = start;
        path.push_back(current);
        visited[current] = true;
        int count = 0;
        while (count < V - 1) {
            int nearest = -1;
            int shortestDist = 9999999;     
            for (auto edge : adj[current]) {
                if (!visited[edge.first] && edge.second < shortestDist) {
                    nearest = edge.first;
                    shortestDist = edge.second;
                }
            }

            if (nearest != -1) {
                current = nearest;
                visited[current] = true;
                path.push_back(current);
            }
            count++;
        }
        
        path.push_back(start);

        return path;
    }
    
    void twoOptSwap(vector<int>& tour, int i, int k) {
        while (i < k) {
            swap(tour[i], tour[k]);
            i++;
            k--;
        }
    }

    bool twoOpt(vector<int>& tour) {
        bool improved = false;
        int best_distance = calculateTotalDistance(tour);
        for (int i = 1; i < tour.size() - 2; i++) {
            for (int k = i + 1; k < tour.size() - 1; k++) {
                twoOptSwap(tour, i, k);
                int new_distance = calculateTotalDistance(tour);
                if (new_distance < best_distance) {
                    best_distance = new_distance;
                    improved = true;
                } else {
                    twoOptSwap(tour, i, k);
                }
            }
        }
        return improved;
    }

    int calculateTotalDistance(const vector<int>& tour) {
        int total_distance = 0;
        for (int i = 0; i < tour.size() - 1; i++) {
            int u = tour[i];
            int v = tour[i + 1]; 
            for (int j = 0; j < adj[u].size(); j++) {
                if (adj[u][j].first == v) {
                    total_distance += adj[u][j].second;
                    break; 
                }
            }
        }
        int last = tour.back();
        int first = tour.front();
        for (int j = 0; j < adj[last].size(); j++) {
            if (adj[last][j].first == first) {
                total_distance += adj[last][j].second;
                break;
            }
        }
        return total_distance;
    }
};

int main(){
    Graph_with_weight g(7);
    g.addEdge(0, 1, 12);
    g.addEdge(0, 2, 10);
    g.addEdge(0, 6, 12);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 3, 11);
    g.addEdge(2, 4, 3);
    g.addEdge(2, 6, 9);
    g.addEdge(3, 4, 11);
    g.addEdge(3, 5, 10);
    g.addEdge(4, 5, 6);
    g.addEdge(4, 6, 7);
    g.addEdge(5, 6, 9);
    g.printGraph();
    
    vector<int> path = g.SLPP(0);
    int total = g.calculateTotalDistance(path);
    cout << "Total: " << total << endl;
    cout << "Path: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;

    vector<int> tour = {0, 1, 2, 3, 4, 5, 6, 0}; 
    cout << "\nTotal distance: " << g.calculateTotalDistance(tour) << endl;
    
    bool improved = g.twoOpt(tour);
    g.printGraph();

    if (improved) {
        cout << "Improved tour: ";
        for (int i : tour) {
            cout << i << " ";
        }
        cout << "\nTotal distance: " << g.calculateTotalDistance(tour) << endl;
    } else {
        cout << "No improvement found." << endl;
    }

    return 0;
}
