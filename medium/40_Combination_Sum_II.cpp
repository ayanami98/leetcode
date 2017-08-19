/******************************************************************************
 * Given a collection of candidate numbers (C) and a target number (T), find all
 * unique combinations in C where the candidate numbers sums to T.
 *
 * Each number in C may only be used once in the combination.
 *
 * Note:
 * All numbers (including target) will be positive integers.
 * The solution set must not contain duplicate combinations.
 * For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
 * A solution set is: 
 * [
 *  [1, 7],
 *  [1, 2, 5],
 *  [2, 6],
 *  [1, 1, 6]
 * ] 
******************************************************************************/

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> r;
        vector<int> path;
        if (!candidates.empty()) {
            dfs(candidates, 0, target, -1, path, r);
        }
        return r;
    }
    
private:
    void dfs(vector<int>& candidates, int idx, int target, int last_choice, vector<int>& path, vector<vector<int>>& r) {
        int candidate = candidates[idx];
        if (candidate > target) {
            return;
        }
        // skip all the selected choice
        while (candidate == last_choice) {
            if (++idx == candidates.size()) {
                break;
            }
            candidate = candidates[idx];
        }
        if (candidate == last_choice) { // reach the end;
            return;
        }
        if (candidate == target) {
            path.push_back(candidate);
            r.push_back(path);
            path.pop_back();
            return;
        }
        ++idx;
        // find the next distinct number
        if (idx == candidates.size()) {
            return;
        }
        // case 1: not use this element
        dfs(candidates, idx, target, candidate, path, r);
        // case 2: use this element
        target -= candidate;
        path.push_back(candidate);
        dfs(candidates, idx, target, -1, path, r);
        target += candidate;
        path.pop_back();
    }
};
