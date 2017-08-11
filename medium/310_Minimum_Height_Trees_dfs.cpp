/******************************************************************************
 * Copyright (c)  2017, GraphSQL Inc.                                      *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 310_Minimum_Height_Trees_dfs.cpp
*
* Created on : 2017-08-10
* Author : tufeng
*
* Last Modified : Thu 10 Aug 2017 06:38:42 PM PST
******************************************************************************/

/*************************************************************************
 * For a undirected graph with tree characteristics, we can choose any node
 * as the root. The result graph is then a rooted tree. Among all possible
 * rooted trees, those with minimum height are called minimum height trees
 * (MHTs). Given such a graph, write a function to find all the MHTs and
 * return a list of their root labels.
 *
 * Format
 * The graph contains n nodes which are labeled from 0 to n - 1. You will be
 * given the number n and a list of undirected edges (each edge is a pair of
 * labels).
 *
 * You can assume that no duplicate edges will appear in edges. Since all edges
 * are undirected, [0, 1] is the same as [1, 0] and thus will not appear together
 * in edges.
 *
 * Example 1:
 * Given n = 4, edges = {{1, 0], [1, 2], [1, 3}}
 *
 *       0
 *       |
 *       1
 *      / \
 *     2   3
 * return [1]
 *
 * Example 2:
 * Given n = 6, edges = {{0, 3], [1, 3], [2, 3], [4, 3], [5, 4}}
 *
 *    0  1  2
 *     \ | /
 *       3
 *       |
 *       4
 *       |
 *       5
 * return [3, 4]
 *
 * Note:
 * (1) According to the definition of tree on Wikipedia: “a tree is an undirected
 * graph in which any two vertices are connected by exactly one path. In other words,
 * any connected graph without simple cycles is a tree.”
 * (2) The height of a rooted tree is the number of edges on the longest downward
 * path between the root and a leaf.
 ************************************************************************************/



#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        vector<vector<int>> graph(n, vector<int>());
        for (auto& edge : edges) {
            graph[edge.first].push_back(edge.second);
            graph[edge.second].push_back(edge.first);
        }
        unordered_set<int> r;
        // dfs: the root must locate at the middle node(s) of the longest path
        int end_v = longestPath(graph, 0, nullptr);
        longestPath(graph, end_v, &r);
        return vector<int>(r.begin(), r.end());
    }
    
    int longestPath(const vector<vector<int>>& graph, int start_node, unordered_set<int>* r = nullptr) {
        vector<pair<int, int> > path;
        int longest_path = 0;
        path.emplace_back(start_node, 0);
        int end_v = -1;
        while (!path.empty()) {
            auto cur_v = path.back();
            int next_v = graph[cur_v.first][cur_v.second];
            while (graph[next_v].size() > 1) {
                if (graph[next_v][0] == path.back().first) {
                  path.emplace_back(next_v, 1);
                } else {
                  path.emplace_back(next_v, 0);
                }
                next_v = graph[next_v][path.back().second];
            }
            if (path.size() >= longest_path) {
                end_v = next_v;
                // print result here
                if (nullptr != r) {
                    if (longest_path < path.size()) {
                        r->clear();
                        longest_path = path.size();
                    }
                    if (longest_path & 0x1) { // remember we don't push the end node into path
                        r->insert(path[longest_path / 2].first);
                        r->insert(path[longest_path / 2 + 1].first);
                    } else {
                        r->insert(path[longest_path / 2].first);
                    }
                }
                longest_path = path.size();
            }
            cur_v = path.back();
            if (path.size() > 1 && cur_v.second < (graph[cur_v.first].size() - 1)) {
              auto parent = path[path.size() - 2];
              if (graph[cur_v.first][cur_v.second + 1] == parent.first) {
                ++(path.back().second);
                ++(cur_v.second);
              }
            }
            while (cur_v.second == (graph[cur_v.first].size() - 1)) {
                path.pop_back();
                if (path.empty()) {
                    return end_v;
                }
                cur_v = path.back();
                if (path.size() > 1 && cur_v.second < (graph[cur_v.first].size() - 1)) {
                  auto parent = path[path.size() - 2];
                  if (graph[cur_v.first][cur_v.second + 1] == parent.first) {
                    ++(path.back().second);
                    ++(cur_v.second);
                  }
                }
            }
            ++(path.back().second);
        }
        return end_v;
    }
};

int main() {
  vector<pair<int, int> > edges({{0,1},{0,2},{0,3},{2,4},{0,5},{5,6},{6,7},{2,8},{7,9}});
  auto r = Solution().findMinHeightTrees(10, edges);
  for (auto v : r) {
    cout << v << endl;
  }
  return 0;
}


