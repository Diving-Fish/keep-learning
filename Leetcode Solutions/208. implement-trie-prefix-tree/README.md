## 题目描述

实现一个 Trie (前缀树)，包含 `insert`, `search`, 和 `startsWith` 这三个操作。

```
示例:

Trie trie = new Trie();

trie.insert("apple");
trie.search("apple");   // 返回 true
trie.search("app");     // 返回 false
trie.startsWith("app"); // 返回 true
trie.insert("app");   
trie.search("app");     // 返回 true
```

## 解法
普通的Trie树实现，和题解不同的是对某一深度进行了排序（增加了插入代价，减小了搜索代价）。
菜的真实 :(

## 代码

```cpp
struct node {
    node *next;
    node *child;
    char c;
    bool end;
    node(char ch) : c(ch), next(nullptr), child(nullptr), end(false) {};
};

void insert_node(node *&n, int index, string s) {
    if (index == s.length()) return;
    char c = s[index];
    for (node *cur = n;; cur = cur->next) {
        if (cur->c == c) {
            if (index == s.length() - 1) {
                cur->end = true;
                break;
            }
            if (cur->child == nullptr) {
                cur->child = new node(s[index + 1]);
            }
            insert_node(cur->child, index + 1, s);
            break;
        }
        if (cur->c > c) {
            n = new node(c);
            n->next = cur;
            cur = n;
        } else if (cur->next == nullptr || cur->next->c > c) {
            node *next = cur->next;
            cur->next = new node(c);
            cur = cur->next;
            cur->next = next;
        } else {
            continue;
        }
        index++;
        while (index < s.length()) {
            cur->child = new node(s[index]);
            index++;
            cur = cur->child;
        }
        cur->end = true;
        break;
    }
}

class Trie {
public:
    node *root;
    /** Initialize your data structure here. */
    Trie() {
        root = nullptr;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        if (root == nullptr) {
            root = new node(word[0]);
            insert_node(root, 0, word);
        } else if (root->c > word[0]) {
            node *swap = root;
            root = new node(word[0]);
            root->next = swap;
            insert_node(root, 0, word);
        } else
            insert_node(root, 0, word);
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        node *cur = root;
        int index = 0;
        while (cur != nullptr) {
            if (cur->c == word[index]) {
                if (index == word.length() - 1 && cur->end) return true;
                cur = cur->child;
                index++;
            } else {
                cur = cur->next;
            }
        }
        return false;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        node *cur = root;
        int index = 0;
        while (cur != nullptr) {
            if (cur->c == prefix[index]) {
                if (index == prefix.length() - 1) return true;
                cur = cur->child;
                index++;
            } else {
                cur = cur->next;
            }
        }
        return false;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```