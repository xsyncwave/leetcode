struct DSUF {
    std::vector<int> head;
    std::vector<int> rank;

    DSUF(int n) {
        head.resize(n + 1); std::iota(head.begin(), head.end(), 0);
        rank.resize(n + 1); std::fill(rank.begin(), rank.end(), 0);
    }
    
    void join(int x, int y) {
        int headX = find(x);
        int headY = find(y);

        if(headX == headY) return;

        int smol = (rank[headX] <= rank[headY])? headX: headY; // if(rankX == rankY) smol = X;
        int bigg = (rank[headY] >= rank[headX])? headY: headX; // if(rankX == rankY) bigg = Y;

        if(rank[smol] == rank[bigg]) {
            head[smol] = bigg;
            rank[bigg]++;
        }
        else head[smol] = bigg;
    }
    
    int find(int z) {
        if(head[z] != z) head[z] = find(head[z]);
        return head[z];
    }
    
    bool connected(int x, int y) { return find(x) == find(y); }
};

class Solution {
public:
    std::vector<bool> areConnected(int n, int threshold, std::vector<std::vector<int>>& queries) {
        DSUF dsuf(n+1);

        std::function<void()> precompute = [&]() -> void {
            std::vector<bool> visited(n + 1, 0);

            for(int z = threshold + 1; z <= n; z++) {
                if(!visited[z]) {
                    int mult = 1;
                    while(z * mult <= n) {
                        dsuf.join(z, z * mult);
                        visited[z * mult] = 1; 
                        ++mult;
                    }
                }
            }
        };
        precompute();

        std::vector<bool> answer;
        for(const std::vector<int>& query: queries) 
            answer.push_back(dsuf.connected(query[0], query[1]));
        return answer;
    }
};
