class Solution {
private:
    const int mod = 1e9 + 7;
    int fac[100001], inv[100001], cnt[26];

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
    int countAnagrams(std::string s) {
        std::stringstream ss; std::string word;

        int n = 0; 
        ss.str(s); 
        while(ss >> word) n = std::max(n, (int) word.size()); ss.clear();

        precompute(n);
        
        ss.str(s);
        int ans = 1;
        while(ss >> word) {
            std::fill(cnt, cnt + 26, 0);
            
            n = (int) word.size();
            for(char& ch: word) ++cnt[ch - 'a'];

            int res = 1;
            res = (1LL * res * fac[n]) % mod;
            for(int i: cnt) res = (1LL * res * inv[i]) % mod;

            ans = (1LL * ans * res) % mod;
        }
        return ans;
    }
};
