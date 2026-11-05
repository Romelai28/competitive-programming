int cur[MAXN], nxt[MAXN];
void perturbate() {
	int op = rnd_int(0, 2);
	if (op == 0) {
		int i = rnd_int(1, K), j = rnd_int(1, K);
		swap(nxt[i], nxt[j]);
	} else if (op == 1) {
		int i = rnd_int(1, K), j = rnd_int(1, K);
		if (i > j) swap(i, j);
		int x = nxt[i];
		for (int k = i; k < j; ++k) nxt[k] = nxt[k + 1];
		nxt[j] = x;
	} else {
		int i = rnd_int(1, K), j = rnd_int(1, K);
		if (i > j) swap(i, j);
		reverse(nxt + i, nxt + j + 1);
	}
}
auto start = chrono::steady_clock::now();
double elapsed() {
	return chrono::duration<double>(chrono::steady_clock::now() - start).count();
}
double T0 = 1e4;
double T_end = 0.01;
double alpha = 0.9995;
while (elapsed() < TIME_LIMIT) {
	double T = T0;
	for1(i, K) cur[i] = i;
	shuffle(cur + 1, cur + K + 1, rng);
	int cur_val = evaluate(cur);
	while (T > T_end) {
		if (elapsed() > TIME_LIMIT) break;
		for1(i, K) nxt[i] = cur[i];
		perturbate();
		int nxt_val = evaluate(nxt);
		int delta = cur_val - nxt_val;
		if (delta <= 0 or uniform_real_distribution<>(0, 1)(rng) < exp(-(double)delta / T)) {
			for1(i, K) cur[i] = nxt[i];
			cur_val = nxt_val;
		}
		T *= alpha;
	}
}   // Keen on Order solution