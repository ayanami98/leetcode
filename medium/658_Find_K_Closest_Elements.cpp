/******************************************************************************
 * Copyright (c)  2017, GraphSQL Inc.                                      *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 658_Find_K_Closest_Elements.cpp
*
* Created on : 2017-08-16
* Author : tufeng
*
* Last Modified : Wed 16 Aug 2017 10:35:22 PM PST
******************************************************************************/

/**********************************************************************
 * Given a sorted array, two integers k and x, find the k closest elements
 * to x in the array. The result should also be sorted in ascending order.
 * If there is a tie, the smaller elements are always preferred.
 *
 * Example 1:
 * Input: [1,2,3,4,5], k=4, x=3
 * Output: [1,2,3,4]
 * Example 2:
 * Input: [1,2,3,4,5], k=4, x=-1
 * Output: [1,2,3,4]
 * Note:
 * 1) The value k is positive and will always be smaller than the length of
 *    the sorted array.
 * 2) Length of the given array is positive and will not exceed 104
 * 3) Absolute value of elements in the array and x will not exceed 104
 **********************************************************************/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> r;
        int size = arr.size();
        if (x <= arr[0]) {
            for (int i = 0; i < k; ++i) {
                r.push_back(arr[i]);
            }
            return r;
        }
        if (x >= arr.back()) {
            for (int i = 1; i <= k; ++i) {
                r.push_back(arr[size - i]);
            }
            return r;
        }
        auto it = lower_bound(arr.begin(), arr.end(), x);
        int x_idx = distance(arr.begin(), it);
        int s = max(0, x_idx - k - 1);       // the left_most spot of left end
        int e = min(size - k, x_idx);        // the right most spot of the left end
        while (s < e) {
            int mid = (s + e) / 2;
            if ((x - arr[mid]) > (arr[mid + k - 1] - x)) {
                if (arr[mid + k] - x >= x - arr[mid]) {
                  e = mid;
                } else {
                  s = mid + 1;
                }
            } else {
                e = mid;
            }
        }
        for (int i = 0; i < k; ++i) {
            r.push_back(arr[s + i]);
        }
        return r;
    }
};

int main() {
  vector<int> data({1,2,3,4,4});
  auto r = Solution().findClosestElements(data, 4, 3);
  for (auto n : r) {
    cout << n << " ";
  }
  cout << endl;
  return 0;
}
