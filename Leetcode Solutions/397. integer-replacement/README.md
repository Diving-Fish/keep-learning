## 题目描述


给定一个正整数 n，你可以做如下操作：

1. 如果 n 是偶数，则用 n / 2替换 n。
2. 如果 n 是奇数，则可以用 n + 1或n - 1替换 n。
   
n 变为 1 所需的最小替换次数是多少？

## 解法

二进制化。
对于除了3以外的任何xxxxx11形式的串，+1消耗的次数不大于-1。
对于任何xxxxx01形式的串，+1消耗的次数大于-1。
循环解决即可。

## 代码

```cpp
class Solution {
public:
    int integerReplacement(int n) {
        int digit0 = 0;
        int times = 0;
        while (n != 1) {
            if (n == 3) {
                times += 2;
                break;
            }
            times++;
            digit0 = n & 1;
            if (digit0 == 0) {
                n >>= 1;
                continue;
            }
            int digit1 = (n & 2) >> 1;
            if (digit1 == 1) {
                while (digit0 != 0) {
                    // a little trick for add and right shift
                    n >>= 1;
                    digit0 = n & 1;
                    times++;
                }
                n |= 1;
            } else {
                n >>= 1;
                times++;
            }
        }
        return times;
    }
};
```