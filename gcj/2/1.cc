#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void print_p(const std::vector<int>& p) {
  printf("[");
  for (const auto& v : p) {
    printf("%d,", v);
  }
  printf("]\n");
}

#ifndef DEBUG
#define DEBUG 0
#endif
#define d_printf if (DEBUG) printf
#define d_print_p if (DEBUG) print_p

int main(int argc, char** argv) {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    int d; scanf("%d", &d);
    std::vector<int> p;
    int max = 0;
    for (int j = 0; j < d; j++) {
      int v;
      scanf("%d", &v);
      p.push_back(v);
      max = std::max(max, v);
    }

    int mins_spent = 0;
    int max_elem = max;
    int max_index = std::distance(p.begin(), std::max_element(p.begin(), p.end()));
    do {
      mins_spent ++;
      p[max_index] -= max_elem / 2;
      p.push_back(max_elem/2);
      max_index = std::distance(p.begin(), std::max_element(p.begin(), p.end()));
      if (mins_spent + p[max_index] > max_elem)
        break;
      max_elem = p[max_index];
      d_printf("max=%d max_index=%d\n",max_elem, max_index);
      d_print_p(p);
    } while (1);
    printf ("Case #%d: %d\n", i, mins_spent);
  }
  return 0;
}
