/*You have a business with several offices; you want to lease phone lines to connect them
up with each other; and the phone company charges different amounts of money to
connect different pairs of cities. You want a set of lines that connects all your offices with
a minimum total cost. Solve the problem by suggesting appropriate data structures. */

#include <iostream>
#include <string>
using namespace std;

#define MAX_NUM_CITIES 10
#define INF 99999  // Replaces INT32_MAX

struct edge {
    int start;
    int end;
    int wt;
};

class graph {
    int adj_mat[MAX_NUM_CITIES][MAX_NUM_CITIES];
    string city_names[MAX_NUM_CITIES];
    int city_count;
    edge mst[MAX_NUM_CITIES - 1];
    edge edge_list[100];  // Custom priority queue
    int edge_list_size;
    int cost;

    void add_to_list(edge);

public:
    graph();
    void prims_algo(int);
    void display_mst();
};

graph::graph() {
    cost = 0;
    edge_list_size = 0;
    cout << "Number of cities are (1-" << MAX_NUM_CITIES << "): ";
    cin >> city_count;
    if (city_count > MAX_NUM_CITIES) city_count = MAX_NUM_CITIES;

    for (int i = 0; i < city_count; i++) {
        cout << "Enter city " << i + 1 << ": ";
        cin >> city_names[i];
    }

    for (int i = 0; i < city_count; i++)
        for (int j = 0; j < city_count; j++)
            adj_mat[i][j] = INF;

    int num_pairs;
    cout << "Number of city pairs: ";
    cin >> num_pairs;

    cout << "City codes are:\n";
    for (int i = 0; i < city_count; i++) {
        cout << i << " - " << city_names[i] << endl;
    }

    for (int i = 0; i < num_pairs; i++) {
        int x, y, wt;
        cout << "Enter pair " << i + 1 << ": ";
        cin >> x >> y;
        cout << "Enter cost between city " << city_names[x] << " & city " << city_names[y] << ": ";
        cin >> wt;
        adj_mat[x][y] = wt;
        adj_mat[y][x] = wt;
    }
}

void graph::add_to_list(edge e) {
    // Insert edge while keeping edge_list sorted by weight
    int i = edge_list_size - 1;
    while (i >= 0 && edge_list[i].wt > e.wt) {
        edge_list[i + 1] = edge_list[i];
        i--;
    }
    edge_list[i + 1] = e;
    edge_list_size++;
}

void graph::prims_algo(int start) {
    bool visited[MAX_NUM_CITIES] = {false};
    visited[start] = true;
    int visited_count = 1;

    for (int i = 0; i < city_count; i++) {
        if (adj_mat[start][i] != INF) {
            edge e = {start, i, adj_mat[start][i]};
            add_to_list(e);
        }
    }

    while (visited_count < city_count && edge_list_size > 0) {
        edge min_edge = edge_list[0];

        // Remove the front edge
        for (int i = 1; i < edge_list_size; i++) {
            edge_list[i - 1] = edge_list[i];
        }
        edge_list_size--;

        if (!visited[min_edge.end]) {
            mst[visited_count - 1] = min_edge;
            cost += min_edge.wt;
            visited[min_edge.end] = true;
            visited_count++;

            for (int i = 0; i < city_count; i++) {
                if (!visited[i] && adj_mat[min_edge.end][i] != INF) {
                    edge e = {min_edge.end, i, adj_mat[min_edge.end][i]};
                    add_to_list(e);
                }
            }
        }
    }
}

void graph::display_mst() {
    cout << "\nMost efficient network is:\n";
    for (int i = 0; i < city_count - 1; i++) {
        cout << city_names[mst[i].start] << " to " << city_names[mst[i].end]
             << " of weight " << mst[i].wt << endl;
    }
    cout << "\nThe cost of network is: " << cost << endl;
}

int main() {
    graph g;
    int start;
    cout << "Enter beginning city: ";
    cin >> start;
    if (start >= MAX_NUM_CITIES) start = 0;
    g.prims_algo(start);
    g.display_mst();
    return 0;
}

