/******************************************************************************
 * Given an integer array with no duplicates. A maximum tree building on this
 * array is defined as follow:
 * 
 * The root is the maximum number in the array.
 * The left subtree is the maximum tree constructed from left part subarray
 * divided by the maximum number.
 * The right subtree is the maximum tree constructed from right part subarray
 * divided by the maximum number. 
 * Construct the maximum tree by the given array and output the root node of
 * this tree.
 * 
 * Example 1:
 * Input: [3,2,1,6,0,5]
 * Output: return the tree root node representing the following tree:
 *
 *     6
 *   /   \
 *  3     5
 *   \    / 
 *    2  0   
 *      \
 *       1
 * Note:
 * The size of the given array will be in the range [1,1000].
******************************************************************************/

#include <vector>
#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        stack<TreeNode*> st;
        st.push(new TreeNode(nums[0]));
        TreeNode* prev = new TreeNode(nums[0]);
        for (int i = 1; i < nums.size(); ++i) {
            TreeNode* cur = new TreeNode(nums[i]);
            TreeNode* prev = nullptr;
            if (cur->val < st.top()->val) {
                st.top()->right = cur;
                st.push(cur);
            } else {
                TreeNode* prev = nullptr;
                while (!st.empty() && st.top()->val < cur->val) {
                    prev = st.top();
                    st.pop();
                } 
                if (st.empty()) {
                    // new root
                    cur->left = prev;
                } else {
                    st.top()->right = cur;
                    cur->left = prev;
                }
                st.push(cur);
            }
        }
        while (st.size() > 1) {
            st.pop();
        }
        return st.top();
    }
};

int main() {
  vector<int> data({7, 20, 10, 11, 13, 12});
  Solution().constructMaximumBinaryTree(data);
  return 0;
}
