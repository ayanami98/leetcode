/******************************************************************************
 * Copyright (c)  2017, GraphSQL Inc.                                      *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 95_Unique_Binary_Search_Trees_II.cpp
*
* Created on : 2017-08-30
* Author : tufeng
*
* Last Modified : Wed 30 Aug 2017 05:37:35 PM PST
******************************************************************************/

/******************************************************************************
 * Given an integer n, generate all structurally unique BST's (binary search trees)
 * that store values 1...n.
 *
 * For example,
 * Given n = 3, your program should return all 5 unique BST's shown below.
 *  1         3     3      2      1
 *   \       /     /      / \      \
 *    3     2     1      1   3      2
 *   /     /       \                 \
 *  2     1         2                 3 
******************************************************************************/

#include <vector>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // you should have a deep copy for every subtree
    vector<TreeNode*> generateTrees(int n) {
        if (n < 1) {
            return vector<TreeNode*>();
        }
        vector<vector<vector<TreeNode*> > > dp(n + 1, vector<vector<TreeNode*> >(n + 1));
        for (int i = 1; i <= n; ++i) {
            dp[i][i].push_back(new TreeNode(i));
        }
        for (int len = 2; len <= n; ++len) {
            for (int i = 1; i <= n - len + 1; ++i) {
                // scan all the possible root
                // select the 1st element as root
                auto& rights = dp[i + 1][i + len - 1];
                for (auto right : rights) {
                    auto root = new TreeNode(i);
                    root->right = right;
                    dp[i][i + len - 1].push_back(root);
                }
                
                // select the last element as root
                auto& lefts = dp[i][i + len - 2];
                for (auto left : lefts) {
                    auto root = new TreeNode(i + len - 2);
                    root->left = left;
                    dp[i][i + len - 1].push_back(root);
                }
                
                for (int r = i + 1; r < i + len - 1; ++r) {
                    auto& lefts = dp[i][r - 1];
                    auto& rights = dp[r + 1][i + len - 1];
                    for (auto left : lefts) {
                        for (auto right : rights) {
                            auto root = new TreeNode(r);
                            root->left = left;
                            root->right = right;
                            dp[i][i + len - 1].push_back(root);
                        }
                    }
                }
            }
        }
        return dp[1][n];
    }
};

int main() {
  auto res = Solution().generateTrees(3);
  cout << res.size() << endl;
  return 0;
}
