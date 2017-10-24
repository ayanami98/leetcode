/******************************************************************************
 * Given two strings s1, s2, find the lowest ASCII sum of deleted characters to
 * make two strings equal.
 *
 * Example 1:
 * Input: s1 = "sea", s2 = "eat"
 * Output: 231
 * Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the
 * sum. Deleting "t" from "eat" adds 116 to the sum.
 * At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum
 * possible to achieve this.
 * 
 * Example 2:
 * Input: s1 = "delete", s2 = "leet"
 * Output: 403
 * Explanation: Deleting "dee" from "delete" to turn the string into "let",
 * adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to
 * the sum. At the end, both strings are equal to "let", and the answer is 100+101
 * +101+101 = 403. If instead we turned both strings into "lee" or "eet", we would
 * get answers of 433 or 417, which are higher.
 * 
 * Note:
 * 0 < s1.length, s2.length <= 1000.
 * All elements of each string will have an ASCII value in [97, 122].
******************************************************************************/

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int len1 = s1.length();
        int len2 = s2.length();
        vector<vector<int> > dp(len1, vector<int>(len2, 0));
        bool skip = false;
        int sum = s1[0];
        for (int i = 0; i < len2; ++i) {
            if (!skip && s1[0] == s2[i]) {
                sum -= s1[0];
                dp[0][i] = sum;
                skip = true;
            } else {
                sum += s2[i];
                dp[0][i] = sum;
            }
        }
        skip = false;
        sum = s2[0];
        for (int i = 0; i < len1; ++i) {
            if (!skip && s1[i] == s2[0]) {
                skip = true;
                sum -= s2[0];
                dp[i][0] = sum;
            } else {
                sum += s1[i];
                dp[i][0] = sum;
            }
        }
        for (int i = 1; i < len1; ++i) {
            for (int j = 1; j < len2; ++j) {
                dp[i][j] = min(dp[i - 1][j - 1] + (s1[i] == s2[j] ? 0 : s1[i] + s2[j]), 
                                min(dp[i - 1][j] + s1[i], dp[i][j - 1] + s2[j]));
            }
        }
        return dp[len1 - 1][len2 - 1];
    }
};
