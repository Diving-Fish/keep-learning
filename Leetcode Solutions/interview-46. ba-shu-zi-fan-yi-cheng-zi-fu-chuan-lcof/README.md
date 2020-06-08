## 题目描述

给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

```
示例 1:

输入: 12258
输出: 5
解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"
```

## 解法

假设一个数字有`k`位(digits, not bits)，
那么逐位翻译到第`i`位时，有如下两种情况：
第一，第`i`位和第`i+1`位可以一起翻译，也就是`atoi(num[i:i+1]) <= 25 && num[i] != '0'`
除此之外就是不能一起翻译的情况。
因此状态转移方程为：
可以一起翻译的情况
`dp[i] = dp[i - 1] + dp[i - 2]`
否则
`dp[i] = dp[i - 1]`


## 代码
```cpp
class Solution {
public:
    int translateNum(int num) {
        int translateType[16];
        char c[16];
        char buff[16];
        sprintf(c, "%d", num);
        int index;
        translateType[0] = 1;
        translateType[1] = 1;
        for (index = 2; index <= strlen(c); index++) {
            memset(buff, 0, 16);
            memcpy(buff, c + index - 2, 2);
            if (buff[0] != '0' & atoi(buff) <= 25) {
                translateType[index] = translateType[index - 1] + translateType[index - 2];
            } else {
                translateType[index] = translateType[index - 1];
            }
        }
        return translateType[index - 1];
    }
};
```