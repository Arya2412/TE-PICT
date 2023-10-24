#include <bits/stdc++.h>
using namespace std;

#define N 5
#define INF INT_MAX

class Node {
public:
    vector<pair<int, int>> path;
    int reducedMatrix[N][N];
    int totalCost;
    int currentNode;
    int currentLevel;
};

// Create a new node with updated data
Node* createNode(int parentMatrix[N][N], vector<pair<int, int>> const& path, int level, int i, int j) {
    Node* node = new Node;
    node->path = path;
    if (level != 0)
        node->path.push_back(make_pair(i, j));
    memcpy(node->reducedMatrix, parentMatrix, sizeof node->reducedMatrix);
    for (int k = 0; level != 0 && k < N; k++) {
        node->reducedMatrix[i][k] = INF;
        node->reducedMatrix[k][j] = INF;
    }
    node->reducedMatrix[j][0] = INF;
    node->currentLevel = level;
    node->currentNode = j;
    return node;
}

// Reduce the rows of the matrix
void reduceRows(int reducedMatrix[N][N], int row[N]) {
    fill_n(row, N, INF);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] < row[i])
                row[i] = reducedMatrix[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] != INF && row[i] != INF)
                reducedMatrix[i][j] -= row[i];
}

// Reduce the columns of the matrix
void reduceColumns(int reducedMatrix[N][N], int col[N]) {
    fill_n(col, N, INF);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] < col[j])
                col[j] = reducedMatrix[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (reducedMatrix[i][j] != INF && col[j] != INF)
                reducedMatrix[i][j] -= col[j];
}

// Calculate the total cost of the reduced matrix
int calculateCost(int reducedMatrix[N][N]) {
    int cost = 0;
    int row[N];
    reduceRows(reducedMatrix, row);
    int col[N];
    reduceColumns(reducedMatrix, col);
    for (int i = 0; i < N; i++)
        cost += (row[i] != INT_MAX) ? row[i] : 0, cost += (col[i] != INT_MAX) ? col[i] : 0;
    return cost;
}

// Print the path of the nodes
void printPath(vector<pair<int, int>> const& path) {
    for (int i = 0; i < path.size(); i++)
        cout << path[i].first + 1 << " -> " << path[i].second + 1 << endl;
}

class Comparator {
public:
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->totalCost > rhs->totalCost;
    }
};

// Solve the problem using A* algorithm
int solve(int adjacencyMatrix[N][N]) {
    priority_queue<Node*, vector<Node*>, Comparator> pq;
    vector<pair<int, int>> v;
    Node* root = createNode(adjacencyMatrix, v, 0, -1, 0);
    root->totalCost = calculateCost(root->reducedMatrix);
    pq.push(root);
    while (!pq.empty()) {
        Node* minNode = pq.top();
        pq.pop();
        int i = minNode->currentNode;
        if (minNode->currentLevel == N - 1) {
            minNode->path.push_back(make_pair(i, 0));
            cout << "Optimal Path: " << endl;
            printPath(minNode->path);
            return minNode->totalCost;
        }
        for (int j = 0; j < N; j++) {
            if (minNode->reducedMatrix[i][j] != INF) {
                Node* child = createNode(minNode->reducedMatrix, minNode->path, minNode->currentLevel + 1, i, j);
                child->totalCost = minNode->totalCost + minNode->reducedMatrix[i][j] + calculateCost(child->reducedMatrix);
                pq.push(child);
            }
        }
        delete minNode;
    }
}

int main() {
    int adjacencyMatrix[N][N];
    
    // Input adjacency matrix from the user
    cout << "Enter the adjacency matrix (" << N << "x" << N << "):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> adjacencyMatrix[i][j];
        }
    }

    cout << "Optimal Cost: " << solve(adjacencyMatrix) << endl;

    return 0;
}




// Enter the adjacency matrix (5x5):
// INF 20 30 10 11
// 15 INF 16 4 2
// 3 5 INF 2 4
// 19 6 18 INF 3
// 16 4 7 16 INF

// Optimal Path:
// 1 -> 4
// 4 -> 2
// 2 -> 5
// 5 -> 3
// Optimal Cost: 16
