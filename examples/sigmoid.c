#include "../autodiff.h"
#include <stdio.h>

#define N 100
#define XMIN -10.0
#define XMAX 10.0

// sigmoid function
// a: gain
adv sigmoid(adv a, adv x) {
  return addiv(adconst(1.0),
               adadd(adconst(1.0),
                     adexp(adsub(adconst(0.0), admul(a, x))))); // 1/(1+e^(-ax))
}

int main(void) {
  adv a, x, y;
  double h = (XMAX - XMIN) / N;
  a = adconst(1.0);
  for (int i = 0; i <= N; i++) {
    setadv(&x, XMIN + i * h, 1.0);
    y = sigmoid(a, x);
    printf("%f %f %f\n", x.v, y.v, y.dv);
  }
  return 0;
}
