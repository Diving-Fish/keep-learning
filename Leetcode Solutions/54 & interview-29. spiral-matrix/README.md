## 题目描述

给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。

```
示例 1:

输入:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
输出: [1,2,3,6,9,8,7,4,5]
示例 2:

输入:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
输出: [1,2,3,4,8,12,11,10,9,5,6,7]
```

## 解法

很自然的想到逐圈遍历即可。

## 代码

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        int posx = -1;
        int posy = 0;
        int y = matrix.size();
        if (y == 0) return result;
        int x = matrix[0].size();
        while (true) {
            for (int i = 0; i < x; i++) {
                posx++;
                result.push_back(matrix[posy][posx]);
            }
            y--;
            if (y == 0) break;
            for (int i = 0; i < y; i++) {
                posy++;
                result.push_back(matrix[posy][posx]);
            }
            x--;
            if (x == 0) break;
            for (int i = 0; i < x; i++) {
                posx--;
                result.push_back(matrix[posy][posx]);
            }
            y--;
            if (y == 0) break;
            for (int i = 0; i < y; i++) {
                posy--;
                result.push_back(matrix[posy][posx]);
            }
            x--;
            if (x == 0) break;
        }
        return result;
    }
};
```