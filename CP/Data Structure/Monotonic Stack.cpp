#include <bits/stdc++.h>
using namespace std;

vector<int> nextMax(vector<int> &a, int n) {
    stack<int> st;
    vector<int> ret(n, n);
    for (int j = 0; j < n; j++) {
        while (!st.empty() && a[st.top()] < a[j]) {
            ret[st.top()] = j;
            st.pop();
        }
        st.push(j);
    }
    return ret;
}

vector<int> prevMax(vector<int> &a, int n) {
    stack<int> st;
    vector<int> ret(n, -1);
    for (int j = n - 1; j >= 0; j--) {
        while (!st.empty() && a[st.top()] <= a[j]) {
            ret[st.top()] = j;
            st.pop();
        }
        st.push(j);
    }
    return ret;
}

vector<int> nextMin(vector<int> &a, int n) {
    stack<int> st;
    vector<int> ret(n, n);
    for (int j = 0; j < n; j++) {
        while (!st.empty() && a[st.top()] > a[j]) {
            ret[st.top()] = j;
            st.pop();
        }
        st.push(j);
    }
    return ret;
}

vector<int> prevMin(vector<int> &a, int n) {
    stack<int> st;
    vector<int> ret(n, -1);
    for (int j = n - 1; j >= 0; j--) {
        while (!st.empty() && a[st.top()] >= a[j]) {
            ret[st.top()] = j;
            st.pop();
        }
        st.push(j);
    }
    return ret;
}
