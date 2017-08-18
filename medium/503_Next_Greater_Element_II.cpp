/********************************************************************
 * Given a circular array (the next element of the last element is the
 * first element of the array), print the Next Greater Number for every
 * element. The Next Greater Number of a number x is the first greater
 * number to its traversing-order next in the array, which means you could
 * search circularly to find its next greater number. If it doesn't exist,
 * output -1 for this number.
 *
 * Example 1:
 * Input: [1,2,1]
 * Output: [2,-1,2]
 * Explanation: The first 1's next greater number is 2; 
 * The number 2 can't find next greater number; 
 * The second 1's next greater number needs to search circularly,
 * which is also 2.
 * Note: The length of given array won't exceed 10000. 
 *********************************************************************/ 

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int size = nums.size();
        vector<int> r(size, -1);
        if (size < 2) {
            return r;
        }
        // pair<value, position>
        stack<pair<int, int> > st;
        st.emplace(nums[0], 0);
        // round one
        for (int i = 1; i < size; ++i) {
            int cur_num = nums[i];
            while (!st.empty() && st.top().first < cur_num) {
                r[st.top().second] = cur_num;
                st.pop();
            }
            st.emplace(cur_num, i);
        }
        // round two
        for (int i = 0; i < size; ++i) {
            int cur_num = nums[i];
            while (!st.empty() && st.top().first < cur_num) {
                r[st.top().second] = cur_num;
                st.pop();
            }            
        }
        return r;
    }
};
