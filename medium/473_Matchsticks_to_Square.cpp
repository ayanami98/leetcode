/******************************************************************************
 * Remember the story of Little Match Girl? By now, you know exactly what
 * matchsticks the little match girl has, please find out a way you can make one
 * square by using up all those matchsticks. You should not break any stick, but
 * you can link them up, and each matchstick must be used exactly one time.
 *
 * Your input will be several matchsticks the girl has, represented with their
 * stick length. Your output will either be true or false, to represent whether
 * you could make one square using all the matchsticks the little match girl has.
 *
 * Example 1:
 * Input: [1,1,2,2,2]
 * Output: true
 *
 * Explanation: You can form a square with length 2, one side of the square came
 * two sticks with length 1.
 * Example 2:
 * Input: [3,3,3,3,4]
 * Output: false
 *
 * Explanation: You cannot find a way to form a square with all the matchsticks.
 * Note:
 * The length sum of the given matchsticks is in the range of 0 to 10^9.
 * The length of the given matchstick array will not exceed 15. 
 ******************************************************************************/

ass Solution {
public:
    bool makesquare(vector<int>& nums) {
        if (nums.size() < 4) {
            return false;
        }
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 4 != 0) {
            return false;
        }
        sort(nums.begin(), nums.end());
        used.resize(nums.size(), false);
        int target = sum / 4;
        if (nums.back() > target) {
            return false;
        }
        if (nums.back() > target) {
            return false;
        }
        return dfs(nums, target, 0, 4, nums.size() - 1);
    }

private:
    bool dfs(vector<int>& nums, int target, int sum, int k, int end) {
        if (sum == target) {
            if (k == 1) {
                return true;
            }
            return dfs(nums, target, 0, k - 1, nums.size() - 1);
        }
        for (int i = end; i >= 0; --i) {
            if (used[i]) {
                continue;
            }
            int tmp = sum + nums[i];
            if (tmp <= target) {
                used[i] = true;
                bool ret = dfs(nums, target, tmp, k, i - 1);
                used[i] = false;
                if (ret) {
                    return true;
                }
            }
        }
        return false;
    }
    
private:
    vector<bool> used;
};
