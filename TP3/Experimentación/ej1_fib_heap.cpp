#include <bits/stdc++.h>
#include <boost/heap/fibonacci_heap.hpp>

using namespace std;

typedef long long ll;
const ll inf = 1e18;

int n, m, s, t, k;


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

void seleccionarCandidata(vector<vector<arista>>& g, vector<vector<arista>>& g_inverso, vector<arista>& cand){
    vector<ll> distS = dijkstra(g, s);
    vector<ll> distT = dijkstra(g_inverso, t);
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
    if(minimo == inf){
        cout << -1 << endl;
    }else{
        cout << minimo << endl;
    }
}


int main() {
    int cantCasos;
    cin >> cantCasos;
    vector<vector<arista>> grafo;
    vector<vector<arista>> grafo_inverso;
    vector<arista> candidatas;
    while(cantCasos--){
        cin >> n >> m >> k >> s >> t;
        grafo.clear();
        grafo_inverso.clear();
        candidatas.clear();
        grafo.resize(n+1);
        grafo_inverso.resize(n+1);

        // inicializar grafos
        for(int i = 0; i < m; i++){
            int x, y;
            ll c;
            cin >> x >> y >> c;
            arista a = {c, x, y};
            arista a_inversa = {c, y, x};
            grafo[x].push_back(a);
            grafo_inverso[y].push_back(a_inversa);
        }
        // inicializar calles candidatas
        for (int i = 0; i < k; i++)
        {
            int x, y;
            ll c;
            cin >> x >> y >> c;
            arista a = {c, x, y};
            candidatas.push_back(a);
        }
        // resolver

        seleccionarCandidata(grafo, grafo_inverso, candidatas);
    }

    return 0;
} 
