#include "autodiff.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

adv advar(double a) {
  adv x = {a, 1.0};
  return x;
}

adv adconst(double a) {
  adv x = {a, 0.0};
  return x;
}

void setadv(adv *a, double v, double dv) {
  (*a).v = v;
  (*a).dv = dv;
}

advl setadvl(unsigned int n, ...) {
  va_list arglist;
  unsigned int i;
  adv **vl = (adv **)malloc(n * sizeof(adv *));
  vl[0] = (adv *)malloc(n * sizeof(adv *));
  for (i = 1; i < n; ++i) {
    vl[i] = vl[0] + i;
  }
  va_start(arglist, n);
  for (i = 0; i < n; ++i) {
    vl[i] = va_arg(arglist, adv *);
  }
  va_end(arglist);
  advl advl = {vl, n};
  return advl;
}

void adselect(adv *x, advl vl) {
  unsigned int i;
  for (i = 0; i < vl.len; ++i) {
    vl.vl[i]->dv = 0.0;
  }
  (*x).dv = 1.0;
}

adv adadd(adv a, adv b) {
  adv x;
  x.v = a.v + b.v;
  x.dv = a.dv + b.dv;
  return x;
}

adv adsub(adv a, adv b) {
  adv x;
  x.v = a.v - b.v;
  x.dv = a.dv - b.dv;
  return x;
}

adv admul(adv a, adv b) {
  adv x;
  x.v = a.v * b.v;
  x.dv = a.dv * b.v + a.v * b.dv;
  return x;
}

adv addiv(adv a, adv b) {
  adv x;
  x.v = a.v / b.v;
  x.dv = (a.dv * b.v - a.v * b.dv) / (b.v * b.v);
  return x;
}

adv adpow(adv a, double b) {
  adv x;
  x.v = pow(a.v, b);
  x.dv = b * pow(a.v, b - 1.0) * a.dv;
  return x;
}

adv adexp(adv a) {
  adv x;
  x.v = exp(a.v);
  x.dv = a.dv * exp(a.v);
  return x;
}

adv adlog(adv a) {
  adv x;
  x.v = log(a.v);
  x.dv = a.dv / a.v;
  return x;
}

adv adsin(adv a) {
  adv x;
  x.v = sin(a.v);
  x.dv = cos(a.v) * a.dv;
  return x;
}

adv adcos(adv a) {
  adv x;
  x.v = cos(a.v);
  x.dv = -sin(a.v) * a.dv;
  return x;
}

adv adsum(unsigned int n, ...) {
  va_list arglist;
  unsigned int i;
  adv x = {0.0, 0.0}, temp;

  va_start(arglist, n);
  for (i = 0; i < n; ++i) {
    temp = va_arg(arglist, adv);
    x.v += temp.v;
    x.dv += temp.dv;
  }
  va_end(arglist);
  return x;
}
