## 题目描述

给定一副牌，每张牌上都写着一个整数。

此时，你需要选定一个数字 `X`，使我们可以将整副牌按下述规则分成 1 组或更多组：

每组都有 `X` 张牌。
组内所有的牌上都写着相同的整数。
仅当你可选的 `X >= 2` 时返回 `true`。

```
示例 1：

输入：[1,2,3,4,4,3,2,1]
输出：true
解释：可行的分组是 [1,1]，[2,2]，[3,3]，[4,4]
示例 2：

输入：[1,1,1,2,2,2,3,3]
输出：false
解释：没有满足要求的分组。
示例 3：

输入：[1]
输出：false
解释：没有满足要求的分组。
示例 4：

输入：[1,1]
输出：true
解释：可行的分组是 [1,1]
示例 5：

输入：[1,1,2,2,2,2]
输出：true
解释：可行的分组是 [1,1]，[2,2]，[2,2]
```

## 解法

求各个卡牌种类数量的最大公约数即可，如果大于2，则存在，否则不存在。

## 代码
```cpp
inline int gcd(int a, int b) {
    int r;
    while(b > 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

class Solution {
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        map<int, int> deckMap;
        for (int &num: deck) {
            if (deckMap[num]) {
                deckMap[num]++;
            } else {
                deckMap[num] = 1;
            }
        }
        int firstValue = deckMap.begin()->second;
        if (firstValue == 1) return false;
        for (auto it = deckMap.begin(); it != deckMap.end(); it++) {
            int value = it->second;
            if (value % firstValue == 0) {
                continue;
            } else if ((value = gcd(value, firstValue)) != 1) {
                firstValue = value;
                continue;
            }
            return false;
        }
        return true;
    }
};
```