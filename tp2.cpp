#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

struct Vertex {
    int begin;
    int end;
    int k; 
    string name;

    Vertex(int b, int e, string s) : begin(b), end(e), name(s), k(0) {}
};

struct Graph {
    vector<Vertex> S;  

    void addVertex(const Vertex& vertex) {
        S.push_back(vertex);
    }


    void colorVertices() {
        sort(S.begin(), S.end(), [](Vertex a,Vertex b) {
            return a.begin < b.begin;
        });

        for (auto& vertex : S) {
            vector<bool> used(S.size(), false);

            for (const auto& other : S) {
                if (&vertex != &other && !(vertex.end <= other.begin || other.end <= vertex.begin)) {
                    if (other.k != 0) { 
                        used[other.k - 1] = true; 
                    }
                }
            }

            
            for (int i = 0; i < used.size(); ++i) {
                if (!used[i]) {
                    vertex.k = i + 1;
                    break;
                }
            }
        }
    }
};

int main() {
    Graph g;

    
    g.addVertex(Vertex(1, 3,"a"));
    g.addVertex(Vertex(2, 5,"b"));
    g.addVertex(Vertex(2, 8,"c"));
    g.addVertex(Vertex(4, 6,"d"));
    g.addVertex(Vertex(6, 11,"e"));
    g.addVertex(Vertex(9, 11,"f"));
    g.addVertex(Vertex(10, 12,"g"));

   
    g.colorVertices();

    
    cout << "Vertex colors:" << endl;
    for (const auto& vertex : g.S) {
        cout << "Vertex [" << vertex.begin << ", " << vertex.end << "]"<<" "<< vertex.name<<" has color " << vertex.k << endl;
    }

    return 0;
}
