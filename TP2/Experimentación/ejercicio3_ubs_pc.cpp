// Modems
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<tuple<int, int>> localizacion;
int n, r, w, u, v;
double costoUTP, costoFibra; 
const char UTP = 'U';
const char Fibra = 'F';
int caso = 0;

struct arista{
    double costo;
    int x, y;
    char tipo;
};

bool orden(arista a, arista b){
    return a.costo < b.costo;
}

vector<arista> agm;

struct DSU {
    DSU(int k) {
        padre = vector<int>(k);
        size = vector<int>(k, 1);  // Agregar vector para almacenar los tamaños de los conjuntos
        for (int h = 0; h < k; h++) padre[h] = h;
    }

    int find(int h) {
        if (h == padre[h]) return h;
        return padre[h] = find(padre[h]);
    }

    void unite(int h, int k) {
        h = find(h), k = find(k);
        if (h == k) return;
        if (size[h] < size[k]) swap(h, k);  // Comparar por tamaño en lugar de rango
        padre[k] = padre[h];
        size[h] += size[k];  // Actualizar el tamaño del conjunto representado por u
    }

    vector<int> padre;
    vector<int> size;
};

void kruskal(vector<arista> &grafo){
    sort(grafo.begin(),grafo.end(), orden);
    DSU dsu(n);
    for(auto k : grafo){
        int x = k.x;
        int y = k.y;
        if(dsu.find(x) != dsu.find(y)){
            dsu.unite(x,y);
            agm.push_back(k);
            }
        }
    }

void calcularCostos(){
    for(int h = w - 1; h > 0; h--){
        agm.pop_back();
    }
    for(auto k : agm){
        if(k.tipo == UTP){
            costoUTP += k.costo;
        } else {
            costoFibra += k.costo;
        }
    }
    agm.clear();
}

double distancia(int x1, int y1, int x2, int y2){
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

vector<arista> init_grafo(vector<tuple<int, int>> &p){
    double costo;
    char tipo;
    vector<arista> aristas;
    for(int i = 0; i < p.size(); i++){
        for(int j = i+1; j < p.size(); j++){
            int x1 = get<0>(p[i]);
            int y1 = get<1>(p[i]);
            int x2 = get<0>(p[j]);
            int y2 = get<1>(p[j]);
            double d = distancia(x1, y1, x2, y2);
            if(d <= r){
                costo = u * d;
                tipo = UTP;
            } else {
                costo = v * d;
                tipo = Fibra;
            }
            arista cable = {costo, i, j, tipo};
            aristas.push_back(cable);
        }
    }
    return aristas;
}

void imprimirCaso(){
    cout << "Caso #" << caso << ": " << setprecision(3) << fixed << costoUTP << " " << setprecision(3) << fixed << costoFibra << endl;
}


int main() {
    int cantCasos;
    cin >> cantCasos;
    vector<arista> grafo;
    for(int i = 0; i < cantCasos; i++){
        caso ++;
        costoUTP = 0;
        costoFibra = 0;
        cin >> n >> r >> w >> u >> v;
        localizacion.clear();
        for(int i = 0; i < n; i++){
            int x, y;
            cin >> x >> y;
            localizacion.push_back({x, y});
        }
        grafo = init_grafo(localizacion);
        kruskal(grafo);
        calcularCostos();
        imprimirCaso();
    }

    return 0;
} 