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

class Solution {
public:
    bool isAdditiveNumber(string num) {
        int size = num.length();
        // find the starting point
        for (int i = 1; i <= size / 2; ++i) {
            for (int j = 1; j <= size / 2; ++j) {
                if ((i + j < size) && hasAdditiveNumber(num, 0, i, i, i + j)) {
                    return true;
                }
            }
        }
        return false;
    }
    
private:
    // num1 is [s1, e1), num2 is [s2, e2)
    bool hasAdditiveNumber(const string& num, int s1, int e1, int s2, int e2) const {
        int size1 = e1 - s1;
        int size2 = e2 - s2;
        int k = max(size1, size2);
        int remain_digit_num = num.length() - e2;
        int max_k = min(remain_digit_num, k + 1); // not enough digits left in string for sum number
        while (k <= max_k) {
            if (isAdditiveNumber(num, s1, e1, s2, e2, e2, e2 + k)) {
                bool ret = hasAdditiveNumber(num, s2, e2, e2, e2 + k);
                if (ret) {
                    return true;
                }
            }
            ++k;
        }
        return max_k == 0; // reach the end
    }
    
    bool isAdditiveNumber(const string& num, int s1, int e1, int s2, int e2, int s3, int e3) const {
        if ((num[s1] == '0' && (e1 - s1) != 1) ||
            (num[s2] == '0' && (e2 - s2) != 1) ||
            (num[s3] == '0' && (e3 - s3) != 1)) {
            return false;
        }
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
            int sum = num[--e1] - '0' + carry;
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
  cout << (Solution().isAdditiveNumber("199111992") ? "yes" : "no") << endl;
  return 0;
}
