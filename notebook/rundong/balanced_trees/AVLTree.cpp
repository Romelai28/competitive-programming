struct AVLTree
{
    inline static const int nil = 0;
    int root = nil;
    vi left, right, height, sz, key, cnt;
    
    void up(int n) {
        height[n] = 1 + max(height[left[n]], height[right[n]]);
        sz[n] = cnt[n] + sz[left[n]] + sz[right[n]];
    }
    
    int left_rotate(int n) {
        int r = right[n];
        right[n] = left[r];
        left[r] = n;
        up(n);
        up(r);
        return r;
    }
    
    int right_rotate(int n) {
        int l = left[n];
        left[n] = right[l];
        right[l] = n;
        up(n);
        up(l);
        return l;
    }
    
    int maintain(int n) {
        int lh = height[left[n]];
        int rh = height[right[n]];
        if (lh > rh + 1) {
            if (height[left[left[n]]] >= height[right[left[n]]])
                n = right_rotate(n);
            else
                left[n] = left_rotate(left[n]),
                n = right_rotate(n);
        }
        else if (rh > lh + 1) {
            if (height[right[right[n]]] >= height[left[right[n]]])
                n = left_rotate(n);
            else
                right[n] = right_rotate(right[n]),
                n = left_rotate(n);
        }
        return n;
    }
    
    int make_node(int x) {
        int n = key.size();
        left.push_back(nil);
        right.push_back(nil);
        height.push_back(1);
        sz.push_back(1);
        key.push_back(x);
        cnt.push_back(1);
        return n;
    }
    
    int insert(int n, int x) {
        if (n == nil) return make_node(x);
        
        if (key[n] == x) cnt[n]++;
        else if (x < key[n]) left[n] = insert(left[n], x);
        else if (key[n] < x) right[n] = insert(right[n], x);

        up(n);
        return maintain(n);
    }
    
    pair<int, int> get_leftmost(int n) {
        if (left[n] == nil) return { right[n], n };
        
        auto [ i, leftmost ] = get_leftmost(left[n]);
        left[n] = i;
        up(n);
        return { maintain(n), leftmost };
    }
    
    int erase(int n, int x) {
        if (n == nil) return nil;
        
        if (x < key[n]) left[n] = erase(left[n], x);
        else if (key[n] < x) right[n] = erase(right[n], x);
        else if (cnt[n] > 1) cnt[n]--;
        else
        {
            if (left[n] == nil and right[n] == nil) return 0;
            
            if (left[n] == nil) n = right[n];
            else if (right[n] == nil) n = left[n];
            else
            {
                auto [ i, leftmost ] = get_leftmost(right[n]);
                int l = left[n];
                n = leftmost;
                left[n] = l, right[n] = i;
            }
        }
        
        up(n);
        return maintain(n);
    }
    
    int count(int n, int x) {
        if (n == nil) return 0;
        if (x < key[n]) return count(left[n], x);
        else if (x > key[n]) return count(right[n], x);
        else return cnt[n];
    }
    
    void reserve() {
        if (key.size() >= key.capacity() - 3)
        {
            int n = key.capacity() * 2;
            left.reserve(n);
            right.reserve(n);
            height.reserve(n);
            sz.reserve(n);
            key.reserve(n);
            cnt.reserve(n);
        }
    }
    
    int order_of_key(int n, int x) { // starts counting at 0
        if (n == nil) return 0;
        if (x <= key[n]) return order_of_key(left[n], x);
        if (key[n] < x) return sz[left[n]] + cnt[n] +
            order_of_key(right[n], x);
    }
    
    int find_by_order(int n, int k) { // starts counting at 0
        if (k < sz[left[n]]) return find_by_order(left[n], k);
        else if (k < sz[left[n]] + cnt[n]) return key[n];
        else return find_by_order(right[n],
            k - sz[left[n]] - cnt[n]);
    }
    
    int pre_lower_bound(int n, int x, int best) {
        if (n == nil) return best;
        if (key[n] < x) return
            pre_lower_bound(right[n], x, max(best, key[n]));
        else
            return pre_lower_bound(left[n], x, best);
    }
    
    int upper_bound(int n, int x, int best) {
       if (n == nil) return best;
        if (x < key[n]) return
            upper_bound(left[n], x, min(best, key[n]));
        else
            return upper_bound(right[n], x, best);
    }
    
public:
    AVLTree() { left = right = height = sz = key = cnt = vi(1, nil); }
    
    void insert(int x) { reserve(); root = insert(root, x); }
    void erase(int x) { root = erase(root, x); }
    int count(int x) { return count(root, x); }
    int size() { return sz[root]; }
    int order_of_key(int x) { return order_of_key(root, x); }
    int find_by_order(int k) { return find_by_order(root, k); }
    int pre_lower_bound(int x) { return pre_lower_bound(root, x, -1e8); }
    int upper_bound(int x) { return upper_bound(root, x, 1e8); }
};