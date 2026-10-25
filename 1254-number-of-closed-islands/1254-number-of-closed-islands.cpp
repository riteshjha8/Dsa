class Solution {
public:
    void dfs(int r, int c, vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        if(r < 0 || r >= n || c < 0 || c >= m || grid[r][c] == 1)
            return;

        grid[r][c] = 1;

        dfs(r+1, c, grid);
        dfs(r-1, c, grid);
        dfs(r, c+1, grid);
        dfs(r, c-1, grid);
    }

    int closedIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // Remove boundary-connected lands
        for(int i = 0; i < n; i++) {
            if(grid[i][0] == 0) dfs(i, 0, grid);
            if(grid[i][m-1] == 0) dfs(i, m-1, grid);
        }

        for(int j = 0; j < m; j++) {
            if(grid[0][j] == 0) dfs(0, j, grid);
            if(grid[n-1][j] == 0) dfs(n-1, j, grid);
        }

        int count = 0;

        for(int i = 1; i < n-1; i++) {
            for(int j = 1; j < m-1; j++) {
                if(grid[i][j] == 0) {
                    count++;
                    dfs(i, j, grid);
                }
            }
        }

        return count;
    }
};