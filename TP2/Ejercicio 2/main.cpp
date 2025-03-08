#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


ll n, m;
vector<bool> visitados, tiene_entrada, condensado_tiene_entrada, tiradas;
vector<int> pila, cfc, vertices_raiz;
vector<vector<int>> grafo, grafo_rev;
set<int> res;

void dfs1(int v) {
    visitados[v] = true;
    for(int u : grafo[v]){
        if (!visitados[u]){
            dfs1(u);
        }
    }
    pila.push_back(v);
}

void dfs2(int v){
    visitados[v] = true;
    cfc.push_back(v);
    for(int u : grafo_rev[v]){
        if (!visitados[u]){
            dfs2(u);
        }
    }
}

// idea del algoritmo de condensacion tomada de https://cp-algorithms.com/graph/strongly-connected-components.html#condensation-graph-implementation
void condensar(){
    vector<int> raices(n + 1, 0);
    vector<vector<int>> grafo_condensado(n + 1);    

    for(int v : pila){
        if (!visitados[v]) {
            dfs2(v);
            //condensar grafo
            int raiz = cfc.front();
            for (int u : cfc){
                raices[u] = raiz;
            }
            vertices_raiz.push_back(raiz);

            cfc.clear();
        }
    }
    pila.clear(); // borramos la pila
    // armar grafo condensado
    for (int v = 1; v <= n; v++)
        for (int u : grafo[v]) {
            int raiz_v = raices[v];
            int raiz_u = raices[u];
            if (raiz_v != raiz_u){
                grafo_condensado[raiz_v].push_back(raiz_u); 
                condensado_tiene_entrada[raiz_u] = true; // el grado de entrada del vertice es mayor a 0
            }
        }
}

// idea de kosaraju tomada de https://cp-algorithms.com/graph/strongly-connected-components.html#implementation
void kosaraju() {
   visitados = vector<bool>(n + 1, false);
   for (int i = 1; i <= n; i++){
        if (!visitados[i] && !tiradas[i])
            dfs1(i);
    }
    visitados.assign(n+1, false);
    reverse(pila.begin(), pila.end());
    condensar();
}

void tirar(int u){
    tiradas[u] = true;
    for(int v : grafo[u]){
        if(!tiradas[v]){
            tirar(v);
        }
    }
}

int main() {
    cin >> n >> m;

    grafo.assign(n + 1, vector<int>());
    grafo_rev.assign(n + 1, vector<int>());
    tiene_entrada.assign(n + 1, false);
    condensado_tiene_entrada.assign(n + 1, false);
    tiradas.assign(n + 1, false);

    // inicializar grafo
    int a, b;
    while(m--) {
        cin >> a >> b;
        grafo[a].push_back(b);
        grafo_rev[b].push_back(a);
    }

    kosaraju();

    for(int u : vertices_raiz){
        if(!condensado_tiene_entrada[u]){
            res.insert(u);
            tirar(u);
        }
    }

    // imprimir conjunto minimo
    cout << res.size()<< endl;
    for(int i : res){
        cout << i << " ";
    }

    return 0;
}