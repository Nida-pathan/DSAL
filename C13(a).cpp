/*Represent a given graph using adjacency matrix/list to perform DFS and using adjacency
list to perform BFS. Use the map of the area around the college as the graph. Identify the
prominent land marks as nodes and perform DFS and BFS on that.*/

#include <iostream>
using namespace std;

class GraphTraversal {
private:
    int top, f, r, x;
    int **adjList;
    int stackData[30], queueData[30];
    int visit[20];
    int adjMatrix[10][10];

public:
    GraphTraversal() {
        top = -1;
        f = r = -1;
        adjList = nullptr;
        x = 0;
        // Initialize adjacency matrix to 0
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    ~GraphTraversal() {
        // Clean up adjacency list memory
        if(adjList != nullptr) {
            for(int i = 0; i < x; i++) {
                delete[] adjList[i];
            }
            delete[] adjList;
        }
    }

    void createMatrix() {
        cout << "Number of nodes (max 10):\t";
        cin >> x;
        if(x > 10) {
            cout << "Maximum 10 nodes allowed!\n";
            x = 10;
        }
        
        for(int i = 0; i < x; i++) {
            for(int j = 0; j < x; j++) {
                cout << "Enter link status from node (" << i << ") to node (" << j << "): ";
                cin >> adjMatrix[i][j];
            }
        }
    }

    void createList() {
        cout << "Number of nodes:\t";
        cin >> x;
        
        // Clean up previous adjacency list if it exists
        if(adjList != nullptr) {
            for(int i = 0; i < x; i++) {
                delete[] adjList[i];
            }
            delete[] adjList;
        }
        
        adjList = new int*[x];
        for(int i = 0; i < x; i++) {
            adjList[i] = new int[x];
            for(int j = 0; j < x; j++) {
                adjList[i][j] = 0;
            }
        }

        int connected, node;
        for(int i = 0; i < x; i++) {
            cout << "\nEnter number of nodes connected to node " << i << ": ";
            cin >> connected;
            cout << "Enter the nodes connected to node " << i << ": ";
            for(int j = 0; j < connected; j++) {
                cin >> node;
                if(node >= 0 && node < x) {
                    adjList[i][node] = 1;
                } else {
                    cout << "Invalid node! Skipping.\n";
                    j--; // Retry this connection
                }
            }
        }
    }

    void displayList() {
        if(adjList == nullptr) {
            cout << "Adjacency list not created yet!\n";
            return;
        }
        
        for(int i = 0; i < x; i++) {
            cout << "\nNode " << i << " is connected to: ";
            for(int j = 0; j < x; j++) {
                if(adjList[i][j] == 1) {
                    cout << j << " ";
                }
            }
        }
        cout << "\n";
    }

    void displayMatrix() {
        cout << "   ";
        for(int i = 0; i < x; i++) {
            cout << " " << i;
        }
        cout << "\n";
        
        for(int i = 0; i < x; i++) {
            cout << i << " |";
            for(int j = 0; j < x; j++) {
                cout << " " << adjMatrix[i][j];
            }
            cout << "\n";
        }
    }

    void push(int t) {
        if(top < 29) {
            top++;
            stackData[top] = t;
        } else {
            cout << "Stack overflow!\n";
        }
    }

    int pop() {
        if(top != -1) {
            int y = stackData[top];
            top--;
            return y;
        }
        cout << "Stack underflow!\n";
        return -1;
    }

    void enqueue(int t) {
        if(r < 29) {
            if(f == -1) {
                f = 0;
            }
            r++;
            queueData[r] = t;
        } else {
            cout << "Queue overflow!\n";
        }
    }

    int dequeue() {
        if(f == -1 || f > r) {
            cout << "Queue underflow!\n";
            return -1;
        }
        int y = queueData[f];
        f++;
        if(f > r) {
            f = r = -1;
        }
        return y;
    }

    void dfs() {
        if(x == 0) {
            cout << "Graph not created yet!\n";
            return;
        }
        
        for(int i = 0; i < x; i++) {
            visit[i] = 0;
        }
        
        int v1;
        cout << "\nEnter starting node (0 to " << x-1 << "): ";
        cin >> v1;
        
        if(v1 < 0 || v1 >= x) {
            cout << "Invalid starting node!\n";
            return;
        }
        
        push(v1);
        cout << "DFS traversal is:";
        
        while(top != -1) {
            int v = pop();
            if(visit[v] == 0) {
                cout << " " << v;
                visit[v] = 1;
                // Push adjacent nodes in reverse order
                for(int i = x-1; i >= 0; i--) {
                    if(adjMatrix[v][i] == 1 && visit[i] == 0) {
                        push(i);
                    }
                }
            }
        }
        cout << "\n";
    }

    void bfs() {
        if(adjList == nullptr) {
            cout << "Adjacency list not created yet!\n";
            return;
        }
        
        for(int i = 0; i < x; i++) {
            visit[i] = 0;
        }
        
        int v1;
        cout << "\nEnter starting node (0 to " << x-1 << "): ";
        cin >> v1;
        
        if(v1 < 0 || v1 >= x) {
            cout << "Invalid starting node!\n";
            return;
        }
        
        enqueue(v1);
        visit[v1] = 1;
        cout << "BFS traversal is:";
        
        while(f != -1 && f <= r) {
            int v = dequeue();
            cout << " " << v;
            
            for(int i = 0; i < x; i++) {
                if(adjList[v][i] == 1 && visit[i] == 0) {
                    enqueue(i);
                    visit[i] = 1;
                }
            }
        }
        cout << "\n";
    }
};

int main() {
    GraphTraversal gt;
    int choice;
    
    while(true) {
        cout << "\n*** MENU ***\n";
        cout << "1. Create Graph (Matrix)\n";
        cout << "2. DFS Traversal (Using Matrix)\n";
        cout << "3. Create Graph (List)\n";
        cout << "4. BFS Traversal (Using List)\n";
        cout << "5. Display Matrix\n";
        cout << "6. Display List\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                gt.createMatrix();
                break;
            case 2:
                gt.dfs();
                break;
            case 3:
                gt.createList();
                break;
            case 4:
                gt.bfs();
                break;
            case 5:
                gt.displayMatrix();
                break;
            case 6:
                gt.displayList();
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
