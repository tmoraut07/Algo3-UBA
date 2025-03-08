#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <queue>
#include <boost/heap/fibonacci_heap.hpp>

using namespace std;
using namespace std::chrono;

// ----------- DECLARACION DE ESTRUCTURAS, FUNCIONES Y VARIABLES GLOBALES ----------------------------
typedef long long ll;
const ll inf = 1e18;

struct arista{
    ll costo;
    int from, to;
    
    bool operator>(const arista& otro) const {
        return costo > otro.costo;
    }
};

vector<ll> dijkstra(int n, vector<vector<arista>>& grafo, int& src) {
    // Declarar el Fibonacci heap
    boost::heap::fibonacci_heap<arista, boost::heap::compare<greater<arista>>> pq;
    vector<boost::heap::fibonacci_heap<arista, boost::heap::compare<greater<arista>>>::handle_type> handles(n + 1);

    vector<ll> dist(n + 1, inf);
    handles[src] = pq.push({0, -1, src});
    dist[src] = 0;
    vector<bool> visitado(n + 1, false);

    while (!pq.empty()) {
        int u = pq.top().to;
        pq.pop();
        if (visitado[u]) continue;
        visitado[u] = true;
        for (arista i : grafo[u]) {
            int v = i.to;
            ll peso = i.costo;
            if (dist[v] > dist[u] + peso) {
                dist[v] = dist[u] + peso;
                if (handles[v] != boost::heap::fibonacci_heap<arista, boost::heap::compare<greater<arista>>>::handle_type()) {
                    pq.erase(handles[v]);
                }
                handles[v] = pq.push({dist[v], u, v});
            }
        }
    }
    return dist;
}


void seleccionarCandidata(int s, int t, int n, vector<vector<arista>>& g, vector<vector<arista>>& g_inverso, vector<arista>& cand){
    vector<ll> distS = dijkstra(n, g, s);
    vector<ll> distT = dijkstra(n, g_inverso, t);
    ll minimo = distS[t];
    for(arista c : cand){
        int u = c.from;
        int v = c.to;
        ll nuevoMin = distS[u] + c.costo + distT[v];
        ll nuevoMin2 = distS[v] + c.costo + distT[u];
        if(nuevoMin < minimo || nuevoMin2 < minimo){
            minimo = min(nuevoMin, nuevoMin2);
        }
    }
}



// Función que resuelve el problema para un caso de prueba específico
void solveProblem(int n, int m, int k, int s, int t, vector<tuple<int, int, ll>>& calles_unidireccionales, vector<tuple<int, int, ll>>& calles_bidireccionales) {
    vector<vector<arista>> grafo = vector<vector<arista>>(n+1);
    vector<vector<arista>> grafo_inverso = vector<vector<arista>>(n+1);
    vector<arista> candidatas;
    grafo.resize(n+1);
    grafo_inverso.resize(n+1);

    // inicializar grafos
    for(int i = 0; i < m; i++){
        tuple<int,int,ll> calle = calles_unidireccionales[i];
        int x = get<0>(calle);
        int y = get<1>(calle);
        ll c = get<2>(calle);
        arista a = {c, x, y};
        arista a_inversa = {c, y, x};
        grafo[x].push_back(a);
        grafo_inverso[y].push_back(a_inversa);
    }
    // inicializar calles candidatas
    for (int i = 0; i < k; i++)
    {
        tuple<int,int,ll> calle = calles_bidireccionales[i];
        int x = get<0>(calle);
        int y = get<1>(calle);
        ll c = get<2>(calle);
        arista a = {c, x, y};
        candidatas.push_back(a);
    }
    // resolver

    seleccionarCandidata(s, t, n, grafo, grafo_inverso, candidatas);
    
}

int main() {
    const string outputFilename = "resultados_fib_heap.csv";  // Nombre del archivo de salida
    const string inputFilename = "input.txt";                 // Nombre del archivo de entrada
    ifstream inputFile(inputFilename);    // Archivo de entrada
    ofstream outputFile(outputFilename); // Archivo de salida
    int c; // Cantidad de casos de prueba
    inputFile >> c; 
    int i = 0; 
    while(c--){ 
        int n, m, k, s, t;
        inputFile >> n >> m >> k >> s >> t;

        vector<tuple<int, int, ll>> calles_unidireccionales(m);
        for (int i = 0; i < m; ++i) {
            int di, ci; 
            ll li;
            inputFile >> di >> ci >> li;
            calles_unidireccionales[i] = make_tuple(di, ci, li);
        }

        vector<tuple<int, int, ll>> calles_bidireccionales(k);
        for (int i = 0; i < k; ++i) {
            int uj, vj;
            ll qj;
            inputFile >> uj >> vj >> qj;
            calles_bidireccionales[i] = make_tuple(uj, vj, qj);
        }

        // Medir el tiempo de ejecución del código de solución
        auto start = high_resolution_clock::now();
        solveProblem(n, m, k, s, t, calles_unidireccionales, calles_bidireccionales);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        // Guardar los resultados en el archivo CSV
        outputFile << n << ',' << m << ',' << duration.count() << endl;

        i++;
        cout << "Caso #" << i << " completado." << endl;
    }
    
    inputFile.close();
    outputFile.close();

    cout << "Proceso completado. Los resultados se han guardado en el archivo: " << outputFilename << endl;

    return 0;
}