/******************************************************************************
 * Copyright (c)  2018, TigerGraph Inc.                                    *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 10_Regular_Expression_Matching.cpp
*
* Created on : 2018-01-21
* Author : tufeng
*
* Last Modified : Sun 21 Jan 2018 11:11:01 AM PST
******************************************************************************/

/******************************************************************************
******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int s_len = s.length();
        int p_len = p.length();
        if (p_len < 2) {
            return s == p;
        }
        if (s_len == 0) {
            return p == ".*";
        }
        vector<bool> has_star;
        string p2;
        for (int j = 0; j < p_len; ++j) {
            if (p[j] == '*') {
                has_star.back() = true;
            } else {
                p2 += p[j];
                has_star.push_back(false);
            }
        }
        //for (int i = 0; i < p2.length(); ++i) {
        //    cout << p2[i] << ": " << (has_star[i] ? "yes" : "no") << endl;
        //}
        p_len = p2.length();
        vector<vector<bool> > dp(s_len, vector<bool>(p_len, false));
        // dp[?][0]
        dp[0][0] = s[0] == p2[0] || p2[0] == '.';
        if (dp[0][0] && has_star[0]) {
            for (int i = 1; i < s_len; ++i) {
                if (s[i] == s[i - 1] || p2[0] == '.') {
                    dp[i][0] = true;
                } else {
                    break;
                }
            }
        }
        // dp[0][?]
        int no_star_count = has_star[0] ? 0 : 1;
        for (int j = 1; j < p_len; ++j) {
            if (has_star[j]) {
                if (no_star_count == 0) {
                    if (p2[j] == s[0] || p2[j] == '.' || dp[0][j - 1]) {
                        dp[0][j] = true;
                    }
                } else {
                    dp[0][j] = true;
                }
            } else {
                if (no_star_count > 0) {
                    break;
                }
                if (p2[j] != s[0] && p2[j] != '.') {
                    break;
                }
                dp[0][j] = true;
                ++no_star_count;
            }
        }
        for (int i = 1; i < s_len; ++i) {
            for (int j = 1; j < p_len; ++j) {
                if (s[i] == p2[j] || p2[j] == '.') {
                    if (has_star[j]) {
                        if (dp[i - 1][j] || dp[i][j - 1]) {
                            dp[i][j] = true;
                        }
                    } else {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                } else if (has_star[j]) {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        return dp.back().back();
    }
};

int main() {
  cout << (Solution().isMatch("aab", "c*a*b") ? "yes" : "no") << endl;
  return 0;
}
