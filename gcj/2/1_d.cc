#include <math.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


#ifndef DEBUG
#define DEBUG 0
#endif
#define d_printf if (DEBUG) printf
#define d_print_p if (DEBUG) print_p

int main(int argc, char** argv) {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    int max = 0;
    int d; scanf("%d", &d);
    double sum = 0;
    for (int j = 0; j < d; j++) {
      int v;
      scanf("%d", &v);
      sum += v;
      max = std::max(max, v);
    }

    int min_index = -d + 1;
    double d_point = sum/(d+min_index) + min_index;
    for (int k = min_index + 1; ; k++) {
      double n_d_point = sum/(d+k) + k;
      d_printf("[%d, %lf]\n", k, n_d_point);
      if (d_point >= n_d_point) {
        d_point = n_d_point;
        min_index = k;
      } else
        break;
    }
    if (min_index > 0)
      min_index = 0;
    #if 0
    //double d_point = sum / d;
    //double d_point = std::numeric_limits<double>::max();
    int new_d = 1;
    while (1) {
      double n_d_point = sum/(d+new_d) + new_d;
      new_d ++;
      if (n_d_point < d_point)
        d_point = n_d_point;
      else
        break;
    }
    #endif
    d_printf ("min_index=%d\n", min_index);
    printf ("Case #%d: %d\n", i, (int)std::ceil(d_point - min_index));
  }
  return 0;
}
