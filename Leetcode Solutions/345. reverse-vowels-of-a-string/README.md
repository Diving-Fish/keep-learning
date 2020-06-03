## 题目描述

编写一个函数，以字符串作为输入，反转该字符串中的元音字母。

## 解法

双指针，判断元音字母反转。

## 代码

```cpp
class Solution {
public:
    bool isVowel(char c) {
        return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
        || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
    }
    string reverseVowels(string s) {
        int p1 = 0, p2 = s.length() - 1;
        bool b1, b2;
        while (p1 < p2) {
            b1 = isVowel(s[p1]);
            b2 = isVowel(s[p2]);
            if (!b1) p1++;
            if (!b2) p2--;
            if (b1 && b2) {
                swap(s[p1], s[p2]);
                p1++;
                p2--;
            }
        }
        return s;
    }
};
```