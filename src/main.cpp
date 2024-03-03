#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Arista {
    int from;
    int to;
    int weight;
    Arista(int f, int t, int w) : from(f), to(t), weight(w) {}
};

struct Nodo {
    vector<Arista> edges;
};

// Algoritmo de Prim 
vector<Arista> primAEM(vector<Nodo>& graph) {
    int numUbicaciones = graph.size();
    vector<bool> visited(numUbicaciones, false);
    vector<Arista> AEM;

    // Cola de prioridad para elegir la arista más corta en cada paso
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, 0});

    while (!pq.empty()) {
        // Esto obtiene la arista más corta y el vértice al que conduce
        int w = pq.top().first; 
        int v = pq.top().second;
        pq.pop();

        if (visited[v])
            continue;

        visited[v] = true;

        // Agregar la arista al AEM
        if (v != 0)
            AEM.push_back({pq.top().second, v, w});

        // Pusheamos las aristas conectadas a la cola de prioridad
        for (const Arista& e : graph[v].edges) {
            int u = e.to;
            int weight = e.weight;
            if (!visited[u])
                pq.push({weight, u});
        }
    }

    return AEM;
}

int main() {
    int numUbicaciones, lineasTransmision; 
    cout << "Ingrese el número de ubicaciones y líneas de transmisión: ";
    cin >> numUbicaciones >> lineasTransmision;

    vector<Nodo> graph(numUbicaciones);

    for (int i = 0; i < lineasTransmision; ++i) {
        cout << "Ingrese las líneas de transmisión y sus distancias (ubicación1 ubicación2 distancia) ["<<i<<"]: ";
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].edges.push_back(Arista(u, v, w));
        graph[v].edges.push_back(Arista(v, u, w));
    }

    // Aquí llamo a la función o algoritmo prim que me va a dar el arbol de expansión mínima
    vector<Arista> AEM = primAEM(graph);

    // Mostrar el arbol de expansión mínima y su coste total
    int totalCost = 0;
    cout << "Árbol de expansión mínima para la red de distribución eléctrica:" << endl;
    for (const Arista& e : AEM) {
        cout << "Ubicación " << e.from << " - Ubicación " << e.to << " - Distancia: " << e.weight << endl;
        totalCost += e.weight;
    }
    cout << "Costo total de la red de distribución eléctrica: " << totalCost << endl;
    return 0;
}