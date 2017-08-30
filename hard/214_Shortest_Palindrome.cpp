/******************************************************************************
 * Copyright (c)  2017, GraphSQL Inc.                                      *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 214_Shortest_Palindrome.cpp
*
* Created on : 2017-08-30
* Author : tufeng
*
* Last Modified : Wed 30 Aug 2017 05:08:58 AM PST
******************************************************************************/

/******************************************************************************
 * Given a string S, you are allowed to convert it to a palindrome by adding
 * characters in front of it. Find and return the shortest palindrome you can
 * find by performing this transformation.
 *
 * For example:
 * Given "aacecaaa", return "aaacecaaa".
 * Given "abcd", return "dcbabcd". 
 ******************************************************************************/

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        reverse(s.begin(), s.end());
        int start = 0;
        int end = s.length() - 1;
        while (!check(s, start, end)) {
            auto match_spot = s.find_first_of(s[start], end + 1);
            if (match_spot == string::npos) {
                // cannot find the match spot
                start = start + 1;
                end = s.length() - 1;
            } else {
                // find the new match spot
                start = start + match_spot + 1 - s.length();
                end = s.length() - 1;
            }
        }
        for (int i = start - 1; i >= 0; --i) {
            s.append(1, s[i]);            
        }
        return s;
    }
    
private:
    bool check(const string& s, int& start, int& end) {
        int length = end - start + 1;
        int left = -1;
        int right = -1;
        if ((length & 0x1) == 1) {
            left = (start + end) / 2 - 1;
            right = left + 2;
        } else {
            left = (start + end) / 2;
            right = left + 1;
        }
        while (left >= start) {
            if (s[left] != s[right]) {
                // record the mismatching spot
                start = left;
                end = right;
                return false;
            }
            --left;
            ++right;
        }
        return true;
    }
};

int main() {
  string data = "aacecaaa";
  cout << Solution().shortestPalindrome(data) << endl;
  return 0;
}
