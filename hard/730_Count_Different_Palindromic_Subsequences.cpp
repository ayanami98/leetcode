/******************************************************************************
 * Given a string S, find the number of different non-empty palindromic
 * subsequences in S, and return that number modulo 10^9 + 7.
 *
 * A subsequence of a string S is obtained by deleting 0 or more characters from S.
 *
 * A sequence is palindromic if it is equal to the sequence reversed.
 *
 * Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some
 * i for which A_i != B_i.
 *
 * Example 1:
 * Input: 
 * S = 'bccb'
 * Output: 6
 * Explanation: 
 * The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc',
 * 'bcb', 'bccb'.
 * Note that 'bcb' is counted only once, even though it occurs twice.
 * Example 2:
 * Input: 
 * S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
 * Output: 104860361
 * Explanation: 
 * There are 3104860382 different non-empty palindromic subsequences, which is
 * 104860361 modulo 10^9 + 7.
 * Note:
 *
 * The length of S will be in the range [1, 1000].
 * Each character S[i] will be in the set {'a', 'b', 'c', 'd'}. 
******************************************************************************/
// refer to https://csacademy.com/contest/round-57/task/distinct-palindromes/solution/ 

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    const static size_t mod = 1000000007;
public:
    int countPalindromicSubsequences(string S) {
        int length = S.length();
        vector<vector<vector<int>>> dp(length, vector<vector<int>>(length, vector<int>(4, 0)));
        for (int i = 0; i < length; ++i) {
            dp[i][i][S[i] - 'a'] = 1;
        }
        
        for (int l = 1; l < length; ++l) {
            for (int s = 0; s < length - l; ++s) {
                int e = s + l;
                for (int i = 0; i < 4; ++i) {
                    char ch = 'a' + i;
                    if (ch == S[e] && ch == S[s]) {
                        dp[s][e][i] = (2 + dp[s + 1][e - 1][0] + dp[s + 1][e - 1][1] +
                                    dp[s + 1][e - 1][2] + dp[s + 1][e - 1][3]) % mod;
                    } else {
                        dp[s][e][i] = (dp[s + 1][e][i] + dp[s][e - 1][i] - dp[s + 1][e - 1][i]) % mod;
                    }   
                }
            }
        }
        int r = 0;
        for (int i = 0; i < 4; ++i) {
            r += dp[0][length - 1][i];
        }
        return r % mod;
    }
};

int main() {
  cout << Solution().countPalindromicSubsequences("bccb") << endl;
  return 0;
}
