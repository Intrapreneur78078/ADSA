#include <bits/stdc++.h>
using namespace std;
// BFS
vector<int> bfsOfGraph(int V, vector<vector<int>>& adjMat) {
    vector<int> bfs;
    vector<int> vis(V, 0);
    queue<int> q;
    vis[0] = 1;
    q.push(0);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        bfs.push_back(node);
        for (int nbr = 0; nbr < V; nbr++) {
            if (adjMat[node][nbr] && !vis[nbr]) {
                vis[nbr] = 1;
                q.push(nbr);
            }
        }
    }
    return bfs;
}
// DFS
void dfsHelper(int node, vector<vector<int>>& adjMat, vector<int>& vis, vector<int>& res) {
    vis[node] = 1;
    res.push_back(node);
    for (int nbr = 0; nbr < adjMat.size(); nbr++) {
        if (adjMat[node][nbr] && !vis[nbr]) {
            dfsHelper(nbr, adjMat, vis, res);
        }
    }
}
vector<int> dfsOfGraph(int V, vector<vector<int>>& adjMat) {
    vector<int> vis(V, 0), res;
    dfsHelper(0, adjMat, vis, res);
    return res;
}
// Count Connected Components
void dfsCount(int node, vector<vector<int>>& adjMat, vector<int>& vis) {
    vis[node] = 1;
    for (int nbr = 0; nbr < adjMat.size(); nbr++) {
        if (adjMat[node][nbr] && !vis[nbr]) {
            dfsCount(nbr, adjMat, vis);
        }
    }
}
int countComponents(int V, vector<vector<int>>& adjMat) {
    vector<int> vis(V, 0);
    int count = 0;
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            count++;
            dfsCount(i, adjMat, vis);
        }
    }
    return count;
}
// Dijkstra 
vector<int> dijkstra(int V, vector<vector<int>>& adjMat, int S) {
    vector<int> dist(V, INT_MAX);
    vector<int> vis(V, 0);
    dist[S] = 0;
    for (int i = 0; i < V - 1; i++) {
        int minDist = INT_MAX, u = -1;
        for (int j = 0; j < V; j++) {
            if (!vis[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        vis[u] = 1;
        for (int v = 0; v < V; v++) {
            if (adjMat[u][v] && !vis[v]) {
                int weight = adjMat[u][v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }
    return dist;
}
int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;
    vector<vector<int>> adjMat(n, vector<int>(n, 0));
    cout << "\nEnter " << m << " edges (u v [w]) — weight optional (default 1):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w = 1;
        string line;
        getline(cin >> ws, line);
        stringstream ss(line);
        ss >> u >> v >> w;
        adjMat[u][v] = w;
        adjMat[v][u] = w; // remove if directed graph
    }
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << adjMat[i][j] << " ";
        cout << endl;
    }
    // BFS
    vector<int> bfs = bfsOfGraph(n, adjMat);
    cout << "\nBFS Traversal: ";
    for (auto it : bfs) cout << it << " ";
    cout << endl;
    // DFS
    vector<int> dfsRes = dfsOfGraph(n, adjMat);
    cout << "DFS Traversal: ";
    for (auto it : dfsRes) cout << it << " ";
    cout << endl;
    // Components
    cout << "Number of Connected Components: " << countComponents(n, adjMat) << endl;
    // Dijkstra
    int src;
    cout << "Enter source node for Dijkstra: ";
    cin >> src;
    vector<int> dist = dijkstra(n, adjMat, src);
    cout << "\nShortest distances from node " << src << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "To " << i << " -> ";
        if (dist[i] == INT_MAX) cout << "INF";
        else cout << dist[i];
        cout << endl;
    }
    return 0;
}
