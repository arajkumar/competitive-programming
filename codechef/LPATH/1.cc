#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits>
#include <math.h>
#include <algorithm>
#include <cmath>

namespace {
#define gc getchar_unlocked
#define pc putchar_unlocked

// TODO(arunprasadr): Support fast version of scan and print for
// all other types using templates.
int scan_d() {int ip=gc(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=gc())if(ip=='-'){flag=-1;ip=gc();break;}for(;ip>='0'&&ip<='9';ip=gc())ret=ret*10+ip-'0';return flag*ret;}
 
void print_d(int n) {if(n<0){n=-n;pc('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc ( output_buffer [ i ] ) ; } while ( ++i< 10 ) ; pc(' ');}

#define printf if (0) printf

size_t grid[201][201];
size_t rc, cc;

size_t find(long r, long c, size_t n) {
  if ( r < 0 || c < 0 || r >= rc || c >= cc) {
    printf("return r=%ld c=%ld n=%ld\n", r, c, n);
    return 0;
  }
  printf("find r=%ld c=%ld n=%ld gr=%ld\n", r, c, n, grid[r][c]);
  if (grid[r][c] != n)
    return n;

  size_t res_max = 1;
  // r-1,c-1
  res_max = std::max(res_max, find(r - 1, c - 1, n + 1));
  // r-1,c
  res_max = std::max(res_max, find(r - 1, c, n + 1));
  // r-1,c+1
  res_max = std::max(res_max, find(r - 1, c + 1, n + 1));
  // r, c+1
  res_max = std::max(res_max, find(r, c + 1, n + 1));
  // r, c-1
  res_max = std::max(res_max, find(r, c - 1, n + 1));
  // r+1,c-1
  res_max = std::max(res_max, find(r + 1, c - 1, n + 1));
  // r+1,c
  res_max = std::max(res_max, find(r + 1, c, n + 1));
  // r+1, c+1
  res_max = std::max(res_max, find(r + 1, c + 1, n + 1));

  printf("res_max=%ld\n", res_max);
  return res_max;
}

} // namespace

int main(int argc, char **argv) {
  const size_t t = scan_d();
  for (size_t i = 0; i < t; i++) {
    rc = scan_d();
    cc = scan_d();
    for (size_t r = 0; r < rc; r++) {
      for (size_t c = 0; c < cc; c++) {
        grid[r][c] = scan_d();
      }
    }
    size_t max_number = 0;
    for (size_t r = 0; r < rc; r++) {
      for (size_t c = 0; c < cc; c++) {
        if (grid[r][c] == 0) {
          printf("r=%lu, c=%lu\n", r, c);
          max_number = std::max(max_number, find(r,c,0));
        }
      }
    }
    print_d(max_number);
  }
  return 0;
}
