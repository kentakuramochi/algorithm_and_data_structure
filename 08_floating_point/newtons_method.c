#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// equation
// x^3 + x + 1 = 0
double f(double x)
{
    return x * x * x + x + 1;
}

// derivative of f(x)
double df(double x)
{
    return 3 * x * x + 1;
}

// newton's method
double newtons_method(double(*f)(double), double(*df)(double),
        double x0, double epsilon, int iteration)
{
    double prev_x, x = x0;

    while ((fabs(x - prev_x) > epsilon) && (iteration > 0)) {
        prev_x = x;
        x = prev_x - f(prev_x) / df(prev_x);
        iteration--;
    }

    return x;
}

int main(void)
{
    double x = newtons_method(f, df, 0.1, 0.000001, 1000);

    printf("x=%f\nf(%f)=%f\n", x, x, f(x));

    return EXIT_SUCCESS;
}
