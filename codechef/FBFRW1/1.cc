#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits>
#include <math.h>
#include <algorithm>
#include <cmath>
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector

namespace {
#define gc getchar_unlocked
#define pc putchar_unlocked

// TODO(arunprasadr): Support fast version of scan and print for
// all other types using templates.
int scan_d() {int ip=gc(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=gc())if(ip=='-'){flag=-1;ip=gc();break;}for(;ip>='0'&&ip<='9';ip=gc())ret=ret*10+ip-'0';return flag*ret;}
 
void print_d(int n) {if(n<0){n=-n;pc('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{pc ( output_buffer [ i ] ) ; } while ( ++i< 10 ) ; pc(' ');}

#define printf if (0) printf

} // namespace

int main(int argc, char **argv) {
  const size_t n = scan_d(), m = scan_d();
  const size_t n_th_small = n - m;
  std::vector<size_t> speed_list;
  for (size_t i = 0; i < n; i++) {
    speed_list.push_back(scan_d());
  }
  std::sort(speed_list.begin(), speed_list.end());
  print_d(speed_list[n_th_small]);
}
