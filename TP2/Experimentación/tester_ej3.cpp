#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace std::chrono;

// ----------- DECLARACION DE ESTRUCTURAS, FUNCIONES Y VARIABLES GLOBALES ----------------------------
const char UTP = 'U';
const char Fibra = 'F';
struct arista{
    double costo;
    int x, y;
    char tipo;
};

struct DSU{

    DSU(int k){
        padre = rank = vector<int>(k);
        for(int b = 0; b < k; b++) padre[b] = b;
    }

    int find(int b){
        if(b == padre[b]) return b;
        return padre[b] = find(padre[b]);
    }

    void unite(int a, int b){
        a = find(a), b = find(b);
        if(a == b) return;
        if(rank[a] < rank[b]) swap(a,b);
        padre[b] = padre[a];
        rank[a] = max(rank[a],rank[b]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

bool orden(arista a, arista b){
    bool res = a.costo < b.costo;
    return res;
}

double distancia(int x1, int y1, int x2, int y2){
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
// -------------------------------------------------------------------

void solveProblem(int N, int R, int W, int U, int V, vector<tuple<int, int>>& office_positions) {

    // Declaracion de variables
    double costoUTP = 0;
    double costoFibra = 0; 
    vector<arista> agm;
    vector<arista> grafo;
    double costo;
    char tipo;

    // Inicializacion del grafo
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            int x1 = get<0>(office_positions[i]);
            int y1 = get<1>(office_positions[i]);
            int x2 = get<0>(office_positions[j]);
            int y2 = get<1>(office_positions[j]);
            double d = distancia(x1, y1, x2, y2);
            if(d <= R){
                costo = U * d;
                tipo = UTP;
            } else {
                costo = V * d;
                tipo = Fibra;
            }
            arista cable = {costo, i, j, tipo};
            grafo.push_back(cable);
        }
    }

    // Kruskal
    sort(grafo.begin(),grafo.end(), orden);
    DSU dsu(N);
    for(auto k : grafo){
        int x = k.x;
        int y = k.y;
        if(dsu.find(x) != dsu.find(y)){
            dsu.unite(x,y);
            agm.push_back(k);
            }
        }

    // Calculo de costos
    for(int h = W - 1; h > 0; h--){
        agm.pop_back();
    }
    for(auto k : agm){
        if(k.tipo == UTP){
            costoUTP += k.costo;
        } else {
            costoFibra += k.costo;
        }
    }
}

int main() {
    const string inputDirectory = "./inputs/";  // Directorio de los archivos de entrada
    const string outputFilename = "results.csv";  // Nombre del archivo CSV de salida

    // Abrir el archivo CSV de salida
    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "No se pudo abrir el archivo CSV de salida: " << outputFilename << endl;
        return 1;
    }

    // Escribir encabezado en el archivo CSV
    outputFile << "Tamaño del input, Tiempo (ms)" << endl;

    for (int power = 16; power <= 26; ++power) {
        int n = 1 << power;
        string inputFilename = inputDirectory + "input_" + to_string(n);

        ifstream inputFile(inputFilename);
        if (!inputFile) {
            cerr << "No se pudo abrir el archivo de entrada: " << inputFilename << endl;
            return 1;
        }

        int c;
        inputFile >> c;  // Leer el número de casos de prueba

        // Procesar cada caso de prueba
        for (int i = 0; i < c; ++i) {
            int N, R, W, U, V;
            inputFile >> N >> R >> W >> U >> V;

            vector<tuple<int, int>> office_positions(N);
            for (int j = 0; j < N; ++j) {
                int x, y;
                inputFile >> x >> y;
                office_positions[j] = make_tuple(x, y);
            }

            // Medir el tiempo de ejecución del código de solución
            auto start = high_resolution_clock::now();
            solveProblem(N, R, W, U, V, office_positions);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);

            // Guardar los resultados en el archivo CSV
            outputFile << N << ", " << duration.count() << endl;
        }

        inputFile.close();
    }

    outputFile.close();

    cout << "Proceso completado. Los resultados se han guardado en el archivo: " << outputFilename << endl;

    return 0;
}
