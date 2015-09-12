#include <stdio.h>
#include<stdint.h>
#include <inttypes.h>
int print_uint128(uint64_t first, uint64_t second) {
  printf("first=%"SCNx64" second=%"SCNx64"\n", first, second);
  // AB * A'B'
  //  AB*B'
  // AB*A'

  // split into 32 * 32 x 32 * 32
  const uint64_t c_factor = 10 * 10 * 10 * 10 * 10 * 10 * 10 * 10;
  uint64_t left8_1 = first / c_factor;
  uint64_t right8_1 = first % c_factor;
  uint64_t left8_2 = second / c_factor;
  uint64_t right8_2 = second % c_factor;
  uint64_t res0 = (right8_1 * right8_2)%c_factor;
  uint64_t res1 = (left8_1 * right8_2) + (left8_2 * right8_1) + ((right8_1 * right8_2)/c_factor)*c_factor + ((left8_1 *
  left8_2)%c_factor)*c_factor;
  uint64_t res3 = (left8_1 * left8_2)/c_factor;
  printf("%llu|",res3);
  printf("%llu|",res1);
  printf("%llu\n",res0);
}
int main(int argc, char** argv) {
  int n, n1 = 0;
  scanf("%d",&n);
  if (n > 50) {
    n1 = n - 50;
    n -= n1;
  }
  uint64_t first = (uint64_t)1 << n;
  uint64_t second = (uint64_t)1 << n1;
  print_uint128(first, second);
  return 0;
}
