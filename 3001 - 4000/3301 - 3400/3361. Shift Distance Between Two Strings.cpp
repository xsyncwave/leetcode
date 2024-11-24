class Solution {
private:
    long long memo[26][26];
    std::function<long long (int, int, char)> compute;

public:
    long long shiftDistance(std::string s, std::string t, 
                            std::vector<int>& nextCost, std::vector<int>& prevCost) {
        
        int n = s.length() & t.length();
        long long cost = 0;

        std::fill(&memo[0][0], &memo[0][0] + sizeof(memo) / sizeof(memo[0][0]), -1LL);

        compute = [&](int x, int y, char z) -> long long {
            long long cost = 0;
            while(x != y) {
                if(z == '+') { cost += nextCost[x]; x = (x + 1 + 26) % 26; }
                if(z == '-') { cost += prevCost[x]; x = (x - 1 + 26) % 26; }
            }
            return cost;
        };

        for(int i = 0; i < n; i++) {
            int x = s[i] - 'a';
            int y = t[i] - 'a';

            if(memo[x][y] == -1) {
                long long nCost = compute(x, y, '+');
                long long pCost = compute(x, y, '-');
                
                memo[x][y] = std::min(nCost, pCost);
                cost += memo[x][y];
            }
            else cost += memo[x][y];
        }

        return cost;
    }
};
