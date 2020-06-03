## 题目描述

给你一个整数数组 `digits`，你可以通过按任意顺序连接其中某些数字来形成 3 的倍数，请你返回所能得到的最大的 3 的倍数。

由于答案可能不在整数数据类型范围内，请以字符串形式返回答案。

如果无法得到答案，请返回一个空字符串。
```
示例 1：

输入：digits = [8,1,9]
输出："981"

示例 2：

输入：digits = [8,6,7,1,0]
输出："8760"

示例 3：

输入：digits = [1]
输出：""

示例 4：

输入：digits = [0,0,0,0,0,0]
输出："0"
```
## 解法

如果数组中有模3余0的，直接加入结果数组。
另建立两个数组`mod1`, `mod2`存储模3余1和模3余2的数。

之后，逐个从`mod1`, `mod2`中取值。
当其中某个数组A被取值完毕后，开始取另一个数组B的值，三个三个地取，直到取不出来下一组三个。
此时有两种情况，如果B中剩余两个元素，应该替换掉A中取出的最小的元素（比如1 1 替换2，这样会多一位）
如果B中只剩余一个元素或没有元素，则不进行替换。

> 但是这个方法很慢，因为需要排序，改进方法是把数组转为频数表示，这样既不需要排序，也减小了遍历的开销，大概能优化10倍速度左右。

## 代码

```cpp
class Solution {
public:
    static bool comp(int a, int b) {
        return a > b;
    }
    string largestMultipleOfThree(vector<int>& digits) {
        vector<int> result;
        vector<int> mod2;
        vector<int> mod1;
        for (int digit: digits) {
            if (digit % 3 == 2) {
                mod2.push_back(digit);
            } else if (digit % 3 == 1) {
                mod1.push_back(digit);
            } else {
                result.push_back(digit);
            }
        }
        sort(mod2.begin(), mod2.end(), comp);
        sort(mod1.begin(), mod1.end(), comp);
        int i;
        vector<int> *larger = (mod1.size() > mod2.size()) ? &mod1 : &mod2;
        for (i = 0; i < min(mod1.size(), mod2.size()); i++) {
            result.push_back(mod2[i]);
            result.push_back(mod1[i]);
        }
        for (; i <= (int) larger->size() - 3; i += 3) {
            result.push_back((*larger)[i]);
            result.push_back((*larger)[i + 1]);
            result.push_back((*larger)[i + 2]);
        }
        if (larger->size() - i == 2) {
            int smaller_mod = 3 - (*larger)[0] % 3;
            for (vector<int>::reverse_iterator it = result.rbegin(); it != result.rend(); it++) {
                if (*it % 3 == smaller_mod) {
                    result.erase((++it).base());
                    result.push_back((*larger)[i]);
                    result.push_back((*larger)[i + 1]);
                    break;
                }
            }
        }
        sort(result.begin(), result.end(), comp);
        if (result.empty()) {
            return string("");
        } else if (result[0] == 0) {
            return string("0");
        } else {
            string s = "";
            for (int i: result) {
                s += i + 0x30;
            }
            return s;
        }
    }
};
```