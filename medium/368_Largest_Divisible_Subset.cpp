/******************************************************************************
 * Given a set of distinct positive integers, find the largest subset such that
 * every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.
 *
 * If there are multiple solutions, return any subset is fine.
 *
 * Example 1:
 * nums: [1,2,3]
 * Result: [1,2] (of course, [1,3] will also be ok)
 *
 * Example 2:
 * nums: [1,2,4,8]
 *Result: [1,2,4,8] 
*****************************************************************************/

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int size = nums.size();
        vector<int> r;
        if (size < 1) {
            return r;
        }
        sort(nums.begin(), nums.end());
        // pair<size, choice>
        vector<int> dp_size(size, 1);
        vector<int> dp_choice(size, -1);
        int max_set = 1;
        int max_choice = -1;
        for (int i = 1; i < size; ++i) {
            int num = nums[i];
            int set_num = 0;
            int choice = -1;
            int max_factor = num / 2;
            for (int j = 0; j < i; ++j) {
                int factor = nums[j];
                if (factor > max_factor) {
                    break;
                }
                if (0 == (num % factor) && (dp_size[j] + 1) > set_num) {
                    // find a factor
                    set_num = dp_size[j] + 1;
                    choice = j;
                }
            }
            if (-1 != choice) {
                dp_size[i] = set_num;
                dp_choice[i] = choice;
                if (set_num > max_set) {
                    max_set = set_num;
                    max_choice = i;
                }
            }
        }
        if (-1 == max_choice) {
            r.push_back(nums[0]);
        } else {
            while (-1 != max_choice) {
                r.push_back(nums[max_choice]);
                max_choice = dp_choice[max_choice];
            }
        }
        return r;
    }
};
