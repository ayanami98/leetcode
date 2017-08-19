/******************************************************************************
 * Implement next permutation, which rearranges numbers into the lexicographically
 * next greater permutation of numbers.
 * If such arrangement is not possible, it must rearrange it as the lowest possible
 * order (ie, sorted in ascending order).
 *
 * The replacement must be in-place, do not allocate extra memory.
 * Here are some examples. Inputs are in the left-hand column and its corresponding
 * outputs are in the right-hand column.
 * 1,2,3 → 1,3,2
 * 3,2,1 → 1,2,3
 * 1,1,5 → 1,5,1 
 ******************************************************************************/

class Solution {
public:
/*    
    void nextPermutation(vector<int>& nums) {
        if (!next_permutation(nums.begin(), nums.end())) {
            sort(nums.begin(), nums.end());
        }
    }
*/
    void nextPermutation(vector<int>& nums) {
        int size = nums.size();
        if (size < 2) {
            return;
        }
        // find the descending tail first
        int i = size - 2;
        for (; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                break;
            }
        }
        if (-1 == i) {
            // no next permutation
            sort(nums.begin(), nums.end());
            return;
        }
        reverse(nums.begin() + i + 1, nums.end());
        for (int j = i + 1; j < size; ++j) {
            if (nums[j] > nums[i]) {
                swap(nums[j], nums[i]);
                break;
            }
        }
    }
};

