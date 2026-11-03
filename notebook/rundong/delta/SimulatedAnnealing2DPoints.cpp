Num cost(Point p) {
    Num ans = 0;
    for1(i, n) {
        Num d = sqrt(dist2(p, {x[i], y[i]}));
        ans = max(ans, d * c[i]);
    }
    return ans;
}
Num best_val = 1e50;
void simulated_annealing() {
    const double T0 = 1e5;
    const double Tend = 1e-10;
    const double alpha = 0.9995;
    while (elapsed() < TIME_LIMIT) {
        double T = T0;
        Point cur = { x[rnd_int(1, n)], y[rnd_int(1, n)] };
        Num cur_val = cost(cur);
        if (cur_val < best_val) best_val = cur_val;
        while (T > Tend) {
            if (elapsed() > TIME_LIMIT) break;
            Num sigma = T;
            Point nxt = { cur.fst + gauss()*sigma,
                          cur.snd + gauss()*sigma };
            Num nxt_val = cost(nxt);
            if (nxt_val < best_val) best_val = nxt_val;
            Num delta = nxt_val - cur_val;
            if (delta <= 0 or rnd(0, 1) < exp(-delta / T)) {
            // if (delta <= 0) {
                cur_val = nxt_val;
                cur = nxt;
            }
            T *= alpha;
        }
    }
    cout << best_val;
}   // Going to the Regional solution