/******************************************************************************
 * Given a binary tree and a sum, determine if the tree has a root-to-leaf path
 * such that adding up all the values along the path equals the given sum.
 *
 * For example:
 * Given the below binary tree and sum = 22,
 *             5
 *            / \
 *           4   8
 *          /   / \
 *         11  13  4
 *        /  \      \
 *       7    2      1
 * return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22. 
******************************************************************************/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (nullptr == root) {
            return false;
        }
        if (nullptr == root->left && nullptr == root->right) {
            return sum == root->val;
        }
        int path_sum = 0;
        path_sum = root->val;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            auto cur = st.top();
            while (nullptr != cur->left) {
                st.push(cur->left);
                cur = cur->left;
                path_sum += cur->val;
            }
            if (nullptr == cur->right && path_sum == sum && st.size() > 1) {
                return true;
            }
            while (nullptr == cur->right) {
                path_sum -= cur->val;
                st.pop();
                if (st.empty()) {
                    break;
                }
                cur = st.top();
            }
            if (nullptr != cur->right) {
                st.push(cur->right);
                // cout << "add " << st.top()->val << endl;
                path_sum += st.top()->val;
                cur->right = nullptr;
            }
        }
        return false;
    }
};
