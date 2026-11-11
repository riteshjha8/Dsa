
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {

        long long ans = 0;

        // Buy items for the common requirement
        int common = min(need1, need2);

        if (costBoth < cost1 + cost2) {
            ans += 1LL * common * costBoth;
        } else {
            ans += 1LL * common * (cost1 + cost2);
        }

        // Remaining requirements
        need1 -= common;
        need2 -= common;

        // Greedily choose the cheaper option
        ans += 1LL * need1 * min(cost1, costBoth);
        ans += 1LL * need2 * min(cost2, costBoth);

        return ans;
    }
};
