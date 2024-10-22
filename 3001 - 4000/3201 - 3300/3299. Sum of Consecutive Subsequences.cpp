class Solution {
private:
    const int mod = 1e9 + 7;
    int n;
    std::map<int, int> csum, ends;

    int modadd(int x, int y) { return (x % mod + y % mod) % mod; }
    int modmul(int x, int y) { long long z = 1LL * x * y; z %= mod; return (int) z; }
    int modsub(int x, int y) { return (x % mod - y % mod) % mod; }

public:
    int getSum(std::vector<int>& nums) {
        n = nums.size();

        int sum = 0;
        for(int i: nums) sum = modadd(sum, i);

        csum.clear(); ends.clear();
        for(int i: nums) {
            int x, y, z;
            if(ends[i - 1] > 0) {
                x = csum[i - 1];
                y = modmul(ends[i - 1], i);
                z = modadd(x, y);
                csum[i] = modadd(csum[i], z);
                ends[i] = modadd(ends[i], ends[i - 1]);
            }
            csum[i] = modadd(csum[i], i);
            ends[i] = modadd(ends[i], 1);
        }
        int sum_inc = 0;
        for(const auto& [i, cnt]: csum) sum_inc = modadd(sum_inc, cnt);

        csum.clear(); ends.clear();
        for(int i: nums) {
            int x, y, z;
            if(ends[i + 1] > 0) {
                x = csum[i + 1];
                y = modmul(ends[i + 1], i);
                z = modadd(x, y);
                csum[i] = modadd(csum[i], z);
                ends[i] = modadd(ends[i], ends[i + 1]);
            }
            csum[i] = modadd(csum[i], i);
            ends[i] = modadd(ends[i], 1);
        }
        int sum_dec = 0;
        for(const auto& [i, cnt]: csum) sum_dec = modadd(sum_dec, cnt);

        int ans = 0;
        ans = modadd(ans, sum_inc);  
        ans = modadd(ans, sum_dec);
        ans = modsub(ans, sum);
        ans = (ans + mod) % mod;
        return ans;
    }
};
