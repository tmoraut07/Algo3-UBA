#include <iostream>
#include <vector>

using namespace std;

int n;
int k;
int numeroMagico;
vector<int> usados;
vector<vector<int>> m;
int cont = 0;
vector<int> fil;
vector<int> col;
int sumaDiagonal1;
int sumaDiagonal2;

bool esMagico() {                       //chequeamos como ultimo recurso si al finalizar las diagonales estas son correctas
    sumaDiagonal1 = sumaDiagonal2 = 0;
    for (int i = 0; i < n; i++) {
        sumaDiagonal1 += m[i][i];
        sumaDiagonal2 += m[i][n-i-1];
    }
    if (sumaDiagonal1 != numeroMagico || sumaDiagonal2 != numeroMagico) {
        return false;
    }
    return true;
}


bool esDiagonal1(int i, int j){
    return i == j;
}
bool esDiagonal2(int i, int j){
    return j == n - i - 1;
}

bool construirCuadrado(int i, int j, vector<int> &sumFil, vector<int> &sumCol){
    if(i == n) {
        if(esMagico()){
            cont++;
            if(cont == k) return true;          //devolvemos el k-esimo cuadrado magico
        }
    } else {
        if(m[i][j] == 0){
            for(int x = 1; x <= n*n; x++){
                if(usados[x] == 0){             //chequeamos si ya habiamos usado x en el cuadrado.
                    m[i][j] = x;
                    usados[x] = 1;              //marcamos x como usado
                    sumFil[i] += x;
                    sumCol[j] += x;
                    bool cheq_diag1 = esDiagonal1(i,j);     //nos fijamos si estamos en alguna de las diagonales
                    bool cheq_diag2 = esDiagonal2(i,j);
                    if(cheq_diag1) sumaDiagonal1 += x;
                    if(cheq_diag2) sumaDiagonal2 += x;
                    bool diag_ok = sumaDiagonal1 <= numeroMagico && sumaDiagonal2 <= numeroMagico; //chequeamos q la suma parcial de las diagonales sea valida
                    if(!(i == n - 1 && sumCol[j] != numeroMagico))                                  //nos fijamos si estamos o no en la ultima fila. si estamos, necesitamos que las sumas de las columnas sean iguales al numero magico.
                    {if(j + 1 < n){
                        if(sumFil[i] < numeroMagico && diag_ok && sumCol[j] <= numeroMagico && construirCuadrado(i, j + 1, sumFil, sumCol)) return true;  //chequeamos si las sumas parciales son validas y hacemos la recursion.
                    } else {
                        if(sumFil[i] == numeroMagico && diag_ok && sumCol[j] <= numeroMagico && construirCuadrado(i + 1, 0, sumFil, sumCol)) return true;
                    }}
                    m[i][j] = 0;                //backtrack: sacamos el elemento q pusimos, lo marcamos como no usado y lo restamos de las sumas parciales.
                    sumFil[i] -= x;
                    sumCol[j] -= x;
                    usados[x] = 0;
                    if(cheq_diag1) sumaDiagonal1 -= x;
                    if(cheq_diag2) sumaDiagonal2 -= x;
                }
            }
        }
    }
    return false;
}


int main(){
    cin >> n;
    cin >> k;
    numeroMagico = ((n*n*n + n)/2);
    m = vector<vector<int>>(n, vector<int>(n, 0));
    usados = vector<int>(n*n, 0);
    fil = vector<int>(n, 0);
    col = vector<int>(n, 0);
    sumaDiagonal1 = 0;
    sumaDiagonal2 = 0;
    if (construirCuadrado(0, 0, fil, col)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << m[i][j] << " ";
            }
            cout << "\n";
        }
    }
    else{
        cout << -1 << endl;
    }
    return 0;
}
