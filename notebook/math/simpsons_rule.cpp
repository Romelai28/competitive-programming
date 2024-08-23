typedef double Funcion(double);
double integrar(Funcion *f, double a,double b, int n)
{
    double h = (b-a)/(double)(n);
    double res = 0.0;
    double x0 = a;
    double fx0 = f(x0);
    const double h2 = h/2.0;
    forn(i,n) {
        double fx0h = f(x0+h);
        res += fx0 + fx0h + 4.0 * f(x0+h2);
        x0 += h;
        fx0 = fx0h;
    }
    return res * h / 6.0;
}
