## 题目描述

给定一个未排序的整数数组，找出最长连续序列的长度。

要求算法的时间复杂度为 O(n)。
```
示例:

输入: [100, 4, 200, 1, 3, 2]
输出: 4
解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。
```

## 解法

先将所有数据插入HashSet中，然后进行迭代。
注意到如果`n-1`在HashSet中，那`n`自身不需要进行迭代，因为`n-1`产生的连续序列长度一定大于`n`。
事实上，在后续迭代过程中，每个元素最多被访问两次，时间复杂度为O(n)。

## 代码
```cpp
struct node {
    int value;
    node* next;
    node(int v) : value(v), next(nullptr) {}
};

inline int getHashValue(int value) {
    return value & 0xffff;
}

void insert(node **hashset, int value) {
    int hashValue = getHashValue(value);
    if (hashset[hashValue] == nullptr) {
        hashset[hashValue] = new node(value);
        return;
    }
    node *current;
    for (current = hashset[hashValue]; current->next != nullptr; current = current->next);
    current->next = new node(value);
}

bool find(node **hashset, int value) {
    int hashValue = getHashValue(value);
    node *n = hashset[hashValue];
    if (n == nullptr) return false;
    for (; n != nullptr; n = n->next) {
        if (n->value == value) return true;
    }
    return false;
}

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        node *hashset[1 << 16];
        memset(hashset, 0, sizeof(hashset));
        for (int num: nums) {
            insert(hashset, num);
        }
        int maxLength = 0;
        int curLength = 0;
        for (int num: nums) {
            curLength = 1;
            if (find(hashset, num - 1)) {
                continue;
            }
            for (int i = num + 1; find(hashset, i); i++) {
                curLength++;
            }
            maxLength = max(curLength, maxLength);
        }
        return maxLength;
    }
};
```