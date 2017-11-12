/******************************************************************************
 * Given strings S and T, find the minimum (contiguous) substring W of S, so
 * that T is a subsequence of W.
 *
 * If there is no such window in S that covers all characters in T, return the
 * empty string "". If there are multiple such minimum-length windows, return the
 * one with the left-most starting index.
 * 
 * Example 1:
 * Input: 
 * S = "abcdebdde", T = "bde"
 * Output: "bcde"
 * Explanation: 
 * "bcde" is the answer because it occurs before "bdde" which has the same length.
 * "deb" is not a smaller window because the elements of T in the window must occur
 * in order.
 * Note:
 *
 * All the strings in the input will only contain lowercase letters.
 * The length of S will be in the range [1, 20000].
 * The length of T will be in the range [1, 100]. 
 ******************************************************************************/

ass Solution {
public:
    string minWindow(string S, string T) {
        int s_len = S.length();
        int t_len = T.length();
        // dp[i][j] means the size of the smallest windows which ends at S[i] and T[j]
        vector<vector<int> > dp(s_len, vector<int>(t_len, 200000));
        int i = 0;
        for (; i < s_len; ++i) {
            if (S[i] == T[0]) {
                dp[i][0] = 1;
                break;
            }
        }
        for (++i; i < s_len; ++i) {
            if (S[i] == T[0]) {
                dp[i][0] = 1;
            } else {
                dp[i][0] = dp[i - 1][0] + 1;
            }
        }
        for (int i = 1; i < s_len; ++i) {
            for (int j = 1; j < t_len; ++j) {
                if (S[i] == T[j]) {
                    //dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1);
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = dp[i - 1][j] + 1;
                }
            }
        }
        int r = 200000;
        string s;
        for (int i = 0; i < s_len; ++i) {
            if (r > dp[i][t_len - 1]) {
                r = dp[i][t_len - 1];
                int j = t_len - 1;
                int p = i;
                for (; p >= 0; --p) {
                    if (S[p] == T[j]) {
                        --j;
                    }
                    if (j < 0) {
                        break;
                    }
                }
                if (p == -1) {
                    s = S.substr(0, i + 1);
                } else {
                    s = S.substr(p, i - p + 1);
                }
            }
        }
        return s;
    }
};
