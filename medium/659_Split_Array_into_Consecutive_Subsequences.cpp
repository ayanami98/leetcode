/*************************************************************************
 * You are given an integer array sorted in ascending order (may contain
 * duplicates), you need to split them into several subsequences, where
 * each subsequences consist of at least 3 consecutive integers. Return
 * whether you can make such a split.
 *
 * Example 1:
 * Input: [1,2,3,3,4,5]
 * Output: True
 * Explanation:
 * You can split them into two consecutive subsequences : 
 * 1, 2, 3
 * 3, 4, 5
 * Example 2:
 * Input: [1,2,3,3,4,4,5,5]
 * Output: True
 * Explanation:
 * You can split them into two consecutive subsequences : 
 * 1, 2, 3, 4, 5
 * 3, 4, 5
 * Example 3:
 * Input: [1,2,3,4,4,5]
 * Output: False
 * Note:
 * The length of the input is in range of [1, 10000]
 **************************************************************************/

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        int size = nums.size();
        // end_number -> set<length>
        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> num_set;
        for (auto num : nums) {
            // check if bad slice exists;  when you reach 5, you don't need care about the slice that ends with 3 anymore
            int bad_num = num - 2;
            auto bad_it = num_set.find(bad_num);
            if (num_set.end() != bad_it) {
                if (bad_it->second.top() < 3) {
                    return false;
                } else {
                    num_set.erase(bad_it);
                }
            }   
            int last_num = num - 1;
            auto it = num_set.find(last_num);
            if (num_set.end() == it) {
                num_set[num].push(1);
            } else {
                num_set[num].push(it->second.top() + 1);
                if (it->second.size() == 1) {
                    num_set.erase(it);
                } else {
                    it->second.pop();                    
                }
            }
        }
        for (auto& kv : num_set) {
            if (kv.second.top() < 3) {
                return false;
            }
        }
        return true;
    }
};
