/******************************************************************************
 * Given a set of candidate numbers (C) (without duplicates) and a target number
 * (T), find all unique combinations in C where the candidate numbers sums to T.
 *
 * The same repeated number may be chosen from C unlimited number of times.
 *
 * Note:
 * All numbers (including target) will be positive integers.
 * The solution set must not contain duplicate combinations.
 * For example, given candidate set [2, 3, 6, 7] and target 7, 
 * A solution set is: 
 * [
 *  [7],
 *  [2, 2, 3]
 * ] 
 ******************************************************************************/

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> r;
        vector<int> path;
        dfs(candidates, 0, target, path, r);
        return r;
    }
    
private:
    void dfs(vector<int>& candidates, int idx, int target, vector<int>& path, vector<vector<int>>& r) {
        if (idx == candidates.size()) {
            return;
        }
        int candidate = candidates[idx];
        if (candidate > target) {
            // you cannot find a valid result
            return;
        }
        ++idx;
        if (idx == candidates.size()) {
            // this is leaf node
            if (0 == target % candidate) {
                int old_size = path.size();
                path.resize(old_size + target / candidate, candidate);
                r.push_back(path);
                path.resize(old_size);
            }
            return;
        }
        int max_num = target / candidate;
        path.resize(path.size() + max_num, candidate);
        target -= max_num * candidate;
        if (0 == target) {
            r.push_back(path);
        }
        for (int i = 0; i < max_num; ++i) {
            path.pop_back();
            target += candidate;
            dfs(candidates, idx, target, path, r);
        }
    }
};
