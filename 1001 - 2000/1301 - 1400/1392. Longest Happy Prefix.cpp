class Solution {
public:
    string longestPrefix(std::string& s) {
        const int mod = 1e9 + 7;
      
        long long pHash = 0, sHash = 0, po = 1;        
        int len = 0;

        int sz = s.length();
        for(int i = 0, j = sz - 1; i < sz - 1 && j > 0; ++i, --j) {
            pHash = (pHash * 31 + (s[i] - 'a' + 1)) % mod;
            sHash = ((s[j] - 'a' + 1) * po + sHash) % mod;
            po = po * 31 % mod;

            len = (pHash == sHash)? i + 1: len;
        }

        return s.substr(0, len);
    }
};
