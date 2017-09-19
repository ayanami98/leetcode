/******************************************************************************
 * Given an unsorted array of integers, find the number of longest increasing subsequence.
 *
 * Example 1:
 * Input: [1,3,5,4,7]
 * Output: 2
 * Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].
 *
 * Example 2:
 * Input: [2,2,2,2,2]
 * Output: 5
 * Explanation: The length of longest continuous increasing subsequence is 1, and there are
 * 5 subsequences' length is 1, so output 5.
 * Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to
 * be fit in 32-bit signed int.
******************************************************************************/

// The solution is based on DP.
// For a sequence of numbers,
// cnt[k] is total number of longest subsequence ending with nums[k];
// len[k] is the length of longest subsequence ending with nums[k];
// Then we have following equations
// 
// len[k+1] = max(len[k+1], len[i]+1) for all i <= k and nums[i] < nums[k+1];
// cnt[k+1] = sum(cnt[i]) for all i <= k and nums[i] < nums[k+1] and len[i] = len[k+1]-1;
// Starting case and default case: cnt[0] = len[0] = 1;

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size(), maxlen = 1;
        vector<int> cnt(n, 1), len(n, 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    if (len[j]+1 > len[i]) {
                        len[i] = len[j]+1;
                        cnt[i] = cnt[j];
                    }
                    else if (len[j]+1 == len[i]) 
                        cnt[i] += cnt[j];
                }
            }
            maxlen = max(maxlen, len[i]);
        }
        // find the longest increasing subsequence of the whole sequence
       // sum valid counts
        int ans = 0;
        for (int i = 0; i < n; i++) 
            if (len[i] == maxlen) ans += cnt[i];
        return ans;
    }
};

