/***********************************************************
 * Given an array S of n integers, are there elements a, b, c,
 * and d in S such that a + b + c + d = target? Find all unique
 * quadruplets in the array which gives the sum of target.
 *
 * Note: The solution set must not contain duplicate quadruplets.
 *
 * For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.
 *
 * A solution set is:
 * [
 *   [-1,  0, 0, 1],
 *   [-2, -1, 1, 2],
 *   [-2,  0, 0, 2]
 * ]
 *************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int> > r;
        int size = nums.size();
        if (size < 4) {
            return r;
        }
        sort(nums.begin(), nums.end());
        int i = 0;
        while (i < size - 3) {
            int num1 = nums[i];
            int j = i + 1;
            while (j < size - 2) {
                int num2 = nums[j];
                int sum = target - num1 - num2;
                int count = hasPair(nums, sum, j + 1, r);
                while (count > 0) {
                  auto& vec = r[r.size() - count];
                  vec.push_back(nums[i]);
                  vec.push_back(nums[j]);
                  --count;
                }
                // skip the same numbers
                while (++j < size - 2 && nums[j] == num2) {} 
            }
            // skip the same numbers
            while (++i < size - 3 && nums[i] == num1) {}
        }
        return r;
    }
    
    int hasPair(const vector<int>& nums, int target, int start, vector<vector<int> >& pairs) {
        int end = nums.size() - 1;
        int count = 0;
        while (start < end) {
            int sum = nums[start] + nums[end];
            if (target == sum) {
                ++count;
                pairs.push_back(vector<int>({nums[start], nums[end]}));
                while (++start < end && nums[start] == nums[start - 1]) {}
                while (start < --end && nums[end] == nums[end + 1]) {}
            } else if (target > sum) {
                ++start;
            } else {
                --end;
            }
        }
        return count;
    }
};

int main() {
  vector<int> test_data({-3,-2,-1,0,0,1,2,3});
  auto r = Solution().fourSum(test_data, 0);
  for (auto& list : r) {
    for (auto num : list) {
      cout << num << " ";  
    }
    cout << endl;
  }

}
