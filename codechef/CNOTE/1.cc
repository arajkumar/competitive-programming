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


} // namespace

int main(int argc, char **argv) {
  const size_t t = scan_d();
  for (size_t i = 0; i < t; i++) {
    const size_t x = scan_d(), y = scan_d(), k = scan_d(), n = scan_d();
    const size_t pages_needed = x - y;
    bool is_chef_lucky = false;
    for (size_t j = 0; j < n; j++) {
      const size_t p = scan_d(), c = scan_d();
      if (p >= pages_needed && c <= k) {
        is_chef_lucky = true;
        break;
      }
    }
    printf("%s\n", is_chef_lucky ? "LuckyChef" : "UnluckyChef");
  }
  return 0;
}
