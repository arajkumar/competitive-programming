#include <stdio.h>
#include <algorithm>
#include <array>

typedef unsigned long long u64_t;
typedef signed long long i64_t;

#define gc getchar_unlocked
#define pc putchar_unlocked
template <class T> inline T scan() {
  T ip = gc(), ret = 0, flag = 1;
  for (; ip < '0' || ip > '9'; ip = gc())
    if (ip == '-') {
      flag = -1;
      ip = gc();
      break;
    }
  for (; ip >= '0' && ip <= '9'; ip = gc())
    ret = ret * 10 + ip - '0';
  return flag * ret;
}

template <class T, bool nl = true> inline void print(T n) {
  if (n < 0) {
    n = -n;
    pc('-');
  }
  char output_buffer[32];
  T i = sizeof(output_buffer);
  do {
    output_buffer[--i] = (n % 10) + '0';
    n /= 10;
  } while (n);
  do {
    pc(output_buffer[i]);
  } while (++i < sizeof(output_buffer));
  pc(nl ? '\n' : ' ');
}

int main(int argc, char *argv[]) {
  const u64_t n = scan<u64_t>();
  std::array<u64_t, int(std::pow(10, 5) * 5 + 1)> budgets;
  for (u64_t i = 0; i < n; i++)
    budgets[i] = scan<u64_t>();
  std::sort(budgets.begin(), budgets.begin() + n);
  u64_t good_budget = 0;
  for (u64_t i = 0; i < n; i++)
    good_budget = std::max(good_budget, budgets[i] * (n - i));
  print<u64_t>(good_budget);
  return 0;
}
