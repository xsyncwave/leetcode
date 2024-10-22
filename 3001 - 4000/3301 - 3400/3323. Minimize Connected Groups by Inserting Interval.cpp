bool cmp(const std::vector<int>& a, std::vector<int>& b) {
    if(a[0] == b[0]) return a[1] < b[1];
    return a[0] < b[0];
}

class Solution {
public:
    int minConnectedGroups(std::vector<std::vector<int>>& intervals, int k) {
        std::sort(intervals.begin(), intervals.end(), cmp);

        std::vector<std::vector<int>> merged;
        merged.push_back(intervals[0]);
        for(int i = 1; i < intervals.size(); i++) {
            if(intervals[i][0] <= merged.back()[1]) {
                merged.back()[1] = std::max(merged.back()[1], intervals[i][1]);
            }
            else merged.push_back(intervals[i]);
        }
        
        int n = merged.size();
        int answer = n;
        for(int i = 0; i < merged.size() - 1; i++) {
            int threshold = merged[i][1] + k;

            int lo = i, hi = n;
            int idx = i;
            while(lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if(merged[mid][0] <= threshold) {
                    idx = std::max(idx, mid);
                    lo = mid + 1;
                }
                else hi = mid;
            }
            answer = std::min(answer, n - (idx - i + 1) + 1);
        }

        return answer;
    }
};
