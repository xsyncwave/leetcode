class Solution {
private:
    const int mod = 1e9 + 7;
    long long pow[100001];
    
    std::vector<std::vector<int>> tree;
    std::vector<int> count;
    std::vector<long long> fHash, rHash;

    void pre_compute(int n) {
        pow[0] = 1LL;
        for(int i = 1; i <= n; i++) {
            pow[i] = (pow[i-1] % mod * 31 % mod) % mod;
        }
    }

    void for_dfs(int curr, const std::string_view &s) {
        count[curr] = 0; 
        fHash[curr] = 0;

        for(int i = 0; i <= (int) tree[curr].size() - 1; i++) {
            int child = tree[curr][i];
            for_dfs(child, s);
            
            fHash[curr] = (fHash[curr] + (fHash[child] * pow[count[curr]]) % mod) % mod;
            count[curr] += count[child];
        }

        fHash[curr] = (fHash[curr] + (pow[count[curr]] * (s[curr] - 'a' + 1)) % mod) % mod;
        count[curr]++;
    }

    void rev_dfs(int curr, const std::string_view &s) {
        count[curr] = 1;
        rHash[curr] = s[curr] - 'a' + 1;

        for(int i = (int) tree[curr].size() - 1; i >= 0; i--) {
            int child = tree[curr][i];
            rev_dfs(child, s);
            
            rHash[curr] = (rHash[curr] + (rHash[child] * pow[count[curr]]) % mod) % mod;
            count[curr] += count[child];
        }
    }

public:
    std::vector<bool> findAnswer(std::vector<int>& parent, std::string& s) {
        int n = parent.size() & s.length();

        pre_compute(n);
        
        tree.resize(n);
        for(int i = 1; i < n; i++) tree[parent[i]].push_back(i);

        fHash.resize(n); rHash.resize(n); count.resize(n);
        for_dfs(0, std::string_view(s));
        rev_dfs(0, std::string_view(s));

        std::vector<bool> answer(n);
        for(int i = 0; i < n; i++) answer[i] = (fHash[i] == rHash[i]); 
        return answer;
    }
};
