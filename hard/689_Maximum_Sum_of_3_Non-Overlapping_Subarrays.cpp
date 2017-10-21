/******************************************************************************
 * In a given array nums of positive integers, find three non-overlapping
 * subarrays with maximum sum.
 *
 * Each subarray will be of size k, and we want to maximize the sum of all 3*k
 * entries. Return the result as a list of indices representing the starting
 * position of each interval (0-indexed). If there are multiple answers, return
 * the lexicographically smallest one.
 *
 * Example:
 * Input: [1,2,1,2,6,7,5,1], 2
 * Output: [0, 3, 5]
 * Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
 * We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
 * Note:
 * nums.length will be between 1 and 20000.
 * nums[i] will be between 1 and 65535.
 * k will be between 1 and floor(nums.length / 3). 
******************************************************************************/

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int size = nums.size();
        vector<vector<int> > dp(3, vector<int>(size, 0));
        vector<vector<int> > choice(3, vector<int>(size, -1));
        vector<int> r; 
        int max_choice = -1;
        for (int i = 0; i < 3; ++i) {
            // cout << "i = " << i << endl;
            int max_sum = 0;
            int c = 0;
            for (int n = i * k; n < (i + 1) * k; ++n) {
                c += nums[n];
            }
            max_sum = c + (i > 0 ? dp[i - 1][i * k - 1] : 0);
            dp[i][(i + 1) * k - 1] = max_sum;
            choice[i][(i + 1) * k - 1] = (i + 1) * k - 1;
            max_choice = (i + 1) * k - 1;
            // cout << "i = " << i << ", " << max_choice << ", " << max_sum << endl;
            for (int j = (i + 1) * k; j < size - (2 - i) * k; ++j) {
                c -= nums[j - k];
                c += nums[j];
                int sum = c + (i > 0 ? dp[i - 1][j - k] : 0);
                if (sum > max_sum) {
                    dp[i][j] = sum;
                    choice[i][j] = j;
                    max_sum = sum;
                    max_choice = j;
                    // cout << "i = " << i << ", " << max_choice << ", " << max_sum << endl;
                } else {
                    dp[i][j] = dp[i][j - 1];
                    choice[i][j] = choice[i][j - 1];
                }
            }
            //for (int j = (size - (2 - i) * k); j < size; ++j) {
            //    dp[i][j] = dp[i][j - 1];
            //    choice[i][j] = choice[i][j - 1];
            //}
        }
        // orgnize the output
        r.push_back(max_choice - k + 1);
        // cout << max_choice << endl;
        max_choice = choice[1][max_choice - k];
        // cout << max_choice << endl;
        r.push_back(max_choice - k + 1);
        // cout << max_choice << endl;
        max_choice = choice[0][max_choice - k];
        r.push_back(max_choice - k + 1);
        reverse(r.begin(), r.end());
        return r;
    }
};
