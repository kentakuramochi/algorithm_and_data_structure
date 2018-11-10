#include <stdio.h>
#include <float.h>

void roundError(void)
{
    float f1, f2;
    f1 = 0.1f;
    f2 = 0.100000001f;
    printf("f1=%20.18f\nf2=%20.18f\n", f1, f2);
}

void roundError2(void)
{
    double d1, d2;
    d1 = 0.1;
    d2 = 0.100000001;
    printf("d1=%20.18f\nd2=%20.18f\n", d1, d2);
}

void cancellationError(void)
{
    float f1, f2;
    f1 = 1.0000101f;
    f2 = 1.0000100f;
    printf("%15.13f + %15.13f = %15.13f\n", f1, f2, (f1 + f2));
    printf("%15.13f - %15.13f = %15.13f\n", f1, f2, (f1 - f2));
}

void lossOfTrailingDigit(void)
{
    unsigned int n;
    float f1, f2;
    f1 = 10000000.0f;
    f2 = 0.0000001f;

    for (n = 0; n < 1000000; n++) {
        f1 += f2;
    }

    printf("%f\n", f1);
}

int main(void)
{
    roundError();
    roundError2();
    cancellationError();
    lossOfTrailingDigit();

    // machine epsilon
    printf("FLT_EPSILON=%e\n", FLT_EPSILON);
    printf("DBL_EPSILON=%e\n", DBL_EPSILON);

    return 0;
}
