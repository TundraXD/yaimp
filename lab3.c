#include <stdio.h>
#include <math.h>

double U(double x, double y)
{
    if (x / (y * y) < 1.0) {
        double a = cos(x * x * x - sqrt(y));
        double b = cbrt(x * y * y);
        return (a > b) ? a : b;          
    } else {
        return log(y * y - x);           
    }
}

int main(void)
{
    const double x0 = 1.0, x1 = 2.0, hx = 0.3;
    const double y0 = 2.0, y1 = 2.5, hy = 0.5;
    const double eps = 1e-9;             
    double product = 1.0;
    int count = 0;

    printf("%8s %8s %12s\n", "x", "y", "U");
    printf("-----------------------------\n");

    for (int i = 0; x0 + i * hx <= x1 + eps; i++) {
        double x = x0 + i * hx;
        for (int j = 0; y0 + j * hy <= y1 + eps; j++) {
            double y = y0 + j * hy;
            double u = U(x, y);
            printf("%8.2f %8.2f %12.6f\n", x, y, u);
            product *= u;
            count++;
        }
    }

    printf("\nВычислено значений: %d\n", count);
    printf("Произведение значений U: %.6f\n", product);

    return 0;
}
