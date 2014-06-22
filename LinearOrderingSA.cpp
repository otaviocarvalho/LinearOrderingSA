#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

vector<int> graph_read_degrees(int n, vector<int> v){
    int v_aux;

    v.reserve(n);
    for (int i = 0; i < n; i++) {
        cin >> v_aux;
        v.push_back(v_aux);
        //cout << v[i] << " ";
    }
    //cout << endl;

    return v;
}

vector<int> graph_read_content(int m, vector<int> v){
    int v_aux;

    v.reserve(2*m);
    for (int i = 0; i < 2*m; i++) {
        cin >> v_aux;
        v.push_back(v_aux);
        //cout << v[i] << " ";
    }
    //cout << endl;

    return v;
}

vector<int> graph_read_adj_map(int n, vector<int> v){
    int v_aux;

    v.reserve(n);
    for (int i = 0; i < n; i++) {
        cin >> v_aux;
        v.push_back(v_aux);
        //cout << v[i] << " ";
    }
    //cout << endl;

    return v;
}

vector< vector<int> > graph_read(int n, int m, vector< vector<int> > graph){
    int v_aux;

    vector<int> v_degree;
    v_degree = graph_read_degrees(n, v_degree); // Read graph degrees from file

    vector<int> v_values;
    v_values = graph_read_content(m, v_values);
    cin >> v_aux; // Read -1 separator

    vector<int> v_adj_map;
    v_adj_map = graph_read_adj_map(n, v_adj_map);

    graph.resize(n);
    // Build graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < v_degree[i]; j++) {
            graph[i].push_back( v_values[ v_adj_map[i]+j ] );
        }
    }

    // Print graph
    //cout << endl;
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            //cout << graph[i][j] << " ";
        }
        //cout << endl;
    }
    //cout << endl;

    return graph;
}

double graph_cost(int n, vector< vector<int> > graph, unordered_map<int, int> graph_map){
    double lop_sum = 0;

    vector<int> visited(n,0);
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++){
            if ( !visited[ graph_map[graph[i][j]] ] ){
                ////cout << i << " " << graph[i][j] << " " << fabs(i - graph[i][j]);
                //cout << graph_map[i] << " " << graph_map[graph[i][j]] << " " << fabs(graph_map[i] - graph_map[graph[i][j]]);
                //cout << endl;
                ////lop_sum += fabs(i - graph[i][j]);

                // Sum vertexes using their mapped values (1..N)
                lop_sum += fabs(graph_map[i] - graph_map[graph[i][j]]);
            }
        }
        visited[graph_map[i]] = 1;
    }
    //cout << endl << lop_sum << endl;

    return lop_sum;
}

unordered_map<int, int> graph_map_phi_random(int n, vector< vector<int> > graph, unordered_map<int,int> graph_map){

    for (int i = 0; i < n; i++) {
        int marked = 0;
        while(!marked){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dist(0,graph.size()-1);
            int val_rand = dist(gen);
            //cout << val_rand << endl;

            if (graph_map.count(val_rand) == 0){
                graph_map.insert(make_pair(val_rand,i));
                marked = 1;
            }
        }
    }

    //Print map values
    //for (auto& x : graph_map) {
        //cout << x.first << ": " << x.second << endl;
    //}

    return graph_map;
}

unordered_map<int, int> graph_map_phi(int n, vector< vector<int> > graph, unordered_map<int,int> graph_map){
    int count_values = n-1;
    //int count_values = 0;
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++){
            if (graph_map.count(graph[i][j]) == 0){
                graph_map.insert(make_pair(graph[i][j],count_values));
                count_values--;
                //count_values++;
            }
        }
    }

    // Print map values
    //for (auto& x : graph_map) {
        //cout << x.first << ": " << x.second << endl;
    //}

    return graph_map;
}

unordered_map<int,int> generate_graph_neighbourhood(int n, vector< vector<int> > graph, unordered_map<int,int> graph_map){

    // Generate random number for lines of the graph
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist1(0,graph.size()-1);
    int val_rand1 = dist1(gen);
    //cout << endl << "graph size " << graph.size()-1 << " val rand " << val_rand1 << endl;

    // Generate random number for columns, given a line of the graph
    uniform_int_distribution<int> dist2(0,graph[val_rand1].size()-1);
    int val_rand2 = dist2(gen);
    //cout << endl << graph[val_rand1].size()-1 << " " << val_rand2 << endl;

    // Find the two originally mapped values
    int vertex_1_mapped_val = graph_map[val_rand1];
    //cout << "vertex_1 is " << vertex_1_mapped_val << endl;
    int vertex_2_mapped_val = graph_map[val_rand2];
    //cout << "vertex_2 is " << vertex_2_mapped_val << endl;

    // Swap values of two neighbours
    swap(graph_map[val_rand1], graph_map[val_rand2]);

    vertex_1_mapped_val = graph_map[val_rand1];
    //cout << "swapped vertex 1 is " << vertex_1_mapped_val << endl;
    vertex_2_mapped_val = graph_map[val_rand2];
    //cout << "swapped vertex_2 is " << vertex_2_mapped_val << endl;

    //double cost = graph_cost(n, graph, graph_map);
    //cout << "test cost " << cost << endl;

    //exit(1);

    // Change two values into the graph
    return graph_map;
}

double acceptance_probability(double actual_cost, double new_cost, double temperature){
    // Accept solution when a best one was found
    if (new_cost < actual_cost){
        //cout << "Best one was found!" << endl;
        return 1.0;
    }
    else {
        //cout << "exp result: " << exp((actual_cost - new_cost) / temperature) << endl;
        return exp((actual_cost - new_cost) / temperature);
    }
}

double simulated_annealing(int round, int n, int m, vector< vector<int> > graph){
    // Generate Inicial Solution
    // Map graph to phi function
    unordered_map<int,int> graph_map;
    graph_map = graph_map_phi(n, graph, graph_map);
    //graph_map = graph_map_phi_random(n, graph, graph_map);

    // Calculate Inicial Solution Cost
    double best_cost = graph_cost(n, graph, graph_map);
    unordered_map<int,int> best_cost_graph_map = graph_map;

    // Set Current Solution As Best
    double actual_cost = best_cost;
    unordered_map<int,int> actual_cost_graph_map = best_cost_graph_map;

    // Simulated Annealing
    double temperature = 100000;
    double cooling_rate = 0.90;

    // Loop Until System Has Cooled
    int while_count = 0;
    while (temperature > 1){
    //while (temperature > 6000){
        // Create new neighbour solution
        unordered_map<int,int> new_cost_graph_map = generate_graph_neighbourhood(n, graph, graph_map);

        // Calculate cost of new solution
        double new_cost = graph_cost(n, graph, new_cost_graph_map);
        //cout << "new cost: " << new_cost << endl;
        //cout << "actual cost: " << actual_cost << endl;
        //cout << "best cost: " << best_cost << endl;

        // Decide if we should accept the neighbour (acceptance probability for a worse solution included)
        // Update best solution
        random_device rd;
        mt19937 gen(rd());
        double rand_value = generate_canonical<double,10>(gen);
        //cout << "rand value " << rand_value << endl;
        //if (0.5 > rand_value){
        if (acceptance_probability(actual_cost, new_cost, temperature) > rand_value){
            actual_cost = new_cost;
            actual_cost_graph_map = new_cost_graph_map;
        }

        //if (while_count == 100)
            //exit(1);

        // Keep track of the best solution found
        if (new_cost < best_cost){
            best_cost = new_cost;
            best_cost_graph_map = new_cost_graph_map;
        }

        // Cool system
        temperature *= 1 - cooling_rate;
        //cout << "temperature changed: " << temperature << endl << endl;

        while_count++;
        new_cost_graph_map.clear();
    }

    // Print Best Solution
    // Print Cost of Best Solution
    cout << "Round #" << round << " - Best solution found: " << best_cost << endl;
    graph.clear();
    graph_map.clear();
    best_cost_graph_map.clear();
    actual_cost_graph_map.clear();

    return best_cost;
}

int main(){
    int n, m; // Graph dimensions
    vector< vector<int> > graph;

    // Read graph dimensions
    cin >> n;
    //cout << n << endl;
    cin >> m;
    //cout << m << endl;

    // Read input file and build graph structure
    graph = graph_read(n, m, graph);

    double mean_cost;
    for (int i = 0; i < 20; i++) {
        mean_cost += simulated_annealing(i,n,m,graph);
    }
    cout << "Mean cost: " << (int) (mean_cost / 20);

    return 0;
}
