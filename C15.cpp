/*You have a business with several offices; you want to lease phone lines to connect them
up with each other; and the phone company charges different amounts of money to
connect different pairs of cities. You want a set of lines that connects all your offices with
a minimum total cost. Solve the problem by suggesting appropriate data structures. */
  
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#define MAX_NUM_CITIES 10

using namespace std;

struct Edge {
    int start;
    int end;
    int weight;
    
    // For easier sorting
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class Graph {
    vector<vector<int>> adj_mat;
    vector<string> city_names;
    vector<Edge> mst;
    int city_count;
    int total_cost;
    
    void add_sorted_edge(vector<Edge>& edges, Edge e) {
        edges.insert(
            upper_bound(edges.begin(), edges.end(), e),
            e
        );
    }

public:
    Graph();
    void prims_algorithm(int start);
    void display_mst();
};

Graph::Graph() : total_cost(0) {
    cout << "Number of cities (1-" << MAX_NUM_CITIES << "): ";
    cin >> city_count;
    city_count = min(city_count, MAX_NUM_CITIES);
    
    adj_mat.resize(city_count, vector<int>(city_count, INT_MAX));
    city_names.resize(city_count);
    
    for (int i = 0; i < city_count; i++) {
        cout << "Enter city #" << i+1 << ": ";
        cin >> city_names[i];
    }
    
    int num_pairs;
    cout << "Number of city pairs: ";
    cin >> num_pairs;
    
    cout << "City codes:\n";
    for (int i = 0; i < city_count; i++) {
        cout << i << " - " << city_names[i] << endl;
    }
    
    for (int i = 0; i < num_pairs; i++) {
        int x, y, weight;
        cout << "Pair #" << i+1 << " (enter two city codes): ";
        cin >> x >> y;
        
        if (x < 0 || x >= city_count || y < 0 || y >= city_count) {
            cout << "Invalid city code! Try again.\n";
            i--;
            continue;
        }
        
        cout << "Enter cost between " << city_names[x] << " and " << city_names[y] << ": ";
        cin >> weight;
        adj_mat[x][y] = weight;
        adj_mat[y][x] = weight;
    }
}

void Graph::prims_algorithm(int start) {
    if (start < 0 || start >= city_count) {
        cerr << "Invalid starting city!\n";
        return;
    }
    
    vector<bool> visited(city_count, false);
    vector<Edge> edges;
    total_cost = 0;
    mst.clear();
    
    visited[start] = true;
    
    // Add initial edges
    for (int i = 0; i < city_count; i++) {
        if (adj_mat[start][i] != INT_MAX) {
            add_sorted_edge(edges, {start, i, adj_mat[start][i]});
        }
    }
    
    while (mst.size() < city_count - 1 && !edges.empty()) {
        Edge current = edges.front();
        edges.erase(edges.begin());
        
        if (!visited[current.end]) {
            mst.push_back(current);
            total_cost += current.weight;
            visited[current.end] = true;
            
            // Add new edges from the newly visited node
            for (int i = 0; i < city_count; i++) {
                if (adj_mat[current.end][i] != INT_MAX && !visited[i]) {
                    add_sorted_edge(edges, {current.end, i, adj_mat[current.end][i]});
                }
            }
        }
    }
    
    if (mst.size() != city_count - 1) {
        cerr << "Warning: Graph is not fully connected. MST may be incomplete.\n";
    }
}

void Graph::display_mst() {
    cout << "\nMost efficient network:\n";
    for (const auto& edge : mst) {
        cout << city_names[edge.start] << " to " << city_names[edge.end] 
             << " (cost: " << edge.weight << ")\n";
    }
    cout << "\nTotal network cost: " << total_cost << endl;
}

int main() {
    Graph g;
    int start;
    
    cout << "Enter starting city code: ";
    cin >> start;
    
    g.prims_algorithm(start);
    g.display_mst();
    
    return 0;
}
