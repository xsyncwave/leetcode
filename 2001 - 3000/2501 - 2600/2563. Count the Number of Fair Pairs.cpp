class Solution {
private:
    std::vector<int> segtree;
    
    void update(int v, int lft, int rht, int idx) {
        if(lft > idx || rht < idx) return;

        if(lft == rht) segtree[v] += 1;
        else {
            int mid = (lft + rht) / 2;
            update(v * 2, lft, mid, idx);
            update(v * 2 + 1, mid + 1, rht, idx);
            segtree[v] = segtree[v * 2] + segtree[v * 2 + 1];
        }
    }

    int find(int v, int lft, int rht, int q_lft, int q_rht) {
        if(lft > q_rht || rht < q_lft) return 0;

        if(lft >= q_lft && rht <= q_rht) return segtree[v];

        int mid = (lft + rht) / 2;
        int lft_val = find(v * 2, lft, mid, q_lft, q_rht);
        int rht_val = find(v * 2 + 1, mid + 1, rht, q_lft, q_rht);

        return lft_val + rht_val;
    }

public:
    long long countFairPairs(std::vector<int>& nums, int lower, int upper) {
        int n = nums.size(), sz;
        
        std::map<int, int> compress;
        for(int i: nums) 
            compress[lower - i] = compress[i] = compress[upper - i] = 0;
        
        sz = 1;
        for(auto &[num, cnum]: compress) cnum = sz++;
        
        segtree.resize(4 * sz);

        long long count = 0;
        for(int j: nums) {
            count += find(1, 0, sz, compress[lower - j], compress[upper - j]);
            update(1, 0, sz, compress[j]);
        }
        
        return count;
    }
};
