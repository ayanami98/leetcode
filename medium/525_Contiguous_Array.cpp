/******************************************************************************
 * Given a binary array, find the maximum length of a contiguous subarray with
 * equal number of 0 and 1.
 * 
 * Example 1:
 * Input: [0,1]
 * Output: 2
 * Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
 * Example 2:
 * Input: [0,1,0]
 * Output: 2
 * Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal
 * number of 0 and 1.
 * Note: The length of the given binary array will not exceed 50,000. 
 ******************************************************************************/

class Solution {
public:
// Since in this problem the range of possible sums is [-size...size],
// we can use an array instead of unordered_map. We can consider size as
// the zero point, so the array indexes will be [0... 2 * size].
int findMaxLength(vector<int>& nums) {
    int size = nums.size(), ballance = size, max_len = 0;
    int ballances[size * 2 + 1] = {};
    for (auto i = 0; i < size; ++i) {
        ballance += nums[i] == 0 ? -1 : 1;
        if (ballance == size) max_len = i + 1;
        else {
            if (ballances[ballance] != 0) max_len = max(max_len, i - ballances[ballance] + 1);
            else ballances[ballance] = i + 1;
        }
    }
    return max_len;
}
};
