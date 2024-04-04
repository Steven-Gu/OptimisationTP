#include <iostream>
#include <vector>
#include <utility> // Pour std::pair

using namespace std;

struct Vertex {
    int id; 
    int k;

    Vertex(int i){
        id = i;
        k = 0;
    }
};


struct Graph {
    vector<Vertex> S;  
    vector< pair<int,int> > A;  

    void addVertex(Vertex vertex) {
        S.push_back(vertex);
    }

    // Fonction pour ajouter une arête au graphe
    void addEdge(int vertexId1, int vertexId2) {
        A.emplace_back(vertexId1, vertexId2);
    }

    void colorVertices() {
        for (auto& vertex : S) {
            vector<bool> used(S.size() + 1, false); // Marqueur pour les couleurs utilisées
            
            // Parcourir toutes les arêtes pour marquer les couleurs utilisées par les voisins
            for (const auto& edge : A) {
                if (edge.first == vertex.id && S[edge.second - 1].k != 0) { // -1 car l'indexation commence à 0
                    used[S[edge.second - 1].k] = true;
                } else if (edge.second == vertex.id && S[edge.first - 1].k != 0) {
                    used[S[edge.first - 1].k] = true;
                }
            }

            // Attribuer la plus petite couleur non utilisée
            for (int i = 1; i <= S.size(); ++i) {
                if (!used[i]) {
                    vertex.k = i;
                    break;
                }
            }
        }
    }
};




int main() {
    Graph g;

    // Ajout de sommets au graphe
    g.addVertex(Vertex(1)); 
    g.addVertex(Vertex(2)); 
    g.addVertex(Vertex(3)); 
    g.addVertex(Vertex(4));
    g.addVertex(Vertex(5));
    g.addVertex(Vertex(6));
    g.addVertex(Vertex(7)); 


    // Ajout d'arêtes au graphe
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(5, 6);
    g.addEdge(5, 7);
    g.addEdge(6, 7);

    g.colorVertices();

    // Affichage des couleurs des sommets
    cout << "Couleurs des sommets:" << endl;
    for (const auto& vertex : g.S) {
        cout << "Sommet " << vertex.id << " a la couleur " << vertex.k << endl;
    }

    return 0;
}