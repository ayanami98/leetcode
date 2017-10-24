/******************************************************************************
 * Your are given an array of positive integers nums. Count and print the number
 * of (contiguous) subarrays where the product of all the elements in the subarray
 * is less than k.
 *
 * Example 1:
 * Input: nums = [10, 5, 2, 6], k = 100
 * Output: 8
 * Explanation: The 8 subarrays that have product less than 100 are: [10], [5],
 * [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
 * Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
 *
 * Note:
 * 0 < nums.length <= 50000.
 * 0 < nums[i] < 1000.
 * 0 <= k < 10^6.  
******************************************************************************/

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0] >= k ? 0 : 1;
        for (int i = 1; i < nums.size(); ++i) {
            int product = 1;
            int count = 0;
            for (int j = i; j >= 0; --j) {
                product *= nums[j];
                if (product >= k) {
                    break;
                }
                ++count;
            }
            dp[i] = dp[i - 1] + count;
        }
        return dp.back();
    }
};
