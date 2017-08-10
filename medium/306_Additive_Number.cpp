/******************************************************************************
 * Copyright (c)  2017, GraphSQL Inc.                                      *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 306_Additive_Number.cpp
*
* Created on : 2017-08-09
* Author : tufeng
*
* Last Modified : Wed 09 Aug 2017 06:58:28 PM PST
******************************************************************************/

/***********************************************************************
 * additive number is a string whose digits can form additive sequence.
 *
 * A valid additive sequence should contain at least three numbers. Except for the first two numbers,
 * each subsequent number in the sequence must be the sum of the preceding two.
 *
 * For example:
 * "112358" is an additive number because the digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
 *
 * 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
 * "199100199" is also an additive number, the additive sequence is: 1, 99, 100, 199.
 * 1 + 99 = 100, 99 + 100 = 199
 * Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.
 *
 * Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.
 *
 * Follow up:
 * How would you handle overflow for very large input integers?
 *********************************************************/

#include <iostream>
#include <string>

using namespace std;

// dynamic programming
class Solution {
public:
    bool isAdditiveNumber(string num) {
        int size = num.length();
        vector<bool> dp(size + 1, false);
        dp[0] = true;
        for (int i = 3; i <= size; ++i) {
            for (int j = 3; j <= i; ++j) {
                if (dp[i - j] && hasAdditiveNumber(num, i - j, i)) {
                    dp[i] = true;
                }
            }
        }
        return dp[size];
    }
    
private:
    // determine if it is possible that we have additive number in slice [s, e)
    bool hasAdditiveNumber(const string& num, int s, int e) const {
        if (num[s] == '0') {
            return false;
        }
        int size = e - s;
        for (int i = 1; i <= size / 2; ++i) { // i is the size of the first number
            int idx2 = s + i;
            if (num[idx2] == '0') {
                continue;
            }
            for (int j = 1; j <= size / 2; ++j) { // j is the second size
                int k = size - i - j;
                int max_size = max(i, j);
                if (k < max_size) {
                    break;
                }
                if (k > max_size + 1) {
                    continue;
                }
                int idx3 = s + i + j;
                if (num[idx3] == '0') {
                    continue;
                }
                // check if it is additive
                if (isAdditiveNumber(num, s, idx2, idx2, idx3, idx3, e)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool isAdditiveNumber(const string& num, int s1, int e1, int s2, int e2, int s3, int e3) const {
        int carry = 0; 
        while (e3 > s3 && e2 > s2 && e1 > s1) {
            int tgt = num[--e3] - '0';
            int sum = num[--e1] - '0' + num[--e2] - '0' + carry;
            if (tgt != (sum % 10)) {
                return false;
            }
            carry = sum / 10;
        }
        while (e3 > s3 && e2 > s2) {
            int tgt = num[--e3] - '0';
            int sum = num[--e2] - '0' + carry;
            if (tgt != (sum % 10)) {
                return false;
            }
            carry = sum / 10;
        }
        while (e3 > s3 && e1 > s1) {
            int tgt = num[--e3] - '0';
            int sum = num[--e2] - '0' + carry;
            if (tgt != (sum % 10)) {
                return false;
            }
            carry = sum / 10;
        }
        if (0 == carry) {
            return e3 == s3 && e2 == s2 && e1 == s1;
        } else {
            return (e3 - s3) == 1 && num[s3] == '1';
        }
    }
};

int main() {
  cout << (Solution().isAdditiveNumber("199100199")) << endl;
  return 0;
}
