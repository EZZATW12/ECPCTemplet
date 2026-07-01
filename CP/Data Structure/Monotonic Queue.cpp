#include <bits/stdc++.h>
using namespace std;

// Sliding Window Maximum / Minimum
// find the Maximum / Minimum element in a window of fixed size.

struct MonotonicQueue {
    stack<int> st2;
    stack<pair<int, int> > st1;

    void push(int x) {
        int mx = st1.empty() ? x : max(x, st1.top().second);
        st1.push(make_pair(x, mx));
    }

    void pop() {
        if (st2.empty()) {
            while (!st1.empty()) {
                int nxt = st1.top().first;
                st2.push((st2.empty() ? nxt : max(st2.top(), nxt)));
                st1.pop();
            }
        }
        st2.pop();
    }

    int get() {
        if (st1.empty() || st2.empty()) {
            return (st1.empty() ? st2.top() : st1.top().second);
        }
        return max(st1.top().second, st2.top());
    }

    bool empty() {
        return (st1.empty() && st2.empty());
    }

    int size() {
        return (st1.size() + st2.size());
    }
};