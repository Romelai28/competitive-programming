Point Dykstra(Point x) {    // proyecta x a la interseccion de n figuras convexas
    vector<Point> p(n + 1, Point{0, 0});
    while (elapsed() < TIME_LIMIT) {    // n=500 con 2000 iteraciones andaba
        for1(i, n) {
            Point y = x + p[i];
            x = project(y, i);
            p[i] = y - x;
        }
    }
    return x;
} // O(iteraciones * cantidad de figuras * costo de una proyeccion)