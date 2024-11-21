class Solution {
public:
    int minZeroArray(std::vector<int>& nums, std::vector<std::vector<int>>& query) {
        int n = nums.size();

        std::vector<int> diff(n + 1, 0);
        int sum = 0, k = -1;
        
        for(int i = 0; i < n; i++) {
            while(sum + diff[i] < nums[i]) {
                ++k;
                if(k >= query.size()) return -1;

                int l = query[k][0];
                int r = query[k][1];
                int z = query[k][2];

                if(r < i) continue;
                diff[std::max(l, i)] += z;
                diff[r + 1] -= z;
            }
            sum += diff[i];
        }
        
        return k + 1;
    }
};
