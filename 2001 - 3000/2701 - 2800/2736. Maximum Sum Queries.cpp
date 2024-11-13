class Solution {
private:
    int n;

    std::vector<std::array<int, 2>> tempx, tempy; // temporary
    std::vector<int> sortx[2], sorty[2];          // sorted pair : w.r.t x / y
    std::vector<int> suffx, suffy;                // max-suffix  : w.r.t sorty / sortx
    std::vector<std::vector<int>> xtable, ytable; // sparse table: w.r.t sortx / sorty

public:
    std::vector<int> maximumSumQueries(std::vector<int>& nums1, std::vector<int>& nums2, 
                                       std::vector<std::vector<int>>& queries) {
        
        n = nums1.size() & nums2.size();

        tempx.resize(n); tempy.resize(n);
        for(int i = 0; i < n; i++) tempx[i] = tempy[i] = {nums1[i], nums2[i]};
        std::sort(tempx.begin(), tempx.end(), [](std::array<int, 2> p, std::array<int, 2> q){
            if(p[0] == q[0]) return p[1] < q[1];
            return p[0] < q[0];
        });
        std::sort(tempy.begin(), tempy.end(), [](std::array<int, 2> p, std::array<int, 2> q) {
            if(p[1] == q[1]) return p[0] < q[0];
            return p[1] < q[1];
        });

        sortx[0].resize(n); sortx[1].resize(n);
        sorty[0].resize(n); sorty[1].resize(n);
        for(int i = 0; i < n; i++) {
            sortx[0][i] = tempx[i][0]; sortx[1][i] = tempx[i][1];
            sorty[0][i] = tempy[i][0]; sorty[1][i] = tempy[i][1];
        }

        suffx.resize(n); suffy.resize(n);

        suffx[n - 1] = sorty[0][n - 1];
        for(int i = n - 2; i >= 0; i--) 
            suffx[i] = std::max(sorty[0][i], suffx[i + 1]);
        
        suffy[n - 1] = sortx[1][n - 1];
        for(int i = n - 2; i >= 0; i--) 
            suffy[i] = std::max(sortx[1][i], suffy[i + 1]);

        int log = std::bit_width(1U * n);
        
        xtable.resize(log, std::vector<int>(n));
        ytable.resize(log, std::vector<int>(n));

        for(int j = 0; j < n; j++) xtable[0][j] = sortx[0][j] + sortx[1][j];
        for(int i = 1; i < log; i++) {
            for(int j = 0; j + (1 << i) - 1 < n; j++) {
                xtable[i][j] = std::max(xtable[i - 1][j], xtable[i - 1][j + (1 << (i - 1))]);
            }
        }

        for(int j = 0; j < n; j++) ytable[0][j] = sorty[0][j] + sorty[1][j];
        for(int i = 1; i < log; i++) {
            for(int j = 0; j + (1 << i) - 1 < n; j++) {
                ytable[i][j] = std::max(ytable[i - 1][j], ytable[i - 1][j + (1 << (i - 1))]);
            }
        }
        
        std::vector<int> answer;
        for(std::vector<int>& q: queries) {
            int x = q[0], y = q[1];

            int idx;
            int minIdx, maxIdx;

            int ansx = -1;
            while(true) {
                idx = std::lower_bound(sortx[0].begin(), sortx[0].end(), x) - sortx[0].begin();
                if(idx == n) break;
                minIdx = idx;

                idx = std::lower_bound(sorty[1].begin(), sorty[1].end(), y) - sorty[1].begin();
                if(idx == n) break;
                idx = std::upper_bound(sortx[0].begin(), sortx[0].end(), suffx[idx]) - sortx[0].begin() - 1;
                if(idx < 0)  break;
                maxIdx = idx;

                if(minIdx > maxIdx) break;

                int len = maxIdx - minIdx + 1;
                int k = std::bit_width(1U * len) - 1;

                ansx = std::max(xtable[k][minIdx], xtable[k][maxIdx - (1 << k) + 1]);
                break;
            }

            int ansy = -1;
            while(true) {
                idx = std::lower_bound(sorty[1].begin(), sorty[1].end(), y) - sorty[1].begin();
                if(idx == n) break;
                minIdx = idx;

                idx = std::lower_bound(sortx[0].begin(), sortx[0].end(), x) - sortx[0].begin();
                if(idx == n) break;
                idx = std::upper_bound(sorty[1].begin(), sorty[1].end(), suffy[idx]) - sorty[1].begin() - 1;
                if(idx < 0)  break;
                maxIdx = idx;

                if(minIdx > maxIdx) break;

                int len = maxIdx - minIdx + 1;
                int k = std::bit_width(1U * len) - 1;

                ansy = std::max(ytable[k][minIdx], ytable[k][maxIdx - (1 << k) + 1]);
                break;
            }

            answer.push_back(ansx & ansy);
        }

        return answer;
    }
};
