#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numTrees(int n) {
        vector<int> v;
        v.push_back(1);
        v.push_back(1);
        int total = 1;
        for (int i = 2; i <= n; i++) {
            total = 0;
            for (int j = 1; j <= i; j++) {
                total += v[j - 1] * v[i - j];
            }
            v.push_back(total);
        }
        return total;
    }
};