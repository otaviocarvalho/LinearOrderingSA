#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    int m;
    int n;
    int v_aux;

    cin >> m;
    cin >> n;

    vector<int> v_mapping;
    v_mapping.reserve(m);
    for (int i = 0; i < m; i++) {
        cin >> v_aux;
        v_mapping.push_back(v_aux);
        cout << v_mapping[i] << " ";
    }
    cout << endl;

    vector<int> arc_mapping;
    arc_mapping.reserve(2*n);
    for (int i = 0; i < 2*n; i++) {
        cin >> v_aux;
        arc_mapping.push_back(v_aux);
        cout << arc_mapping[i] << " ";
    }
    cout << endl;
    cin >> v_aux; // Read -1

    vector<int> func_mapping;
    func_mapping.reserve(m);
    for (int i = 0; i < m; i++) {
        cin >> v_aux;
        func_mapping.push_back(v_aux);
        cout << func_mapping[i] << " ";
    }
    cout << endl;

    return 0;
}

