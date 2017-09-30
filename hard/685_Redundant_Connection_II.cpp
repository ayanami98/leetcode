/******************************************************************************
 * In this problem, a rooted tree is a directed graph such that, there is exactly
 * one node (the root) for which all other nodes are descendants of this node,
 * plus every node has exactly one parent, except for the root node which has no
 * parents.
 *
 * The given input is a directed graph that started as a rooted tree with N nodes
 * (with distinct values 1, 2, ..., N), with one additional directed edge added.
 * The added edge has two different vertices chosen from 1 to N, and was not an
 * edge that already existed.
 *
 * The resulting graph is given as a 2D-array of edges. Each element of edges is
 * a pair [u, v] that represents a directed edge connecting nodes u and v, where
 * u is a parent of child v.
 * 
 * Return an edge that can be removed so that the resulting graph is a rooted
 * tree of N nodes. If there are multiple answers, return the answer that occurs
 * last in the given 2D-array.
 *
 * Example 1:
 * Input: [[1,2], [1,3], [2,3]]
 * Output: [2,3]
 * Explanation: The given directed graph will be like this:
 *   1
 *  / \
 * v   v
 * 2-->3
 *
 * Example 2:
 * Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
 * Output: [4,1]
 * Explanation: The given directed graph will be like this:
 * 5 <- 1 -> 2
 *      ^    |
 *      |    v
 *      4 <- 3
 * Note:
 * The size of the input 2D-array will be between 3 and 1000.
 * Every integer represented in the 2D-array will be between 1 and N, where N is
 * the size of the input array. 
******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        vector<int> r;
        unordered_map<int, int> parents;
        bool dup = false;
        bool has_loop = false;
        for (auto& edge : edges) {
            int p = edge[0];
            int c = edge[1];
            // cout << "[" << p << ", " << c << "]" << endl;
            auto res = parents.insert(make_pair(c, p));
            if (!res.second) {
                if (!r.empty()) {
                    // has a loop before
                    r[1] = c;
                    r[0] = parents[c];
                    break;
                } else {
                    r = edge;
                }
                dup = true;
            } else if (!has_loop && has_a_loop(parents, c)) {
                if (dup) {
                    r[0] = parents[r[1]];
                } else {
                    r = edge;
                }
                has_loop = true;
            }
        }
        return r;
    }
    
private:
    bool has_a_loop(const unordered_map<int, int>& parents, int s) {
        int cur = s;
        auto it = parents.find(cur);
        while (it != parents.end()) {
            if (it->second == s) {
                return true;
            }
            cur = it->second;
            it = parents.find(cur);
        }
        return false;
    }
};

int main() {
  vector<vector<int> > data;
  data.push_back({1, 2});
  data.push_back({2, 3});
  data.push_back({3, 4});
  data.push_back({4, 1});
  data.push_back({1, 5});
  auto res = Solution().findRedundantDirectedConnection(data);
  cout << res[0] << ", " << res[1] << endl;
  return 0; 
}
