/******************************************************************************
 * Copyright (c)  2017, TigerGraph Inc.                                    *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 719_Find_K-th_Smallest_Pair_Distance.cpp
*
* Created on : 2017-11-08
* Author : tufeng
*
* Last Modified : Wed 08 Nov 2017 11:24:47 PM PST
******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int size = nums.size() - 1;
        int min_dis = 0;
        int max_dis = nums.back() - nums.front();
        return topK(nums, min_dis, max_dis, k);
    }
    
private:
    int topK(const vector<int>& nums, int min_dis, int max_dis, int k) {
        if (min_dis == max_dis) {
            return min_dis;
        }
        int mid_dis = (min_dis + max_dis) / 2;
        int count = 0;
        int dis = 0;
        for (auto it = nums.begin(); it != nums.end(); ++it) {
            auto large_it = upper_bound(it, nums.end(), *it + mid_dis);
            int c = distance(it, large_it) - 1;
            if (c > 0) {
                count += c;
                dis = max(dis, *prev(large_it) - *it);
            }
        }
        if (count == k) {
            return dis;
        } else if (count < k) {
            return topK(nums, mid_dis + 1, max_dis, k);
        } else {
            return topK(nums, min_dis, mid_dis, k);
        }
    }
};

int main() {
  vector<int> data({1,3,1, 2, 2, 2, 4, 1, 2, 6, 7, 8, 11, 23, 2, 3, 6, 9, 10, 2, 12, 16, 18});
  cout << Solution().smallestDistancePair(data, 10) << endl;
  return 0;
}
