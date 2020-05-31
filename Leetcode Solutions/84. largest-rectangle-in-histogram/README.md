## 题目描述

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

## 单调栈解法

详见：https://leetcode-cn.com/problems/largest-rectangle-in-histogram/solution/84-by-ikaruga/

## 代码
```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> stack;
        int ans = 0;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        for (int i = 0; i < heights.size(); i++) {
            while (!stack.empty() && heights[stack.back()] > heights[i]) {
                int cur = stack.back();
                stack.pop_back();
                int left = stack.back() + 1;
                int right = i;
                ans = max(ans, (right - left) * heights[cur]);
            }
            stack.push_back(i);
        }
        return ans;
    }
};
```