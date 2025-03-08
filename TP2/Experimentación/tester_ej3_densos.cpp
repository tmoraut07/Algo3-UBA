#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;
using namespace std::chrono;

// ----------- DECLARACION DE ESTRUCTURAS, FUNCIONES Y VARIABLES GLOBALES ----------------------------
const char UTP = 'U';
const char Fibra = 'F';

double distancia(int x1, int y1, int x2, int y2){
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
// -------------------------------------------------------------------

void solveProblem(int N, int R, int W, int U, int V, vector<tuple<int, int>>& office_positions) {

    // Declaracion de variables
    double costoUTP = 0;
    double costoFibra = 0; 

    vector<vector<double>> grafo(N, vector<double>(N,INFINITY));
    vector<double> costos(N, INFINITY);
    vector<bool> vistos(N, false);

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
            grafo[i][j] = grafo[j][i] = costo;
        }
    }

    vector<bool> visitado(N, false);

    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            costos[i] = min(costos[i], grafo[i][j]);
        }
    }

    int aristas = N - 1;
    while (aristas + 1 > W) {
        //buscar minimo
        int idx = 0;
        while (vistos[idx]) idx++;
        for (int i = idx + 1; i < N; i++) {
            if (vistos[i]) continue;
            if (costos[i] < costos[idx]) idx = i;
        }
        costo = costos[idx];
        int destino = 0;
        for (int i = 0; i < N; ++i) {
            if (vistos[i]) continue;
            if (grafo[idx][i] == costo) {
                destino = i;
                break;
            }
        }

        pair<double, pair<int, int>> minimo = make_pair(costo, make_pair(idx, destino));

        //calcular costos
        if (minimo.first/U <= R && minimo.first/V <= R){
            costoUTP += minimo.first;
        } else {
            costoFibra += minimo.first;
        }

        //unificar
        int u = minimo.second.first, // nuevo padre
        v = minimo.second.second; // nuevo hijo
        vistos[v] = true;
        costos[u] = INFINITY;
        for (int i = 0; i < N; ++i) {
            if (vistos[i]) continue;
            if (i == u) continue;
            grafo[i][u] = grafo[u][i] = min(grafo[u][i], grafo[v][i]);
            costos[u] = min(costos[u], grafo[u][i]);
        }

        aristas--;
    }

}

int main() {
    const string inputDirectory = "./inputs/";  // Directorio de los archivos de entrada
    const string outputFilename = "resultados_densos.csv";  // Nombre del archivo CSV de salida

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
