template<class T>
class SlidingQueue{
    stack<T> s1[2], s2[2];

    T merge(T a, T b){
        return __gcd(a, b);
    }
    void add(T val, stack<T> s[]){
        s[0].push(val);
        s[1].push((s[1].empty() ? val : merge(s[1].top(), val)));
    }
    void rem(stack<T> s[]){
        s[0].pop(), s[1].pop();
    }
public:
    void push(T val){ add(val, s1); }
    void pop(){
        if(s2[0].empty()) while(s1[0].size()) add(s1[0].top(), s2), rem(s1);
        rem(s2);
    }
    T query(){
        return (s1[1].size() && s2[1].size() ? merge(s1[1].top(), s2[1].top()) :
                (s1[1].size()? s1[1].top() : s2[1].top()));
    }
};

template<class T>
class SlidingQueueMin{
    stack<T> s1[2], s2[2];

    T merge(T a, T b){
        return min(a, b);
    }
    void add(T val, stack<T> s[]){
        s[0].push(val);
        s[1].push((s[1].empty() ? val : merge(s[1].top(), val)));
    }
    void rem(stack<T> s[]){
        s[0].pop(), s[1].pop();
    }
public:
    void push(T val){ add(val, s1); }
    void pop(){
        if(s2[0].empty()) while(s1[0].size()) add(s1[0].top(), s2), rem(s1);
        rem(s2);
    }
    T query(){
        return (s1[1].size() && s2[1].size() ? merge(s1[1].top(), s2[1].top()) :
                (s1[1].size()? s1[1].top() : s2[1].top()));
    }
};
 