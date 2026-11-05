// 0: [0, 180) 1: [180, 360)
int half(Point p) {return (p.y > 0 || (p.y == 0 && p.x > 0)) ? 0 : 1;}
bool angleCmp(Point a, Point b) {  // CCW.
	int ha = half(a), hb = half(b);
	if (ha != hb) return ha < hb;
	ll c = a ^ b;  // Cross product > 0 significa 'a' va antes que 'b'
	if (c != 0) return c > 0;
	return a.dist2() < b.dist2(); // Opcional: Desempate si son colineales
}
void polar_sort(vector<Point>& pts, Point o = {0, 0}) {
	sort(pts.begin(), pts.end(), [o](Point a, Point b) {
		return angleCmp(a - o, b - o);
	});
}