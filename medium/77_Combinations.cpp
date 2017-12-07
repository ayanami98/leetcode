/******************************************************************************
 * Copyright (c)  2017, TigerGraph Inc.                                    *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 77_Combinations.cpp
*
* Created on : 2017-12-06
* Author : tufeng
*
* Last Modified : Wed 06 Dec 2017 11:56:09 PM PST
******************************************************************************/

/******************************************************************************
 * Given two integers n and k, return all possible combinations of k numbers out
 * of 1 ... n.
 *
 * For example,
 * If n = 4 and k = 2, a solution is:
 * [
 *  [2,4],
 *  [3,4],
 *  [2,3],
 *  [1,2],
 *  [1,3],
 *  [1,4],
 * ] 
******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> r;
        if (k < 1) {
            return r;
        }
        for (int i = 1; i <= n - k + 1; ++i) {
            r.emplace_back(1, i);
        }
        --k;
        while (k > 0) {
            int size = r.size();
            for (int i = 0; i < size; ++i) {
                vector<int> v = r[i];
                int back = v.back();
                for (int j = back + 2; j <= n - k + 1; ++j) {
                    vector<int> o(v);
                    o.push_back(j);
                    r.push_back(move(o));
                }
                r[i].push_back(back + 1);
            }
            --k;
        }
        return r;
    }
};

int main() {
  auto r = Solution().combine(7, 3);
  for (auto& v : r) {
    cout << "[";
    for (auto n : v) {
      cout << n << ", ";
    }
    cout << "]" << endl;
  }
  return 0;
}
