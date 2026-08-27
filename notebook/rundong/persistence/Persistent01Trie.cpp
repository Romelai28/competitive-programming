const int MAXN = 3e5 + 10;
const int N = MAXN * 25 * 2;

int children[N][2];
int pass[N];
const int nil = 0;
int c1 = 1;
int root_of_version[2 * MAXN];
int c2 = 1;

const int B = 25;
class PersistentTrie
{
	int clone(int n) {
		int i = c1++;
		children[i][0] = children[n][0];
		children[i][1] = children[n][1];
		pass[i] = pass[n];
		return i;
	}
	int make_node() { return clone(nil); }
	bool has_child(int n, bool x) {
		return children[n][x] != nil;
	}
	int get_child(int n, bool x) {
		return children[n][x] = clone(children[n][x]);
	}
public:
	void insert(int a) {
		int n = clone(root_of_version[c2 - 1]);
		root_of_version[c2++] = n;
		for (int i = B; i >= 0; --i)
		{
			n = get_child(n, (a >> i) & 1);
			pass[n]++;
		}
	}
	int query(int l, int r, int x) {
		int n1 = root_of_version[l - 1],
			n2 = root_of_version[r];
		int ans = 0;
		for (int i = B; i >= 0; --i)
		{
			int bit = (x >> i) & 1;
			int tgt = not bit;
			if (pass[children[n2][tgt]] - pass[children[n1][tgt]] > 0) {
				ans |= (tgt << i);
				n2 = children[n2][tgt];
				n1 = children[n1][tgt];
			} else {
				ans |= (bit << i);
				n2 = children[n2][bit],
				n1 = children[n1][bit];
			}
		}
		return ans;
	}
};