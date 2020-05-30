#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> stack;
        int ans = 0;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        for (int i = 0; i < heights.size(); i++) {
            while (!stack.empty() && heights[stack.back()] > heights[i]) {
                int cur = stack.back();
                stack.pop_back();
                int left = stack.back() + 1;
                int right = i;
                ans = max(ans, (right - left) * heights[cur]);
            }
            stack.push_back(i);
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> v = {2, 1, 5, 6, 2, 3};
    cout << s.largestRectangleArea(v);
}