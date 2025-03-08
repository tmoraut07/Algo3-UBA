#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <tuple>

using namespace std;

vector<int> read_input(int size) {
    vector<int> input(size); string file_name = "./inputs/input_" + to_string(size);
    cout << file_name << endl;
    ifstream read_file(file_name);
    for (int i=0; i<size; i++) read_file >> input[i];
    read_file.close();
    return input;
}

double measure(vector<int> act) {
    auto start = chrono::high_resolution_clock::now();

    int tam = act.size();

    vector<pair<int,int> > a(tam); // pasamos el input a un vector de pares
    for(int i = 0; i < tam - 1; i++){
        int si = act[i];
        int ti = act[i+1];
        a[i] = make_pair(si, ti);
    }

    vector<tuple<int, int, int>> res;
    int n = a.size();

    vector<tuple<int, int, int> > r;
    for(int i = 0; i < n; i++){ // crear triplas
        int si = a[i].first;
        int ti = a[i].second;
        tuple<int, int, int> t = make_tuple(si, ti, i);
        r.push_back(t);
    }

    vector<list<tuple<int, int, int> > > s((2*n) + 1); // bucket sort
    for(int i = 0; i < n; i++){
        s[get<1>(r[i])].push_back(r[i]);
    }
    int k = 0;
    for(int i = 0; i < s.size(); i++){
        while(!s[i].empty()){ 
            r[k] = s[i].front();
            s[i].pop_front();
            k++;
        }
    }

    res.push_back(r[0]); // solucion golosa
    for(int i = 1; i < n; i ++){
        if(get<0>(r[i]) >= get<1>(res.back())){
            res.push_back(r[i]);
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main() {
    int repeat = 10;
    ofstream output_file; output_file.open("runtime_random.csv");
    output_file << "n,time\n";
    
    int limit = 1<<27;
    for (int n=65536; n<limit; n*=2) {
        vector<int> input = read_input(n);

        double counter = 0;
        for (int ignore=0; ignore<repeat; ignore++) counter += measure(input);
        
        output_file << n << "," << counter / repeat << endl;
    }

    output_file.close();
    return 0;
}
