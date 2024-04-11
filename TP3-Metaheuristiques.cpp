#include<iostream>
#include<vector>
#include <utility> 
#include <random>
using namespace std;

pair<int, int> select_Two_indice(int n){ 
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1, n - 2);
    
    int i = distrib(gen);
    int j = distrib(gen);
    while (i == j) {
        j = distrib(gen);
    }
    return make_pair(i, j);
}

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
    
    void twoOptSwap(vector<int>& tour, int i, int k) {
        while (i < k) {
            swap(tour[i], tour[k]);
            i++;
            k--;
        }
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

    bool isValidPath(vector<int> path) {
        for (int i = 0; i < path.size() - 1; ++i) {
            int u = path[i];
            int v = path[i + 1];
            bool nodeConnected = false;
            for (const auto& edge : adj[u]) {
                if (edge.first == v) {
                    nodeConnected = true;
                    break;
                }
            }
            if (!nodeConnected) {
                return false;
            }
        }
        return true;
   }

    vector<int> Recuit_simule(vector<int> tour, int max_iter, double min_accept_rate){
        int Zc = calculateTotalDistance(tour);
        double T = 0.2 * Zc;
        int nb_moves = 1;
        for (int i = 0; i < max_iter; i++) {
            bool valide = false;
            int j, k;
            while (!valide) {
                pair<int, int> indices = select_Two_indice(tour.size());
                j = indices.first;
                k = indices.second;
                twoOptSwap(tour, j, k);
                if(!isValidPath(tour)){
                    twoOptSwap(tour, j, k);
                    continue;
                }
                valide = true;
            }
            int Zn = calculateTotalDistance(tour);
            int delta = Zn - Zc;
            if (delta < 0) {
                Zc = Zn;
                nb_moves++;
            } else {
                double p = exp(-delta / T);
                double r = (double) rand() / RAND_MAX;
                if (r > p) {
                    twoOptSwap(tour, j, k);
                } else {
                    Zc = Zn;
                    nb_moves++;
                }
            }
            if (i % 5 == 4) T /= 2;
            double accept_rate = max_iter/(double) nb_moves;
            cout<<"Iteration : "<<i<<" Distance : "<<Zc<<" Accept rate : "<<accept_rate<<endl;
            if (accept_rate < min_accept_rate) {
                break;
            }
        }
        return tour;
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
    vector<int> tour = {0, 1, 2, 3, 4, 5, 6, 0};
    cout << "Distance initial : "<< g.calculateTotalDistance(tour) << endl;
    tour = g.Recuit_simule(tour, 25, 1.01);
    for (int i = 0; i < tour.size(); i++) {
        cout << tour[i] << " ";
    }
    cout << endl;
    cout << "Distance optimale : "<< g.calculateTotalDistance(tour) << endl;
    return 0;
}
