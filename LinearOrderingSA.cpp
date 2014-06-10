#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

int main(){
    int m;
    int n;
    int v_aux;

    cin >> m;
    cin >> n;

    vector<int> v_degree;
    v_degree.reserve(m);
    for (int i = 0; i < m; i++) {
        cin >> v_aux;
        v_degree.push_back(v_aux);
        cout << v_degree[i] << " ";
    }
    cout << endl;

    vector<int> v_values;
    v_values.reserve(2*n);
    for (int i = 0; i < 2*n; i++) {
        cin >> v_aux;
        v_values.push_back(v_aux);
        cout << v_values[i] << " ";
    }
    cout << endl;
    cin >> v_aux; // Read -1

    vector<int> v_adj_mapping;
    v_adj_mapping.reserve(m);
    for (int i = 0; i < m; i++) {
        cin >> v_aux;
        v_adj_mapping.push_back(v_aux);
        cout << v_adj_mapping[i] << " ";
    }
    cout << endl;

    // Build graph
    vector< vector<int> > graph(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < v_degree[i]; j++) {
            graph[i].push_back( v_values[ v_adj_mapping[i]+j ] );
        }
    }

    // Print graph
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Calculate cost
    int lop_sum = 0;
    vector<int> visited(n,0);
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++){
            if ( !visited[graph[i][j]] ){
                cout << i << " " << graph[i][j] << " " << fabs(i - graph[i][j]);
                cout << endl;
                lop_sum += fabs(i - graph[i][j]);
            }
        }
        visited[i] = 1;
    }
    cout << endl << lop_sum << endl;

    return 0;
}

