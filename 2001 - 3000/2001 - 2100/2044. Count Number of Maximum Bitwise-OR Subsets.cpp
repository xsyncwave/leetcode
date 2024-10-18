// Tabulation: TC - O(n * maxOR). SC - O(1 << 17).
class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        int maxOR = 0, dp[1 << 17] = {};

        dp[0] = 1;
        for(int n: nums) {
            maxOR |= n;                                       // exclude - do ()
            for(int i = max; i >= 0; --i) dp[i | n] += dp[i]; // include - do OR
        }
        return dp[maxOR];
    }
};
