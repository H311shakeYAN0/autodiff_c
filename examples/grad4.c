#include "../autodiff.h"
#include <stdio.h>
#include <stdlib.h>

#define Q1 1.0
#define Q1X 1.0
#define Q1Y 1.0

#define Q2 -1.0
#define Q2X -1.0
#define Q2Y 1.0

#define Q3 1.0
#define Q3X -1.0
#define Q3Y -1.0

#define Q4 -1.0
#define Q4X 1.0
#define Q4Y -1.0

#define N 50
#define XMIN -5.0
#define XMAX 5.0
#define YMIN -5.0
#define YMAX 5.0

//#define PLT_CONTOUR
//#define PLT_CONTOUR_N 30
#define PLT_COLOR // splotでは使えない.

adv phi(adv x, adv y);
void grad2d(adv (*funcpt)(adv, adv), advl vl, double result[2]);
void plotscript(char *data);

int main(void) {
  adv x, y, z;
  advl vl;
  double hx, hy;
  double gradient[2];
  FILE *fp;
  fp = fopen("grad4.dat", "w+");
  vl = setadvl(2, &x, &y);
  hx = (XMAX - XMIN) / N;
  hy = (YMAX - YMIN) / N;
  for (int i = 0; i <= N; i++) {
    x = advar(XMIN + i * hx);
    for (int j = 0; j <= N; j++) {
      y = advar(YMIN + j * hy);
      z = phi(x, y);
      grad2d(phi, vl, gradient);
      fprintf(fp, "%f %f %f %f %f\n", x.v, y.v, z.v, -gradient[0],
              -gradient[1]);
    }
    fputc('\n', fp);
  }
  fclose(fp);
  plotscript("grad4.dat");
  return 0;
}

adv phi(adv x, adv y) {
  return adsum(
      4,
      admul(adconst(Q1), adpow(adadd(adpow(adsub(x, adconst(Q1X)), 2.0),
                                     adpow(adsub(y, adconst(Q1Y)), 2.0)),
                               -0.5)),
      admul(adconst(Q2), adpow(adadd(adpow(adsub(x, adconst(Q2X)), 2.0),
                                     adpow(adsub(y, adconst(Q2Y)), 2.0)),
                               -0.5)),
      admul(adconst(Q3), adpow(adadd(adpow(adsub(x, adconst(Q3X)), 2.0),
                                     adpow(adsub(y, adconst(Q3Y)), 2.0)),
                               -0.5)),
      admul(adconst(Q4), adpow(adadd(adpow(adsub(x, adconst(Q4X)), 2.0),
                                     adpow(adsub(y, adconst(Q4Y)), 2.0)),
                               -0.5)));
}

void grad2d(adv (*funcpt)(adv, adv), advl vl, double result[2]) {
  adselect(vl.vl[0], vl);
  result[0] = funcpt(*vl.vl[0], *vl.vl[1]).dv;
  adselect(vl.vl[1], vl);
  result[1] = funcpt(*vl.vl[0], *vl.vl[1]).dv;
}

void plotscript(char *data) {
  FILE *plt;
  plt = fopen("grad4.gp", "w+");

  fprintf(plt, "set xrange [%f:%f]\n", XMIN * 1.1, XMAX * 1.1);
  fprintf(plt, "set yrange [%f:%f]\n", YMIN * 1.1, YMAX * 1.1);
#ifdef PLT_CONTOUR
  fputs("set view equal xyz\n", plt);
  fputs("set contour\n", plt);
  fputs("unset surface\n", plt);
  fputs("set view 0, 0\n", plt);
  fputs("set cntrparam levels auto ", plt);
#ifdef PLT_CONTOUR_N
  fprintf(plt, "%d\n", PLT_CONTOUR_N);
#else
  fputc('\n', plt);
#endif
  fprintf(plt, "splot \"%s\" u 1:2:3 w l\n", data);
  fprintf(plt,
          "replot \"%s\" u "
          "1:2:3:($4/sqrt($4*$4+$5*$5)*0.1):($5/sqrt($4*$4+$5*$5)*0.1):(0) w "
          "vector ti \"\"\n",
          data);
#else
  fputs("set size ratio -1\n", plt);
#ifdef PLT_COLOR
  fprintf(plt,
          "plot \"%s\" u "
          "1:2:($4/sqrt($4*$4+$5*$5)*0.1):($5/"
          "sqrt($4*$4+$5*$5)*0.1):(log10(sqrt($4*$4+$5*$5))) w vector lc "
          "palette ti \"\"\n",
          data);
#else
  fprintf(plt,
          "plot \"%s\" u "
          "1:2:($4/sqrt($4*$4+$5*$5)*0.1):($5/sqrt($4*$4+$5*$5)*0.1) "
          "w vector ti \"\"\n",
          data);
#endif
#endif
  fclose(plt);
}
