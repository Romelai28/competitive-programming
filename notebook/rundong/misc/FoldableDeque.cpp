template <class T, class Op>
class FoldableDeque {
    using TT = pair<T, T>;
    Op op;
    vector<TT> L, R;
    
    void push_left(T x) {
        L.push_back({ x, L.empty() ? x : op(x, L.back().second) });
    }
    void push_right(T x) {
        R.push_back({ x, R.empty() ? x : op(R.back().second, x) });
    }
    void refill_left() {
        vector<T> tmp;
        for (auto [x, _] : R) tmp.push_back(x);
        R.clear();
        
        int half = tmp.size() / 2 + tmp.size() % 2;
        for (int i = half - 1; i >= 0; --i)
            push_left(tmp[i]);
        for (int i = half; i < tmp.size(); ++i)
            push_right(tmp[i]);
    }
    void refill_right() {
        vector<T> tmp;
        for (auto [x, _] : L) tmp.push_back(x);
        L.clear();
        
        int half = tmp.size() / 2 + tmp.size() % 2;
        for (int i = half - 1; i >= 0; --i)
            push_right(tmp[i]);
        for (int i = half; i < tmp.size(); ++i)
            push_left(tmp[i]);
    }
    
public:
    bool empty() { return L.empty() and R.empty(); }
    void push_front(T x) { push_left(x); }
    void pop_front() { if (L.empty()) refill_left(); L.pop_back(); }
    void push_back(T x) { push_right(x); }
    void pop_back() { if (R.empty()) refill_right(); R.pop_back(); }
    T fold() {
        if (L.empty()) return R.back().second;
        if (R.empty()) return L.back().second;
        return op(L.back().second, R.back().second);
    }
};