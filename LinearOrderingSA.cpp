#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <chrono>

// Define start solution: 1 to BFS, 2 to random and 3 to statically ordered
#define PHI_FUNCTION 1

using namespace std;

double best_start_solution = numeric_limits<double>::infinity();

vector<int> graph_read_degrees(int n, vector<int> v){
    int v_aux;

    v.reserve(n);
    for (int i = 0; i < n; i++) {
        cin >> v_aux;
        v.push_back(v_aux);
    }

    return v;
}

vector<int> graph_read_content(int m, vector<int> v){
    int v_aux;

    v.reserve(2*m);
    for (int i = 0; i < 2*m; i++) {
        cin >> v_aux;
        v.push_back(v_aux);
    }

    return v;
}

vector<int> graph_read_adj_map(int n, vector<int> v){
    int v_aux;

    v.reserve(n);
    for (int i = 0; i < n; i++) {
        cin >> v_aux;
        v.push_back(v_aux);
    }

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

    return graph;
}

double graph_cost(int n, vector< vector<int> > graph, unordered_map<int, int> graph_map){
    double lop_sum = 0;

    vector<int> visited(n,0);
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++){
            if ( !visited[ graph_map[graph[i][j]] ] ){
                // Sum vertexes using their mapped values (1..N)
                lop_sum += fabs(graph_map[i] - graph_map[graph[i][j]]);
            }
        }
        visited[graph_map[i]] = 1;
    }

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

            if (graph_map.count(val_rand) == 0){
                graph_map.insert(make_pair(val_rand,i));
                marked = 1;
            }
        }
    }

    return graph_map;
}

unordered_map<int, int> graph_map_phi_random_bfs(int n, vector< vector<int> > graph, unordered_map<int,int> graph_map){
    vector<int> visited(n,0);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0,graph.size()-1);
    int val_rand = dist(gen);

    // Start from a random value and name vertices by performing bfs in the graph
    int count_visited = 0;
    queue<int> q;
    q.push(val_rand);
    while (!q.empty() && count_visited != n-1){
        int current_node = q.front();
        q.pop();

        // Mark node as visited and put a value on them
        graph_map.insert(make_pair(current_node,count_visited));
        count_visited++;

        // Push neighbours to queue
        for (int i = 0; i < graph[current_node].size(); i++) {
            if ( !visited[ graph[current_node][i]] ){
                q.push(graph[current_node][i]);
                visited[ graph[current_node][i] ] = 1;
            }
        }
    }

    return graph_map;
}

unordered_map<int, int> graph_map_phi(int n, vector< vector<int> > graph, unordered_map<int,int> graph_map){
    int count_values = n-1;
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++){
            if (graph_map.count(graph[i][j]) == 0){
                graph_map.insert(make_pair(graph[i][j],count_values));
                count_values--;
            }
        }
    }

    return graph_map;
}

unordered_map<int,int> generate_graph_neighbourhood(int n, vector< vector<int> > graph, unordered_map<int,int> graph_map){

    // Generate random number for lines of the graph
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist1(0,graph.size()-1);
    int val_rand1 = dist1(gen);

    // Generate random number for columns, given a line of the graph
    uniform_int_distribution<int> dist2(0,graph[val_rand1].size()-1);
    int val_rand2 = dist2(gen);

    // Find the two originally mapped values
    int vertex_1_mapped_val = graph_map[val_rand1];
    int vertex_2_mapped_val = graph_map[val_rand2];

    // Swap values of two neighbours
    swap(graph_map[val_rand1], graph_map[val_rand2]);

    vertex_1_mapped_val = graph_map[val_rand1];
    vertex_2_mapped_val = graph_map[val_rand2];

    // Change two values into the graph
    return graph_map;
}

double acceptance_probability(double actual_cost, double new_cost, double temperature){
    // Accept solution when a best one was found
    if (new_cost < actual_cost){
        return 1.0;
    }
    else {
        return exp((actual_cost - new_cost) / temperature);
    }
}

double simulated_annealing(int round, int n, int m, vector< vector<int> > graph){
    // Generate Inicial Solution
    unordered_map<int,int> graph_map;

    // Map graph to phi function
    if (PHI_FUNCTION == 1)
        graph_map = graph_map_phi_random_bfs(n, graph, graph_map);
    else if (PHI_FUNCTION == 2)
        graph_map = graph_map_phi_random(n, graph, graph_map);
    else
        graph_map = graph_map_phi(n, graph, graph_map);

    // Calculate Inicial Solution Cost
    double best_cost = graph_cost(n, graph, graph_map);
    unordered_map<int,int> best_cost_graph_map = graph_map;

    // Set Current Solution As Best
    double actual_cost = best_cost;
    unordered_map<int,int> actual_cost_graph_map = best_cost_graph_map;

    // Print start solution cost
    cout << "Round #" << round << " - Start solution: " << actual_cost << endl;
    if (best_start_solution > actual_cost){
        best_start_solution = actual_cost;
    }

    // Simulated Annealing
    double temperature = 1000000;
    double cooling_rate = 0.8;

    // Loop Until System Has Cooled
    int while_count = 0;
    while (temperature > 1){
        // Create new neighbour solution
        unordered_map<int,int> new_cost_graph_map = generate_graph_neighbourhood(n, graph, graph_map);

        // Calculate cost of new solution
        double new_cost = graph_cost(n, graph, new_cost_graph_map);

        // Decide if we should accept the neighbour (acceptance probability for a worse solution included)
        random_device rd;
        mt19937 gen(rd());
        double rand_value = generate_canonical<double,10>(gen);
        if (acceptance_probability(actual_cost, new_cost, temperature) > rand_value){
            actual_cost = new_cost;
            actual_cost_graph_map = new_cost_graph_map;
        }

        // Keep track of the best solution found
        if (new_cost < best_cost){
            best_cost = new_cost;
            best_cost_graph_map = new_cost_graph_map;
        }

        // Cool system
        temperature *= 1 - cooling_rate;

        while_count++;
        new_cost_graph_map.clear();
    }

    // Print Best Solution
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
    cin >> m;

    // Read input file and build graph structure
    graph = graph_read(n, m, graph);

    double best_solution = numeric_limits<double>::infinity();
    double actual_solution = 0;
    double mean_cost;
    auto t_start = chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; i++) {
        actual_solution = simulated_annealing(i,n,m,graph);
        mean_cost += actual_solution;

        // Keep track of the best overall solution found
        if (actual_solution < best_solution){
            best_solution = actual_solution;
        }
    }
    auto t_end = chrono::high_resolution_clock::now();
    cout << "Total execution time: " << chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count() << " milliseconds" << endl;
    cout << "Total execution time: " << chrono::duration_cast<std::chrono::seconds>(t_end - t_start).count() << " seconds" << endl;
    cout << "Mean cost: " << (int) (mean_cost / 20) << endl;
    cout << "Best overall start solution found: " << best_start_solution << endl;
    cout << "Best overall solution found: " << best_solution << endl;

    return 0;
}
