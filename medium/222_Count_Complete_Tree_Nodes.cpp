/******************************************************************************
 * Given a complete binary tree, count the number of nodes.
 *
 * Definition of a complete binary tree from Wikipedia:
 * In a complete binary tree every level, except possibly the last, is completely
 * filled, and all nodes in the last level are as far left as possible. It can have
 * between 1 and 2h nodes inclusive at the last level h.
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
    int countNodes(TreeNode* root) {
        if (nullptr == root) {
            return 0;
        }
        int h = 1;
        TreeNode* cur = root;
        while (nullptr != cur->left) {
            ++h;
            cur = cur->left;
        }
        return countNodes2(root, h);
    }
    
private:
    int countNodes2(TreeNode* root, int high) {
        if (nullptr == root->left) {
            return 1;
        }
        if (nullptr == root->right) {
            return 2;
        }
        int h = 2;
        TreeNode* cur = root->left;
        while (nullptr != cur->right) {
            cur = cur->right;
            ++h;
        }
        if (h == high) {
            // boundry in the right substree
            return 1 + // itself
                (1 << (high - 1)) - 1 + // left side
                countNodes2(root->right, high - 1); // right side
        } else {
            // boundry in the left substree
            return 1 + // itself
                countNodes2(root->left, high - 1) + // left side
                (1 << (high - 2)) - 1; // right side
        }
    }
};
