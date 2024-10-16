struct elem { int val; int cnt; };
struct cmp_for {
    bool operator()(const elem& a, const elem& b) const {
        if(a.cnt == b.cnt) return a.val < b.val;
        return a.cnt < b.cnt;
    }
};
struct cmp_rev {
    bool operator()(const elem& a, const elem& b) const {
        if(a.cnt == b.cnt) return a.val > b.val;
        return a.cnt > b.cnt;
    }
};

class Solution {
private:
    int n;
    std::set<elem, cmp_for> top;
    std::set<elem, cmp_rev> rem;
    std::map<int, int> freq;

    long long product(int x, int y) { return 1LL * x * y; }

public:
    std::vector<long long> findXSum(std::vector<int>& nums, int k, int x) {
        n = nums.size();
        std::vector<long long> answer;
        
        for(int i = 0; i < k; i++) ++freq[nums[i]];

        int L = 0, R = k;
        long long sm = 0;
        for(const auto& [val, cnt]: freq) {
            elem e;
            e.val = val; e.cnt = cnt;

            top.insert(e);
            sm += product(e.val, e.cnt);
        }
        
        while(top.size() > x) {
            elem e = *top.begin();
            sm -= product(e.val, e.cnt);
            top.erase(e); rem.insert(e);        
        }
        answer.push_back(sm);
        
        elem e;

        std::function<void(char)> updateSet = [&](char ch) -> void {
            if(top.count(e)) {
                top.erase(e);
                sm -= product(e.val, e.cnt);

                if(ch == 'R') e.cnt = ++freq[e.val];
                if(ch == 'L') e.cnt = --freq[e.val];
                top.insert(e);
                sm += product(e.val, e.cnt);
            }
            else {
                if(rem.count(e)) rem.erase(e);
                if(ch == 'R') e.cnt = ++freq[e.val];
                if(ch == 'L') e.cnt = --freq[e.val];
                rem.insert(e);
            }
        };

        while(R < n) {
            e.val = nums[R]; e.cnt = freq[nums[R]]; updateSet('R');
            e.val = nums[L]; e.cnt = freq[nums[L]]; updateSet('L');
            
            elem eTop = *top.begin(); 
            elem eRem = *rem.begin();

            if(top.size() < x) {
                top.insert(eRem); rem.erase(eRem);
                sm += product(eRem.val, eRem.cnt);
            }
            else {
                bool check = 
                (eTop.cnt < eRem.cnt) || ((eTop.cnt == eRem.cnt) && (eTop.val < eRem.val));

                if(check) {
                    sm -= product(eTop.val, eTop.cnt);
                    sm += product(eRem.val, eRem.cnt);
                    top.erase(eTop); top.insert(eRem);
                    rem.erase(eRem); rem.insert(eTop);
                }
            }
            answer.push_back(sm);
            ++L; ++R;
        }     
        return answer;
    }
};
