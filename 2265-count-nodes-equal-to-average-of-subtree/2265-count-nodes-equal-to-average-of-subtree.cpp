class Solution {
public:
    int ans = 0;

    pair<int, int> dfs(TreeNode* root) {
        if (root == nullptr) {
            return {0, 0};
        }

        // Get information from left and right subtrees
        auto left = dfs(root->left);
        auto right = dfs(root->right);

        // Information about current subtree
        int sum = root->val + left.first + right.first;
        int count = 1 + left.second + right.second;

        // Check whether current node equals subtree average
        if (root->val == sum / count) {
            ans++;
        }

        return {sum, count};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};