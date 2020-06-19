## 题目描述

给你一个字符串 `s` 和一个字符规律 `p`，请你来实现一个支持 `'.'` 和 `'*'` 的正则表达式匹配。

```
'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
```
所谓匹配，是要涵盖**整个**字符串`s`的，而不是部分字符串。

说明:

`s` 可能为空，且只包含从 `a-z` 的小写字母。
`p` 可能为空，且只包含从 `a-z` 的小写字母，以及字符 `.` 和 `*`。

```
示例 1:

输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。

示例 2:

输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。

示例 3:

输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

示例 4:

输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。

示例 5:

输入:
s = "mississippi"
p = "mis*is*p*."
输出: false
```

## 解法

动态规划。

用`dp[i][j]`表示`p`中的第`j`个字符匹配到`s`中的第`i`个字符。

接下来有两种情况：

第一，`p[j - 1]`不是`*`，那很容易理解，只需要判断`p[j - 1]`和`s[i - 1]`能否匹配，并且和`dp[i - 1][j - 1]`的结果取与，即：

`dp[i][j] = dp[i - 1][j - 1] && (p[j - 1] == s[i - 1])`

第二，`p[j - 1]`是`*`：

那此时又有两种情况，一种是`p[j - 2:j - 1]`这个串匹配 0 次的情况，此时

`dp[i][j] = dp[i][j - 2]`

另一种情况是，继续与`p[j - 2]`这个字符进行匹配：

`dp[i][j] = dp[i - 1][j] && (p[j - 2] == s[i - 1])`

再将以上两方程取或即可得出结果。

## 代码

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        auto match = [&](int i, int j) {
            if (i == 0) {
                return false;
            } else if (p[j - 1] == '.') {
                return true;
            } else {
                return (s[i - 1] == p[j - 1]);
            }
        };
        vector<vector<int>> dp(s.length() + 1, vector<int>(p.length() + 1));
        dp[0][0] = true;
        for (int j = 1; j < p.length() + 1; j++) {
            for (int i = 0; i < s.length() + 1; i++) {
                if (p[j - 1] == '*') {
                    dp[i][j] = ((match(i, j - 1) && dp[i - 1][j]) || dp[i][j - 2]);
                } else {
                    dp[i][j] = match(i, j) && dp[i - 1][j - 1];
                }
            }
        }
        return dp[s.length()][p.length()];
    }
};
```