 struct Point {
	coordinate_t x, y;
	Point(coordinate_t x_ = 0, coordinate_t y_ = 0) : x(x_), y(y_) {}
	
	Point operator+(const Point& o) const { return {x+o.x, y+o.y}; }
	Point operator-(const Point& o) const { return {x-o.x, y-o.y}; }
	coordinate_t operator*(const Point& o) const { return x*o.x + y*o.y; }  // Dot product
	coordinate_t operator^(const Point& o) const { return x*o.y - y*o.x; }  // Cross product
	
	Point proj(Point b) { return b*((*this)*b) / (b*b); }
	ld norm() { return sqrt(x*x + y*y); }
	ld dist(Point b) { return (b - (*this)).norm(); }


	bool operator < (Point other) const {
		if (x != other.x){
			return x < other.x;
		}
		return y < other.y;
	}
};

// Print points.
std::ostream &operator <<(std::ostream &os, const Point&p) {
	return os << "(" << p.x << "," << p.y << ")";
}