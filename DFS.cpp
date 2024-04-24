//DFS

#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <omp.h>

using namespace std;

// Node struct with a visited flag for DFS
struct Node {
    int data;
    vector<Node*> neighbors;
    bool visited = false;

    Node(int _data) : data(_data) {}
};

// Parallel DFS implementation
void parallelDFS(Node* root) {
    root->visited = true;
    cout << root->data << " ";  // Visit node

    #pragma omp parallel for
    for (int i = 0; i < root->neighbors.size(); ++i) {
        Node* neighbor = root->neighbors[i];
        if (!neighbor->visited) {
            parallelDFS(neighbor);
        }
    }
}

int main() {
    const int num_nodes = 100; // Number of nodes
    vector<Node*> nodes(num_nodes);

    // Creating nodes
    for (int i = 0; i < num_nodes; ++i) {
        nodes[i] = new Node(i);
    }

    // Establishing random connections between nodes
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, num_nodes - 1);

    for (int i = 0; i < num_nodes; ++i) {
        int num_connections = dis(gen); // Random number of connections for each node
        for (int j = 0; j < num_connections; ++j) {
            int rand_index = dis(gen);
            nodes[i]->neighbors.push_back(nodes[rand_index]);
        }
    }

    // Call parallel DFS with a randomly chosen root node
    int root_index = dis(gen);
    parallelDFS(nodes[root_index]);

    // Deallocate memory for nodes
    for (Node* node : nodes) {
        delete node;
    }

    return 0;
}
