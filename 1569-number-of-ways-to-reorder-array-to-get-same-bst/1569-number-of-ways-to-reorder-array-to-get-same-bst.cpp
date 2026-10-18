class Solution {
public:
    int numOfWays(vector<int>& nums) {
       
    const int MOD = 1e9 + 7;
    vector<vector<long long>> nCr;

    auto buildComb = [&](int n) {
        nCr.assign(n+1, vector<long long>(n+1, 0));
        for (int i = 0; i <= n; i++) {
            nCr[i][0] = nCr[i][i] = 1;
            for (int j = 1; j < i; j++) {
                nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]) % MOD;
            }
        }
    };

    function<long long(vector<int>&)> dfs = [&](vector<int>& arr) {
        int n = arr.size();
        if (n <= 2) return 1LL;

        vector<int> left, right;
        for (int i = 1; i < n; i++) {
            if (arr[i] < arr[0]) left.push_back(arr[i]);
            else right.push_back(arr[i]);
        }

        long long leftWays = dfs(left);
        long long rightWays = dfs(right);
        long long ways = nCr[n-1][left.size()];

        return (((ways * leftWays) % MOD) * rightWays) % MOD;
    };

    buildComb(nums.size());
    return (dfs(nums) - 1 + MOD) % MOD; 


    }
};