struct polar_cmp {
	punto o, v;
	cmp(Point no, Point nv) : o(no), v(nv) {}
	bool half(pto p) {
		assert(!(p.x == 0 && p.y == 0)); // (0,0) isn't well defined
		return (v ^ p) < 0 || ((v ^ p) == 0 && (v * p) < 0);
	}
	bool operator()(Point &p1, Point &p2) {
		return mp(half(p1 - o), 0) < mp(half(p2 - o), ((p1 - o) ^ (p2 - o)))
	}
};