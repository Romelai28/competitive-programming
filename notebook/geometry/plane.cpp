struct Plane {
	Point_3d n; coordinate_t d;
	// From normal n and offset d
	Plane(Point_3d n, coordinate_t d) : n(n), d(d) {}
	// From normal n and point P
	Plane(Point_3d n, Point_3d p) : n(n), d(dot(n,p)) {}
	// From three non-collinear points P,Q,R
	Plane(Point_3d p, Point_3d q, Point_3d r) : Plane(cross((q-p), (r-p)), p) {}
	
	// El plano PI divide a R^3 en 2 secciones, dado un punto p, tenemos 3 casos:
	// 1. side(p) es positivo, si p esta en el lado de PI apuntado por el vector normal n.
	// 2. da 0 si p esta en el plano PI.
	// 3. negativo en el otro caso (esta en el lado de PI que no esta siendo apuntado por el vector normal n).
	coordinate_t side(Point_3d p){ return (dot(n,p))-d;}
};