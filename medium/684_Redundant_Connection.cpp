/******************************************************************************
 * We are given a "tree" in the form of a 2D-array, with distinct values for each
 * node. In the given 2D-array, each element pair [u, v] represents that v is a
 * child of u in the tree. We can remove exactly one redundant pair in this "tree"
 * to make the result a tree.
 *
 * You need to find and output such a pair. If there are multiple answers for this
 * question, output the one appearing last in the 2D-array. There is always at least
 * one answer.
 *
 * Example 1:
 * Input: [[1,2], [1,3], [2,3]]
 * Output: [2,3]
 * Explanation: Original tree will be like this:
 *   1
 *  / \
 * 2 - 3
 * Example 2:
 * Input: [[1,2], [1,3], [3,1]]
 * Output: [3,1]
 * Explanation: Original tree will be like this:
 *   1
 *  / \\
 * 2   3
 * Note:
 * The size of the input 2D-array will be between 1 and 1000.
 * Every integer represented in the 2D-array will be between 1 and 2000.
******************************************************************************/

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        unordered_map<int, vector<int> > child_map;
        unordered_map<int, vector<int> > reverse_map;
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            auto& children = child_map[(*it)[0]];
            // check duplicate
            for (auto child : children) {
                if (child == (*it)[1]) {
                    return *it;
                }
            }
            if (has_a_loop(child_map, reverse_map, (*it)[0], (*it)[1])) {
                return *it;
            }
            children.push_back((*it)[1]);
            reverse_map[(*it)[1]].push_back((*it)[0]);
        }
        return vector<int>();
    }
    
    bool has_a_loop(unordered_map<int, vector<int>>& child_map, unordered_map<int, vector<int>>& reverse_map, int s, int e) {
        queue<int> q;
        q.push(s);
        unordered_set<int> visited;
        visited.insert(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            if (cur == e) {
                return true;
            }
            auto& children1 = child_map[cur];
            for (auto child : children1) {
                if (visited.count(child) == 0) {
                    q.push(child);
                    visited.insert(child);
                }
            } 
            auto& children2 = reverse_map[cur];
            for (auto child : children2) {
                if (visited.count(child) == 0) {
                    q.push(child);
                    visited.insert(child);
                }
            }
        }
        return false;
    }
};

