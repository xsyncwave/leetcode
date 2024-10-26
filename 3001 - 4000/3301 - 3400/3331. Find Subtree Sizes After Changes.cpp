class Solution {
private:
    int n;
    std::vector<std::vector<int>> realTree, fakeTree;
    std::vector<int> newparent;

    void dfs(int curr, int prev, std::array<int, 26>& ancestor, std::string& s) {
        int tmp = ancestor[s[curr] - 'a'];
        
        ancestor[s[curr] - 'a'] = curr;
        for(int next: realTree[curr]) {
            dfs(next, curr, ancestor, s);
        }
        
        ancestor[s[curr] - 'a'] = tmp;
        newparent[curr] = ancestor[s[curr] - 'a'];
    }

    int dfs(int curr, int prev, std::vector<int>& answer) {
        for(int next: fakeTree[curr]) {
            answer[curr] += dfs(next, curr, answer);
        }
        return answer[curr];
    }

public:
    std::vector<int> findSubtreeSizes(std::vector<int>& parent, std::string s) {
        n = parent.size() & s.size();
        realTree.resize(n); fakeTree.resize(n); newparent.resize(n);
        for(int i = 1; i < n; i++) realTree[parent[i]].push_back(i);

        std::array<int, 26> ancestor;
        std::fill(ancestor.begin(), ancestor.end(), -1);
        dfs(0, -1, ancestor, s);
      
        for(int i = 1; i < n; i++) newparent[i] = (newparent[i] == -1)? parent[i]: newparent[i];
        for(int i = 1; i < n; i++) fakeTree[newparent[i]].push_back(i);

        std::vector<int> answer(n, 1); 
        answer[0] = dfs(0, -1, answer);
        
        return answer;
    }
};
