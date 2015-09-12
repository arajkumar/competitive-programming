#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


struct max_info {
  int max;
  int max_count;
  int second_max;
};

static inline max_info find_max(const std::vector<int>& p) {
  max_info info = {0};
  for(const auto& i : p) {
    if (i < info.max && i > info.second_max) {
      info.second_max = i;
    } else if (i >= info.max) {
      if (info.max != i) {
        info.second_max = info.max;
        info.max = i;
        info.max_count = 0;
      }
      info.max_count ++;
    }
  }
  if (info.second_max == 0)
    info.second_max = info.max;
  return info;
}

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
    int max_time = 0;
    int d; scanf("%d", &d);
    std::vector<int> p;
    for (int j = 0; j < d; j++) {
      int v;
      scanf("%d", &v);
      p.push_back(v);
    }

    auto info = find_max(p);
    d_printf("max=%d max_count=%d second_max=%d\n",info.max, info.max_count, info.second_max);
    int mins_spent = 0;
    while ((mins_spent + info.max_count + info.second_max) <= info.max) {
      mins_spent += info.max_count;
      for (auto& k : p) {
        if (k == info.max) {
          k -= k / 2;
        }
      }
      for (int z = 0; z < info.max_count; z++)
        p.push_back(info.max / 2);
      info = find_max(p);
      d_printf("max=%d max_count=%d second_max=%d spent=%d\n",info.max, info.max_count, info.second_max, mins_spent);
      d_print_p(p);
    }
    printf ("Case #%d: %d\n", i, mins_spent + info.max);
  }
  return 0;
}
