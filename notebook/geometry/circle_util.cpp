// https://github.com/ShahjalalShohag/code-library/tree/b1d164f9fc6e9a0896370cebf43793043ee30e7b/Geometry
int sign(double x) { return (x > eps) - (x < -eps); }
vector<Point> circle_line_intersection(Point c, double r, Point a, Point b) {
	vector<Point> ret;
	b = b - a; a = a - c;
	double A = dot(b, b), B = dot(a, b);
	double C = dot(a, a) - r * r, D = B * B - A * C;
	if (D < -eps) return ret;
	ret.push_back(c + a + b * (-B + sqrt(D + eps)) / A);
	if (D > eps) ret.push_back(c + a + b * (-B - sqrt(D)) / A);
	return ret;
}
vector<Point> circle_circle_intersection(Point a, double r, Point b, double R) {
	if (a == b && sign(r - R) == 0) return {Point(1e18, 1e18)};
	vector<Point> ret;
	double d = sqrt(dist2(a,  b));
	if (d > r + R || d + min(r,  R) < max(r,  R)) return ret;
	double x = (d * d - R * R + r * r) / (2 * d);
	double y = sqrt(r * r - x * x);
	Point v = (b - a) / d;
	ret.push_back(a + v * x  +  rotateccw90(v) * y);
	if (y > 0) ret.push_back(a + v * x - rotateccw90(v) * y);
	return ret;
}