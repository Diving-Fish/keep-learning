## 题目描述

编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。
```
示例:

现有矩阵 matrix 如下：

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]

给定 target = 5，返回 true。
给定 target = 20，返回 false。
```

## 解法

从左下角开始搜索，如果cur > target，往上走，否则往右走。

## 代码

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return false;
        int row = matrix.size() - 1;
        int col = 0;
        int cur = matrix[row][col];
        while (cur != target) {
            if (cur > target) {
                row--;
            } else {
                col++;
            }
            if (row < 0 || col >= matrix[0].size()) return false;
            cur = matrix[row][col];
        }
        return true;
    }
};
```