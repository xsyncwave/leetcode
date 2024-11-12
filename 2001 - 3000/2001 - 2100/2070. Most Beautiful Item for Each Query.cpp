class Solution {
public:
    std::vector<int> maximumBeauty(std::vector<std::vector<int>>& items, std::vector<int>& queries) {
        int n = items.size();
        std::sort(items.begin(), items.end(), [](std::vector<int> i1, std::vector<int> i2){
            if(i1[0] == i2[0]) return i1[1] < i2[1];
            return i1[0] < i2[0];
        });

        std::vector<std::array<int, 2>> v;
        v.push_back({0, 0});

        for(int i = 0; i < n; i++) {
            if(v.back()[0] == items[i][0]) v.back()[1] = items[i][1];
            else v.push_back({items[i][0], items[i][1]});
        }

        n = v.size();
        for(int i = 1; i < n; i++) v[i][1] = std::max(v[i][1], v[i - 1][1]);
        
        std::vector<int> z[2];
        for(int i = 0; i < n; i++) {
            z[0].push_back(v[i][0]);
            z[1].push_back(v[i][1]);
        }

        std::vector<int> answer;
        for(int i: queries) {
            int idx = std::upper_bound(z[0].begin(), z[0].end(), i) - z[0].begin();
            answer.push_back(z[1][--idx]);
        }
        return answer;
    }
};
