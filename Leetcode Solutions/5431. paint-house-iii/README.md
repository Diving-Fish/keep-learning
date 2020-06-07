## 题目描述

在一个小城市里，有 m 个房子排成一排，你需要给每个房子涂上 n 种颜色之一（颜色编号为 1 到 n ）。有的房子去年夏天已经涂过颜色了，所以这些房子不需要被重新涂色。

我们将连续相同颜色尽可能多的房子称为一个街区。（比方说 houses = [1,2,2,3,3,2,1,1] ，它包含 5 个街区  [{1}, {2,2}, {3,3}, {2}, {1,1}] 。）

给你一个数组 houses ，一个 m * n 的矩阵 cost 和一个整数 target ，其中：

houses[i]：是第 i 个房子的颜色，0 表示这个房子还没有被涂色。
cost[i][j]：是将第 i 个房子涂成颜色 j+1 的花费。
请你返回房子涂色方案的最小总花费，使得每个房子都被涂色后，恰好组成 target 个街区。如果没有可用的涂色方案，请返回 -1 。
 
```
示例 1：

输入：houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
输出：9
解释：房子涂色方案为 [1,2,2,1,1]
此方案包含 target = 3 个街区，分别是 [{1}, {2,2}, {1,1}]。
涂色的总花费为 (1 + 1 + 1 + 1 + 5) = 9。
示例 2：

输入：houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
输出：11
解释：有的房子已经被涂色了，在此基础上涂色方案为 [2,2,1,2,2]
此方案包含 target = 3 个街区，分别是 [{2,2}, {1}, {2,2}]。
给第一个和最后一个房子涂色的花费为 (10 + 1) = 11。
示例 3：

输入：houses = [0,0,0,0,0], cost = [[1,10],[10,1],[1,10],[10,1],[1,10]], m = 5, n = 2, target = 5
输出：5
示例 4：

输入：houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4, n = 3, target = 3
输出：-1
解释：房子已经被涂色并组成了 4 个街区，分别是 [{3},{1},{2},{3}] ，无法形成 target = 3 个街区。
 

提示：

m == houses.length == cost.length
n == cost[i].length
1 <= m <= 100
1 <= n <= 20
1 <= target <= m
0 <= houses[i] <= n
1 <= cost[i][j] <= 10^4
```

## 解法

用`dp[i][j][k]`表示染色到第i个房子、颜色为j、已经分成k的街区的花费。
如果房子已经染过色，则状态转移方程为：
```cpp
for l in 1..n:
ans[i][houses[i]][k + (houses[i] != l)] = min(ans[i][houses[i]][k + (houses[i] != l)], ans[i - 1][l][k]);
```

如果没有染过色，则状态转移方程为：
```cpp
for l in 1..n:
ans[i][j][k + (j != l)] = min(ans[i][j][k + (j != l)], ans[i - 1][l][k] + cost[i][l - 1]);
```

## 代码
```cpp
class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        int ans[111][22][111];
        memset(ans, 0xf, sizeof(ans));
        if (houses[0] == 0) {
            for (int j = 1; j <= n; j++) {
                ans[0][j][1] = cost[0][j - 1];
            }
        } else {
            ans[0][houses[0]][1] = 0;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= i; k++) {
                    if (houses[i] != 0) {
                        int c = ans[i - 1][j][k];
                        ans[i][houses[i]][k + (houses[i] != j)] = min(ans[i][houses[i]][k + (houses[i] != j)], c);
                    } else {
                        for (int l = 1; l <= n; l++) {
                            int c = ans[i - 1][j][k];
                            ans[i][l][k + (l != j)] = min(ans[i][l][k + (l != j)], c + cost[i][l - 1]);
                        }
                    }
                }
            }
        }
        int minv = 0xf0f0f0f;
        for (int j = 1; j <= n; j++) {
            minv = min(minv, ans[m - 1][j][target]);
        }
        if (minv >= 0xf0f0f0f) minv = -1;
        return minv;
    }
};
```