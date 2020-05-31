## 题目描述
给你一个数组 `candies` 和一个整数 `extraCandies` ，其中 `candies[i]` 代表第 `i` 个孩子拥有的糖果数目。

对每一个孩子，检查是否存在一种方案，将额外的 `extraCandies` 个糖果分配给孩子们之后，此孩子有 **最多** 的糖果。注意，允许有多个孩子同时拥有 最多 的糖果数目。

## 解法

非常简单，找出数组最大值再计算每个元素 + `extraCandies`是否大于等于最大值。怀疑是LeetCode六一儿童节特地选的题。

## 代码
```cpp
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        vector<bool> ans;
        int maxCandy = 0;
        for (int candy: candies) {
            maxCandy = max(maxCandy, candy);
        }
        for (int candy: candies) {
            ans.push_back(candy + extraCandies >= maxCandy);
        }
        return ans;
    }
};
```