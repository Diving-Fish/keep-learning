## 题目描述

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

```
示例：

输入：n = 3
输出：[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"
     ]
```

## 解法

搜索所有可能性（类似dfs）。

## 代码

```cpp
struct node {
    int left;
    int right;
    string s;
    node(int init): left(init), right(0) {}
    node(node old, int o) {
        if (o == 0) {
            left = old.left - 1;
            right = old.right + 1;
            s = old.s + '(';
        } else {
            left = old.left;
            right = old.right - 1;
            s = old.s + ')';
        }
    }
};

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        node start(n);
        vector<node> stack;
        stack.push_back(start);
        while (!stack.empty()) {
            node cur = stack.back();
            stack.pop_back();
            if (cur.left + cur.right == 0) {
                ans.push_back(cur.s);
                continue;
            }
            if (cur.left > 0) {
                stack.push_back(node(cur, 0));
            }
            if (cur.right > 0) {
                stack.push_back(node(cur, 1));
            }
        }
        return ans;
    }
};
```