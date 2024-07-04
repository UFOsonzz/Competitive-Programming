
class Solution {
static const int N = 1e5 + 5;
public:
    int n, l[N], r[N];
    stack<int> st;
    int largestRectangleArea(vector<int>& heights) {
        n = heights.size();
        for (int i = 0; i < n; i++) {
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                st.pop();
            }
            if (st.empty()) l[i] = -1;
            else l[i] = st.top();
            st.push(i);
        }
        while (!st.empty()) st.pop();
        for (int i = n-1; i >= 0; i--) {
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                st.pop();
            }
            if (st.empty()) r[i] = n;
            else r[i] = st.top();
            st.push(i);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, heights[i] * (r[i] - l[i] - 1));
        }
        return ans;
    }
};
