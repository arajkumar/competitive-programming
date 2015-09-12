#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits>
#include <math.h>
#include <algorithm>
#include <cmath>
#include <map>

namespace {
#define gc getchar_unlocked
#define pc putchar_unlocked

// TODO(arunprasadr): Support fast version of scan and print for
// all other types using templates.
int scan_d() {int ip=gc(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=gc())if(ip=='-'){flag=-1;ip=gc();break;}for(;ip>='0'&&ip<='9';ip=gc())ret=ret*10+ip-'0';return flag*ret;}
 
void print_d(int n) {if(n<0){n=-n;pc('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc ( output_buffer [ i ] ) ; } while ( ++i< 10 ) ; pc(' ');}

#define printf if (0) printf
size_t pow_t[20][20];
inline size_t is_arm_weak(size_t n) {
  size_t power = 1;
  size_t sum = 0;
  while (n) {
    const size_t digit = n % 10;
    size_t& pow = pow_t[digit][power];
    if (!pow && digit) {
      pow = std::pow(digit, power);
      // std::cout << "not cached:" << digit << ", " << power << "\n";
    }
    sum += pow; 
    power++;
    n /= 10;
  }
  return sum % 7;
}
#if 0
  static std::map<size_t, size_t> d;
  if (d[n])
    return d[n];
  if (n < 7 ) return 0;
  if (n == 7) return 1;
  size_t count = is_arm_weak(n) + arm_weak_count(n-1);
  d[n] = count;
  return count;
#endif
size_t arm_weak_count(long n) {
  size_t count = 0;
  while (n > 0) {
    size_t mod7 = is_arm_weak(n);
    if (!mod7)
      count ++;
    mod7 = mod7 ? mod7 : 1;
    n -= mod7;
    // std::cout << "n:" << n << "\n";
  }
  return count;
}
} // namespace

int main(int argc, char **argv) {
  const size_t t = scan_d();
  for(size_t i = 0; i < t; i++) {
    print_d(arm_weak_count(scan_d()));
  }
  return 0;
}
