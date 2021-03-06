## 题目描述

给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？

## 解法

对给定的n，首先遍历根节点。

根节点k左侧的子树包含1 ... k - 1，右侧的子树包含k + 1 ... n。

容易得到：
> Q(0) = 1, Q(1) = 1
> Ans(n) = Sigma (k = 1 to n) Q(k - 1) * Q(n - k)

采用动态规划思想，将已经算出的Q(n)存入数组中即可逐步求解。

## 代码

```cpp
class Solution {
public:
    int numTrees(int n) {
        vector<int> v;
        v.push_back(1);
        v.push_back(1);
        int total = 1;
        for (int i = 2; i <= n; i++) {
            total = 0;
            for (int j = 1; j <= i; j++) {
                total += v[j - 1] * v[i - j];
            }
            v.push_back(total);
        }
        return total;
    }
};
```