#include <bits/stdc++.h>
using namespace std;
// BFS
vector<int> bfsOfGraph(int V, vector<int> adj[]) {
    vector<int> bfs;
    vector<int> vis(V, 0);
    queue<int> q;
    vis[0] = 1;
    q.push(0);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        bfs.push_back(node);
        for (auto it : adj[node]) {
            if (!vis[it]) {
                vis[it] = 1;
                q.push(it);
            }
        }
    }
    return bfs;
}
// DFS 
void dfs(int node, vector<int> adj[], vector<int>& vis, vector<int>& res) {
    vis[node] = 1;
    res.push_back(node);
    for (auto it : adj[node]) {
        if (!vis[it]) {
            dfs(it, adj, vis, res);
        }
    }
}
vector<int> dfsOfGraph(int V, vector<int> adj[]) {
    vector<int> vis(V, 0), res;
    dfs(0, adj, vis, res);
    return res;
}
// Count Connected Components
void dfsCount(int node, vector<int> adj[], vector<int>& vis) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (!vis[it]) dfsCount(it, adj, vis);
    }
}
int countComponents(int V, vector<int> adj[]) {
    vector<int> vis(V, 0);
    int count = 0;
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            count++;
            dfsCount(i, adj, vis);
        }
    }
    return count;
}
// Dijkstras
vector<int> dijkstra(int V, vector<vector<pair<int, int>>> adj, int S) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[S] = 0;
    pq.push({0, S});
    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();
        for (auto &edge : adj[currentNode]) {
            int adjNode = edge.first;
            int weight = edge.second;
            if (currentDist + weight < dist[adjNode]) {
                dist[adjNode] = currentDist + weight;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }
    return dist;
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;
    vector<int> adjUnweighted[n];
    vector<vector<pair<int, int>>> adjWeighted(n);
    cout << "Enter " << m << " edges (u v w):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // Undirected graph
        adjUnweighted[u].push_back(v);
        adjUnweighted[v].push_back(u);

        adjWeighted[u].push_back({v, w});
        adjWeighted[v].push_back({u, w});
    }
    cout << "\nAdjacency List (Unweighted):\n";
    for (int i = 0; i < n; i++) {
        cout << i << " -> ";
        for (auto it : adjUnweighted[i]) cout << it << " ";
        cout << endl;
    }
    // BFS
    vector<int> bfs = bfsOfGraph(n, adjUnweighted);
    cout << "\nBFS Traversal: ";
    for (auto it : bfs) cout << it << " ";
    cout << endl;
    // DFS
    vector<int> dfsRes = dfsOfGraph(n, adjUnweighted);
    cout << "DFS Traversal: ";
    for (auto it : dfsRes) cout << it << " ";
    cout << endl;
    // Components
    cout << "Number of Connected Components: " << countComponents(n, adjUnweighted) << endl;
    // Dijkstras
    int src;
    cout << "\nEnter source node for Dijkstras: ";
    cin >> src;
    vector<int> dist = dijkstra(n, adjWeighted, src);
    cout << "\nShortest distances from node " << src << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "To " << i << " -> ";
        if (dist[i] == INT_MAX) cout << "INF";
        else cout << dist[i];
        cout << endl;
    }
    return 0;
}
