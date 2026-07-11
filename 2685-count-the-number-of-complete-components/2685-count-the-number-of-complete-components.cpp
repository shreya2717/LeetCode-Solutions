class Solution {
public:
    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited,
             int& vertices, int& degreeSum) {
        
        visited[node] = true;
        vertices++;
        degreeSum += adj[node].size();

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, vertices, degreeSum);
            }
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<bool> visited(n, false);
        int answer = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int vertices = 0;
                int degreeSum = 0;

                dfs(i, adj, visited, vertices, degreeSum);

                // Each edge is counted twice in degreeSum
                int actualEdges = degreeSum / 2;
                int requiredEdges = vertices * (vertices - 1) / 2;

                if (actualEdges == requiredEdges) {
                    answer++;
                }
            }
        }

        return answer;
    }
};