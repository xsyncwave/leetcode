class Solution {
private:
    int n, u, v, dist;
    std::vector<std::vector<int>> graph;
    std::vector<int> dist_u, dist_v, answer;

public:
    std::vector<int> lastMarkedNodes(std::vector<std::vector<int>>& edges) {
        n = edges.size() + 1; 
        graph.resize(n); dist_u.assign(n, -1); dist_v.assign(n, -1); answer.resize(n);

        for(const std::vector<int>& edge: edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }

        std::function<void(int, int, int, int&)> dfs = [&](int curr, int prev, int d, int& w) -> void {
            if(d > dist) { dist = d; w = curr; }
            for(const int& next: graph[curr]) {
                if(next == prev) continue;
                dfs(next, curr, d + 1, w);
            }
        };
        u = -1; dist = -1; dfs(0, -1, 0, u);
        v = -1; dist = -1; dfs(u, -1, 0, v);
        
        std::queue<int> qbfs;
      
        std::function<void(std::vector<int>&)> bfs = [&](std::vector<int>& dist_w) -> void {
            int d = 1;
            while(!qbfs.empty()) {
                int sz = qbfs.size();
                for(int i = 0; i < sz; i++) {
                    int node = qbfs.front();
                    for(const int& i: graph[node]) {
                        if(dist_w[i] > -1) continue;
                        dist_w[i] = d; qbfs.push(i);
                    }
                    qbfs.pop();
                }
                ++d;
            }
        };
        dist_u[u] = 0; qbfs.push(u); bfs(dist_u);
        dist_v[v] = 0; qbfs.push(v); bfs(dist_v);

        for(int i = 0; i < n; i++) answer[i] = (dist_u[i] > dist_v[i])? u: v;
        return answer;
    }
};
