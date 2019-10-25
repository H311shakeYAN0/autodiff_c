#include <stdio.h>
#include <math.h>
#include "../autodiff.h"

#define N 100
#define XMIN -10.0
#define XMAX 10.0

// sigmoid function
// a: gain
adv sigmoid(adv a, adv x) {
    return addiv(advar(1), adadd(advar(1), adexp(adsub(advar(0), admul(a, x))))); // 1/(1+e^(-ax))
}

int main(void) {
    adv a, x, y;
    advl vl;
    double h = (XMAX-XMIN)/N;
    a = advar(1.0);
    vl = setadvl(2, &a, &x);
    for (int i=0; i<=N; i++) {
        x = advar(XMIN+i*h);
        adselect(&x, vl);
        y = sigmoid(a, x);
        printf("%f %f %f\n", x.v, y.v, y.dv);
    }
    return 0;
}
