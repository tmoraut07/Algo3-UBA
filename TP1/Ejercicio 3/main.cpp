#include <iostream>
#include<vector>
#include<algorithm>
#include<tuple>
#include<list>

using namespace std;

// ------- declaracion de variables globales -----------
int n; // cantidad de actividades
//------------------------------------------------------


vector<tuple<int, int, int>> paresATriplas(vector<pair<int, int> > &a){
    vector<tuple<int, int, int> > r;
    for(int i = 0; i < a.size(); i++){
        int si = a[i].first;
        int ti = a[i].second;
        tuple<int, int, int> t = make_tuple(si, ti, i);
        r.push_back(t);
    }
    return r;
}

void ordenarTriplas(vector<tuple<int, int, int> >& p){ // bucket sort, ordena las actividades por tiempo de finalizacion
    vector<list<tuple<int, int, int> > > s((2*n) + 1);
    for(int i = 0; i < n; i++){
        s[get<1>(p[i])].push_back(p[i]); // siendo p[i] = <si, ti, i>, lo guardo en la posicion ti del vector s
    }
    int k = 0;
    for(int i = 0; i < s.size(); i++){
        while(!s[i].empty()){ 
            p[k] = s[i].front();
            s[i].pop_front();
            k++;
        }
    }
}

vector<tuple<int, int, int>> subconj(vector<pair<int, int> > &a){
    vector<tuple<int, int, int>> res;
    vector<tuple<int, int, int>> r = paresATriplas(a);
    ordenarTriplas(r); // ordenamos las actividades por tiempo de finalizacion
    res.push_back(r[0]); // agrego la actividad que termina mas temprano
    for(int i = 1; i < n; i ++){
        if(get<0>(r[i]) >= get<1>(res.back())){ // si la actividad i comienza despues de que termine la actividad que esta en el vector res, la agrego
            res.push_back(r[i]);
        }
    }
    return res;
}

int main() {
    cin >> n;
    vector<pair<int,int> > a(n);
    for(int i = 0; i < n; i++){
        int si; cin >> si;
        int ti; cin >> ti;
        a[i] = make_pair(si, ti);
    }
    vector<tuple<int, int, int> > h = subconj(a);
    cout << h.size() << "\n";
    for(int i = 0; i < h.size(); i++){
        cout << ((get<2>(h[i])) + 1) << " ";
    }
    return 0;
}
