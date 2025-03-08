#include <iostream>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;
typedef long long ll;

vector<vector<int>> grafo;      // Lista de adyacencia.
ll n; ll m;
ll prob;
vector<int> desc;            //momento en el que descubri cada nodo (si es -1 no lo descubri)
vector<int> low;             //minimo nivel al que puedo llegar a traves de backedges
int tiempo = 0;
vector<bool> visitados;
vector<pair<int,int>> puentes; //guarda las aristas puente
vector<int> componentes;       //guarda los nodos de cada componente
int cont;

void guardarPuentes(int u, int p){     //quiero guardar en un vector todas las aristas puente para luego eliminarlas
    visitados[u] = true;
    tiempo++;
    desc[u] = tiempo;
    low[u] = tiempo;
    for(int i = 0; i < grafo[u].size(); i++){
        int v = grafo[u][i];
        if(v == p) continue;
        if(!visitados[v]){
            guardarPuentes(v,u);
            low[u] = min(low[u],low[v]);
            if(low[v] > desc[u]){
            puentes.push_back({u,v});
            }
        }
        else low[u] = min(low[u],desc[v]);
    }
}


void borrar(int u,int v){
    for(int i = 0; i < grafo[u].size(); i++){
        if(grafo[u][i] == v){
            grafo[u].erase(grafo[u].begin() + i);
            break;
        }
    }
    for(int j = 0; j < grafo[v].size(); j++){
        if(grafo[v][j] == u){
            grafo[v].erase(grafo[v].begin() + j);
            break;
        }
    }
}

void eliminarPuentes(){
    for(int i = 0; i < puentes.size(); i++){
        int u = puentes[i].first;
        int v = puentes[i].second;
        borrar(u,v);
    }
}


void dfs(int u, int p = -1){
    visitados[u] = true;
    for(int i = 0; i < grafo[u].size(); i++){
        int v = grafo[u][i];
        if(v == p) continue;
        if(!visitados[v]){
            dfs(v,u);
            cont++;
        }
    }
}


void guardarComponentes(){
    for(int i = 1; i <= n; i++){
        if(!visitados[i]){
            cont = 1;
            dfs(i);
            componentes.push_back(cont);
        }
    }
}


double sumaGauss(ll n){
    return (n*(n+1))/2;
}


int main(){
    cin >> n >> m;
    double formasDeJugar = sumaGauss(n -1);
    grafo.assign(n + 1, vector<int>(0));
    desc = vector<int>(n+1,-1);
    low = vector<int>(n+1,-1);
    visitados = vector<bool>(n+1,false);
    while (m--){ // Inicializo las lista de adyacencia
        int u,v;
        cin >> u >> v;
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    for(int i = 1; i < visitados.size(); i++){
        if(!visitados[i]){
            guardarPuentes(i,-1);
        }
    }
    eliminarPuentes();
    visitados = vector<bool>(n + 1,false);
    guardarComponentes();
    while(!componentes.empty()){
        ll c = componentes.back();
        prob += sumaGauss(c - 1);
        componentes.pop_back();
    }
    cout << setprecision(5) << fixed << 1.0 - (double(prob)/formasDeJugar) << '\n';
    return 0;
}