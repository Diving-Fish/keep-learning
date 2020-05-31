## 题目描述

给定一个二叉树，检查它是否是镜像对称的。

## 解法

简单地前序遍历后压栈，对比镜像节点的值是否相同即可。

## 代码

```cpp
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
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        if (root->left == NULL && root->right == NULL) return true;
        vector<TreeNode *> leftQueue = {root->left};
        vector<TreeNode *> rightQueue = {root->right};
        TreeNode *left;
        TreeNode *right;
        while (!leftQueue.empty() && !rightQueue.empty()) {
            left = leftQueue.back();
            leftQueue.pop_back();
            right = rightQueue.back();
            rightQueue.pop_back();
            if (left == NULL && right == NULL) continue;
            if ((left == NULL) ^ (right == NULL)) return false;
            if (left->val == right->val) {
                leftQueue.push_back(left->right);
                leftQueue.push_back(left->left);
                rightQueue.push_back(right->left);
                rightQueue.push_back(right->right);
            } else {
                return false;
            }
        }
        return true;
    }
};
```