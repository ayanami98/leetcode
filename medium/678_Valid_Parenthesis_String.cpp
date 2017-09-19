/******************************************************************************
 * Given a string containing only three types of characters: '(', ')' and '*',
 * write a function to check whether this string is valid. We define the validity
 * of a string by these rules:
 *
 * Any left parenthesis '(' must have a corresponding right parenthesis ')'.
 * Any right parenthesis ')' must have a corresponding left parenthesis '('.
 * Left parenthesis '(' must go before the corresponding right parenthesis ')'.
 * '*' could be treated as a single right parenthesis ')' or a single left
 * parenthesis '(' or an empty string.
 * An empty string is also valid.
 *
 * Example 1:
 * Input: "()"
 * Output: True
 *
 * Example 2:
 * Input: "(*)"
 * Output: True
 *
 * Example 3:
 * Input: "(*))"
 * Output: True
 * Note:
 * The string size will be in the range [1, 100]. 
******************************************************************************/

class Solution {
public:
    bool checkValidString(string s) {
        int length = s.length();
        if (length == 0) {
            return true;
        }
        vector<unordered_set<int> > dp(length);
        if (')' == s[0]) {
            return false;
        }
        if ('*' == s[0]) {
            dp[0].insert(0);
        }
        dp[0].insert(1);
        for (int i = 1; i < length; ++i) {
            char ch = s[i];
            int left_ch = length - i - 1;
            if ('(' == ch) {
                for (auto val : dp[i - 1]) {
                    if (val < left_ch) {
                        dp[i].insert(val + 1);
                    }
                }
            } else if (')' == ch) {
                for (auto val : dp[i - 1]) {
                    if (val > 0) {
                        dp[i].insert(val - 1);
                    }
                }
            } else {
                for (auto val : dp[i - 1]) {
                    if (val > 0) {
                        dp[i].insert(val - 1);
                    }
                    if (val < left_ch) {
                        dp[i].insert(val + 1);
                    }
                    dp[i].insert(val);
                }
            }
            if (dp[i].empty()) {
                return false;
            }
        }
        for (auto val : dp.back()) {
            if (val == 0) {
                return true;
            }
        }
        return false;
    }
};
