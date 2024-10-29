class Solution {
public:
    int maxMoves(std::vector<std::vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();

        std::vector<int> prev(r, 0), curr(r, 0);
        int moves = 0;
        for(int j = 1; j < c; j++) {
            for(int i = 0; i < r; i++) {
                int x = std::max(i - 1, 0), y = std::min(i + 1, r - 1), z = i;
                
                curr[i] = 0;
                curr[i] = (grid[i][j] > grid[x][j - 1])? std::max(curr[i], 1 + prev[x]): curr[i];
                curr[i] = (grid[i][j] > grid[y][j - 1])? std::max(curr[i], 1 + prev[y]): curr[i];
                curr[i] = (grid[i][j] > grid[z][j - 1])? std::max(curr[i], 1 + prev[z]): curr[i];
                moves = std::max(moves, curr[i]);
            }
            if(moves < j) return moves;
            std::swap(prev, curr);
        }
        
        return moves;
    }
};
