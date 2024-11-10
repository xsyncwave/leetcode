class Solution {
private:
    const int mod = 1e9 + 7;
    int n;
    std::map<int, int> csum, ends;

public:
    int sumOfGoodSubsequences(std::vector<int>& nums) {
        n = nums.size();
        
        for(int i: nums) {
            int x, y, z;
            if(ends[i - 1] > 0) {
                x = csum[i - 1];
                y = (1LL * ends[i - 1] * i) % mod;
                z = (x + y) % mod;
                csum[i] = (csum[i] + z) % mod;
                ends[i] = (ends[i] + ends[i - 1]) % mod;
            }
            if(ends[i + 1] > 0) {
                x = csum[i + 1];
                y = (1LL * ends[i + 1] * i) % mod;
                z = (x + y) % mod;
                csum[i] = (csum[i] + z) % mod;
                ends[i] = (ends[i] + ends[i + 1]) % mod;
            }
            
            csum[i] = (csum[i] + i) % mod;
            ends[i] = (ends[i] + 1) % mod;
        }

        int ans = 0;
        for(const auto& [i, sum]: csum) ans = (ans + sum) % mod;
        return ans;
    }
};
