//
// Created by Ezzat on 6/2/2025.
//
template<class T>
struct Mono_stack {
    stack <pair<T, T>> st;
    void push(const T &val) {
        if (st.empty())
            st.emplace(val, val);
        else st.emplace(val, std::max(val, st.top().second));
    }
    void pop() {
        st.pop();
    }

    bool empty() {
        return st.empty();
    }

    int size() {
        return st.size();
    }

    T top() {
        return st.top().first;
    }

    T max() {
        return st.top().second;
    }
};

template<class T>
struct Mono_queue {
    Mono_stack<T> pop_st, push_st;

    void push(const T &val) {
        push_st.push(val);
    }

    void move() {
        if (pop_st.size())return;
        while (!push_st.empty())
            pop_st.push(push_st.top()), push_st.pop();
    }

    void pop() {
        move();
        pop_st.pop();
    }

    bool empty() {
        return pop_st.empty() && push_st.empty();
    }

    int size() {
        return pop_st.size() + push_st.size();
    }

    T top() {
        move();
        return pop_st.top();
    }

    T max() {
        if (pop_st.empty())return push_st.max();
        if (push_st.empty())return pop_st.max();
        return std::max(push_st.max(), pop_st.max());
    }
};