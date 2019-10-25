/*==============================================================================
  Automatic Differentiation
==============================================================================*/

#ifndef __AUTODIFF_H__
#define __AUTODIFF_H__
typedef struct {
  double v;
  double dv;
} adv;
typedef struct {
  adv **vl;
  unsigned int len;
} advl;
adv advar(double a);
adv adconst(double a);
void setadv(adv *a, double v, double dv);
advl setadvl(unsigned int n, ...);
void adselect(adv *x, advl vl);
adv adadd(adv a, adv b); // a + b
adv adsub(adv a, adv b); // a - b
adv admul(adv a, adv b); // a * b
adv addiv(adv a, adv b); // a / b
adv adpow(adv a, double b);
adv adexp(adv a);
adv adlog(adv a);
adv adsin(adv a);
adv adcos(adv a);
adv adsum(unsigned int n, ...);
#endif
