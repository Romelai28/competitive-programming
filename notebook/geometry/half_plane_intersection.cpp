struct Halfplane {  // Usar ld.
	Point p, pq; // 'p' is a passing point of the line and 'pq' is the direction vector of the line.
	long double angle;
	Halfplane() {}
	Halfplane(const Point& a, const Point& b) : p(a), pq(b - a) {
		angle = atan2l(pq.y, pq.x);    
	}
	// Every half-plane allows the region to the LEFT of its line.
	bool out(const Point& r) { return cross(pq, r - p) < -eps; }
	bool operator < (const Halfplane& e) const { return angle < e.angle;}
	friend Point inter(const Halfplane& s, const Halfplane& t) {
		long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
		return s.p + (s.pq * alpha);
	}
};
vector<Point> hp_intersect(vector<Halfplane>& H) { 
	Point box[4] = {Point(inf, inf), Point(-inf, inf), Point(-inf, -inf), Point(inf, -inf)};
	forn(i, 4){
		Halfplane aux(box[i], box[(i+1) % 4]);
		H.pb(aux);
	}
	sort(H.begin(), H.end());
	deque<Halfplane> dq;
	int len = 0;
	for(int i = 0; i < int(H.size()); i++) {
		while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
			dq.pop_back();
			--len;
		}
		while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
			dq.pop_front();
			--len;
		}
		if (len > 0 && fabsl(cross(H[i].pq, dq[len-1].pq)) < eps) {
			if (dot(H[i].pq, dq[len-1].pq) < 0.0)
				return vector<Point>();
			if (H[i].out(dq[len-1].p)) {
				dq.pop_back();
				--len;
			}
			else continue;
		}
		dq.pb(H[i]);
		++len;
	}
	while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
		dq.pop_back(); --len;
	}
	while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
		dq.pop_front(); --len;
	}
	if (len < 3) return vector<Point>();
	vector<Point> ret(len);
	for(int i = 0; i+1 < len; i++) {
		ret[i] = inter(dq[i], dq[i+1]);
	}
	ret.back() = inter(dq[len-1], dq[0]);
	return ret;
}