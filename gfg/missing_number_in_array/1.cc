#include <stdio.h>
#include <stdlib.h>
static size_t test_case()
{
  size_t N;
  scanf("%lu", &N);
  size_t sum {};
  for (auto i = 0; i < N - 1; i++) {
    size_t n;
    scanf("%lu", &n);
    sum += n;
  }
  const size_t EXPECTED_SUM = (N * (N + 1) / 2 );
  // printf("EX-SU %lu SU %lu\n", EXPECTED_SUM, sum);
  return EXPECTED_SUM - sum;
}

int main()
{
    size_t T;
    scanf("%lu", &T);
    for (auto t = 0; t < T; t++)
        printf("%lu\n", test_case());

    return 0;
}
