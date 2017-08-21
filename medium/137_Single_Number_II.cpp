/******************************************************************************
 * Given an array of integers, every element appears three times except for one,
 * which appears exactly once. Find that single one.
 *
 * Note:
 * Your algorithm should have a linear runtime complexity. Could you implement
 * it without using extra memory? 
******************************************************************************/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0;
        int twos = 0;
        int threes = 0;
        for (auto num : nums) {
            // one bit can only exist in single one of those 3 variables
            threes = twos & num;
            twos &= ~threes; // remove all the promoted bits
            twos |= (ones & num);
            ones |= num;
            ones &= (~twos & ~threes);
            // cout << threes <<", " << twos << ", " << ones << endl;
        } 
        return ones;
    }
};
