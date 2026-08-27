const int N = 1e7;
int lch[N], rch[N];
int key[N], cnt[N];
int sz[N];
int prio[N];
int c1 = 1;
const int nil = 0;
struct Treap
{
	int head = nil;
	mt19937 rng{114};
	uniform_int_distribution<> dist{1, (int)1e9};
	int make_node(int k) {
		int n = c1++;
		key[n] = k; cnt[n] = 1; sz[n] = 1;
		prio[n] = dist(rng);
		return n;
	}
	void up(int n) {
		sz[n] = sz[lch[n]] + cnt[n] + sz[rch[n]];
	}
	int left_rotate(int n) {
		int r = rch[n];
		rch[n] = lch[r];
		lch[r] = n;
		up(n);
		up(r);
		return r;
	}
	int right_rotate(int n) {
		int l = lch[n];
		lch[n] = rch[l];
		rch[l] = n;
		up(n);
		up(l);
		return l;
	}
	int insert(int n, int k) {
		if (n == nil) return make_node(k);
		if (key[n] < k) {
			rch[n] = insert(rch[n], k);
			if (prio[rch[n]] > prio[n]) n = left_rotate(n);
		}
		else if (key[n] == k) {
			cnt[n]++;
		}
		else if (key[n] > k) {
			lch[n] = insert(lch[n], k);
			if (prio[lch[n]] > prio[n]) n = right_rotate(n);
		}
		up(n);
		return n;
	}
	int erase(int n, int k) {
		if (n == nil) return nil;
		if (key[n] < k)
			rch[n] = erase(rch[n], k);
		else if (key[n] > k)
			lch[n] = erase(lch[n], k);
		else if (key[n] == k and cnt[n] > 1)
			cnt[n]--;
		else if (key[n] == k and cnt[n] == 1)
		{
			if (not lch[n] and not rch[n]) return nil;
			else if (not lch[n] and rch[n]) return rch[n];
			else if (lch[n] and not rch[n]) return lch[n];
			else
			{
				if (prio[lch[n]] > prio[rch[n]]) {
					n = right_rotate(n);
					rch[n] = erase(rch[n], k);
				} else {
					n = left_rotate(n);
					lch[n] = erase(lch[n], k);
				}
			}
		}
		up(n);
		return n;
	}
	int find_by_order(int n, int i) {
		if (i < sz[lch[n]]) return find_by_order(lch[n], i);
		else if (i < sz[lch[n]] + cnt[n]) return key[n];
		else return find_by_order(rch[n], i - sz[lch[n]] - cnt[n]);
	}
	int order_of_key(int n, int k) {
		if (n == nil) return 0;
		if (k < key[n]) return order_of_key(lch[n], k);
		else if (k == key[n]) return sz[lch[n]];
		else return sz[lch[n]] + cnt[n] + order_of_key(rch[n], k);
	}
	int upper_bound(int n, int k) {
		if (n == nil) return 1e9;
		if (k < key[n]) return min(key[n], upper_bound(lch[n], k));
		else return upper_bound(rch[n], k);
	}
	int pre_lower_bound(int n, int k) {
		if (n == nil) return -1e9;
		if (k > key[n]) return max(key[n], pre_lower_bound(rch[n], k));
		else return pre_lower_bound(lch[n], k);
	}
public:
	void insert(int k) { head = insert(head, k); }
	void erase(int k) { head = erase(head, k); }
	int find_by_order(int i) { return find_by_order(head, i); }
	int order_of_key(int k) { return order_of_key(head, k); }
	int upper_bound(int k) { return upper_bound(head, k); }
	int pre_lower_bound(int k) { return pre_lower_bound(head, k); }
} s;