class Solution {
public:
    long long minimumTotalDistance(std::vector<int>& robot, std::vector<std::vector<int>>& factory) {

        std::sort(robot.begin(), robot.end()); std::sort(factory.begin(), factory.end());
        std::vector<int> facto;
        for(std::vector<int>& f: factory) {
            for(int i = 0; i < f[1]; i++) facto.push_back(f[0]);
        }

        int rCount = robot.size();
        int fCount = facto.size();
        std::vector<std::vector<long long>> memo(rCount, std::vector<long long>(fCount , -1));

        auto compute = [&](auto&& compute, int rIdx, int fIdx) -> long long {
            if(rIdx == rCount) return 0;
            if(fIdx == fCount) return 2e12 + 1;
            if(memo[rIdx][fIdx] != -1) return memo[rIdx][fIdx];

            long long take = std::abs(robot[rIdx] - facto[fIdx]) + 
                             compute(compute, rIdx + 1, fIdx + 1);
            long long skip = compute(compute, rIdx, fIdx + 1);

            return memo[rIdx][fIdx] = std::min(take, skip);
        };
        return compute(compute, 0, 0);
    }
};
