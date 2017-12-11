/******************************************************************************
 * Copyright (c)  2017, TigerGraph Inc.                                    *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 3_Longest_Substring_Without_Repeating_Characters.cpp
*
* Created on : 2017-12-11
* Author : tufeng
*
* Last Modified : Mon 11 Dec 2017 11:35:38 AM PST
******************************************************************************/

/******************************************************************************
 * Given a string, find the length of the longest substring without repeating
 * characters.
 *
 * Examples:
 * Given "abcabcbb", the answer is "abc", which the length is 3.
 * Given "bbbbb", the answer is "b", with the length of 1.
 * Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer
 * must be a substring, "pwke" is a subsequence and not a substring.
******************************************************************************/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
/*
int lengthOfLongestSubstring(string s) {
        vector<int> dict(256, -1);
        int maxLen = 0, start = -1;
        for (int i = 0; i != s.length(); i++) {
            if (dict[s[i]] > start)
                start = dict[s[i]];
            dict[s[i]] = i;
            maxLen = max(maxLen, i - start);
        }
        return maxLen;
    }
*/
    int lengthOfLongestSubstring(string s) {
        vector<int> map(128, 0);
        int begin = 0; 
        int end = 0;
        int count = 0;
        int length = 0;
        while (end < s.size()) {
            if (map[s[end++]]++ > 0) {
                ++count;
            }
            while (count > 0) {
                if (map[s[begin++]]-- == 1) {
                    --count;
                }
            }
            length = max(length, end - begin);
        }
        return length;
    }
};

int main() {
  cout << Solution().lengthOfLongestSubstring("abcabcbb") << endl;
  return 0;
}

