class Solution {
public:
    struct polyrollhash {
        const int mod = 1e9 + 7;
        const int p = 31;
        int n;
        std::string text;
        std::vector<int> hash, ppow;

        polyrollhash(std::string t) {
            n = t.length(); text = t;
            ppow.resize(n); hash.resize(n);
        }

        void precompute() {
            ppow[0] = 1;
            for(int i = 1; i < n; i++) ppow[i] = (1LL * ppow[i - 1] * p) % mod;

            hash[0] = text[0] - 'a' + 1;
            for(int i = 1; i < n; i++) 
                hash[i] = ((1LL * hash[i - 1] * p) % mod + text[i] - 'a' + 1) % mod;
        }

        int compute(int l, int r) {
            int hashval = hash[r];
            if(l > 0) 
                hashval = (hashval - (1LL * hash[l - 1] * ppow[r - l + 1]) % mod + mod) % mod;
            return hashval; 
        }
    };

    int distinctEchoSubstrings(std::string text) {
        polyrollhash prh(text);
        prh.precompute();

        std::set<int> hashset;

        for(int sz = 1; sz <= (int) text.length() / 2; ++sz) {
            int i = 0, j = i + sz;
            while(j + sz - 1 < (int) text.length()) {
                int hash1 = prh.compute(i, i + sz - 1);
                int hash2 = prh.compute(j, j + sz - 1);

                if(hash1 == hash2) hashset.insert(hash1 & hash2);
                ++i; ++j;
            }
        }

        return (int) hashset.size();
    }
};
