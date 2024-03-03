#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Arista {
  int destino;
  int peso;
};

// Estructura para representar un grafo
class Grafo {
private:
  int V; // num vertices
  vector<vector<Arista>> listaAdyancencia; 

public:
  Grafo(int V) {
    this->V = V;
    listaAdyancencia.resize(V);
  }

  void agregarArista(int origen, int destino, int peso) {
    Arista arista = {destino, peso};
    listaAdyancencia[origen].push_back(arista);
    arista.destino = origen; 
    listaAdyancencia[destino].push_back(arista);
  }

  void primAEM() {
    vector<int> llave(V, INT_MAX);
    vector<int> padre(V, -1);     
    vector<bool> enAEM(
        V, false);

    // Min Heap para elegir la arista de peso mínimo
    cola_prioridad<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        cola_p;

    int origen = 0;
    cola_p.push({0, origen});
    llave[origen] = 0;

    // Iterariamos hasta que todos los vertices esten en el AEM
    while (!cola_p.empty()) {
      int u = cola_p.top().second; 
      cola_p.pop();

      enAEM[u] = true;

      // Iteramos a través de todos los vértices adyacentes de u y actualizamos los pesos
      for (const auto &arista : listaAdyancencia[u]) {
        int v = arista.destino;
        int peso = arista.peso;

        // Si v no está en el árbol de expansión mínima y el peso de la arista es menor que el peso actual
        if (!enAEM[v] && peso < llave[v]) {
          llave[v] = peso;
          padre[v] = u;
          cola_p.push({llave[v], v});
        }
      }
    }

    // Calculo del costo total
    int costoTotal = 0;
    for (int i = 1; i < V; ++i) {
      costoTotal += llave[i];
    }

    cout << "Arista   Peso\n";
    for (int i = 1; i < V; ++i) {
      cout << padre[i]+1 << " - " << i+1 << "    " << llave[i] << endl;
    }
    cout << "Costo Total del Árbol de Expansión Mínima: " << costoTotal << endl;
  }
};

int main() {
  Grafo g(8);

  g.agregarArista(0, 2, 8);
  g.agregarArista(0, 1, 10);
  g.agregarArista(0, 3, 12);
  g.agregarArista(1, 4, 12);
  g.agregarArista(1, 5, 18);
  g.agregarArista(2, 5, 15);
  g.agregarArista(3, 5, 12);
  g.agregarArista(3, 6, 8);
  g.agregarArista(4, 5, 10);
  g.agregarArista(4, 7, 13);
  g.agregarArista(5, 6, 10);
  g.agregarArista(5, 7, 9);
  g.agregarArista(6, 7, 14);

  cout << "Árbol de Expansión Mínima:\n";
  g.primAEM();

  return 0;
}