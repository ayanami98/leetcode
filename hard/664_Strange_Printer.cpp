/******************************************************************************
 * There is a strange printer with the following two special requirements:
 * 
 * The printer can only print a sequence of the same character each time.
 * At each turn, the printer can print new characters starting from and ending
 * at any places, and will cover the original existing characters.
 * Given a string consists of lower English letters only, your job is to count
 * the minimum number of turns the printer needed in order to print it.
 * 
 * Example 1:
 * Input: "aaabbb"
 * Output: 2
 * Explanation: Print "aaa" first and then print "bbb".
 * Example 2:
 * Input: "aba"
 * Output: 2
 * Explanation: Print "aaa" first and then print "b" from the second place of the
 * string, which will cover the existing character 'a'.
 * Hint: Length of the given string will not exceed 100.  
 ******************************************************************************/

// memorization DFS
class Solution
{
private:
    int dfs(const std::string& s, int l, int r, vector<vector<int>>& dp) {
        if (l > r) return 0;
        if (dp[l][r] > 0) return dp[l][r];
        dp[l][r] = dfs(s, l, r - 1, dp) + 1; // default value
        for (int i = l; i < r; ++i) {
            if (s[i] == s[r]) {
                dp[l][r] = std::min(dp[l][r], dfs(s, l, i, dp) + dfs(s, i + 1, r - 1, dp));
            }
        }
        return dp[l][r];
    }
    
public:
    int strangePrinter(std::string s) {
        int size = s.size();
        // dp[i][j] means the min actions between range [i, j]
        vector<vector<int>> dp(size, vector<int>(size, 0));
        return dfs(s, 0, size - 1, dp);
    }
};
