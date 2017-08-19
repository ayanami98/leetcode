/******************************************************************************
 * Find all possible combinations of k numbers that add up to a number n, given
 * that only numbers from 1 to 9 can be used and each combination should be a
 * unique set of numbers.
 *
 * Example 1:
 * Input: k = 3, n = 7
 * Output:
 * [[1,2,4]]
 *
 * Example 2:
 * Input: k = 3, n = 9
 * Output:
 * [[1,2,6], [1,3,5], [2,3,4]]
******************************************************************************/

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> r;
        if (k < 10) {
            vector<int> path;
            dfs(1, n, k, path, r);
        }
        return r;
    }
    
public:
    void dfs(int num, int n, int k, vector<int>& path, vector<vector<int>>& r) {
        if (n > (9 + 10 - k) * k / 2 || n < k * (num + num + k - 1) / 2) {
            // fast failure
            return;
        } 
        n -= num;
        --k;
        path.push_back(num);
        if (k == 0 && n == 0) {
            r.push_back(path);
            path.pop_back();
            return;
        }
        // case 1: use this element
        dfs(num + 1, n, k, path, r);
        // case 2: not use this element
        n += num;
        ++k;
        if (num != 9) {
            path.pop_back();
            dfs(num + 1, n, k, path, r);
        }
    }
};
