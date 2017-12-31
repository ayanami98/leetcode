/******************************************************************************
 * An integer interval [a, b] (for integers a < b) is a set of all consecutive
 * integers from a to b, including a and b.
 *
 * Find the minimum size of a set S such that for every integer interval A in
 * intervals, the intersection of S with A has size at least 2.
 *
 * Example 1:
 * Input: intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]
 * Output: 3
 * Explanation:
 * Consider the set S = {2, 3, 4}.  For each interval, there are at least 2
 * elements from S in the interval. Also, there isn't a smaller size set that
 * fulfills the above condition. Thus, we output the size of this set, which is 3.
 * 
 * Example 2:
 * Input: intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]
 * Output: 5
 * Explanation:
 * An example of a minimum sized set is {1, 2, 3, 4, 5}.
 *
 * Note:
 * intervals will have length in range [1, 3000].
 * intervals[i] will have length 2, representing some integer interval.
 * intervals[i][j] will be an integer in [0, 10^8].
******************************************************************************/

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
                 return lhs[1] < rhs[1] || (lhs[1] == rhs[1] && lhs[0] > rhs[0]); 
             });
        int result = 2;
        int last_end2 = intervals[0][1] - 1;
        int last_end1 = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i) {
            auto& interval = intervals[i];
            if (interval[0] <= last_end2) {
                // hit already
                continue;
            }
            if (interval[0] > last_end1) {
                result += 2;
                last_end2 = interval[1] - 1;
                last_end1 = interval[1];
            } else  { // interval[0] <= last_end1
                last_end2 = last_end1;
                last_end1 = interval[1];
                ++result;
            }
        }
        return result;
    }
};

