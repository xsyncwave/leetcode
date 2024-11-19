class Solution {
private:
    const int mod = 1e9 + 7;
    int fac[81], inv[81], freq[10] = {};
    int memo[11][41][361];

    inline int binpow(int a, int b) {
        int res = 1;
        while (b > 0) {
            if (b & 1) res = (1LL * res * a) % mod;
            a = (1LL * a * a) % mod;
            b >>= 1;
        }
        return res;
    }

    void precompute(int n) {
        fac[0] = inv[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = (1LL * fac[i - 1] * i) % mod;
            inv[i] = binpow(fac[i], mod - 2);
        }
    }

public:
    int countBalancedPermutations(std::string& num) {
        int len = num.size();
        int sum = 0;

        std::fill(&memo[0][0][0], &memo[0][0][0] + sizeof(memo) / sizeof(memo[0][0][0]), -1);

        for(const char& ch: num) {
            sum += ch - '0';
            ++freq[ch - '0'];
        }
        if(sum & 1) return 0;

        precompute(len);

        int evelen = (len / 2) + (len & 0);
        int oddlen = (len / 2) + (len & 1);

        int ways = 1;
            ways = (1LL * ways * fac[evelen]) % mod;
            ways = (1LL * ways * fac[oddlen]) % mod;

        int targetLen = len / 2;
        int targetSum = sum / 2;

        auto solve = [&](auto&& solve, int k, int l, int s) {
            if(k == 10) return (l == targetLen && s == targetSum)? 1: 0;

            if(memo[k][l][s] != -1) return memo[k][l][s];

            int val = 0;
            for(int f = 0; f <= freq[k]; f++) {
                int newlen = (l + f);
                int newsum = s + (f * k);

                if(newlen > targetLen || newsum > targetSum) continue;
                int tmp = 1;
                    tmp = (1LL * tmp * inv[f]) % mod;
                    tmp = (1LL * tmp * inv[freq[k] - f]) % mod;
                
                val = (0LL + val + (1LL * solve(solve, k + 1, newlen, newsum) * tmp) % mod) % mod;
            }

            return memo[k][l][s] = val;
        };

        ways = (1LL * ways * solve(solve, 0, 0, 0)) % mod;

        return ways;
    }
};

/* bottom-up */
class Solution {
private:
    const int mod = 1e9 + 7;
    int fac[81], inv[81], freq[10] = {};
    int tabu[11][41][361] = {};

    inline int binpow(int a, int b) {
        int res = 1;
        while(b > 0) {
            if(b & 1) res = (1LL * res * a) % mod;
            a = (1LL * a * a) % mod;
            b >>= 1;
        }
        return res;
    }

    void precompute(int n) {
        fac[0] = inv[0] = 1;
        for(int i = 1; i <= n; i++) {
            fac[i] = (1LL * fac[i - 1] * i) % mod;
            inv[i] = binpow(fac[i], mod - 2);
        }
    }

public:
    int countBalancedPermutations(std::string& num) {
        int len = num.size();
        int sum = 0;
        for(const char& ch: num) {
            sum += ch - '0';
            ++freq[ch - '0'];
        }
        if(sum & 1) return 0;

        precompute(len);

        int evelen = (len / 2) + (len & 0);
        int oddlen = (len / 2) + (len & 1);

        int ways = 1;
            ways = (1LL * ways * fac[evelen]) % mod;
            ways = (1LL * ways * fac[oddlen]) % mod;

        int targetLen = len / 2;
        int targetSum = sum / 2;

        tabu[0][0][0] = 1;
        for(int k = 0; k < 10; k++) {
            for(int l = 0; l <= targetLen; l++) {
                for(int s = 0; s <= targetSum; s++) {
                    if(tabu[k][l][s] == 0) continue;

                    for(int f = 0; f <= freq[k]; f++) {
                        int newlen = (l + f);
                        int newsum = s + (f * k);
                        
                        if(newlen > targetLen || newsum > targetSum) continue;
                        int tmp = (1LL * tabu[k][l][s]) % mod;
                            tmp = (1LL * tmp * inv[f]) % mod;
                            tmp = (1LL * tmp * inv[freq[k] - f]) % mod;

                        tabu[k + 1][newlen][newsum] = (0LL + tabu[k + 1][newlen][newsum] + tmp) % mod;
                    }
                }
            }
        }
				
        ways = (1LL * ways * tabu[10][targetLen][targetSum]) % mod;
        return ways;
    }
};
