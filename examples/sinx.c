#include <stdio.h>
#include <math.h>
#include "../autodiff.h"

#define N 100
#define XMIN -M_PI
#define XMAX M_PI

int main(void) {
    adv x, y;
    double h = (XMAX-XMIN)/N;
    for (int i=0; i<=N; i++) {
        x=advar(XMIN+i*h);
        x.dv=1.0;
        y = adsin(x);
        printf("%f %f %f\n",x.v, y.v, y.dv);
    }
    return 0;
}
