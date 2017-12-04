/******************************************************************************
 * In a N x N grid representing a field of cherries, each cell is one of three
 * possible integers.
 * 
 * 0 means the cell is empty, so you can pass through;
 * 1 means the cell contains a cherry, that you can pick up and pass through;
 * -1 means the cell contains a thorn that blocks your way.
 * Your task is to collect maximum number of cherries possible by following the
 * rules below:
 *
 * Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or
 * down through valid path cells (cells with value 0 or 1);
 * After reaching (N-1, N-1), returning to (0, 0) by moving left or up through
 * valid path cells;
 * When passing through a path cell containing a cherry, you pick it up and the
 * cell becomes an empty cell (0);
 * If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can
 * be collected.
 * Example 1:
 * Input: grid =
 * [[0, 1, -1],
 *  [1, 0, -1],
 *  [1, 1,  1]]
 * Output: 5
 * Explanation: 
 * The player started at (0, 0) and went down, down, right right to reach (2, 2).
 * 4 cherries were picked up during this single trip, and the matrix becomes
 * [[0,1,-1],[0,0,-1],[0,0,0]].
 * Then, the player went left, up, up, left to return home, picking up one more
 * cherry.
 * The total number of cherries picked up is 5, and this is the maximum possible.
 * Note:
 * grid is an N by N 2D array, with 1 <= N <= 50.
 * Each grid[i][j] is an integer in the set {-1, 0, 1}.
 * It is guaranteed that grid[0][0] and grid[N-1][N-1] are not -1.
******************************************************************************/

class Solution {
 public:
  int cherryPickup(vector<vector<int>> &grid) {
    const int n = grid.size();
    vector<vector<vector<int>>> dp(n * 2 + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, -1)));
    dp[2][1][1] = (grid[0][0] == 0) ? 0 : 1;
    for (int k = 3; k <= n * 2; ++k) {
      for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
          if (grid[i - 1][k - i - 1] == -1 || grid[j - 1][k - j - 1] == -1) {
            continue;
          }
          dp[k][i][j] = max(max(dp[k - 1][i - 1][j - 1], dp[k - 1][i - 1][j]),
                            max(dp[k - 1][i][j - 1], dp[k - 1][i][j]));
          if (dp[k][i][j] == -1) {
            continue;
          }
          if (i == j) {
            dp[k][i][j] += grid[i - 1][k - i - 1];
          } else {
            dp[k][i][j] += grid[i - 1][k - i - 1] + grid[j - 1][k - j - 1];
          }
        }
      }
    }
    return max(0, dp[n * 2][n][n]);
  }
};
