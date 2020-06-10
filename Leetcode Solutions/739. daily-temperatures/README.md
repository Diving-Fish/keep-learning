## 题目描述

根据每日 `气温` 列表，请重新生成一个列表，对应位置的输出是需要再等待多久温度才会升高超过该日的天数。如果之后都不会升高，请在该位置用 `0` 来代替。

例如，给定一个列表 temperatures = `[73, 74, 75, 71, 69, 72, 76, 73]`，你的输出应该是 `[1, 1, 4, 2, 1, 1, 0, 0]`。

提示：`气温` 列表长度的范围是 `[1, 30000]`。每个气温的值的均为华氏度，都是在 `[30, 100]` 范围内的整数。

## 解法

单调栈解法。构造一个单调递减的栈，栈内元素存储温度和日期。
当一个新元素入栈时，弹出栈顶元素，直到栈空或者栈能保持单调递减为止。弹出的元素表明弹出元素日期后的第一个更高的温度为即将入栈的温度，因此该位置列表的答案为`当前日期-出栈元素日期`。

## 代码

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> output(T.size());
        vector<int> tempSt;
        vector<int> indexSt;
        for (int i = 0; i < T.size(); i++) {
            int temp = T[i];
            while (tempSt.size() != 0 && tempSt.back() < temp) {
                tempSt.pop_back();
                int index = indexSt.back();
                indexSt.pop_back();
                output[index] = i - index;
            }
            tempSt.push_back(temp);
            indexSt.push_back(i);
        }
        return output;
    }
};
```