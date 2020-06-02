## 题目描述

爱丽丝参与一个大致基于纸牌游戏 “21点” 规则的游戏，描述如下：

爱丽丝以 `0` 分开始，并在她的得分少于 `K` 分时抽取数字。 抽取时，她从 `[1, W]` 的范围中随机获得一个整数作为分数进行累计，其中 `W` 是整数。 每次抽取都是独立的，其结果具有相同的概率。

当爱丽丝获得不少于 `K` 分时，她就停止抽取数字。 爱丽丝的分数不超过 `N` 的概率是多少？

## 解法

如果有概率论的基础，其实并不难看出如下规则：

设 ![](http://latex.codecogs.com/gif.latex?P(i)) 为抽出点数为 ![](http://latex.codecogs.com/gif.latex?i) 的概率，则

当 ![](http://latex.codecogs.com/gif.latex?i%20\\leq%20W) 时，

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?P(i)=\\frac{P(0)+P(1)+...+P(i-1)}{W})

（即点数为 ![](http://latex.codecogs.com/gif.latex?0) 到 ![](http://latex.codecogs.com/gif.latex?i-1) 的任何状态，都有 ![](http://latex.codecogs.com/gif.latex?\\frac{1}{W}) 的可能到达点数为 ![](http://latex.codecogs.com/gif.latex?i) 的状态）

当 ![](http://latex.codecogs.com/gif.latex?W<i<K) 时，

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?P(i)=\\frac{P(i-W)+P(i-W+1)+...+P(i-1)}{W})

（同上，不难理解）

当 ![](http://latex.codecogs.com/gif.latex?K%20\\leq%20i<K+W) 时，

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?P(i)=\\frac{P(i-W)+P(i-W+1)+...+P(K-1)}{W})

（因为爱丽丝在点数为 ![](http://latex.codecogs.com/gif.latex?K) 以后会停止抽牌，所以只有点数为 ![](http://latex.codecogs.com/gif.latex?i-W) 到 ![](http://latex.codecogs.com/gif.latex?K-1) 之间的状态才有可能到达点数为 ![](http://latex.codecogs.com/gif.latex?i) 的状态）

当 ![](http://latex.codecogs.com/gif.latex?i>=K+W) 时，

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?P(i)=0)

得出上述的结论以后，就不难理解这是用动态规划解决的一个问题。

## 代码

```cpp
class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0) return 1;
        double *arr = new double[K + W];
        arr[0] = 1.0;
        for (int i = 1; i < K; i++) {
            for (int j = max(0, i - W); j < i; j++) {
                arr[i] += arr[j];
            }
            arr[i] /= W;
        }
        for (int i = K; i < N; i++) {
            for (int j = max(0, i - W); j < K; j++) {
                arr[i] += arr[j];
            }
            arr[i] /= W;
        }
        double ans = 0;
        for (int i = K; i <= min(N, K + W - 1); i++) {
            ans += arr[i];
        }
        delete []arr;
        return ans;
    }
};
```

### 优化

然而，这还远远不是结束……

因为这是一道提交通过率只有18.6%的，中等难度的题。

上述的代码提交以后，首先报了一个WA：

输入：
```
354
348
20
```
输出：
```
0.56665
```
预期：
```
0.56667
```

如果有基础的浮点运算知识，就知道浮点运算会在除法时丢失精度。问题不大，把`arr[0]`的初始值换成`W`的话，就不会出问题了。

第二次提交，TLE：

> 118 / 146 个通过测试用例

问题出在哪呢？在第二次循环中，我计算了 ![](http://latex.codecogs.com/gif.latex?i>=K+W) 的这些值；然而，这些值并不会对结果造成影响，因为都是0。因此，把第二次循环的终止条件约束到 `min(N, K + W - 1)`，并且把第二个和第三个循环写在一起（因为第二个循环中的赋值实际上可以直接在第三个循环中使用），并且把除法放到最外面。改动后的代码大概像这样：

```cpp
double ans = 0;
for (int i = K; i <= min(N, K + W - 1); i++) {
    for (int j = max(0, i - W); j < K; j++) {
        ans += arr[j];
    }
}
ans /= W;
```

当我信心满满地提交第三次以后，还是TLE：

> 123 / 146 个通过测试用例

这时候我突然明白，后面的测试用例都是大数据，仅仅是卡边界没有办法从根本上解决问题。因此，我开始思考前面公式化简的可能性，然后发现

当 ![](http://latex.codecogs.com/gif.latex?i%20\\leq%20W) 时，

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?P(i)=\\frac{P(0)+P(1)+...+P(i-1)}{W})

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?=\\frac{P(0)+P(1)+...+P(i-2)}{W}+\\frac{P(i-1)}{W})

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?=P(i-1)+\\frac{P(i-1)}{W})

单次计算时间复杂度从 O(W) 下降到了 O(1)。同理：

当 ![](http://latex.codecogs.com/gif.latex?W<i%20\\leq%20K) 时，

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?P(i)=\\frac{P(i-W)+P(i-W+1)+...+P(i-1)}{W})

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?=P(i-1)+\\frac{P(i-1)-P(i-W-1)}{W} )


当 ![](http://latex.codecogs.com/gif.latex?K<i<K+W) 时，

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?P(i)=\\frac{P(i-W)+P(i-W+1)+...+P(K-1)}{W})

&nbsp;&nbsp;&nbsp;&nbsp;![](http://latex.codecogs.com/gif.latex?=P(i-1)-\\frac{P(i-W-1)}{W})

这样的话，整个算法的时间复杂度就从 ![](http://latex.codecogs.com/gif.latex?O(W*(K+W))) 降低到了![](http://latex.codecogs.com/gif.latex?O(K+W))，时间大概是从3 ~ 4s降到了4ms。

## 最终代码

```cpp
class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0) return 1;
        if (K + W < N) return 1;
        if (K > N) return 0;
        int i, j, upper;
        double *arr = new double[K + W];
        arr[0] = W;
        arr[1] = 1;
        for (i = 2; i <= K; i++) {
            if (i - W >= 1) {
                arr[i] = arr[i - 1] + (arr[i - 1] - arr[i - W - 1]) / W;
            } else {
                arr[i] = arr[i - 1] + arr[i - 1] / W;
            }
        }
        upper = min(N, K + W - 1);
        double ans = arr[K];
        for (i = K + 1; i <= upper; i++) {
            if (i - W - 1 >= 0) {
                arr[i] = arr[i - 1] - arr[i - W - 1] / W;
            } else {
                arr[i] = arr[i - 1];
            }
            ans += arr[i];
        }
        delete[] arr;
        return ans / W;
    }
};
```