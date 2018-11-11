#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// equation
// x^5 - 10x^4 + 25x^3 + 40x^2 +200x -500 = 0
double f(double x)
{
    return pow(x, 5)
           - 10.0 * pow(x, 4)
           + 25.0 * pow(x, 3)
           + 40.0 * pow(x, 2)
           + 200.0 * x
           - 500;
}

// bisection method
// search resolution with binary search
double bisection_method(double(*f)(double),
        double left, double right, double epsilon)
{
    double mid;

    while ((fabs(right - left) > epsilon) &&
           (fabs(f(left)) > epsilon)) {
        mid = (left + right) / 2.0;

        // if f(left) and f(right) has same signature
        if (f(left) * f(mid) >= 0.0) {
            left = mid;
        } else {
            right = mid;
        }
    }

    return left;
}

int main(void)
{
    double x = bisection_method(f, 1.0, 3.0, 0.00001);

    printf("x=%f\nf(%f)=%f\n", x, x, f(x));

    return EXIT_SUCCESS;
}
