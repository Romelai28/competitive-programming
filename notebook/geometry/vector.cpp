struct vec {
	coordinate_t x, y;
	vec(coordinate_t _x, coordinate_t _y) : x(_x), y(_y) {}
};
 
vec toVec(const Point &a, const Point &b) {  // convert 2 points
	return vec(b.x-a.x, b.y-a.y);            // to vector a->b
}
 
vec scale(const vec &v, double s) {
	return vec(v.x*s, v.y*s);  // return a new vec
}
 
Point translate(const Point &p, const vec &v) {  // translate p
	return Point(p.x+v.x, p.y+v.y);              // according to v
}												 // return a new point
 
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }
 
// returns true if point r is on the left side of line pq
bool ccw(Point p, Point q, Point r) {
	return cross(toVec(p, q), toVec(p, r)) > 0;
}

// returns true if point r is on the same line as the line pq
bool collinear(Point p, Point q, Point r) {
	return cross(toVec(p, q), toVec(p, r)) == 0;
}

ld angle(const Point a, const Point o, const Point b) {
	vec oa = toVec(o, a), ob = toVec(o, b);
	// a != o != b
	return acos(dot(oa, ob) / sqrt(norma_cuadrado(oa) * norma_cuadrado(ob)));
}